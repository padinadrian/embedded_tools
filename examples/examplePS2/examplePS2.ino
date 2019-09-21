/**
 * File:    examplePS2.ino
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

/*
    This example program demonstrates how to use the
    DualShock class with an Arduino.

    This example is intended to be used with the Arduino
    Uno/Genuino. However, it can easily be adapted to any
    target device by implementing the adrian::SPI
    interface.

    (Don't forget you may also need to change the select
    and LED pins!)
*/

/* ===== Includes ===== */
// #include "C:\\Users\\apadi\\Documents\\projects\\n64_dualshock/embedded_tools/spi/adrian_spi_arduino.hpp"
#include "../../adrian_helpers.hpp"
#include "../../spi/adrian_spi_trinket.hpp"
#include "../../ps2/adrian_dualshock.hpp"

/* ===== Globals ===== */
static adrian::ArduinoSPI spi;
static adrian::DualShock ps2_controller(&spi);
static adrian::DualShock::ButtonState buttons;

// Need to define a slave select pin.
const int SSEL_PIN = 10;

// Pin for external LED.
// Can't use built-in since it is 13, already used for SCLK
const int LED_PIN = 9;

/* ===== SETUP ===== */

void setup()
{
    spi.Initialize();
    pinMode(SSEL_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(SSEL_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
}

/* ===== LOOP ===== */

void loop()
{
    // Try to connect to controller
    if (!ps2_controller.IsConnected())
    {
        digitalWrite(SSEL_PIN, LOW);
        while (!ps2_controller.Connect()) { delay(1000); }
        digitalWrite(SSEL_PIN, HIGH);
    }

    // Poll the controller for the button status.
    digitalWrite(SSEL_PIN, LOW);
    ps2_controller.Poll(buttons);
    digitalWrite(SSEL_PIN, HIGH);

    const bool pressed = (buttons.digital_valid && buttons.cross);
    digitalWrite(LED_PIN, pressed ? HIGH : LOW);

    delay(100);
}