/**
 * File:    adrian_single_wire_arduino.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_SINGLE_WIRE_ARDUINO_HPP_
#define ADRIAN_SINGLE_WIRE_ARDUINO_HPP_

/* ===== Includes ===== */
#include <Arduino.h>
#include "adrian_single_wire.hpp"


namespace adrian
{

    /* ===== Helper Macros ===== */

    /** Write a zero bit to pin 2 */
    inline void zero_bit()
    {
        volatile uint8_t i = 0;
        PORTD &= 0xFB;
        i = 1; i = 2; i = 3; i = 4; i = 5;
        PORTD |= 0x04;
        i = 1;
    }

    /** Write a one bit to pin 2 */
    inline void one_bit()
    {
        volatile uint8_t i = 0;
        PORTD &= 0xFB;
        i = 1;
        PORTD |= 0x04;
        i = 1; i = 2; i = 3; i = 4; i = 5;
    }

    /** Write a stop bit to pin 2 */
    inline void stop_bit()
    {
        volatile uint8_t i = 0;
        PORTD &= 0xFB;
        i = 1; i = 2; i = 3;
        PORTD |= 0x04;
        i = 1; i = 2; i = 3;
    }

    /**
     * SingleWire implementation for Arduino.
     */
    class ArduinoSingleWire : public adrian::SingleWire
    {
    public:
        /* ===== Functions ===== */

        /**
         * Constructor
         * Set defaults for frequency and bit order.
         */
        ArduinoSingleWire() :
            m_data_pin(0),
            m_frequency(MHz),
            m_bit_order(BIT_ORDER_LSB_FIRST)
        {
            // Do nothing
        }

        /**
         * Initialize the interface.
         * Set the data pin to OUTPUT mode.
         */
        virtual void Initialize(const uint32_t data_pin)
        {
            m_data_pin = data_pin;
            pinMode(m_data_pin, OUTPUT);
        }

        /** Release the interface (does nothing). */
        virtual void Release() {}

        /** Set the frequency in Hertz. */
        virtual void SetFrequency(const uint32_t frequency)
        {
            m_frequency = frequency;
            Serial.begin(m_frequency * 4);
        }

        /** Set the bit order (see BitOrder). */
        virtual void SetBitOrder(const BitOrder bit_order)
        {
            m_bit_order = bit_order;
        }

        /** Write bytes over the wire using the Serial interface. */
        virtual uint8_t Write(
            const uint8_t tx_buffer[],
            const uint8_t buffer_size)
        {
            pinMode(2, OUTPUT);
            for (uint8_t bytenum = 0; bytenum < buffer_size; ++bytenum)
            {
                for (uint8_t mask = 1; mask > 0; mask <<= 0)
                {
                    if (tx_buffer[bytenum] & mask) { one_bit(); }
                    else { zero_bit(); }
                }
            }
            stop_bit();
        }

        /** Read bytes over the wire using the Serial interface. */
        virtual uint8_t ReadBlocking(
            uint8_t rx_buffer[],
            const uint8_t buffer_size)
        {
            // Spin waiting for input.
            pinMode(2, INPUT_PULLUP);
            while (PIND & 4);

            volatile uint8_t counter = 0;
            for (uint8_t bytenum = 0; bytenum < buffer_size; ++bytenum)
            {
                for (uint32_t mask = 1; mask > 0; mask <<= 1)
                {
                    counter = 1;    // killing time
                    rx_buffer[bytenum] |= ((PIND & 4) ? mask : 0);
                }
            }
            return 0;
        }

    private:

        /* ===== Private Variables ===== */
        uint32_t m_data_pin;    //< Pin number of data pin
        uint32_t m_frequency;   //< Data transfer rate in Hertz
        BitOrder m_bit_order;   //< Data transfer bit order
    };

}   // end namespace adrian

#endif  // ADRIAN_SINGLE_WIRE_ARDUINO_HPP_
