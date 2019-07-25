/**
 * File:    adrian_helpers.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_HELPERS_HPP_
#define ADRIAN_HELPERS_HPP_

/* ===== Includes ===== */
#include <stdint.h>

namespace adrian
{
    /* ===== Constants ===== */
    const uint32_t KHz = 1000;
    const uint32_t MHz = 1000000;


    /* ===== Enums ===== */

    /** The bit order (big endian or little endian) */
    enum BitOrder
    {
        BIT_ORDER_MSB_FIRST = 0,
        BIT_ORDER_LSB_FIRST = 1,
    };


    /* ===== Functions ===== */

    /* Bit Manipulation */

    /** Return 1 if the bit is set, 0 otherwise. */
    template <typename T>
    inline T BitGet(const T number, const uint8_t bitnum)
    {
        return (number & (1 << bitnum)) >> bitnum;
    }

    /** Set a particular bit within the number. */
    template <typename T>
    inline T BitSet(const T number, const uint8_t bitnum)
    {
        return (number | (1 << bitnum));
    }

    /** Set a particular bit within the number. */
    template <typename T>
    inline T BitClear(const T number, const uint8_t bitnum)
    {
        return (number & ~(1 << bitnum));
    }

    /** Return true if the bit is set, false otherwise. */
    template <typename T>
    inline bool IsBitQ(const T number, const uint8_t bitnum)
    {
        return static_cast<bool>(number & (1 << bitnum));
    }

}   // end namespace adrian

#endif  // ADRIAN_HELPERS_HPP_
