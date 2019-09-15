# PlayStation 2 Controller Interface

This document will detail the interface used by the
PlayStation 2 to communicate with the DualShock 2
controllers.

## Physical Layer

### Controller Inputs

The DualShock controller consists of several different kinds
of inputs:

* 12 digital/analog buttons
* 4 digital-only buttons
* 2 analog joysticks

Based on the configuration, the 12 main buttons can be
either simple on/off buttons or fully pressure-sensitive
analog inputs. Start, select, and L3/R3 (joystick buttons)
are digital-only.

The analog joysticks both sit on a two-axis grid and report
their position as a pair of X-Y coordinates.

The controller also has two motors, one larger in the left
and one smaller on the right, that can be used for vibration
feedback.

### Connector Pinout

There are nine pins on the DualShock connector, of which
only eight are used. The pins are as follows, from left to
right on the male side:

1. Brown - Data (controler to console)
2. Orange - Command (console to controller)
3. Gray - Motor power (7.2V - 9V)
4. Black - Ground (GND)
5. Red - Power (3.3V)
6. Yellow - Attention
7. Blue - Clock
8. White - Unused
9. Green - Acknowledge

#### Male Connector

![alt text](ps2_connector.jpg "DualShock connector wires.")

### Data Wires

The PlayStation 2 uses a modified version of the
[SPI](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)
protocol to communicate with the controller. This protocol is
discussed more in-depth in the [Data Layer](#data-layer) section.

SPI uses four pins: two data pins (MISO and MOSI), a clock
pin, and a select pin.

* The **brown** data wire is the equivalent of the MISO pin in
  SPI. This pin is used to transfer data from the controller to
  the console. It is an open-collector output, so it requires a
  pull-up resistor of about 1k to 10k Ohms.

* The **orange** command wire is the equivalent of the MOSI pin
  in SPI. This pin is used by the console to send commands to the
  controller, e.g. to request button data.

* The **blue** clock wire is the equivalent of the SPI clock
  pin. Officially the speed of this clock is 500kHz, but I have
  found that 250kHz is more reliable, especially with 3rd-party
  controllers.

* The **yellow** attention wire is the equivalent of the select
  pin in SPI. It should float high when not in use and be
  pulled low before each data transfer, then released high
  again.

Additionally, the **green** acknowledge wire is an output from the
controller which verifies that it is connected and transmitting
properly. If you are interfacing with a controller, you have the
option to check this pin or not (I generally do not).
However, you must provide this output if you plan to interface
with the PlayStation 2 console as it requires this pin to behave
properly.

### Power Wires

* The red power line is officially 5V but it works easily at
  3.3V and should work anywhere between 3-5V.

* The gray power line which powers the vibration motors is
  listed as 9V but can work as low as 5V. The power of the
  vibration scales with the voltage (high voltag = more
  vibration). However, the motors can draw 500mA or more,
  so be careful about the power source.

## Data Layer

The communication protocol used by the PS2 is a modified form
of SPI with a custom data protocol. SPI is full-duplex,
meaning the console sends commands to the controller and gets
the response within the same transaction.

### Transaction Overview

The general format for a transation goes like this:

1. The PS2 console pulls the select pin low to indicate it is
   starting a transaction.
2. The console then sends a 3-byte header, and in the same
   bytes the controller sends a 3-byte reponse indicating
   the current configuration state.
3. The console then sends 2 bytes indicating the vibration
   level, and the console sends the digital button states.
4. Depending on the configuration, the controller will then
   send up to 16 additional bytes with the joystick and
   analog button data.

### High-Level Protocol

When the controller is first plugged in it defaults to digital
mode and transmits only the digital button data.

| Byte #        |  1   |  2   |  3   |  4   |  5   |
| ------------- |:----:|:----:|:----:|:----:|:----:|
| Command (hex) | 0x01 | 0x42 | 0x00 | 0x00 | 0x00 |
| Data (hex)    | 0xFF | 0x41 | 0x5A | 0xFF | 0xFF |
| Section       |  H   |  H   |  H   |  D   |  D   |

The first 3 bytes sent from the console are the header
(section H).

* First byte:
  * Console always sends 0x01
  * Controller always sends 0xFF
* Second byte:
  * Console sends [command type](#command-type), in this case 0x42
  * Controller sends current [device mode](#device-mode), in this case 0x41
* Third byte:
  * Console always sends 0x00
  * Controller always sends 0x5A

After the header comes the data section, which can be between
2 and 18 bytes. In the default digital mode, this consists of
2 bytes which are the vibration commands, where a higher number
means stronger vibration.

#### Command Type



## Sources

This data was collected over time from various sites, and I
want to pay credit to those who have gone before me and did
the hard work of reverse engineering the SPI protocols.

1. Curious Inventor - Interfacing a PS2 (PlayStation 2) Controller:
   http://store.curiousinventor.com/PS2
