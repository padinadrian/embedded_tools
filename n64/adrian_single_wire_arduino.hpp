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
            uint8_t single_wire_buffer[buffer_size * 4];

            // Block the line for writing.
            Serial.begin(m_frequency * 4);



            // Unblock the line to allow for reading.
            Serial.end();
        }

        /** Read bytes over the wire using the Serial interface. */
        virtual uint8_t ReadBlocking(
            uint8_t rx_buffer[],
            const uint8_t buffer_size)
        {
            // Spin while waiting for input.
            while (!Serial.available());

            // Read as if it were serial data.
            uint8_t serial_rx_buffer[4 * buffer_size];
            const uint8_t bytes_read = Serial.readBytes(serial_rx_buffer, 4 * buffer_size);

            // Translate from Serial bytes to data bytes.
            // TODO

            return 0;
        }

        /** Read bytes over the wire using the Serial interface. */
        virtual uint8_t ReadBlocking(
            uint8_t rx_buffer[],
            const uint8_t buffer_size)
        {
            // Spin while waiting for input.
            while (!Serial.available());

            // Read as if it were serial data.
            uint8_t serial_rx_buffer[4 * buffer_size];
            const uint8_t bytes_read = Serial.readBytes(serial_rx_buffer, 4 * buffer_size);

            // Translate from Serial bytes to data bytes.
            // TODO

            return 0;
        }

    private:

        /* ===== Private Functions ===== */

        /**
         * 
         */
        void FallingEdgeReadHandler()
        {
            
        }

        /* ===== Private Variables ===== */

        // Bit transmission definitions.
        static const uint8_t ZERO_ZERO = 0x88; // 0001 0001
        static const uint8_t ZERO_ONE  = 0xE8; // 0001 0111
        static const uint8_t ONE_ZERO  = 0x8E; // 0111 0001
        static const uint8_t ONE_ONE   = 0xEE; // 0111 0111
        static const uint8_t STOP_BIT  = 0xFC; // 0011 1111

        uint32_t m_data_pin;    //< Pin number of data pin
        uint32_t m_frequency;   //< Data transfer rate in Hertz
        BitOrder m_bit_order;   //< Data transfer bit order
    };

}   // end namespace adrian

#endif  // ADRIAN_SINGLE_WIRE_ARDUINO_HPP_
