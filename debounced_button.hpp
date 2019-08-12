/**
 * File:    DebouncedButton.hpp
 * Creator: padin.adrian@gmail.com
 */

/* ===== Includes ===== */
#include <stdint.h>

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
        /** Constructor - initialize the value array. */
        DebouncedButton() : current_index(0)
        {
            memset(+previous_values, false, N);
        }

        /** Get the debounced button status by providing the current value. */
        bool Debounce(const bool current_value)
        {
            // Put the new sample in the array.
            previous_values[current_index++] = current_value;
            if (current_index >= N)
            {
                current_index = 0;
            }

            // Check if all true
            for (size_t i = 0; i < N; i++)
            {
                if (!previous_values[i])
                {
                    return false;
                }
            }
            return true;
        }

    private:
        bool previous_values[N];    //< Array of previous samples
        size_t current_index;       //< Current sample being taken
    };

}   // end namespace adrian
