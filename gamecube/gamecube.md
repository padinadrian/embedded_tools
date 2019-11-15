# GameCube Controller Interface

## Notes

Wires:
* Yellow - Rumble Power (5V)
* Red - Data (bi-directional, 3v3)
* Green - Ground
* White - Ground (?)
* Blue - Digital Power (3v3)

Data
* Bi-directional, 3v3 logic, 10k pullup resistor, active low
* 24 bit string is sent to controller, 64 bits of button data is sent back
* Similar protocol to N64:
  * 1-bit is 1us low/3us high
  * 0-bit is 3us low/1us high
* Updates are 6ms apart
* Command from console (24 bits):
  * 0100 0000 0000 0011 0000 000R
  * 0x40030R
  * R is for rumble: 1 means rumble, 0 means no rumble
* Response from controller (64 bits):
  * Byte 0: 0 0 0 S Y X B A
  * Byte 1: 1 L R Z DU DD DR DL
  * Byte 2: Joystick X
  * Byte 3: Joystick Y
  * Byte 4: C-stick X
  * Byte 5: C-stick Y
  * Byte 6: Left trigger analog
  * Byte 7: Right trigger analog

Sources:

https://os.mbed.com/users/christopherjwang/code/gamecube_controller/wiki/Homepage