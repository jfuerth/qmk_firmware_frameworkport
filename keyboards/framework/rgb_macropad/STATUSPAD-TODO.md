# RGB Statuspad brainstorm

Ideas for how to turn the RGB Macropad into a "status pad" which can be updated from the USB host

## LED Driver

The RGB Macropad has a IS31FL3743A Driver which is addressed over I2C.
* The QMK API for this driver is at https://docs.qmk.fm/drivers/is31fl3743a
  * It allows updating all the RGB values individually 
  * The GPIO enable pin for the driver is defined in framework.h as `IS31FL3743A_ENABLE_GPIO GP29`
  * I2C data pins are defined in config.h:
    ```
    #define I2C_DRIVER I2CD1
    #define I2C1_SDA_PIN GP26
    #define I2C1_SCL_PIN GP27
    ```
    
Questions:


## QMK RGB Matrix

Questions:
* do we need to disable the QMK RGB Matrix feature in order to set the LEDs to whatever values we want?
  * Maybe not:
    * You can bind RGB_MATRIX_DISABLE to a key to turn the feature off, but this disables the 'indicator' feature too (might be fine if we are using the RGB driver directly)
    * There is an example of how to use the RGB Matrix indicators feature without the RGB Matrix animation effects: https://docs.qmk.fm/features/rgb_matrix#indicators-without-rgb-matrix-effect
    * You can also define fully custom effects: https://docs.qmk.fm/features/rgb_matrix#custom-rgb-matrix-effects
* how do we set an individual value on the RGB matrix?
  * can use `rgb_matrix_set_color()` but the effect is quickly overridden by the current RGB effect.


## Sending data from the host to the Statuspad

Can use RAW HID messages
* VIA uses this already, so it's implicitly enabled by `VIA_ENABLE = yes` in rules.mk even though it says `RAW_ENABLE = no` right after
* the callback is routed to handle_hid() in factory.c whether VIA is enabled or not
* Drawback: there's a relatively low limit on bandwidth from the host (low transfer frequency, max 32 bytes per transfer)

Questions:

* Can we go faster by opening a new USB endpoint using RP2040 APIs directly?
  * Would it actually be faster? How many times per second is QMK updating the LEDs?
