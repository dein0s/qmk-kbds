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


// default layout: LAYOUT_91_ansi
// tmp layout name for formatting: LAYOUT_preonic_grid

#include QMK_KEYBOARD_H
#include <stdio.h>

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

#define OSM_LS OSM(MOD_LSFT)
#define OSM_RA OSM(MOD_RALT)

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
//    ┌──────┐   ┌──────┬──────┬──────┬───────────┬────┬────┬────┐   ┌────┬────┬────┬────────┬───────────┬──────┬─────┬─────┐                    ┌──────┐
//    │ mute │   │ esc  │  f1  │  f2  │    f3     │ f4 │ f5 │ f6 │   │ f7 │ f8 │ f9 │  f10   │    f11    │ f12  │ ins │ del │                    │ mute │
//    ├──────┤   ├──────┼──────┼──────┼───────────┼────┼────┼────┤   ├────┼────┼────┼────────┼───────────┼──────┼─────┴─────┤                    ├──────┤
//    │ MC_1 │   │  `   │  1   │  2   │     3     │ 4  │ 5  │ 6  │   │ 7  │ 8  │ 9  │   0    │     -     │  =   │   bspc    │                    │ pgup │
//    ├──────┤   ├──────┼──────┼──────┼───────────┼────┼────┼────┘   ├────┼────┼────┼────────┼───────────┼──────┼─────┬─────┤                    ├──────┤
//    │ MC_2 │   │ tab  │  q   │  w   │     e     │ r  │ t  │        │ y  │ u  │ i  │   o    │     p     │  [   │  ]  │  \  │                    │ pgdn │
//    ├──────┤   ├──────┴──────┼──────┼───────────┼────┼────┼────┐   ├────┼────┼────┼────────┼───────────┼──────┼─────┴─────┤                    ├──────┤
//    │ MC_3 │   │  TO(MAIN)   │  a   │     s     │ d  │ f  │ g  │   │ h  │ j  │ k  │   l    │     ;     │  '   │    ent    │                    │ home │
//    ├──────┤   ├─────────────┼──────┼───────────┼────┼────┼────┤   ├────┼────┼────┼────────┼───────────┼──────┴─────┬─────┘      ┌──────┐      └──────┘
//    │ MC_4 │   │   OSM_LS    │  z   │     x     │ c  │ v  │ b  │   │ n  │ m  │ ,  │   .    │     /     │    rsft    │            │  up  │
//    ├──────┤   ├──────┬──────┼──────┼───────────┼────┴────┴────┤   ├────┴────┴────┼────────┼───────────┼──────┬─────┘     ┌──────┼──────┼──────┐
//    │ MC_5 │   │ lctl │ lgui │ lalt │ MO(MEDIA) │     spc      │   │     bspc     │ OSM_RA │ MO(MEDIA) │ rctl │           │ left │ down │ rght │
//    └──────┘   └──────┴──────┴──────┴───────────┴──────────────┘   └──────────────┴────────┴───────────┴──────┘           └──────┴──────┴──────┘
[BASE] = LAYOUT_91_ansi(
  KC_MUTE ,     KC_ESC  , KC_F1   , KC_F2   , KC_F3     , KC_F4 , KC_F5 , KC_F6 ,     KC_F7 , KC_F8 , KC_F9   , KC_F10 , KC_F11    , KC_F12  , KC_INS  , KC_DEL  ,                               KC_MUTE,
  MC_1    ,     KC_GRV  , KC_1    , KC_2    , KC_3      , KC_4  , KC_5  , KC_6  ,     KC_7  , KC_8  , KC_9    , KC_0   , KC_MINS   , KC_EQL  ,      KC_BSPC      ,                               KC_PGUP,
  MC_2    ,     KC_TAB  , KC_Q    , KC_W    , KC_E      , KC_R  , KC_T  ,             KC_Y  , KC_U  , KC_I    , KC_O   , KC_P      , KC_LBRC , KC_RBRC , KC_BSLS ,                               KC_PGDN,
  MC_3    ,         TO(MAIN)      , KC_A    , KC_S      , KC_D  , KC_F  , KC_G  ,     KC_H  , KC_J  , KC_K    , KC_L   , KC_SCLN   , KC_QUOT ,      KC_ENT       ,                               KC_HOME,
  MC_4    ,          OSM_LS       , KC_Z    , KC_X      , KC_C  , KC_V  , KC_B  ,     KC_N  , KC_M  , KC_COMM , KC_DOT , KC_SLSH   ,      KC_RSFT      ,                     KC_UP                      ,
  MC_5    ,     KC_LCTL , KC_LWIN , KC_LALT , MO(MEDIA) ,        KC_SPC         ,             KC_BSPC         , OSM_RA , MO(MEDIA) , KC_RCTL ,                     KC_LEFT , KC_DOWN , KC_RGHT
),

