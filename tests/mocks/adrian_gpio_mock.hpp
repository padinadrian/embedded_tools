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
     * Mock GPIO Class
     */
    class MockGPIO : public adrian::GPIO
    {
    public:
        MOCK_METHOD(void, SetPinMode, (const PinMode mode), (override));
        MOCK_METHOD(void, Write, (const bool state), (const, override));
        MOCK_METHOD(void, operator=, (const bool state), (const, override));
        MOCK_METHOD(bool, Read, (), (const, override));
        MOCK_METHOD(bool, operator!, (), (const, override));
    };
}

#endif  // ADRIAN_SPI_MOCK_HPP_
