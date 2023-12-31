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
    MAIN,
    LEFT,
    RIGHT,
    ADJUST,
    BASE,
    MEDIA
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

#define TAB_L LT(LEFT, KC_TAB)
#define TAB_R LT(RIGHT, KC_TAB)

#define SFT_F MT(MOD_LSFT, KC_F)
#define CTL_D MT(MOD_LCTL, KC_D)
#define ALT_S MT(MOD_LALT, KC_S)
#define GUI_A MT(MOD_LGUI, KC_A)
#define SFT_J MT(MOD_RSFT, KC_J)
#define CTL_K MT(MOD_RCTL, KC_K)
#define ALT_L MT(MOD_LALT, KC_L)
#define GUI_SLCN MT(MOD_RGUI, KC_SCLN)
#define SFT_SPC MT(MOD_LSFT, KC_SPC) 

#define KC_COPY LCTL(KC_INSERT)
#define KC_PASTE LSFT(KC_INSERT)

#define OSM_LS OSM(MOD_LSFT)
#define OSM_RS OSM(MOD_RSFT)
#define OSM_RA OSM(MOD_RALT)

enum dein0s_keycodes {
    D_C_RGB1 = SAFE_RANGE, // Dein0s_Custom_RGB1
    D_C_RGB2, // Dein0s_Custom_RGB1
    D_C_RGB3 // Dein0s_Custom_RGB1
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TAB_L:
            if (!record->tap.count && record->event.pressed) {
                set_oneshot_layer(LEFT, ONESHOT_START);
                return false;
            }
            return true;
        case TAB_R:
            if (!record->tap.count && record->event.pressed) {
                set_oneshot_layer(RIGHT, ONESHOT_START);
                return false;
            }
            return true;
        case D_C_RGB1:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_colored_layers);
            }
            return false; // Skip all further processing of this key
        case D_C_RGB2:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_colored_layers_breathing);
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



// base layer
const uint16_t PROGMEM combo_layer_media_toggle[] = {KC_LCTL, MO(MEDIA), COMBO_END};
// main layer
const uint16_t PROGMEM combo_layer_base_activate[] = {QK_GESC, SFT_SPC, COMBO_END};
const uint16_t PROGMEM combo_layer_toggle_left[] = {KC_LALT, TAB_L, COMBO_END};
const uint16_t PROGMEM combo_layer_toggle_right[] = {OSM_RA, TAB_R, COMBO_END};
const uint16_t PROGMEM combo_layer_shot_adjust[] = {TAB_L, TAB_R, COMBO_END};
const uint16_t PROGMEM combo_layer_toggle_adjust[] = {TAB_L, TAB_R, KC_ENT, COMBO_END};

const uint16_t PROGMEM combo_mod_ralt_shot[] = {ALT_S, ALT_L, COMBO_END};
const uint16_t PROGMEM combo_mod_caps_toggle[] = {GUI_A, GUI_SLCN, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_layer_media_toggle, TG(MEDIA)),
    COMBO(combo_layer_base_activate, TO(BASE)),
    COMBO(combo_layer_toggle_left, TG(LEFT)),
    COMBO(combo_layer_toggle_right, TG(RIGHT)),
    COMBO(combo_layer_shot_adjust, OSL(ADJUST)),
    COMBO(combo_layer_toggle_adjust, TG(ADJUST)),
    COMBO(combo_mod_caps_toggle, KC_CAPS),
    COMBO(combo_mod_ralt_shot, OSM(MOD_RALT))};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌──────────┐   ┌─────────┬────┬───────┬───────┬───────┬───────┬────┐   ┌────┬───────┬───────┬───────┬──────────┬──────┬────┬────┐              ┌──────┐
