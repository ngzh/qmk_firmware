#include QMK_KEYBOARD_H

// Fillers to make layering more clear
#define _______ KC_TRNS
#define __      KC_NO

enum custom_keycodes {
    KVM_PC1 = SAFE_RANGE,
    KVM_PC2,
    KVM_PC3,
    KVM_PC4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: qwerty */
  LAYOUT_CJH_V2(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_ESC , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, __,      KC_ENT ,
    KC_LSFT, __,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, __,      KC_RSFT,
    KC_LALT, KC_LGUI, KC_LCTL,                   KC_SPC,  F(1),    KC_SPC,  F(0),    __,      KC_RALT, KC_APP,  KC_RCTL, __
  ),
  /* 1: fn */
  LAYOUT_CJH_V2(
    KC_TILD, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL ,
    _______, KC_EXLM, KC_1   , KC_2   , KC_3   , KC_PERC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS, KC_BSLS, KC_PIPE, _______,
    _______, KC_0   , KC_4   , KC_5   , KC_6   , KC_DLR , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_CIRC, KC_GRV , __     , _______,
    _______, __     , KC_AT,   KC_7   , KC_8   , KC_9   , KC_HASH, KC_UNDS, KC_MINS, KC_EQL , _______, _______, __     , KC_PGUP,
    KC_HOME, KC_END , _______,                   _______, _______, _______, _______, __     , KC_CAPS, KC_INS , KC_PGDN, __
  ),
  /* keyboard functions */
  LAYOUT_CJH_V2(
    RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______,
    RGB_MOD, _______, _______, _______, KVM_PC4, KVM_PC3, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KVM_PC2, KVM_PC1, _______, _______, _______, _______, _______, __     , _______, _______,
    _______, __     , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, __     , _______,
    KC_CAPS, KC_SLCK, _______,                   _______, _______, _______, _______, __     , _______, _______, _______, __
  ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [1] = ACTION_LAYER_MOMENTARY(2),  // toggle arrow overlay
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch(keycode) {
        case KVM_PC3:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_TAP(X_SCROLLLOCK) SS_TAP(X_KP_3));
                SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_TAP(X_SCROLLLOCK) SS_TAP(X_KP_3));
                SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_TAP(X_SCROLLLOCK) SS_TAP(X_KP_3));
            } else {
            }
            break;
        case KVM_PC4:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_TAP(X_SCROLLLOCK) SS_TAP(X_KP_4));
                SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_TAP(X_SCROLLLOCK) SS_TAP(X_KP_4));
                SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_TAP(X_SCROLLLOCK) SS_TAP(X_KP_4));
            } else {
            }
            break;
    }
    return true;
};

void matrix_scan_user(void) {
//Layer LED indicators
};
