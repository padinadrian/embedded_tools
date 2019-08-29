/**
 * File:    adrian_helpers_test_1.cpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

/* ===== Includes ===== */
#include <gtest/gtest.h>
#include "spi/adrian_spi.hpp"
#include "mocks/adrian_spi_mock.hpp"

/* ===== Tests ===== */

// The constructor should configure the SPI interface.
TEST(AdrianDualShock, Constructor)
{
    MockSPI spi;
    EXPECT_CALL(spi, SetMode(SPI::TRANSFER_MODE_3)).Times(1);
    EXPECT_CALL(spi, SetBitOrder(adrian::BIT_ORDER_MSB_FIRST)).Times(1);
    EXPECT_CALL(spi, SetFrequency(250 * adrian::KHz)).Times(1);

    DualShock controller(&spi);
}

// Polling
TEST(AdrianDualShock, PollNoRumble)
{
    MockSPI spi;
    EXPECT_CALL(spi, Transfer).Times(1);

    DualShock controller(&spi);
    DualShock::ButtonState current_button_states;
    controller.Poll(current_button_states);
}