//    │ RGB_TOG  │   │   no    │ f1 │  f2   │  f3   │  f4   │  f5   │ f6 │   │ f7 │  f8   │  f9   │  f10  │   f11    │ f12  │ no │ no │              │ mute │
//    ├──────────┤   ├─────────┼────┼───────┼───────┼───────┼───────┼────┤   ├────┼───────┼───────┼───────┼──────────┼──────┼────┴────┤              ├──────┤
//    │   MC_1   │   │ QK_GESC │ 1  │   2   │   3   │   4   │   5   │ 6  │   │ 7  │   8   │   9   │   0   │    no    │  no  │   no    │              │  no  │
//    ├──────────┤   ├─────────┴────┼───────┼───────┼───────┼───────┼────┤   ├────┼───────┼───────┼───────┼──────────┼──────┼────┬────┤              ├──────┤
//    │   MC_2   │   │     tab      │   q   │   w   │   e   │   r   │ t  │   │ y  │   u   │   i   │   o   │    p     │  no  │ no │ no │              │  no  │
//    ├──────────┤   ├──────────────┼───────┼───────┼───────┼───────┼────┤   ├────┼───────┼───────┼───────┼──────────┼──────┼────┴────┤              ├──────┤
//    │   MC_3   │   │     lctl     │ GUI_A │ ALT_S │ CTL_D │ SFT_F │ g  │   │ h  │ SFT_J │ CTL_K │ ALT_L │ GUI_SLCN │ bspc │   no    │              │  no  │
//    ├──────────┤   ├──────────────┼───────┼───────┼───────┼───────┼────┤   ├────┼───────┼───────┼───────┼──────────┼──────┴────┬────┘    ┌────┐    └──────┘
//    │   MC_4   │   │    OSM_LS    │   z   │   x   │   c   │   v   │ b  │   │ n  │   m   │   ,   │   .   │    /     │    ent    │         │ no │            
//    ├──────────┤   ├─────────┬────┼───────┼───────┼───────┴───────┴────┤   ├────┴───────┴───────┼───────┼──────────┼──────┬────┘    ┌────┼────┼────┐       
//    │ TO(BASE) │   │   no    │ no │ lalt  │ TAB_R │      SFT_SPC       │   │        bspc        │ TAB_L │  OSM_RA  │  no  │         │ no │ no │ no │       
//    └──────────┘   └─────────┴────┴───────┴───────┴────────────────────┘   └────────────────────┴───────┴──────────┴──────┘         └────┴────┴────┘       
[MAIN] = LAYOUT_91_ansi(
  RGB_TOG  ,     XXXXXXX , KC_F1   , KC_F2   , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,     KC_F7 , KC_F8 , KC_F9   , KC_F10 , KC_F11   , KC_F12  , XXXXXXX , XXXXXXX ,                               KC_MUTE,
  MC_1     ,     QK_GESC , KC_1    , KC_2    , KC_3  , KC_4  , KC_5  , KC_6  ,     KC_7  , KC_8  , KC_9    , KC_0   , XXXXXXX  , XXXXXXX ,      XXXXXXX      ,                               XXXXXXX,
  MC_2     ,          KC_TAB       , KC_Q    , KC_W  , KC_E  , KC_R  , KC_T  ,     KC_Y  , KC_U  , KC_I    , KC_O   , KC_P     , XXXXXXX , XXXXXXX , XXXXXXX ,                               XXXXXXX,
  MC_3     ,          KC_LCTL      , GUI_A   , ALT_S , CTL_D , SFT_F , KC_G  ,     KC_H  , SFT_J , CTL_K   , ALT_L  , GUI_SLCN , KC_BSPC ,      XXXXXXX      ,                               XXXXXXX,
  MC_4     ,          OSM_LS       , KC_Z    , KC_X  , KC_C  , KC_V  , KC_B  ,     KC_N  , KC_M  , KC_COMM , KC_DOT , KC_SLSH  ,      KC_ENT       ,                     XXXXXXX                    ,
  TO(BASE) ,     XXXXXXX , XXXXXXX , KC_LALT , TAB_R ,        SFT_SPC        ,             KC_BSPC         , TAB_L  , OSM_RA   , XXXXXXX ,                     XXXXXXX , XXXXXXX , XXXXXXX          
),

