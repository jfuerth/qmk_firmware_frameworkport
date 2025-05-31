# Framework Keyboard Community Firmware

This code is a port of Framework's Laptop 16 keyboard firmware, which lives in a
[public QMK fork](https://github.com/FrameworkComputer/qmk_firmware/tree/fl16-v0.2.8-prep/keyboards/framework)
that contains some modifications to QMK itself, and hasn't been kept up to date with upstream QMK changes
since some time in 2023.

The Framework Laptop 16 keyboard modules are all based on a Raspberry Pi Pico microcontroller, and for per-key RGB,
the [IS31FL3743A I2C LED matrix](https://www.lumissil.com/assets/pdf/core/IS31FL3743A_DS.pdf) driver.

The goal of this port is to make it easy for Framework Laptop 16 owners to produce their own customized QMK firmware
based on current documented QMK APIs and practices, rather than having to dig through history to figure out how things
worked in 2023.

If you are looking for the original, official firmware releases, [they are here](https://github.com/FrameworkComputer/qmk_firmware/releases).

## Differences from Framework's original firmware

These features have been dropped:
* detecting when the UEFI boot screen is active, and ensuring the function keys are always enabled in this state
  * this makes it easier to get into the UEFI configuration menu
  * only makes a difference on the main keyboard modules; doesn't matter for numpad and macropad
  * in Framework's QMK fork, this was accomplished by adding a new `OS_UEFI` constant to QMK itself, along with detection
    code that may not be applicable outside of Framework's UEFI environment.
* custom PWM frequency for LED dimming
* dynamic serial number

These features have been preserved:
* RGB matrix effects
* turn off RGB lights when computer is sleeping
* VIA (edit QMK layers at https://keyboard.frame.work)
* NKRO
* factory debug commands over USB serial (perhaps not worth keeping, but they were easy to port over)

## Organization

This directory contains common support code for the Framework Laptop 16 keyboard modules, and can't be compiled
into a .uf2 firmware build on its own.

Code specific to each keyboard module, which you _can_ compile into .uf2 files, lives in subdirectories:

* [RGB Macropad](rgb_macropad/)
* Other modules: help wanted! With the basic shared code in place, it should be relatively straightforward
  to port the other Framework Laptop 16 keyboard modules.
