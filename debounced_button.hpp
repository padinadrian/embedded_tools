/**
 * File:    debounced_button.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef DEBOUNCED_BUTTON_HPP_
#define DEBOUNCED_BUTTON_HPP_

/* ===== Includes ===== */
#include "adrian_helpers.hpp"

namespace adrian
{
    /**
     * Class for debouncing noisy buttons.
     *
     * If buttons have a lot of jitter they can sometimes
     * trigger multiple actions for a single press or release.
     *
     * Debouncing the button involves taking multiple samples
     * to make sure the button is in a resting state before
     * triggering.
     *
     * The N value indicates how many samples to wait before
     * the sample is considered stable. Most commonly this
     * number is 2.
     */
    template <size_t N>
    class DebouncedButton
    {
    public:
        /* ===== Functions ===== */

        /** Constructor - initialize the value array. */
        DebouncedButton() : m_current_index(0), m_current_value(false)
        {
            memset(+m_previous_values, false, N);
        }

        /** Get the debounced button status by providing the current value. */
        bool Debounce(const bool new_value)
        {
            // Put the new sample in the array.
            m_previous_values[m_current_index++] = new_value;
            if (m_current_index >= N)
            {
                m_current_index = 0;
            }

            // Check if all true
            for (size_t i = 0; i < N; i++)
            {
                if (m_current_value == m_previous_values[i])
                {
                    return m_current_value;
                }
            }
            return (m_current_value = !m_current_value);
        }

    private:
        bool m_previous_values[N];  //< Circular buffer of samples
        size_t m_current_index;     //< Index of sample being taken
        bool m_current_value;       //< Current debounced value
    };

}   // end namespace adrian

#endif  // DEBOUNCED_BUTTON_HPP_