//    ┌─────────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐                 ┌─────────┐
//    │ RGB_TOG │   │     │     │     │     │     │     │     │   │     │     │     │     │     │     │     │     │                 │ RGB_TOG │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │     │     │     │     │     │     │     │   │     │     │     │     │     │     │           │                 │         │
//    ├─────────┤   ├─────┴─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┤                 ├─────────┤
//    │         │   │           │     │  `  │ ""  │  {  │  [  │   │     │     │     │     │     │     │     │     │                 │         │
//    ├─────────┤   ├───────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │           │  |  │  ~  │  '  │  }  │  ]  │   │     │     │     │     │     │     │           │                 │         │
//    ├─────────┤   ├───────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┘     ┌─────┐     └─────────┘
//    │         │   │           │  \  │  +  │  =  │  _  │  -  │   │     │     │     │     │     │           │           │     │                
//    ├─────────┤   ├─────┬─────┼─────┼─────┼─────┴─────┴─────┤   ├─────┴─────┴─────┼─────┼─────┼─────┬─────┘     ┌─────┼─────┼─────┐          
//    │         │   │     │     │     │     │                 │   │                 │     │     │     │           │     │     │     │          
//    └─────────┘   └─────┴─────┴─────┴─────┴─────────────────┘   └─────────────────┴─────┴─────┴─────┘           └─────┴─────┴─────┘          
[LEFT] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               RGB_TOG,
  _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , _______ , KC_GRV  , KC_DQT  , KC_LCBR , KC_LBRC ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               _______,
  _______ ,          _______      , KC_PIPE , KC_TILD , KC_QUOT , KC_RCBR , KC_RBRC ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , KC_BSLS , KC_PLUS , KC_EQL  , KC_UNDS , KC_MINS ,     _______ , _______ , _______ , _______ , _______ ,      _______      ,                     _______                    ,
  _______ ,     _______ , _______ , _______ , _______ ,           _______           ,               _______           , _______ , _______ , _______ ,                     _______ , _______ , _______          
),

//    ┌─────────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐   ┌──────┬───────┬──────┬──────┬──────┬─────┬─────┬─────┐                 ┌─────────┐
//    │ RGB_TOG │   │     │     │     │     │     │     │     │   │      │       │      │      │      │     │     │     │                 │ RGB_TOG │
//    ├─────────┤   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤   ├──────┼───────┼──────┼──────┼──────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │     │     │     │     │     │     │     │   │      │       │      │      │      │     │           │                 │         │
//    ├─────────┤   ├─────┴─────┼─────┼─────┼─────┼─────┼─────┤   ├──────┼───────┼──────┼──────┼──────┼─────┼─────┬─────┤                 ├─────────┤
//    │         │   │           │     │     │     │     │     │   │ copy │ paste │ ins  │ del  │ pscr │     │     │     │                 │         │
//    ├─────────┤   ├───────────┼─────┼─────┼─────┼─────┼─────┤   ├──────┼───────┼──────┼──────┼──────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │           │     │     │     │     │     │   │ left │ down  │  up  │ rght │      │     │           │                 │         │
//    ├─────────┤   ├───────────┼─────┼─────┼─────┼─────┼─────┤   ├──────┼───────┼──────┼──────┼──────┼─────┴─────┬─────┘     ┌─────┐     └─────────┘
//    │         │   │           │     │     │     │     │     │   │ home │ pgdn  │ pgup │ end  │      │           │           │     │                
//    ├─────────┤   ├─────┬─────┼─────┼─────┼─────┴─────┴─────┤   ├──────┴───────┴──────┼──────┼──────┼─────┬─────┘     ┌─────┼─────┼─────┐          
//    │         │   │     │     │     │     │                 │   │         esc         │      │      │     │           │     │     │     │          
//    └─────────┘   └─────┴─────┴─────┴─────┴─────────────────┘   └─────────────────────┴──────┴──────┴─────┘           └─────┴─────┴─────┘          
[RIGHT] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______  , _______   , _______ , _______ , _______ , _______ , _______ ,                               RGB_TOG,
  _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______  , _______   , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , _______ , _______ , _______ , _______ , _______ ,     KC_COPY , KC_PASTE , KC_INSERT , KC_DEL  , KC_PSCR , _______ , _______ , _______ ,                               _______,
  _______ ,          _______      , _______ , _______ , _______ , _______ , _______ ,     KC_LEFT , KC_DOWN  , KC_UP     , KC_RGHT , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , _______ , _______ , _______ , _______ , _______ ,     KC_HOME , KC_PGDN  , KC_PGUP   , KC_END  , _______ ,      _______      ,                     _______                    ,
  _______ ,     _______ , _______ , _______ , _______ ,           _______           ,                 KC_ESC             , _______ , _______ , _______ ,                     _______ , _______ , _______          
),

