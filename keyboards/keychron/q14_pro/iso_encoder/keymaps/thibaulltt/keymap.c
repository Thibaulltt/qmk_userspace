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
#include "keymap_french_afnor.h"

enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  USR_FN1,
};

// clang-format off
/* Here's a rough ascii sketch of the keyboard, straightened up (as the Alice layout
 * is split and angled in the middle to be more ergonomic). The keys should roughly
 * match up with their actual position on the keyboard.
 *
 * The layout presented here is as close to the French AFNOR layout as possible.
 * Here are a few special keys:
 * - ROT: rotary encoder ;
 * - PSN: print screen ;
 * - X-B: extra B key, might be used later for function layers ;
 * - RAL: right alt (Alt-Gr) ;
 * - FN1: function key to layer 1 ;
 * - TGL: toggle, for RGB-related stuff.
 *
 ******************************************************************************************************************************************************
 * ╔═════╗ ╔═════╦═════╦═════╗  ╔═════╗ ╔═════╦═════╦═════╦═════╗ ╔═════╦═════╗       ╔═════╦═════╗ ╔═════╦═════╦═════╦═════╗  ╔═════╗   ╔═════╗      *
 * ║ ROT ║ ║  󰒮  ║ 󰐎   ║ 󰒭   ║  ║ ESC ║ ║ F1  ║ F2  ║ F3  ║ F4  ║ ║ F5  ║ F6  ║       ║ F7  ║ F8  ║ ║ F9  ║ F10 ║ F11 ║ F12 ║  ║ DEL ║   ║ TGL ║      *
 * ╚═════╝ ╚═════╩═════╩═════╝  ╚═════╝ ╚═════╩═════╩═════╩═════╝ ╚═════╩═════╝       ╚═════╩═════╝ ╚═════╩═════╩═════╩═════╝  ╚═════╝   ╚═════╝      *
 * ╔═════╦═════╦═════╗ ╔═════╗   ╔═════╗ ╔═════╦═════╦═════╦═════╦═════╦═════╗          ╔═════╦═════╦═════╦═════╗ ╔═════╦═════╗ ╔═══════════╗ ╔═════╗ *
 * ║NUMLK║  /  ║  *  ║ ║  -  ║   ║  `  ║ ║ 1 à ║ 2 é ║ 3 è ║ 4 ê ║ 5 ( ║ 6 ) ║          ║ 7 ‘ ║ 8 ’ ║ 9 « ║ 0 » ║ ║ " ' ║ ¨ ^ ║ ║ BACKSPACE ║ ║ PSN ║ *
 * ╚═════╩═════╩═════╝ ╚═════╝   ╚═════╝ ╚═════╩═════╩═════╩═════╩═════╩═════╝          ╚═════╩═════╩═════╩═════╝ ╚═════╩═════╝ ╚═══════════╝ ╚═════╝ *
 * ╔═════╦═════╦═════╗ ╔═════╗  ╔══════╗ ╔═════╦═════╦═════╦═════╦═════╗          ╔═════╦═════╦═════╦═════╦═════╗ ╔═════╦═════╗ ╔═══════════╗ ╔═════╗ *
 * ║  7  ║  8  ║  9  ║ ║ NUM ║  ║ TAB  ║ ║  A  ║  Z  ║  E  ║  R  ║  T  ║          ║  Y  ║  U  ║  I  ║  O  ║  P  ║ ║ – - ║ ± + ║ ║ CARRIAGE  ║ ║ PUP ║ *
 * ╚═════╩═════╩═════╝ ║ PAD ║  ╚══════╝ ╚═════╩═════╩═════╩═════╩═════╝          ╚═════╩═════╩═════╩═════╩═════╝ ╚═════╩═════╝ ╚═══╗       ║ ╚═════╝ *
 * ╔═════╦═════╦═════╗ ║     ║  ╔══════════╗ ╔═════╦═════╦═════╦═════╦═════╗          ╔═════╦═════╦═════╦═════╗ ╔═════╦═════╦═════╗ ║  RET  ║ ╔═════╗ *
 * ║  4  ║  5  ║  6  ║ ║  +  ║  ║ CAPSLOCK ║ ║  Q  ║  S  ║  D  ║  F  ║  G  ║          ║  H  ║  J  ║  K  ║  L  ║ ║  M  ║ \ / ║ ½ * ║ ║  URN  ║ ║ PDN ║ *
 * ╚═════╩═════╩═════╝ ╚═════╝  ╚══════════╝ ╚═════╩═════╩═════╩═════╩═════╝          ╚═════╩═════╩═════╩═════╝ ╚═════╩═════╩═════╝ ╚═══════╝ ╚═════╝ *
 * ╔═════╦═════╦═════╗ ╔═════╗  ╔══════╗ ╔═════╦═════╦═════╦═════╦═════╦═════╗  ╔═════╦═════╦═════╦═════╦═════╗ ╔═════╦════════════════╗              *
 * ║  1  ║  2  ║  3  ║ ║ NUM ║  ║ LSHFT║ ║ < > ║  W  ║  X  ║  C  ║  V  ║  B  ║  ║ X-B ║  N  ║ ? . ║ ! , ║ … : ║ ║ = ; ║  RIGHT  SHIFT  ║ ╔═════╗      *
 * ╚═════╩═════╩═════╝ ║ PAD ║  ╚══════╝ ╚═════╩═════╩═════╩═════╩═════╩═════╝  ╚═════╩═════╩═════╩═════╩═════╝ ╚═════╩════════════════╝ ║ ⬆   ║      *
 * ╔═══════════╦═════╗ ║     ║  ╔═══════╦═══════╗ ╔═════╦═════════════╦═════╗    ╔════════════════════╦═════╦═════╗                ╔═════╬═════╬═════╗*
 * ║   NUM 0   ║  .  ║ ║ RET ║  ║ LCTRL ║ SUPER ║ ║ ALT ║    SPACE    ║ FN1 ║    ║    RIGHT  SPACE    ║ RAL ║RCTRL║                ║ ⬅   ║ ⬇   ║ ➡   ║*
 * ╚═══════════╩═════╝ ╚═════╝  ╚═══════╩═══════╝ ╚═════╩═════════════╩═════╝    ╚════════════════════╩═════╩═════╝                ╚═════╩═════╩═════╝*
 ******************************************************************************************************************************************************
 */
