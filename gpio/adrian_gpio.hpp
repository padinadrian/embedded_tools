/**
 * File:    adrian_gpio.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_GPIO_HPP_
#define ADRIAN_GPIO_HPP_

/* ===== Includes ===== */
#include "../adrian_helpers.hpp"

namespace adrian
{
    /**
     * GPIO Interface
     * Implement this interface for each new platform.
     * This interface can then be used for any project
     * which uses the adrian::GPIO class.
     */
    class GPIO
    {
    public:
        /* ===== Enums ===== */
        enum PinMode
        {
            PM_INPUT,
            PM_OUTPUT,
            PM_INPUT_PULLUP,
        };

        /* ===== Functions ===== */

        /** Mandatory virtual destructor. */
        virtual ~GPIO() {};

        /** Set the pin as an input or output. */
        virtual void SetPinMode(const PinMode mode) = 0;

        /**
         * Set the state of the pin.
         * Pin must be configured as an OUTPUT first.
         * Writing to an INPUT pin may result in undefined behavior.
         */
        virtual void Write(const bool state) = 0;

        /**
         * Read the state of the pin.
         * Pin must be configured as an INPUT first.
         * Read from an OUTPUT pin may result in undefined behavior.
         */
        virtual bool Read() const = 0;

        /** Operator form of Write. */
        virtual void operator=(const bool state)
        {
            this->Write(state);
        }

        /**
         * Operator form of Read.
         * Uses the "Safe Bool Idiom"
         * See: https://www.artima.com/cppsource/safebool.html
         */
        virtual bool operator!() const
        {
            return !this->Read();
        }
    };

}   // end namespace adrian

#endif  // ADRIAN_GPIO_HPP_