//    ┌─────────┐   ┌─────┬─────┬──────────┬──────────┬──────────┬─────┬─────┐   ┌──────┬──────┬──────┬──────┬─────┬─────┬─────┬─────┐                 ┌─────────┐
//    │ RGB_TOG │   │     │     │          │          │          │     │     │   │      │      │      │      │     │     │     │     │                 │ RGB_TOG │
//    ├─────────┤   ├─────┼─────┼──────────┼──────────┼──────────┼─────┼─────┤   ├──────┼──────┼──────┼──────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │     │     │          │          │          │     │     │   │      │      │      │      │     │     │           │                 │         │
//    ├─────────┤   ├─────┴─────┼──────────┼──────────┼──────────┼─────┼─────┤   ├──────┼──────┼──────┼──────┼─────┼─────┼─────┬─────┤                 ├─────────┤
//    │         │   │           │ D_C_RGB1 │ D_C_RGB2 │ D_C_RGB3 │     │     │   │      │      │      │      │     │     │     │     │                 │         │
//    ├─────────┤   ├───────────┼──────────┼──────────┼──────────┼─────┼─────┤   ├──────┼──────┼──────┼──────┼─────┼─────┼─────┴─────┤                 ├─────────┤
//    │         │   │           │          │          │          │     │     │   │ mprv │ mute │ mply │ mnxt │     │     │           │                 │         │
//    ├─────────┤   ├───────────┼──────────┼──────────┼──────────┼─────┼─────┤   ├──────┼──────┼──────┼──────┼─────┼─────┴─────┬─────┘     ┌─────┐     └─────────┘
//    │         │   │           │          │          │          │     │     │   │      │      │      │      │     │           │           │     │                
//    ├─────────┤   ├─────┬─────┼──────────┼──────────┼──────────┴─────┴─────┤   ├──────┴──────┴──────┼──────┼─────┼─────┬─────┘     ┌─────┼─────┼─────┐          
//    │         │   │     │     │          │          │                      │   │                    │      │     │     │           │     │     │     │          
//    └─────────┘   └─────┴─────┴──────────┴──────────┴──────────────────────┘   └────────────────────┴──────┴─────┴─────┘           └─────┴─────┴─────┘          
[ADJUST] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , _______ , _______  , _______  , _______  , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               RGB_TOG,
  _______ ,     _______ , _______ , _______  , _______  , _______  , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , D_C_RGB1 , D_C_RGB2 , D_C_RGB3 , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                               _______,
  _______ ,          _______      , _______  , _______  , _______  , _______ , _______ ,     KC_MPRV , KC_MUTE , KC_MPLY , KC_MNXT , _______ , _______ ,      _______      ,                               _______,
  _______ ,          _______      , _______  , _______  , _______  , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ ,      _______      ,                     _______                    ,
  _______ ,     _______ , _______ , _______  , _______  ,           _______            ,               _______           , _______ , _______ , _______ ,                     _______ , _______ , _______          
),

