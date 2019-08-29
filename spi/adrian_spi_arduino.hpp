/**
 * File:    adrian_spi.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_SPI_ARDUINO_HPP_
#define ADRIAN_SPI_ARDUINO_HPP_

/* ===== Includes ===== */
#include "ext/SoftSPI.h"
#include "adrian_spi.hpp"

namespace adrian
{
    /**
     * SPI Implementation for Arduino
     *
     * Wrapper for SoftSPI by Majenko:
     * https://github.com/MajenkoLibraries/SoftSPI
     */
    class ArduinoSPI : public adrian::SPI
    {
    public:
        /* ===== Functions ===== */

        /** Constructor */
        ArduinoSPI(
                uint32_t clk_pin,
                uint32_t mosi_pin,
                uint32_t miso_pin
            ) :
            m_soft_spi(mosi_pin, miso_pin, clk_pin)
        {
            // Nothing
        }

        /** Initialize the SPI interface (platform dependent) */
        virtual void Initialize()
        {
            m_soft_spi.begin();
        }

        /** Release the SPI interface (platform dependent) */
        virtual void Release()
        {
            m_soft_spi.end();
        }

        /** Set the transfer mode (see SPI::TransferMode) */
        virtual void SetMode(const TransferMode mode)
        {
            m_soft_spi.setDataMode(static_cast<uint8_t>(mode));
        }

        /** Set the frequency in Hertz */
        virtual void SetFrequency(const uint32_t frequency)
        {
            // TODO: Figure out mapping from clock dividers to frequency.
        }

        /** Set the bit order (see SPI::BitOrder) */
        virtual void SetBitOrder(const BitOrder order)
        {
            // TODO: I think this is right?
            m_soft_spi.setBitOrder(static_cast<uint8_t>(order));
        }

        /** Perform a single full-duplex SPI transfer */
        virtual void Transfer(
            const uint8_t *tx_buf,
            uint8_t *rx_buf,
            const uint8_t num_bytes)
        {
            for (uint8_t i = 0; i < num_bytes; ++i)
            {
                rx_buf[i] = m_soft_spi.transfer[tx_buf[i]];
            }
        }

    private:
        SoftSPI m_soft_spi;
    };

}   // end namespace adrian

#endif  // ADRIAN_SPI_ARDUINO_HPP_
