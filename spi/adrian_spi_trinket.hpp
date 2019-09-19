/**
 * File:    adrian_spi_trinket
 * .hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_SPI_ARDUINO_HPP_
#define ADRIAN_SPI_ARDUINO_HPP_

/* ===== Includes ===== */
#include "adrian_spi.hpp"


#define SPI_DDR_PORT DDRB
#define USCK_DD_PIN DDB2
#define DO_DD_PIN DDB1
#define DI_DD_PIN DDB0

// SPI data modes
#define SPI_MODE0 0x00
#define SPI_MODE1 0x04

/*
Reference:
https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf

USIDR - USI Data Register

USISR - USI Status Register


USICR - USI Control Register
bits:
7 - USISIE (Start Condition Interrupt Enable)
    Setting to 1 enables the start condition detector interrupt.
6 - USIOIE (Counter Overflow Interrupt Enable)
    Setting to 1 enables the counter overflow interrupt.
5:4 - USIWM[1:0] (Wire Mode)
    Configures USI as one of four serial types:
    GPIO: USIWM1=0, USIWM0=0
    SPI:  USIWM1=0, USIWM0=1
    I2C?: USIWM1=1, USIWM0=0
    I2C?: USIWM1=1, USIWM0=1
3:2 - USICS[1:0] (Clock Source Select)

*/

namespace adrian
{
    /**
     * SPI Implementation for Arduino
     */
    class TrinketSPI : public adrian::SPI
    {
    public:
        /* ===== Functions ===== */

        /** Constructor */
        TrinketSPI() : bit_order(adrian::BIT_ORDER_MSB_FIRST)
        {
            // Nothing
        }

        /** Initialize the SPI interface (platform dependent) */
        virtual void Initialize()
        {
            // TODO
        }

        /** Release the SPI interface (platform dependent) */
        virtual void Release()
        {
            // TODO
        }

        /** Set the transfer mode (see SPI::TransferMode) */
        virtual void SetMode(const TransferMode mode)
        {
            // TODO
        }

        /** Set the frequency in Hertz */
        virtual void SetFrequency(const uint32_t frequency)
        {
            // TODO
        }

        /** Set the bit order (see SPI::BitOrder) */
        virtual void SetBitOrder(const BitOrder order)
        {
            // TODO
            bit_order = order;
        }

        /** Perform a single full-duplex SPI transfer */
        virtual void Transfer(
            const uint8_t *tx_buf,
            uint8_t *rx_buf,
            const uint8_t num_bytes)
        {
            this->BeginTransaction();
            for (uint8_t i = 0; i < num_bytes; i++)
            {
                rx_buf[i] = this->TransferOneByte(tx_buf[i]);
            }
            this->EndTransaction();
        }

    private:

        /** Configure registers for SPI transaction. */
        BeginTransaction()
        {
            // Clear USISIE - disable start condition detector interrupt
            // Clear USIOIE - disable counter overflow interrupt
            // Clear USIWM1 and set USIWM0 - enable 3 wire mode
            // Set USICS1 and clear USICLK -
            USICR &= ~(_BV(USISIE) | _BV(USIOIE) | _BV(USIWM1));
            USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USICLK);

            // Configure pin type
            SPI_DDR_PORT |= _BV(USCK_DD_PIN);   // Clock, output
            SPI_DDR_PORT |= _BV(DO_DD_PIN);     // MOSI, output
            SPI_DDR_PORT &= ~_BV(DI_DD_PIN);    // MISO, input

            PORTB |= _BV(USCK_DD_PIN);  // clock is inactive high
            // PORTB &= ~_BV(DI_DD_PIN);   // disable pull-up
            PORTB |= _BV(DI_DD_PIN);   // disable pull-up

            // Set clock mode
            USICR &= ~_BV(USICS0);

            // USICR |= _BV(USICS0);
        }

        /** Reset register configurations. */
        EndTransaction()
        {
            // TODO

            PORTB |= _BV(USCK_DD_PIN);
        }

        /** Trasnfer a single byte, full-duplex over SPI. */
        TransferOneByte(uint8_t data)
        {
            volatile int i = 0;

            // USI is only capable of doing MSB_FIRST from hardware
            // We need to manually flip the bits for LSB_FIRST
            USIDR = (bit_order == BIT_ORDER_MSB_FIRST) ? data : ReverseByte(data);
            USISR = _BV(USIOIF);

            noInterrupts();

            while ( !(USISR & _BV(USIOIF)) )
            {
                USICR |= _BV(USITC);    // toggle clock
                i = 1;
                i = 1;
                i = 1;
                i = 1;
                i = 1;
                i = 1;
                i = 1;
                i = 1;
            }

            interrupts();

            // USI is only capable of doing MSB_FIRST from hardware
            // We need to manually flip the bits for LSB_FIRST
            return (bit_order == BIT_ORDER_MSB_FIRST) ? USIDR : ReverseByte(USIDR);
        }

    private:
        // Private members
        // uint32_t clock;
        // uint8_t bitOrder;
        // uint8_t dataMode;
        BitOrder bit_order;
    };

}   // end namespace adrian

#endif  // ADRIAN_SPI_ARDUINO_HPP_
