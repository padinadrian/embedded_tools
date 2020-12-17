/**
 * File:    adrian_helpers_test_1.cpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

/* ===== Includes ===== */
#include <gtest/gtest.h>
#include "spi/adrian_spi.hpp"
#include "ps2/adrian_dualshock.hpp"
#include "mocks/adrian_spi_mock.hpp"
#include "mocks/adrian_gpio_mock.hpp"
using adrian::MockSPI;
using adrian::MockGPIO;
using adrian::SPI;
using adrian::DualShock;

/* ===== Tests ===== */

// The constructor should configure the SPI interface.
TEST(AdrianDualShock, Constructor)
{
    MockSPI spi;
    EXPECT_CALL(spi, SetMode(SPI::TRANSFER_MODE_3)).Times(1);
    EXPECT_CALL(spi, SetBitOrder(adrian::BIT_ORDER_LSB_FIRST)).Times(1);
    EXPECT_CALL(spi, SetFrequency(125 * adrian::KHz)).Times(1);

    MockGPIO select_pin;
    EXPECT_CALL(select_pin, SetPinMode(adrian::GPIO::PM_OUTPUT)).Times(1);
    EXPECT_CALL(select_pin, Write(1)).Times(1);

    DualShock controller(&spi, &select_pin);
}

// Polling
TEST(AdrianDualShock, PollNoRumble)
{
    MockSPI spi;
    EXPECT_CALL(spi, SetMode(SPI::TRANSFER_MODE_3)).Times(1);
    EXPECT_CALL(spi, SetBitOrder(adrian::BIT_ORDER_LSB_FIRST)).Times(1);
    EXPECT_CALL(spi, SetFrequency(125 * adrian::KHz)).Times(1);
    EXPECT_CALL(spi, Transfer).Times(1);

    MockGPIO select_pin;
    EXPECT_CALL(select_pin, SetPinMode(adrian::GPIO::PM_OUTPUT)).Times(1);
    EXPECT_CALL(select_pin, Write(1)).Times(2);
    EXPECT_CALL(select_pin, Write(0)).Times(1);

    DualShock controller(&spi, &select_pin);
    DualShock::ButtonState current_button_states;
    controller.Poll(current_button_states);
}

// Configuring analog
TEST(AdrianDualShock, EnableAnalog)
{
    MockSPI spi;
    EXPECT_CALL(spi, SetMode(SPI::TRANSFER_MODE_3)).Times(1);
    EXPECT_CALL(spi, SetBitOrder(adrian::BIT_ORDER_LSB_FIRST)).Times(1);
    EXPECT_CALL(spi, SetFrequency(125 * adrian::KHz)).Times(1);
    EXPECT_CALL(spi, Transfer).Times(3);

    MockGPIO select_pin;
    EXPECT_CALL(select_pin, SetPinMode(adrian::GPIO::PM_OUTPUT)).Times(1);
    EXPECT_CALL(select_pin, Write(1)).Times(4);
    EXPECT_CALL(select_pin, Write(0)).Times(3);

    DualShock controller(&spi, &select_pin);
    DualShock::ButtonState current_button_states;
    controller.EnableAnalog();
}