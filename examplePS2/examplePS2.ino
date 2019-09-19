// examplePS2.ino

// #include "C:\\Users\\apadi\\Documents\\projects\\n64_dualshock/embedded_tools/spi/adrian_spi_arduino.hpp"
#include "C:\\Users\\apadi\\Documents\\projects\\n64_dualshock/embedded_tools/spi/adrian_spi_trinket.hpp"
#include "C:\\Users\\apadi\\Documents\\projects\\n64_dualshock/embedded_tools/ps2/adrian_dualshock.hpp"

// Globals

static adrian::TrinketSPI spi;
static adrian::DualShock ps2_controller(&spi);
static adrian::DualShock::ButtonState buttons;

// Need to define a slave select pin
const int SSEL_PIN = 3;

// External LED (since built-in is 13, already used for SCLK)
const int LED_PIN = 4;

void setup()
{
    spi.Initialize();
    pinMode(SSEL_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(SSEL_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
}

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

    digitalWrite(
        LED_PIN,
        (buttons.digital_valid && buttons.cross) ? HIGH : LOW
    );

    delay(100);
}