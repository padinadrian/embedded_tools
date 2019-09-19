/**
 * File:    adrian_spi_arduino.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_SPI_ARDUINO_HPP_
#define ADRIAN_SPI_ARDUINO_HPP_

/* ===== Includes ===== */
#include <Arduino.h>
#include <SPI.h>
#include "adrian_spi.hpp"

namespace adrian
{
    /**
     * SPI Implementation for Arduino
     */
    class ArduinoSPI : public adrian::SPI
    {
    public:
        /* ===== Functions ===== */

        /** Constructor */
        ArduinoSPI() :
            clock(1000000),
            bitOrder(MSBFIRST),
            dataMode(SPI_MODE0)
        {
            // Nothing
        }

        /** Initialize the SPI interface (platform dependent) */
        virtual void Initialize()
        {
            ::SPI.begin();
            pinMode(12, INPUT_PULLUP);
        }

        /** Release the SPI interface (platform dependent) */
        virtual void Release()
        {
            ::SPI.end();
        }

        /** Set the transfer mode (see SPI::TransferMode) */
        virtual void SetMode(const TransferMode mode)
        {
            // Lookup table
            static uint8_t spi_mode_lookup[] = {
                SPI_MODE0,
                SPI_MODE1,
                SPI_MODE2,
                SPI_MODE3,
            };
            this->dataMode = spi_mode_lookup[mode];
        }

        /** Set the frequency in Hertz */
        virtual void SetFrequency(const uint32_t frequency)
        {
            this->clock = frequency;
        }

        /** Set the bit order (see SPI::BitOrder) */
        virtual void SetBitOrder(const BitOrder order)
        {
            static uint8_t bit_order_lookup[] = {
                MSBFIRST,
                LSBFIRST
            };
            this->bitOrder = bit_order_lookup[order];
        }

        /** Perform a single full-duplex SPI transfer */
        virtual void Transfer(
            const uint8_t *tx_buf,
            uint8_t *rx_buf,
            const uint8_t num_bytes)
        {
            // Arduino SPI copies data in-place,
            // so we need to copy tx data into rx_buf
            memcpy(rx_buf, tx_buf, num_bytes);

            ::SPI.beginTransaction(SPISettings(clock, bitOrder, dataMode));
            ::SPI.transfer(rx_buf, num_bytes);
            ::SPI.endTransaction();
        }

    private:
        uint32_t clock;
        uint8_t bitOrder;
        uint8_t dataMode;
    };

}   // end namespace adrian

#endif  // ADRIAN_SPI_ARDUINO_HPP_
