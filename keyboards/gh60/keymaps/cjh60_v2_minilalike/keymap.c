#include QMK_KEYBOARD_H

// Fillers to make layering more clear
#define _______ KC_TRNS
#define __      KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: qwerty */
  LAYOUT_CJH_V2(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,
    KC_TAB , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_ESC , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, __,      KC_ENT ,
    KC_LSFT, __,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
    KC_LALT, KC_LGUI, KC_LCTL,                   KC_SPC,  KC_SPC,  F(0),    KC_RALT, KC_BSPC, KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT
  ),
  /* 1: fn */
  LAYOUT_CJH_V2(
    KC_TILD, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL ,
    _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS, KC_BSLS, KC_PIPE, _______,
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_CIRC, KC_GRV , __     , _______,
    _______, __     , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_UNDS, KC_MINS, KC_EQL , _______, _______, _______, KC_PGUP,
    KC_CAPS, KC_INS , _______,                   _______, _______, _______, _______, KC_DEL , _______, KC_HOME, KC_PGDN, KC_END
  ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [1] = ACTION_LAYER_TOGGLE   (2),  // toggle arrow overlay
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
