#include QMK_KEYBOARD_H

#define __      KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  /* 0: qwerty */
  LAYOUT_CJH_V2(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, __,      KC_ENT,
    KC_LSFT, __,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, __,      KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,  F(1),    KC_SPC,  F(0),    __,      KC_RALT, KC_APP,  KC_RCTL, _______
  ),
  /* 1: fn */
  LAYOUT_CJH_V2(
    KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 , KC_DEL ,
    _______, _______, KC_1   , KC_2   , KC_3   , _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______,
    _______, KC_0   , KC_4   , KC_5   , KC_6   , _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_GRV , __     , _______,
    _______, __     , _______, KC_7   , KC_8   , KC_9   , _______, _______, _______, _______, _______, _______, __     , _______,
    _______, _______, _______,                   _______, _______, _______, _______, __     , _______, _______, KC_INS , _______
  ),
  /* keyboard functions */
  LAYOUT_CJH_V2(
    RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______,
    RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, __     , _______, _______,
    _______, __     , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, __     , _______,
    _______, _______, _______,                   _______, _______, _______, _______, __     , _______, _______, _______, __
  ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [1] = ACTION_LAYER_MOMENTARY(2),  // toggle arrow overlay
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

void matrix_scan_user(void) {
//Layer LED indicators
};