//    ┌──────────┐   ┌──────┬──────┬──────┬────────────┬────┬────┬────┐   ┌────┬────┬────┬───────────┬────────┬──────┬─────┬─────┐                    ┌──────┐
//    │   mute   │   │ esc  │  f1  │  f2  │     f3     │ f4 │ f5 │ f6 │   │ f7 │ f8 │ f9 │    f10    │  f11   │ f12  │ ins │ del │                    │ mute │
//    ├──────────┤   ├──────┼──────┼──────┼────────────┼────┼────┼────┤   ├────┼────┼────┼───────────┼────────┼──────┼─────┴─────┤                    ├──────┤
//    │ TO(MAIN) │   │  `   │  1   │  2   │     3      │ 4  │ 5  │ 6  │   │ 7  │ 8  │ 9  │     0     │   -    │  =   │   bspc    │                    │ pgup │
//    ├──────────┤   ├──────┴──────┼──────┼────────────┼────┼────┼────┤   ├────┼────┼────┼───────────┼────────┼──────┼─────┬─────┤                    ├──────┤
//    │   MC_2   │   │     tab     │  q   │     w      │ e  │ r  │ t  │   │ y  │ u  │ i  │     o     │   p    │  [   │  ]  │  \  │                    │ pgdn │
//    ├──────────┤   ├─────────────┼──────┼────────────┼────┼────┼────┤   ├────┼────┼────┼───────────┼────────┼──────┼─────┴─────┤                    ├──────┤
//    │   MC_3   │   │    caps     │  a   │     s      │ d  │ f  │ g  │   │ h  │ j  │ k  │     l     │   ;    │  '   │    ent    │                    │ home │
//    ├──────────┤   ├─────────────┼──────┼────────────┼────┼────┼────┤   ├────┼────┼────┼───────────┼────────┼──────┴─────┬─────┘      ┌──────┐      └──────┘
//    │   MC_4   │   │    lsft     │  z   │     x      │ c  │ v  │ b  │   │ n  │ m  │ ,  │     .     │   /    │    rsft    │            │  up  │              
//    ├──────────┤   ├──────┬──────┼──────┼────────────┼────┴────┴────┤   ├────┴────┴────┼───────────┼────────┼──────┬─────┘     ┌──────┼──────┼──────┐       
//    │ TO(BASE) │   │ lctl │ lgui │ lalt │ MO(ADJUST) │     spc      │   │     bspc     │ MO(MEDIA) │ OSM_RA │ rctl │           │ left │ down │ rght │       
//    └──────────┘   └──────┴──────┴──────┴────────────┴──────────────┘   └──────────────┴───────────┴────────┴──────┘           └──────┴──────┴──────┘       
[BASE] = LAYOUT_91_ansi(
  KC_MUTE  ,     KC_ESC  , KC_F1   , KC_F2   , KC_F3      , KC_F4 , KC_F5 , KC_F6 ,     KC_F7 , KC_F8 , KC_F9   , KC_F10    , KC_F11  , KC_F12  , KC_INS  , KC_DEL  ,                               KC_MUTE,
  TO(MAIN) ,     KC_GRV  , KC_1    , KC_2    , KC_3       , KC_4  , KC_5  , KC_6  ,     KC_7  , KC_8  , KC_9    , KC_0      , KC_MINS , KC_EQL  ,      KC_BSPC      ,                               KC_PGUP,
  MC_2     ,          KC_TAB       , KC_Q    , KC_W       , KC_E  , KC_R  , KC_T  ,     KC_Y  , KC_U  , KC_I    , KC_O      , KC_P    , KC_LBRC , KC_RBRC , KC_BSLS ,                               KC_PGDN,
  MC_3     ,          KC_CAPS      , KC_A    , KC_S       , KC_D  , KC_F  , KC_G  ,     KC_H  , KC_J  , KC_K    , KC_L      , KC_SCLN , KC_QUOT ,      KC_ENT       ,                               KC_HOME,
  MC_4     ,          KC_LSFT      , KC_Z    , KC_X       , KC_C  , KC_V  , KC_B  ,     KC_N  , KC_M  , KC_COMM , KC_DOT    , KC_SLSH ,      KC_RSFT      ,                     KC_UP                      ,
  TO(BASE) ,     KC_LCTL , KC_LWIN , KC_LALT , MO(ADJUST) ,        KC_SPC         ,             KC_BSPC         , MO(MEDIA) , OSM_RA  , KC_RCTL ,                     KC_LEFT , KC_DOWN , KC_RGHT          
),

