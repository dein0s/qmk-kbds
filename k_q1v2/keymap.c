/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers{
    BASE,
    MEDIA,
    MAIN,
    LEFT,
    RIGHT,
    ADJUST
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define LC_S MT(MOD_LCTL, KC_S)
#define LG_D MT(MOD_LGUI, KC_D)
#define LA_F MT(MOD_LALT, KC_F)

#define RA_J MT(MOD_RALT, KC_J)
#define RG_K MT(MOD_RGUI, KC_K)
#define RC_L MT(MOD_RCTL, KC_L)
#define TAB_L LT(LEFT, KC_TAB)
#define TAB_R LT(RIGHT, KC_TAB)

enum dein0s_keycodes {
    D_C_RGB1 = SAFE_RANGE, // Dein0s_Custom_RGB1
    D_C_RGB2, // Dein0s_Custom_RGB1
    D_C_RGB3 // Dein0s_Custom_RGB1
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RA_J:
            if (!record->tap.count && record->event.pressed) {
                set_oneshot_mods(MOD_BIT(KC_RALT));
                rgb_matrix_disable();
                rgb_matrix_enable();
                return false;
            } else {
                return true;
            }
        case D_C_RGB1:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_colored_layers);
            }
            return false; // Skip all further processing of this key
        case D_C_RGB2:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_touch_typing);
            }
            return false; // Skip all further processing of this key
        case D_C_RGB3:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_touch_typing_simple);
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
};

const uint16_t PROGMEM media_layer_toggle_combo[] = {KC_LALT, MO(MEDIA), COMBO_END};
const uint16_t PROGMEM adjust_layer_toggle_combo[] = {LT(3, KC_TAB), LT(4, KC_TAB), COMBO_END};
const uint16_t PROGMEM base_layer_activate_combo1[] = {KC_ESC, KC_SPC, COMBO_END};
combo_t key_combos[] = {
    COMBO(media_layer_toggle_combo, TG(MEDIA)),
    COMBO(adjust_layer_toggle_combo, TG(ADJUST)),
    COMBO(base_layer_activate_combo1, TO(BASE))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_82(
        KC_ESC,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,         KC_F11,     KC_F12,   KC_DEL,             KC_MUTE,
        KC_GRV,      KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,           KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,      KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,           KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        TO(MAIN),    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,        KC_QUOT,              KC_ENT,             KC_HOME,
        OSM(MOD_LSFT),         KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,         KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,     KC_LCMD,  KC_LALT,                                KC_SPC,                                 OSM(MOD_RALT),  MO(MEDIA),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MEDIA] = LAYOUT_ansi_82(
        _______,     KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,        KC_VOLD,    KC_VOLU,  KC_INS,             RGB_TOG,
        _______,     D_C_RGB1, D_C_RGB2, D_C_RGB3, _______,  _______,  _______,  _______,  _______,  AS_ON,    AS_OFF,         RGB_VAD,    RGB_VAI,  _______,            _______,
        RGB_TOG,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        RGB_MOD,    RGB_RMOD, KC_PSCR,            _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,                      KC_END,
        _______,               _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,        _______,              _______,   KC_MPLY,
        _______,     _______,  TO(MAIN),                              _______,                                _______,        _______,    _______,  KC_MPRV,   KC_MUTE, KC_MNXT),

    [MAIN] = LAYOUT_ansi_82(
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,           _______,    _______,  _______,            _______,
        _______,     KC_A,     LC_S,     LG_D,     LA_F,     KC_G,     KC_H,     RA_J,     RG_K,     RC_L,     KC_BSPC,        _______,    _______,                      _______,
        _______,               KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,         KC_ENT,               _______,   _______,
        _______,     _______,  TAB_L,                                _______,                                  OSM(MOD_RSFT),  TAB_R,      _______,  _______,   _______, _______),

    [LEFT] = LAYOUT_ansi_82(
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_GRV,   KC_TILD,        _______,    _______,  _______,            _______,
        _______,     KC_DQT,   KC_LBRC,  KC_LCBR,  KC_LPRN,  _______,  KC_SLSH,  KC_MINS,  KC_EQL,   KC_COLN,  KC_SCLN,        _______,    _______,                      _______,
        _______,               KC_QUOT,  KC_RBRC,  KC_RCBR,  KC_RPRN,  _______,  KC_BSLS,  KC_UNDS,  KC_PLUS,  KC_PIPE,        KC_QUES,              _______,   _______,
        _______,     _______,  _______,                                _______,                                KC_ESC,         _______,    _______,  _______,   _______, _______),

    [RIGHT] = LAYOUT_ansi_82(
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,           _______,    _______,  _______,            _______,
        _______,     KC_DEL,   _______,  KC_PSCR,  KC_INS,   _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,        _______,    _______,                      _______,
        _______,               _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,         _______,              _______,   _______,
        _______,     _______,  _______,                              _______,                                  KC_ESC,         _______,    _______,  _______,   _______, _______),

    [ADJUST] = LAYOUT_ansi_82(
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,  _______,            _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,    _______,                      _______,
        _______,               _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,              _______,   _______,
        _______,     _______,  _______,                              _______,                                  _______,        _______,    _______,  _______,   _______, _______),

};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MEDIA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAIN] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [LEFT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [RIGHT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [ADJUST] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)}
};
#endif // ENCODER_MAP_ENABLE
//

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_touch_typing_simple);
}
#endif

// dein0s: use autoshift only on layer 0
/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     switch (get_highest_layer(state)) { */
/*         case BASE: */
/*             autoshift_enable(); */
/*             break; */
/*         default: */
/*             autoshift_disable(); */
/*             break; */
/*     } */
/*     return state; */
/* } */

// dein0s: this does not work properly, the idea is to only highlight keys that are set on the current layer, others should be off
/* bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) { */
/*     if (get_highest_layer(layer_state) > 0) { */
/*         uint8_t layer = get_highest_layer(layer_state|default_layer_state); */
/**/
/*         for (uint8_t row = 0; row < MATRIX_ROWS; ++row) { */
/*             for (uint8_t col = 0; col < MATRIX_COLS; ++col) { */
/*                 uint8_t index = g_led_config.matrix_co[row][col]; */
/**/
/*                 if (index >= led_min && index < led_max && index != NO_LED && */
/*                 keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) { */
/*                     rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR); */
/*                     switch(layer) { */
/*                         case BASE: */
/*                             rgb_matrix_set_color(index, RGB_RED); */
/*                             break; */
/*                         case MEDIA: */
/*                             rgb_matrix_set_color(index, RGB_YELLOW); */
/*                             break; */
/*                         case EMPTY: */
/*                             rgb_matrix_set_color(index, RGB_WHITE); */
/*                             break; */
/*                         case EXTRA: */
/*                             rgb_matrix_set_color(index, RGB_BLUE); */
/*                             break; */
/*                         default: */
/*                             break; */
/*                     } */
/*                 } else { */
/*                     rgb_matrix_set_color(index, RGB_OFF); */
/*                 } */
/*             } */
/*         } */
/*     } */
/*     return false; */
/* } */

