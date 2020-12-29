/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum encoder_names {
  _RIGHT,
  _LEFT,
  _MIDDLE,
};

enum custom_keycodes {
    TASKVIEW = SAFE_RANGE,
    VIRTUALDESKTOPLEFT,
    VIRTUALDESKTOPRIGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Play/Pause                  |                                 | Knob  : Vol Dn/Up  |
        |                             | Win + Tab                       | Press: Mute        |
        | Win + Ctrl + Left           | Win + Ctrl + Right              | Vol Up             |
        | Prev Media                  | Next Media                      | Vol Down           |
     */
    [0] = LAYOUT(
        KC_MPLY, TASKVIEW, KC_MUTE,
        VIRTUALDESKTOPLEFT  , VIRTUALDESKTOPRIGHT  , KC_VOLU,
        KC_MPRV, KC_MNXT, KC_VOLD
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) { 
    switch (keycode) {

    case TASKVIEW:
        if (record->event.pressed) {
            // when keycode TASKVIEW is pressed
            SEND_STRING(SS_DOWN(X_LWIN)SS_DOWN(X_TAB)SS_UP(X_LWIN)SS_UP(X_TAB));
        } else {
            // when keycode TASKVIEW is released
        }
        break;

    case VIRTUALDESKTOPLEFT:
        if (record->event.pressed) {
            // when keycode VIRTUALDESKTOPLEFT is pressed
            SEND_STRING(SS_DOWN(X_LWIN)SS_DOWN(X_LCTRL)SS_DOWN(X_LEFT)SS_UP(X_LEFT)SS_UP(X_LCTRL)SS_UP(X_LWIN));
        } else {
            // when keycode VIRTUALDESKTOPLEFT is released
        }
        break;

    case VIRTUALDESKTOPRIGHT:
        if (record->event.pressed) {
            // when keycode VIRTUALDESKTOPRIGHT is pressed
            SEND_STRING(SS_DOWN(X_LWIN)SS_DOWN(X_LCTRL)SS_DOWN(X_RIGHT)SS_UP(X_RIGHT)SS_UP(X_LCTRL)SS_UP(X_LWIN));
        } else {
            // when keycode VIRTUALDESKTOPRIGHT is released
        }
        break;
        
    }
    return true;
};