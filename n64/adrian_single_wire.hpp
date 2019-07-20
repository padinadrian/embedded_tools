/**
 * File:    adrian_single_wire.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_SINGLE_WIRE_HPP_
#define ADRIAN_SINGLE_WIRE_HPP_

/* ===== Includes ===== */
#include "embedded_tools/adrian_helpers.hpp"

namespace adrian
{
    /**
     * Single Wire Interface
     * Implement this interface for each new platform.
     * This interface can then be used for any project
     * which uses the adrian::SingleWire class.
     * 
     * For more information on single wire, see:
     * https://os.mbed.com/users/fomartin/notebook/n64-controller-interface/
     */
    class SingleWire
    {
    public:
        /* ===== Functions ===== */

        /** Obligatory virtual destructor. */
        virtual ~SingleWire() {};

        /** Initialize the interface (platform dependent). */
        virtual void Initialize(const uint32_t data_pin) = 0;

        /** Release the interface (platform dependent). */
        virtual void Release() = 0;

        /** Set the frequency in Hertz. */
        virtual void SetFrequency(const uint32_t frequency) = 0;

        /** Set the bit order (see BitOrder). */
        virtual void SetBitOrder(const BitOrder bit_order) = 0;

        /**
         * Perform a non-blocking half-duplex write.
         * Returns the number of bytes actually written,
         * or zero if the write failed.
         */
        virtual uint8_t Write(
            const uint8_t tx_buffer[],
            const uint8_t buffer_size) = 0;

        /**
         * Perform a blocking half-duplex read.
         * Returns the number of bytes read,
         * or zero if the read failed.
         */
        virtual uint8_t ReadBlocking(
            uint8_t rx_buffer[],
            const uint8_t buffer_size) = 0;
    };

}   // end namespace adrian

#endif  // ADRIAN_SINGLE_WIRE_HPP_
