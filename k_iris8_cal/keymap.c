// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "g/keymap_combo.h"

enum kayers {
    _DEF,
    _RGT,
    _LFT,
    _ADJ,
};


enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_LSHFT = SAFE_RANGE,
    OS_LCTRL,
    OS_LALT,
    OS_LGUI,

    OS_RSHFT,
    OS_RCTRL,
    OS_RALT,
    OS_RGUI,

    CK_COPY,
    CK_PASTE,
    CK_TAB_R,
    CK_TAB_L,
};

// layer toggles
#define L_DEF MO(_DEF)
#define L_RGT MO(_RGT)
#define L_LFT MO(_LFT)
#define L_ADJ MO(_ADJ)
#define CK_COPY LCTL(KC_INSERT)
#define CK_PASTE LSFT(KC_INSERT)
#define CK_TAB_R LT(_RGT, KC_TAB)
#define CK_TAB_L LT(_LFT, KC_TAB)


// nav keys
#define CK_LTAB LSFT(KC_TAB)

// combos
COMB(XC_COPY, CK_COPY, KC_X, KC_C)
COMB(CV_PASTE, CK_PASTE , KC_C, KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DEF] = LAYOUT(
  QK_GESC , KC_1 , KC_2 , KC_3   , KC_4     , KC_5   ,                         KC_6    , KC_7     , KC_8    , KC_9   , KC_0    , _______,
  KC_TAB  , KC_Q , KC_W , KC_E   , KC_R     , KC_T   ,                         KC_Y    , KC_U     , KC_I    , KC_O   , KC_P    , _______,
  _______ , KC_A , KC_S , KC_D   , KC_F     , KC_G   ,                         KC_H    , KC_J     , KC_K    , KC_L   , KC_SCLN , _______,
  _______ , KC_Z , KC_X , KC_C   , KC_V     , KC_B   , RGB_TOG ,     KC_MUTE , KC_N    , KC_M     , KC_COMM , KC_DOT , KC_SLSH , KC_ENT ,
                          KC_TAB , CK_TAB_R , KC_SPC ,                         KC_BSPC , CK_TAB_L , KC_ENT                              
),

[_RGT] = LAYOUT(
  _______ , _______ , _______ , _______  , _______  , _______ ,                         _______ , _______ , _______ , _______  , _______ , _______,
  _______ , _______ , _______ , _______  , _______  , _______ ,                         _______ , _______ , _______ , _______  , _______ , _______,
  _______ , OS_LGUI , OS_LALT , OS_LCTRL , OS_LSHFT , _______ ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , _______ , _______,
  _______ , _______ , _______ , _______  , _______  , _______ , _______ ,     KC_MPLY , KC_HOME , KC_PGDN , KC_PGUP , KC_END   , _______ , _______,
                                _______  , _______  , _______ ,                         _______ , _______ , _______                               
),

[_LFT] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______  , _______  , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______  , _______  , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , OS_RSHFT , OS_RCTRL , OS_RALT , OS_RGUI , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______  , _______  , _______ , _______ , _______,
                                _______ , _______ , _______ ,                         _______ , _______  , _______                               
),

[_ADJ] = LAYOUT(
  KC_F11  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F12 ,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______,
                                _______ , _______ , _______ ,                         _______ , _______ , _______                              
)
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case TL_LOWR:
    case TL_UPPR:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case TL_LOWR:
    case TL_UPPR:
    case OS_LSHFT,
    case OS_LCTRL,
    case OS_LALT,
    case OS_LGUI,
    case OS_RSHFT,
    case OS_RCTRL,
    case OS_RALT,
    case OS_RGUI,
        return true;
    default:
        return false;
    }
}

oneshot_state os_lshft_state = os_up_unqueued;
oneshot_state os_lctrl_state = os_up_unqueued;
oneshot_state os_lalt_state = os_up_unqueued;
oneshot_state os_lgui_state = os_up_unqueued;
oneshot_state os_rshft_state = os_up_unqueued;
oneshot_state os_rctrl_state = os_up_unqueued;
oneshot_state os_ralt_state = os_up_unqueued;
oneshot_state os_rgui_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_TAB_L:
            if !(!record->tap.count && record->event.pressed) {
                LSFT(KC_TAB);
                return false;
            }
            return true;
    }
    update_oneshot(
        &os_lshft_state, KC_LSFT, OS_LSHFT,
        keycode, record
    );
    update_oneshot(
        &os_lctrl_state, KC_LCTL, OS_LCTRL,
        keycode, record
    );
    update_oneshot(
        &os_lalt_state, KC_LALT, OS_LALT,
        keycode, record
    );
    update_oneshot(
        &os_lcmd_state, KC_LGUI, OS_LGUI,
        keycode, record
    );
    update_oneshot(
        &os_rshft_state, KC_RSFT, OS_RSHFT,
        keycode, record
    );
    update_oneshot(
        &os_rctrl_state, KC_RCTL, OS_RCTRL,
        keycode, record
    );
    update_oneshot(
        &os_ralt_state, KC_RALT, OS_RALT,
        keycode, record
    );
    update_oneshot(
        &os_rcmd_state, KC_RGUI, OS_RGUI,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _FN1, _FN2, _FN3);
}

// #ifdef ENCODER_MAP_ENABLE
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//     [_DEF] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
//     [_RGT] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
//     [_LFT] = { ENCODER_CCW_CW(KC_HOME, KC_END), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
//     [_ADJ] = { ENCODER_CCW_CW(RGB_SPD, RGB_SPI), ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
// };
// #endif




/*
qmk:json:start
{
  "layout": [
  "x x x x x x _ _ _ x x x x x x",
  "x x x x x x _ _ _ x x x x x x",
  "x x x x x x _ _ _ x x x x x x",
  "x x x x x x x _ x x x x x x x",
  "_ _ _ x x x _ _ _ x x x _ _ _"
  ],
  "comment_preview": {
    "position": "none"
  }
}
qmk:json:end
*/


