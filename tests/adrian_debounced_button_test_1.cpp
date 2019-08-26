/**
 * File:    adrian_debounced_button_test_1.cpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

/* ===== Includes ===== */
#include <gtest/gtest.h>
#include "../adrian_debounced_button.hpp"
using namespace adrian;

/* ===== Tests ===== */

/** Non-debounced button */
TEST(DebouncedButton, RawButton)
{
    DebouncedButton<1> button;

    // True always means true
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(true));

    // False always means false
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(false));

    // Alternating has no effect
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_TRUE(button.Debounce(true));
}

/** Debounced by 2 samples */
TEST(DebouncedButton, Debounce2)
{
    DebouncedButton<2> button;

    // Alternating true/false gives false
    EXPECT_FALSE(button.Debounce(true));
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(true));
    EXPECT_FALSE(button.Debounce(false));

    // Two trues in a row means a true
    EXPECT_FALSE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(true));

    // Alternating true/false gives true
    EXPECT_TRUE(button.Debounce(false));
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(false));
    EXPECT_TRUE(button.Debounce(true));

    // Two falses in a row means a false
    EXPECT_TRUE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(false));
}

/** Debounced by 3 samples */
TEST(DebouncedButton, Debounce3)
{
    DebouncedButton<3> button;

    // Alternating true/false gives false
    EXPECT_FALSE(button.Debounce(true));
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(true));
    EXPECT_FALSE(button.Debounce(false));

    // Three trues in a row means a true
    EXPECT_FALSE(button.Debounce(true));
    EXPECT_FALSE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(true));

    // Alternating true/false gives true
    EXPECT_TRUE(button.Debounce(false));
    EXPECT_TRUE(button.Debounce(true));
    EXPECT_TRUE(button.Debounce(false));
    EXPECT_TRUE(button.Debounce(true));

    // Three falses in a row means a false
    EXPECT_TRUE(button.Debounce(false));
    EXPECT_TRUE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(false));
    EXPECT_FALSE(button.Debounce(false));
}