#include QMK_KEYBOARD_H

// readability
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_numpad_6x4( /* Base */
    KC_ESC,   KC_TAB,   F(0),     KC_BSPC, \
    KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS, \
    KC_P7,    KC_P8,    KC_P9,             \
    KC_P4,    KC_P5,    KC_P6,    KC_PPLS, \
    KC_P1,    KC_P2,    KC_P3,             \
    KC_P0,              KC_PDOT,  KC_PENT  \
  ),

  [1] = LAYOUT_numpad_6x4(
     _______, KC_CALC, _______,  _______, \
     KC_CALC, KC_COPY, _______,  KC_PSTE, \
     RGB_SPI, RGB_VAI, RGB_SAI,           \
     RGB_HUD, RGB_TOG, RGB_HUI,  _______, \
     RGB_SPD, RGB_VAD, RGB_SAD,           \
     RGB_MOD,          RGB_RMOD, _______  \
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
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {
    // This keymap only has a single base layer, so reset the default if needed
    if(eeconfig_read_default_layer() > 1){
        eeconfig_update_default_layer(1);
        default_layer_set(1);
    }
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