// clang-format on

/*
#define FR_EACU KC_2    // é
#define FR_EGRV KC_3    // è
#define FR_ECIR KC_4    // ê
#define FR_LPRN KC_5    // (
#define FR_RPRN KC_6    // )
#define FR_LSQU KC_7    // ‘
#define FR_RSQU KC_8    // ’
#define FR_LDAQ KC_9    // «
#define FR_RDAQ KC_0    // »
#define FR_QUOT KC_MINS // '
#define FR_DCIR KC_EQL  // ^ (dead)

*/
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_106_iso(
        KC_MUTE,  KC_F13,   KC_F14,   KC_F15,    KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             RGB_MOD,
        KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,   KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_P7,    KC_P8,    KC_P9,    KC_PPLS,   KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGDN,
        KC_P4,    KC_P5,    KC_P6,               KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,   KC_HOME,
        KC_P1,    KC_P2,    KC_P3,    KC_PENT,   KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        KC_P0,              KC_PDOT,             KC_LCTL,  KC_LOPTN,           KC_LCMMD,           KC_SPC,   MO(MAC_FN),         KC_SPC,             KC_RCMMD, KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),
    [MAC_FN] = LAYOUT_106_iso(
        RGB_TOG,  _______,  _______,  _______,   _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            RGB_TOG,
        _______,  _______,  _______,  _______,   _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,   RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,             _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,            _______,             _______,  _______,            _______,            _______,  _______,            _______,            _______,  _______,            _______,  _______,  _______),
    [WIN_BASE] = LAYOUT_106_iso(
        KC_MUTE,  _______,  _______,  _______,   KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             RGB_MOD,
        KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,   FR_AT,    FR_AGRV,  FR_EACU,  FR_EGRV,  FR_ECIR,  FR_LPRN,  FR_RPRN,  FR_LSQU,  FR_RSQU,  FR_LDAQ,  FR_RDAQ,  FR_QUOT,  FR_DCIR,  KC_BSPC,            KC_PGUP,
        KC_P7,    KC_P8,    KC_P9,    KC_PPLS,   KC_TAB,   FR_A,     FR_Z,     FR_E,     FR_R,     FR_T,     FR_Y,     FR_U,     FR_I,     FR_O,     FR_P,     FR_MINS,  FR_PLUS,                      KC_PGDN,
        KC_P4,    KC_P5,    KC_P6,               KC_CAPS,  FR_Q,     FR_S,     FR_D,     FR_F,     FR_G,               FR_H,     FR_J,     FR_K,     FR_L,     FR_M,     FR_SLSH,  FR_ASTR,  KC_ENT,   KC_HOME,
        KC_P1,    KC_P2,    KC_P3,    KC_PENT,   KC_LSFT,  KC_NUBS,  FR_Z,     FR_X,     FR_C,     FR_V,     FR_B,     FR_B,     FR_N,     FR_DOT,   FR_COMM,  FR_COLN,  FR_SCLN,  KC_RSFT,  KC_UP,
        KC_P0,              KC_PDOT,             KC_LCTL,  KC_LWIN,            KC_LALT,  KC_SPC,   MO(WIN_FN),                   KC_SPC,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),
    [WIN_FN] = LAYOUT_106_iso(
        RGB_TOG,  _______,  _______,  _______,   _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT, KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            RGB_TOG,
        _______,  _______,  _______,  _______,   _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,   _______,  _______,            _______,
        _______,  _______,  _______,  _______,   RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______, _______,  _______,   _______,                      _______,
        _______,  _______,  _______,             _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,            _______,  _______,  _______, _______,  _______,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  NK_TOGG,  _______, _______,  _______,   _______,  _______,  _______,
        _______,            _______,             _______,  _______,            _______,            _______,  _______,            _______,           _______,  _______,             _______,  _______,  _______),
    [USR_FN1] = LAYOUT_106_iso(
        RGB_TOG,  _______,  _______,  _______,   _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT, KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            RGB_TOG,
        _______,  _______,  _______,  _______,   _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,   _______,  _______,            _______,
        _______,  _______,  _______,  _______,   RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______, _______,  _______,   _______,                      _______,
        _______,  _______,  _______,             _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,            _______,  _______,  _______, _______,  _______,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  NK_TOGG,  _______, _______,  _______,   _______,  _______,  _______,
        _______,            _______,             _______,  _______,            _______,            _______,  _______,            _______,           _______,  _______,             _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [USR_FN1]  = {ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
};
#endif // ENCODER_MAP_ENABLE