//    ┌─────────┐   ┌─────┬──────────┬──────────┬──────────┬──────┬─────────┬─────────┐   ┌─────────┬──────┬───────┬────────┬─────────┬─────────┬──────────┬──────┐                    ┌─────────┐
//    │ RGB_TOG │   │     │   bRID   │   bRIU   │   tASK   │ fLXP │ RGB_VAD │ RGB_VAI │   │  mprv   │ mply │ mnxt  │  mute  │  vold   │  volu   │          │      │                    │ RGB_TOG │
//    ├─────────┤   ├─────┼──────────┼──────────┼──────────┼──────┼─────────┼─────────┤   ├─────────┼──────┼───────┼────────┼─────────┼─────────┼──────────┴──────┤                    ├─────────┤
//    │         │   │     │ D_C_RGB1 │ D_C_RGB2 │ D_C_RGB3 │      │         │         │   │         │      │ AS_ON │ AS_OFF │ RGB_VAD │ RGB_VAI │                 │                    │         │
//    ├─────────┤   ├─────┼──────────┼──────────┼──────────┼──────┼─────────┼─────────┘   ├─────────┼──────┼───────┼────────┼─────────┼─────────┼──────────┬──────┤                    ├─────────┤
//    │         │   │     │          │          │          │      │         │             │         │      │       │        │         │ RGB_MOD │ RGB_RMOD │ pscr │                    │         │
//    ├─────────┤   ├─────┴──────────┼──────────┼──────────┼──────┼─────────┼─────────┐   ├─────────┼──────┼───────┼────────┼─────────┼─────────┼──────────┴──────┤                    ├─────────┤
//    │         │   │                │          │          │      │         │         │   │         │      │       │        │         │         │                 │                    │   end   │
//    ├─────────┤   ├────────────────┼──────────┼──────────┼──────┼─────────┼─────────┤   ├─────────┼──────┼───────┼────────┼─────────┼─────────┴──────────┬──────┘      ┌──────┐      └─────────┘
//    │         │   │                │          │          │      │         │         │   │ NK_TOGG │      │       │        │         │                    │             │ mply │
//    ├─────────┤   ├─────┬──────────┼──────────┼──────────┼──────┴─────────┴─────────┤   ├─────────┴──────┴───────┼────────┼─────────┼─────────┬──────────┘      ┌──────┼──────┼──────┐
//    │         │   │     │          │          │          │                          │   │                        │        │         │         │                 │ mprv │ mute │ mnxt │
//    └─────────┘   └─────┴──────────┴──────────┴──────────┴──────────────────────────┘   └────────────────────────┴────────┴─────────┴─────────┘                 └──────┴──────┴──────┘
[MEDIA] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , KC_BRID  , KC_BRIU  , KC_TASK  , KC_FLXP , RGB_VAD , RGB_VAI ,     KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE , KC_VOLD , KC_VOLU , _______  , _______ ,                               RGB_TOG,
  _______ ,     _______ , D_C_RGB1 , D_C_RGB2 , D_C_RGB3 , _______ , _______ , _______ ,     _______ , _______ , AS_ON   , AS_OFF  , RGB_VAD , RGB_VAI ,      _______       ,                               _______,
  _______ ,     _______ , _______  , _______  , _______  , _______ , _______ ,               _______ , _______ , _______ , _______ , _______ , RGB_MOD , RGB_RMOD , KC_PSCR ,                               _______,
  _______ ,          _______       , _______  , _______  , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______       ,                               KC_END ,
  _______ ,          _______       , _______  , _______  , _______ , _______ , _______ ,     NK_TOGG , _______ , _______ , _______ , _______ ,      _______       ,                     KC_MPLY                    ,
  _______ ,     _______ , _______  , _______  , _______  ,           _______           ,               _______           , _______ , _______ , _______ ,                      KC_MPRV , KC_MUTE , KC_MNXT
),

