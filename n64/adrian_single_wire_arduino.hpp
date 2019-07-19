/**
 * File:    adrian_single_wire_arduino.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */


#ifndef ADRIAN_SINGLE_WIRE_ARDUINO_HPP_
#define ADRIAN_SINGLE_WIRE_ARDUINO_HPP_


/* ===== Includes ===== */
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

        /** Set the frequency in Hertz */
        virtual void SetFrequency(const uint32_t frequency)
        {
            m_frequency = frequency;
        }

        /** Set the bit order (see BitOrder) */
        virtual void SetBitOrder(const BitOrder bit_order)
        {
            m_bit_order = bit_order;
        }

        /** Perform a single half-duplex transfer */
        virtual void Transfer(
            const uint8_t *tx_buf,
            const uint8_t num_bytes)
        {
            // TODO
        }

    private:
        uint32_t m_data_pin;    //< Pin number of data pin
        uint32_t m_frequency;   //< Data transfer rate in Hertz
        BitOrder m_bit_order;   //< Data transfer bit order
    };

}   // end namespace adrian


#endif  // ADRIAN_SINGLE_WIRE_ARDUINO_HPP_
