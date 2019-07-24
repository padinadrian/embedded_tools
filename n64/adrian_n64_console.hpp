/**
 * File:    adrian_n64_console.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_N64_CONSOLE_HPP_
#define ADRIAN_N64_CONSOLE_HPP_

/* ===== Includes ===== */
#include <cstring>
#include "adrian_n64_controller.hpp"

namespace adrian {

    /**
     * Class representing a Nintendo 64 console.
     */
    class N64Console
    {
    public:
        /* ===== Functions ===== */

        /**
         * Constructor: TODO
         */
        N64Console() {}

        /**
         * Initialize the communication with the console: TODO
         */
        void Initialize() {}

        /**
         * Performs a blocking wait for a command from the console.
         */
        uint8_t WaitForCommand()
        {
            // Wait for command.
            while (!Serial.available());

            // TODO: sadly it wont be this easy.
            uint8_t command = Serial.read();
            return command;
        }

        /**
         * Identify
         */
        void Identify()
        {
            // First two bytes are always the same.
            // Last byte indicates no controller pack (not supported).
            const uint8_t identify_response[] = {0x05, 0x00, 0x02};
            TransmitToConsole(identify_response, sizeof(identify_response));
        }

        /**
         * Send button and joystick data to the console.
         */
        void TransmitButtonData(const N64::ButtonState n64_buttons)
        {
            uint8_t tx_buffer[sizeof(n64_buttons)];
            (void)memcpy(tx_buffer, &n64_buttons, sizeof(n64_buttons));
            TransmitToConsole(tx_buffer, sizeof(n64_buttons));
        }

    private:

        /* ===== Private Functions ===== */

        /**
         * Send a series of bytes to the console.
         */
        void TransmitToConsole(const uint8_t tx_buffer[], const uint8_t num_bytes)
        {
            // TODO: This isn't going to work either...
            m_single_wire_ptr->Write(tx_buffer, num_bytes);
        }

        /* ===== Private Variables ===== */
        adrian::SingleWire* m_single_wire_ptr;  //< Pointer to single-wire interface.
    };

}   // end namespace adrian

#endif  // ADRIAN_N64_CONSOLE_HPP_