//    ┌─────────┐   ┌─────┬─────┬─────┬──────┬──────┬──────┬─────┐   ┌─────┬──────┬──────┬──────┬─────┬─────┬─────┬─────┐                 ┌─────────┐
//    │ RGB_TOG │   │     │     │     │      │      │      │     │   │     │      │      │      │     │     │     │     │                 │ RGB_TOG │
//    ├─────────┤   ├─────┼─────┼─────┼──────┼──────┼──────┼─────┤   ├─────┼──────┼──────┼──────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │     │     │     │      │      │      │     │   │     │      │      │      │     │     │           │                 │         │
//    ├─────────┤   ├─────┼─────┼─────┼──────┼──────┼──────┼─────┘   ├─────┼──────┼──────┼──────┼─────┼─────┼─────┬─────┤                 ├─────────┤
//    │         │   │     │  q  │  w  │  e   │  r   │  t   │         │  y  │  u   │  i   │  o   │  p  │     │     │     │                 │         │
//    ├─────────┤   ├─────┴─────┼─────┼──────┼──────┼──────┼─────┐   ├─────┼──────┼──────┼──────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │           │  a  │ LC_S │ LG_D │ LA_F │  g  │   │  h  │ RA_J │ RG_K │ RC_L │     │     │           │                 │         │
//    ├─────────┤   ├───────────┼─────┼──────┼──────┼──────┼─────┤   ├─────┼──────┼──────┼──────┼─────┼─────┴─────┬─────┘     ┌─────┐     └─────────┘
//    │         │   │           │  z  │  x   │  c   │  v   │  b  │   │  n  │  m   │  ,   │  .   │     │           │           │     │
//    ├─────────┤   ├─────┬─────┼─────┼──────┼──────┴──────┴─────┤   ├─────┴──────┴──────┼──────┼─────┼─────┬─────┘     ┌─────┼─────┼─────┐
//    │         │   │     │     │     │      │                   │   │                   │      │     │     │           │     │     │     │
//    └─────────┘   └─────┴─────┴─────┴──────┴───────────────────┘   └───────────────────┴──────┴─────┴─────┘           └─────┴─────┴─────┘
[MAIN] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               RGB_TOG,
  _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,     _______ , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,               KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , _______ , _______ , _______ ,                               _______,
  _______ ,          _______      , KC_A    , LC_S    , LG_D    , LA_F    , KC_G    ,     KC_H    , RA_J    , RG_K    , RC_L    , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,     KC_N    , KC_M    , KC_COMM , KC_DOT  , _______ ,      _______      ,                     _______                    ,
  _______ ,     _______ , _______ , _______ , _______ ,           _______           ,               _______           , _______ , _______ , _______ ,                     _______ , _______ , _______
),

//    ┌─────────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐                 ┌─────────┐
//    │ RGB_TOG │   │     │     │     │     │     │     │     │   │     │     │     │     │     │     │     │     │                 │ RGB_TOG │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │     │     │     │     │     │     │     │   │     │     │     │     │     │     │           │                 │         │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┘   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┤                 ├─────────┤
//    │         │   │     │  !  │  @  │  #  │  $  │  %  │         │  ^  │  &  │  *  │  `  │  ~  │     │     │     │                 │         │
//    ├─────────┤   ├─────┴─────┼─────┼─────┼─────┼─────┼─────┐   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │           │ ""  │  [  │  {  │  (  │     │   │  /  │  -  │  =  │  :  │  ;  │     │           │                 │         │
//    ├─────────┤   ├───────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┘     ┌─────┐     └─────────┘
//    │         │   │           │  '  │  ]  │  }  │  )  │     │   │  \  │  _  │  +  │  |  │  ?  │           │           │     │
//    ├─────────┤   ├─────┬─────┼─────┼─────┼─────┴─────┴─────┤   ├─────┴─────┴─────┼─────┼─────┼─────┬─────┘     ┌─────┼─────┼─────┐
//    │         │   │     │     │     │     │                 │   │                 │     │     │     │           │     │     │     │
//    └─────────┘   └─────┴─────┴─────┴─────┴─────────────────┘   └─────────────────┴─────┴─────┴─────┘           └─────┴─────┴─────┘
[LEFT] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               RGB_TOG,
  _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,     _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,               KC_CIRC , KC_AMPR , KC_ASTR , KC_GRV  , KC_TILD , _______ , _______ , _______ ,                               _______,
  _______ ,          _______      , KC_DQT  , KC_LBRC , KC_LCBR , KC_LPRN , _______ ,     KC_SLSH , KC_MINS , KC_EQL  , KC_COLN , KC_SCLN , _______ ,      _______      ,                               _______,
  _______ ,          _______      , KC_QUOT , KC_RBRC , KC_RCBR , KC_RPRN , _______ ,     KC_BSLS , KC_UNDS , KC_PLUS , KC_PIPE , KC_QUES ,      _______      ,                     _______                    ,
  _______ ,     _______ , _______ , _______ , _______ ,           _______           ,               _______           , _______ , _______ , _______ ,                     _______ , _______ , _______
),

