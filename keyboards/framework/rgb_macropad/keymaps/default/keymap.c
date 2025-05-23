// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum _layers {
    _NUMLOCK,
    _FN,
    _FACTORY,
  };

  const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
       /*
       *         ┌────┬────┬────┬────┐
       *  4 keys │Esc │Calc│ =  │ <- │
       *         ├────┼────┼────┼────┤
       *  4 keys │ Num│ /  │ *  │ -  │
       *         ├────┼────┼────┼────┤
       *  3 keys │ 7  │ 8  │ 9  │ +  │
       *         ├────┼────┼────┼────┤
       *  4 keys │ 4  │ 5  │ 6  │ +  │
       *         ├────┼────┼────┼────┤
       *  3 keys │ 1  │ 2  │ 3  │Entr│
       *         ├────┼────┼────┼────┤
       *  3 keys │ 0  │ 0  │ .  │Entr│
       *         └────┴────┴────┴────┴
       * 21 total
       */
      [_NUMLOCK] = LAYOUT(
          KC_ESC,  KC_CALC, KC_EQL,  KC_BSPC,
          KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
          KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
          KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
          KC_P1,   KC_P2,   KC_P3,   KC_PENT,
          KC_P0,   KC_P0,   KC_PDOT, KC_PENT
      ),
       /*
       *         ┌───────┬───────┬───────┬───────┐
       *  4 keys │ RGB   │ RGB + │ RGB + │ RGB + │
       *         │Toggle │ Speed │ Hue   │ Sat   │
       *         ├───────┼───────┼───────┼───────┤
       *  4 keys │Numlock│ RGB - │ RGB - │ RGB - │
       *         │       │ Speed │ Hue   │ Sat   │
       *         ├───────┼───────┼───────┼───────┤
       *  4 keys │ Home  │   ↑   │ Page  │RGB Nxt│
       *         │       │       │ Up    │Effect │
       *         ├───────┼───────┼───────┼───────┤
       *  4 keys │  ←    │QK_BOOT│   →   │RGB Prv│
       *         │       │       │       │Effect │
       *         ├───────┼───────┼───────┼───────┤
       *  4 keys │ End   │  ↓    │ Page  │ BL    │
       *         │       │       │ Down  │ Step  │
       *         ├───────┼───────┼───────┼───────┤
       *  4 keys │ Insert│ Insert│ Delete│ BL    │
       *         │       │       │       │ Step  │
       *         └───────┴───────┴───────┴───────┘
       * 24 total
       */
      [_FN] = LAYOUT(
          RGB_TOG, RGB_SPI, RGB_HUI, RGB_SAI,
          _______, RGB_SPD, RGB_HUD, RGB_SAD,
          _______, _______, _______, RGB_MOD,
          _______, QK_BOOT, _______, RGB_RMOD,
          _______, _______, _______, BL_STEP,
          _______, _______, _______, BL_STEP
      ),
       /* Alphabet
       *         ┌────┬────┬────┬────┐
       *  4 keys │ A  │ B  │ C  │ D  │
       *         ├────┼────┼────┼────┤
       *  4 keys │ E  │ F  │ G  │ H  │
       *         ├────┼────┼────┼────┤
       *  4 keys │ I  │ J  │ K  │ L  │
       *         ├────┼────┼────┼────┤
       *  4 keys │ M  │ N  │ O  │ P  │
       *         ├────┼────┼────┼────┤
       *  4 keys │ Q  │ R  │ S  │ T  │
       *         ├────┼────┼────┼────┤
       *  4 keys │ U  │ V  │ W  │ X  │
       *         └────┴────┴────┴────┘
       * 24 total
       */
      [_FACTORY] = LAYOUT(
          KC_A,    KC_B,    KC_C,    KC_D,
          KC_E,    KC_F,    KC_G,    KC_H,
          KC_I,    KC_J,    KC_K,    KC_L,
          KC_M,    KC_N,    KC_O,    KC_P,
          KC_Q,    KC_R,    KC_S,    KC_T,
          KC_U,    KC_V,    KC_W,    KC_X
      ),
  };

bool led_update_user(led_t led_state) {
    // Link RGB function layer to numlock state (original Framework code did this; not sure why)
    static bool prev_numlock_state = false;
    if (prev_numlock_state != led_state.num_lock) {
        prev_numlock_state = led_state.num_lock;
        if (led_state.num_lock) {
            layer_off(_FN);
        } else {
            layer_on(_FN);
        }
    }
    return true;
}

void enable_factory_mode(bool enable) {
    if (enable)
        layer_on(_FACTORY);
    else
        layer_off(_FACTORY);
}

void keyboard_post_init_user(void) {
    // Sync initial numlock state from the host
    if (host_keyboard_led_state().num_lock) {
        layer_on(_NUMLOCK);
    } else {
        layer_off(_FN);
    }

    // from https://docs.qmk.fm/features/rgb_matrix#indicators-without-rgb-matrix-effect
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // TODO wip - just trying to manipulate the RGB matrix
//     switch (keycode) {
//         case KC_P7:
//             if (record->event.pressed) {
//                 rgb_matrix_set_color(3, RGB_GREEN);
// //                IS31FL_RGB_set_color(3, RGB_GREEN);
//             } else {
//                 rgb_matrix_set_color(3, RGB_RED);
// //                IS31FL_RGB_set_color(3, RGB_RED);
//             }
// //            IS31FL_update_pwm_buffers();
//             return true;
//         case KC_P8:
//             rgb_matrix_set_color(3, RGB_OFF);
//             return true;
//     }
    return true;
};
