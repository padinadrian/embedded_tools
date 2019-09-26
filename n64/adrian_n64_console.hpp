/**
 * File:    adrian_n64_console.hpp
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

#ifndef ADRIAN_N64_CONSOLE_HPP_
#define ADRIAN_N64_CONSOLE_HPP_

/* ===== Includes ===== */
// #include <cstring>
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
         * Constructor - configure the SingleWire interface.
         */
        N64Console(SingleWire* single_wire_ptr) :
            m_single_wire_ptr(single_wire_ptr)
        {
            m_single_wire_ptr->SetFrequency(MHz);
            m_single_wire_ptr->SetBitOrder(BIT_ORDER_LSB_FIRST);
        }

        /**
         * Initialize the communication with the console: TODO
         */
        void Initialize() {}

        /**
         * Performs a blocking wait for a command from the console.
         * Returns true if the
         */
        bool WaitForCommand(N64Controller::Command& command)
        {
            // Do a blocking read on the SingleWire interface.
            const uint8_t buffer_size = 4U;
            uint8_t rx_buffer[buffer_size];
            const uint8_t bytes_read =
                m_single_wire_ptr->ReadBlocking(rx_buffer, buffer_size);

            command = static_cast<N64Controller::Command>(rx_buffer[0]);
            return (bytes_read > 0);
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
        void TransmitButtonData(const N64Controller::ButtonState n64_buttons)
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
        void TransmitToConsole(const uint8_t tx_buffer[], const uint8_t buffer_size)
        {
            // TODO: This isn't going to work either...
            m_single_wire_ptr->Write(tx_buffer, buffer_size);
        }

        /* ===== Private Variables ===== */
        adrian::SingleWire* m_single_wire_ptr;  //< Pointer to single-wire interface.
    };

}   // end namespace adrian

#endif  // ADRIAN_N64_CONSOLE_HPP_