//    ┌─────────┐   ┌─────┬──────────┬──────────┬──────────┬──────┬─────────┬─────────┐   ┌─────────┬──────┬───────┬────────┬─────────┬─────────┬──────────┬──────┐                    ┌─────────┐
//    │ RGB_TOG │   │     │   bRID   │   bRIU   │   tASK   │ fLXP │ RGB_VAD │ RGB_VAI │   │  mprv   │ mply │ mnxt  │  mute  │  vold   │  volu   │          │      │                    │ RGB_TOG │
//    ├─────────┤   ├─────┼──────────┼──────────┼──────────┼──────┼─────────┼─────────┤   ├─────────┼──────┼───────┼────────┼─────────┼─────────┼──────────┴──────┤                    ├─────────┤
//    │         │   │     │ D_C_RGB1 │ D_C_RGB2 │ D_C_RGB3 │      │         │         │   │         │      │ AS_ON │ AS_OFF │ RGB_VAD │ RGB_VAI │                 │                    │         │
//    ├─────────┤   ├─────┴──────────┼──────────┼──────────┼──────┼─────────┼─────────┤   ├─────────┼──────┼───────┼────────┼─────────┼─────────┼──────────┬──────┤                    ├─────────┤
//    │         │   │                │          │          │      │         │         │   │         │      │       │        │         │ RGB_MOD │ RGB_RMOD │ pscr │                    │         │
//    ├─────────┤   ├────────────────┼──────────┼──────────┼──────┼─────────┼─────────┤   ├─────────┼──────┼───────┼────────┼─────────┼─────────┼──────────┴──────┤                    ├─────────┤
//    │         │   │                │          │          │      │         │         │   │         │      │       │        │         │         │                 │                    │   end   │
//    ├─────────┤   ├────────────────┼──────────┼──────────┼──────┼─────────┼─────────┤   ├─────────┼──────┼───────┼────────┼─────────┼─────────┴──────────┬──────┘      ┌──────┐      └─────────┘
//    │         │   │                │          │          │      │         │         │   │ NK_TOGG │      │       │        │         │                    │             │ mply │                 
//    ├─────────┤   ├─────┬──────────┼──────────┼──────────┼──────┴─────────┴─────────┤   ├─────────┴──────┴───────┼────────┼─────────┼─────────┬──────────┘      ┌──────┼──────┼──────┐          
//    │         │   │     │          │          │          │                          │   │                        │        │         │         │                 │ mprv │ mute │ mnxt │          
//    └─────────┘   └─────┴──────────┴──────────┴──────────┴──────────────────────────┘   └────────────────────────┴────────┴─────────┴─────────┘                 └──────┴──────┴──────┘          
[MEDIA] = LAYOUT_91_ansi(
  RGB_TOG ,     _______ , KC_BRID  , KC_BRIU  , KC_TASK  , KC_FLXP , RGB_VAD , RGB_VAI ,     KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE , KC_VOLD , KC_VOLU , _______  , _______ ,                               RGB_TOG,
  _______ ,     _______ , D_C_RGB1 , D_C_RGB2 , D_C_RGB3 , _______ , _______ , _______ ,     _______ , _______ , AS_ON   , AS_OFF  , RGB_VAD , RGB_VAI ,      _______       ,                               _______,
  _______ ,          _______       , _______  , _______  , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , RGB_MOD , RGB_RMOD , KC_PSCR ,                               _______,
  _______ ,          _______       , _______  , _______  , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ ,      _______       ,                               KC_END ,
  _______ ,          _______       , _______  , _______  , _______ , _______ , _______ ,     NK_TOGG , _______ , _______ , _______ , _______ ,      _______       ,                     KC_MPLY                    ,
  _______ ,     _______ , _______  , _______  , _______  ,           _______           ,               _______           , _______ , _______ , _______ ,                      KC_MPRV , KC_MUTE , KC_MNXT          
)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAIN] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LEFT] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [RIGHT] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [ADJUST] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [BASE] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MEDIA] = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
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
  "x _ x^x x x x x x _ x x x x x x x x _ _ _ x",
  "x _ x^x x x x x x _ x x x x x x x^x _ _ _ x",
  "x _ x^x x x x x x _ x x x x x x^x _ _ x _ _",
  "x _ x x x x xx^xx _ xx^xx x x x _ _ x x x _"
  ]
}
qmk:json:end
*/

