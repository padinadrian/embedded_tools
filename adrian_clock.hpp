/**
 * File:    adrian_clock.hpp
 * Author:  padin.adrian@gmail.com
 */

#ifndef ADRIAN_CLOCK_HPP_
#define ADRIAN_CLOCK_HPP_

/* ===== Includes ===== */
#include <inttypes.h>
// #include <iostream>

namespace adrian
{
    /* ===== Public Functions ===== */

    /** Returns a timestamp that will always increase (excluding rollovers). */
    static uint32_t SteadyClock();

    /**
    static uint32_t SteadyClock();
}

#endif  // ADRIAN_CLOCK_HPP_
