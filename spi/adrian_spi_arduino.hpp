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
        ArduinoSPI() : settings(1000000, MSBFIRST, SPI_MODE0)
        {
            // Nothing
        }

        /** Initialize the SPI interface (platform dependent) */
        virtual void Initialize()
        {
            SPI.begin();
        }

        /** Release the SPI interface (platform dependent) */
        virtual void Release()
        {
            SPI.end();
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
            settings._dataMode = spi_mode_lookup[mode];

            // 14000000, MSBFIRST,
        }

        /** Set the frequency in Hertz */
        virtual void SetFrequency(const uint32_t frequency)
        {
            settings._clock = frequency;
        }

        /** Set the bit order (see SPI::BitOrder) */
        virtual void SetBitOrder(const BitOrder order)
        {
            static uint8_t bit_order_lookup[] = {
                MSBFIRST,
                LSBFIRST
            };
            settings._bitOrder = bit_order_lookup[order];
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

            SPI.beginTransaction(settings);
            SPI.transfer(rx_buf, num_bytes);
            SPI.endTransaction();
        }

    private:
        SPISettings settings;
        //  uint32_t _clock;
        //  uint8_t  _bitOrder;
        //  uint8_t  _dataMode;
    };

}   // end namespace adrian

#endif  // ADRIAN_SPI_ARDUINO_HPP_
