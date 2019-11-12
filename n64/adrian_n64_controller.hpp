/**
 * File:    adrian_n64_controller.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_N64_CONTROLLER_HPP_
#define ADRIAN_N64_CONTROLLER_HPP_

/* ===== Includes ===== */
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
            bool a:1;
            bool b:1;
            bool z:1;
            bool start:1;
            bool d_up:1;
            bool d_down:1;
            bool d_left:1;
            bool d_right:1;
            // Byte 2: second set of buttons
            bool valid:1;
            bool reset:1;
            bool l:1;
            bool r:1;
            bool c_up:1;
            bool c_down:1;
            bool c_left:1;
            bool c_right:1;
            // Byte 3: joystick x value (range -0x50 to 0x50)
            int8_t joy_x;
            // Byte 3: joystick x value (range -0x50 to 0x50)
            int8_t joy_y;
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
            m_single_wire_ptr->SetBitOrder(BIT_ORDER_MSB_FIRST);
        }

        /**
         * Initialize the communication with the controller.
         */
        void Initialize()
        {
            // TODO (although I don't think any setup is required).
        }

        /**
         * Ask the controller to identify itself.
         * Returns true if the response data is valid, false otherwise.
         */
        bool RequestIdentify()
        {
            this->SendCommandToController(Command::IDENTIFY);
            // TODO: handle response
            return true;
        }

        /**
         * Ask the controller to recalibrate the joystick.
         * Returns true if the response data is valid, false otherwise.
         */
        bool RequestRecalibrate()
        {
            this->SendCommandToController(Command::RECALIBRATE);
            // TODO: handle response
            return true;
        }

        /**
         * Request the current button and joystick status.
         * Returns true if the response data is valid, false otherwise.
         */
        bool RequestButtonData(ButtonState& n64_buttons)
        {
            // Send the request and handle the response.
            const uint8_t rx_buffer_size = sizeof(n64_buttons);
            uint8_t rx_buffer[rx_buffer_size];
            this->SendCommandToController(Command::DATA);
            (void)this->WaitForResponse(rx_buffer, rx_buffer_size);

            memcpy(&n64_buttons, rx_buffer, sizeof(n64_buttons));
            n64_buttons.joy_x = ReverseByte(n64_buttons.joy_x);
            n64_buttons.joy_y = ReverseByte(n64_buttons.joy_y);

            return !static_cast<bool>(n64_buttons.valid);
        }

    private:

        /* ===== Private Functions ===== */

        /**
         * Send a single one-byte command to the controller.
         */
        void SendCommandToController(const Command command)
        {
            // TODO: This isn't going to work either...
            const uint8_t command_buffer = static_cast<uint8_t>(command);
            m_single_wire_ptr->Write(&command_buffer, sizeof(command_buffer));
        }

        /**
         * Do a blocking read from the controller.
         */
        uint8_t WaitForResponse(uint8_t rx_buffer[], const uint8_t buffer_size)
        {
            return m_single_wire_ptr->ReadBlocking(rx_buffer, buffer_size);
        }

        /* ===== Private Variables ===== */
        adrian::SingleWire* m_single_wire_ptr;  //< Pointer to single-wire interface.
    };

}   // end namespace adrian

#endif  // ADRIAN_N64_CONTROLLER_HPP_
