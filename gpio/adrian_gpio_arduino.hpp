/**
 * File:    adrian_gpio_arduino.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_GPIO_ARDUINO_HPP_
#define ADRIAN_GPIO_ARDUINO_HPP_

/* ===== Includes ===== */
#include <Arduino.h>
#include "adrian_gpio.hpp"

namespace adrian
{
    /**
     * GPIO Interface
     * Implement this interface for each new platform.
     * This interface can then be used for any project
     * which uses the adrian::GPIO class.
     */
    class ArduinoGPIO : public adrian::GPIO
    {
    public:
        /* ===== Functions ===== */

        /** Constructor */
        ArduinoGPIO(const int pin_number) : m_pin_number(pin_number)
        {
            // Nothing
        }

        /** Set the state of the pin. */
        virtual void SetPinMode(const PinMode mode)
        {
            switch (mode)
            {
                case PIN_MODE_OUTPUT:
                    pinMode(m_pin_number, OUTPUT);
                    break;
                case PIN_MODE_INPUT_PULLUP:
                    pinMode(m_pin_number, INPUT_PULLUP);
                    break;
                case PIN_MODE_INPUT:
                default:    // fall-through
                    pinMode(m_pin_number, INPUT);
                    break;
            }
        }

        /** Set the state of the pin. */
        virtual void Write(const bool state)
        {
            digitalWrite(m_pin_number, state ? HIGH : LOW);
        }

        /** Read the state of the pin. */
        virtual bool Read() const
        {
            return (digitalRead(m_pin_number) == HIGH);
        }

    private:
        const int m_pin_number;
    };

}   // end namespace adrian

#endif  // ADRIAN_GPIO_ARDUINO_HPP_