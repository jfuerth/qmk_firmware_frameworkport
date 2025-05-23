# framework/rgb_macropad

![framework/rgb_macropad](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Jonathan Fuerth](https://github.com/jfuerth)
* Hardware Supported: 24-key RGB Macropad for Framework Laptop 16
* Hardware Availability: [Framework store](https://fr.mw/FRAKDNEN)

Make example for this keyboard (after setting up your build environment):

    make framework/rgb_macropad:default

Flashing example for this keyboard:

Enter the bootloader (see Bootloader section below), then copy framework_macropad_default.uf2 to the USB mass storage device that appears.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

When the RP2040 enters bootloader mode, it appears as a USB mass storage device. Copy your compiled .uf2 to it, and it will
instantly restart, running your new code.

Enter the bootloader in 2 ways:

* **Physical reset**: re-seat the macropad while holding down the `2` and `6` keys:
  ```
  - - - -
  - - - -
  - - - -
  - - 6 -
  - 2 - -
  - - - -
  ```
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
