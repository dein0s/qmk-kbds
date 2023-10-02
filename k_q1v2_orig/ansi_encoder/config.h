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

#pragma once

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 45
#define DRIVER_2_LED_TOTAL 37
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
/* #define ENABLE_RGB_MATRIX_SOLID_SPLASH */
/* #undef ENABLE_RGB_MATRIX_SOLID_SPLASH */

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 45

// dein0s AutoShift
/* #define AUTO_SHIFT_TIMEOUT 240 */
/* #define NO_AUTO_SHIFT_SPECIAL */

// dein0s disable RGB animations
/* #undef ENABLE_RGB_MATRIX_BREATHING */

// dein0s tap-hold
// #define TAPPING_TERM 240

// dein0s combos
#define COMBO_ONLY_FROM_LAYER 0

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