//    ┌─────────┐   ┌─────┬─────┬─────┬─────┬──────┬─────┬─────┐   ┌─────┬──────┬──────┬──────┬──────┬─────┬─────┬─────┐                 ┌─────────┐
//    │ RGB_TOG │   │     │     │     │     │      │     │     │   │     │      │      │      │      │     │     │     │                 │ RGB_TOG │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼──────┼─────┼─────┤   ├─────┼──────┼──────┼──────┼──────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │     │     │     │     │      │     │     │   │     │      │      │      │      │     │           │                 │         │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼──────┼─────┼─────┘   ├─────┼──────┼──────┼──────┼──────┼─────┼─────┬─────┤                 ├─────────┤
//    │         │   │     │  1  │  2  │  3  │  4   │  5  │         │  6  │  7   │  8   │  9   │  0   │     │     │     │                 │         │
//    ├─────────┤   ├─────┴─────┼─────┼─────┼──────┼─────┼─────┐   ├─────┼──────┼──────┼──────┼──────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │           │ del │     │ pscr │ ins │     │   │     │ left │ down │  up  │ rght │     │           │                 │         │
//    ├─────────┤   ├───────────┼─────┼─────┼──────┼─────┼─────┤   ├─────┼──────┼──────┼──────┼──────┼─────┴─────┬─────┘     ┌─────┐     └─────────┘
//    │         │   │           │  '  │  ]  │  }   │  )  │     │   │  \  │ home │ pgdn │ pgup │ end  │           │           │     │
//    ├─────────┤   ├─────┬─────┼─────┼─────┼──────┴─────┴─────┤   ├─────┴──────┴──────┼──────┼──────┼─────┬─────┘     ┌─────┼─────┼─────┐
//    │         │   │     │     │     │     │                  │   │                   │      │      │     │           │     │     │     │
//    └─────────┘   └─────┴─────┴─────┴─────┴──────────────────┘   └───────────────────┴──────┴──────┴─────┘           └─────┴─────┴─────┘
[RIGHT] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               RGB_TOG,
  _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,     _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,               KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ , _______ , _______ ,                               _______,
  _______ ,          _______      , KC_DEL  , _______ , KC_PSCR , KC_INS  , _______ ,     _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ ,      _______      ,                               _______,
  _______ ,          _______      , KC_QUOT , KC_RBRC , KC_RCBR , KC_RPRN , _______ ,     KC_BSLS , KC_HOME , KC_PGDN , KC_PGUP , KC_END  ,      _______      ,                     _______                    ,
  _______ ,     _______ , _______ , _______ , _______ ,           _______           ,               _______           , _______ , _______ , _______ ,                     _______ , _______ , _______
),

//    ┌─────────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐                 ┌─────────┐
//    │ RGB_TOG │   │     │     │     │     │     │     │     │   │     │     │     │     │     │     │     │     │                 │ RGB_TOG │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │     │     │     │     │     │     │     │   │     │     │     │     │     │     │           │                 │         │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┘   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┤                 ├─────────┤
//    │         │   │     │     │     │     │     │     │         │     │     │     │     │     │     │     │     │                 │         │
//    ├─────────┤   ├─────┴─────┼─────┼─────┼─────┼─────┼─────┐   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │           │     │     │     │     │     │   │     │     │     │     │     │     │           │                 │         │
//    ├─────────┤   ├───────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┘     ┌─────┐     └─────────┘
//    │         │   │           │     │     │     │     │     │   │     │     │     │     │     │           │           │     │
//    ├─────────┤   ├─────┬─────┼─────┼─────┼─────┴─────┴─────┤   ├─────┴─────┴─────┼─────┼─────┼─────┬─────┘     ┌─────┼─────┼─────┐
//    │         │   │     │     │     │     │                 │   │                 │     │     │     │           │     │     │     │
//    └─────────┘   └─────┴─────┴─────┴─────┴─────────────────┘   └─────────────────┴─────┴─────┴─────┘           └─────┴─────┴─────┘
[ADJUST] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               RGB_TOG,
  _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,               _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               _______,
  _______ ,          _______      , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ ,      _______      ,                     _______                    ,
  _______ ,     _______ , _______ , _______ , _______ ,           _______           ,               _______           , _______ , _______ , _______ ,                     _______ , _______ , _______
)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MEDIA] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [MAIN] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LEFT] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [RIGHT] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [ADJUST] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif // ENCODER_MAP_ENABLE

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_touch_typing_simple);
}
#endif

/*
qmk:json:start
{
  "layout": [
  "x _ x x x x x x x _ x x x x x x x x _ _ _ x",
  "x _ x x x x x x x _ x x x x x x x^x _ _ _ x",
  "x _ x x x x x x _ _ x x x x x x x x _ _ _ x",
  "x _ x^x x x x x x _ x x x x x x x^x _ _ _ x",
  "x _ x^x x x x x x _ x x x x x x^x _ _ x _ _",
  "x _ x x x x xx^xx _ xx^xx x x x _ _ x x x _"
  ]
}
qmk:json:end
*/
