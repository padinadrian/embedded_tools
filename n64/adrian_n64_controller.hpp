/**
 * File:    adrian_n64_controller.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_N64_CONTROLLER_HPP_
#define ADRIAN_N64_CONTROLLER_HPP_

/* ===== Includes ===== */
#include <cstring>
#include "adrian_single_wire.hpp"

namespace adrian {

    /**
     * Class representing a N64 controller.
     */
    class N64Controller
    {
    public:
        /* ===== Classes ===== */

        /**
         * Controller inputs (buttons and joystick data).
         */
        struct ButtonState
        {
            // Byte 1: first set of buttons
            uint8_t a:1;
            uint8_t b:1;
            uint8_t z:1;
            uint8_t start:1;
            uint8_t d_up:1;
            uint8_t d_down:1;
            uint8_t d_left:1;
            uint8_t d_right:1;
            // Byte 2: second set of buttons
            uint8_t unused:2;
            uint8_t l:1;
            uint8_t r:1;
            uint8_t c_up:1;
            uint8_t c_down:1;
            uint8_t c_left:1;
            uint8_t c_right:1;
            // Byte 3: joystick x value (range -0x50 to 0x50)
            uint8_t joy_x;
            // Byte 3: joystick x value (range -0x50 to 0x50)
            uint8_t joy_y;
        };

        /**
         * Commands sent from the console to the controller.
         */
        enum Command
        {
            IDENTIFY    = 0x00, // Request three-byte status.
            DATA        = 0x01, // Get button and joystick data.
            READ        = 0x02, // Read data from game pack (not supported).
            WRITE       = 0x03, // Write data to game pack (not supported).
            RECALIBRATE = 0xFF  // Recalibrate joystick and identify.
        };

        /* ===== Functions ===== */

        /**
         * Constructor - configure the SingleWire interface.
         */
        N64Controller(SingleWire* single_wire_ptr) :
            m_single_wire_ptr(single_wire_ptr)
        {
            m_single_wire_ptr->SetFrequency(MHz);
            m_single_wire_ptr->SetBitOrder(BIT_ORDER_LSB_FIRST);
        }

        /**
         * Initialize the communication with the controller.
         */
        void Initialize()
        {
            // TODO (although I don't think any setup is required).
        }

        /**
         * Performs a blocking wait for a command from the console.
         */
        uint8_t WaitForCommand()
        {
            // Do a blocking read on the SingleWire interface.
            const uint8_t buffer_size = 4U;
            uint8_t rx_buffer[buffer_size];
            const uint8_t bytes_read =
                m_single_wire_ptr->ReadBlocking(rx_buffer, buffer_size);

            // Failure?
            return rx_buffer[0];
        }

        /**
         * Identify
         */
        void Identify()
        {
            // First two bytes are always the same.
            // Last byte indicates no controller pack (not supported).
            const uint8_t identify_response[] = {0x05, 0x00, 0x02};
            TransmitToConsole(+identify_response, sizeof(identify_response));
        }

        /**
         * Send button and joystick data to the console.
         */
        void TransmitButtonData(const ButtonState n64_buttons)
        {
            uint8_t tx_buffer[sizeof(n64_buttons)];
            (void)memcpy(tx_buffer, &n64_buttons, sizeof(n64_buttons));
            TransmitToConsole(+tx_buffer, sizeof(n64_buttons));
        }

    private:

        /* ===== Private Functions ===== */

        /**
         * Send a series of bytes to the console.
         */
        void TransmitToConsole(const uint8_t tx_buffer[], const uint8_t num_bytes)
        {
            // TODO: This isn't going to work either...
            m_single_wire_ptr->Transfer(tx_buffer, num_bytes);
        }

        /* ===== Private Variables ===== */
        adrian::SingleWire* m_single_wire_ptr;  //< Pointer to single-wire interface.
    };

}   // end namespace adrian

#endif  // ADRIAN_N64_CONTROLLER_HPP_
