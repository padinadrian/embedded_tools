/**
 * File:    adrian_spi_mock.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_SPI_MOCK_HPP_
#define ADRIAN_SPI_MOCK_HPP_

/* ===== Includes ===== */
#include <gmock/gmock.h>
#include "spi/adrian_spi.hpp"

namespace adrian
{
    /**
     * Mock SPI Class
     */
    class MockSPI : public adrian::SPI
    {
    public:
        MOCK_METHOD(void, Initialize, (), (override));
        MOCK_METHOD(void, Release, (), (override));
        MOCK_METHOD(void, SetMode, (const TransferMode mode), (override));
        MOCK_METHOD(void, SetFrequency, (const uint32_t frequency), (override));
        MOCK_METHOD(void, SetBitOrder, (const BitOrder order), (override));
        MOCK_METHOD(void, Transfer, (const uint8_t *tx_buf, uint8_t *rx_buf, const uint8_t num_bytes), (override));
    }
}

#endif  // ADRIAN_SPI_MOCK_HPP_
