/**
 * File:    adrian_n64_controller.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

/* ===== Includes ===== */
#include <gtest/gtest.h>
#include "../adrian_helpers.hpp"
using namespace adrian;

/* ===== Tests ===== */

TEST(AdrianHelpers, BitGet)
{
    EXPECT_EQ(BitGet<uint32_t>(0, 0), 0);
    EXPECT_EQ(BitGet<uint32_t>(1, 0), 1);
    EXPECT_EQ(BitGet<uint32_t>(2, 1), 1);
    EXPECT_EQ(BitGet<uint32_t>(4, 2), 1);
    EXPECT_EQ(BitGet<uint32_t>(8, 3), 1);
    EXPECT_EQ(BitGet<uint32_t>(16, 4), 1);
    EXPECT_EQ(BitGet<uint32_t>(32, 5), 1);
    EXPECT_EQ(BitGet<uint32_t>(64, 6), 1);
    EXPECT_EQ(BitGet<uint32_t>(128, 7), 1);
    EXPECT_EQ(BitGet<uint32_t>(256, 8), 1);
    EXPECT_EQ(BitGet<uint32_t>(512, 9), 1);
    EXPECT_EQ(BitGet<uint32_t>(1024, 10), 1);
    EXPECT_EQ(BitGet<uint32_t>(2048, 11), 1);
    EXPECT_EQ(BitGet<uint32_t>(4096, 12), 1);
    EXPECT_EQ(BitGet<uint32_t>(8192, 13), 1);
    EXPECT_EQ(BitGet<uint32_t>(16384, 14), 1);
    EXPECT_EQ(BitGet<uint32_t>(32768, 15), 1);
}

TEST(AdrianHelpers, BitSet)
{
    EXPECT_EQ(BitSet<uint32_t>(0, 0), 1);
    EXPECT_EQ(BitSet<uint32_t>(0, 1), 2);
    EXPECT_EQ(BitSet<uint32_t>(0, 2), 4);
    EXPECT_EQ(BitSet<uint32_t>(0, 3), 8);
    EXPECT_EQ(BitSet<uint32_t>(0, 4), 16);
    EXPECT_EQ(BitSet<uint32_t>(0, 5), 32);
    EXPECT_EQ(BitSet<uint32_t>(0, 6), 64);
    EXPECT_EQ(BitSet<uint32_t>(0, 7), 128);
    EXPECT_EQ(BitSet<uint32_t>(0, 8), 256);
    EXPECT_EQ(BitSet<uint32_t>(0, 9), 512);
    EXPECT_EQ(BitSet<uint32_t>(0, 10), 1024);
    EXPECT_EQ(BitSet<uint32_t>(0, 11), 2048);
    EXPECT_EQ(BitSet<uint32_t>(0, 12), 4096);
    EXPECT_EQ(BitSet<uint32_t>(0, 13), 8192);
    EXPECT_EQ(BitSet<uint32_t>(0, 14), 16384);
    EXPECT_EQ(BitSet<uint32_t>(0, 15), 32768);
}

TEST(AdrianHelpers, BitClear)
{
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 0),  0xFFFFFFFE);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 1),  0xFFFFFFFD);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 2),  0xFFFFFFFB);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 3),  0xFFFFFFF7);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 4),  0xFFFFFFEF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 5),  0xFFFFFFDF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 6),  0xFFFFFFBF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 7),  0xFFFFFF7F);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 8),  0xFFFFFEFF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 9),  0xFFFFFDFF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 10), 0xFFFFFBFF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 11), 0xFFFFF7FF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 12), 0xFFFFEFFF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 13), 0xFFFFDFFF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 14), 0xFFFFBFFF);
    EXPECT_EQ(BitClear<uint32_t>(0xFFFFFFFF, 15), 0xFFFF7FFF);
}