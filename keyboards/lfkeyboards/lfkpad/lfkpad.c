#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "lfkpad.h"
#include "keymap.h"
#include <issi/is31fl3731.h>
// #include "TWIlib.h"
// #include "lighting.h"
#include "debug.h"
#include "quantum.h"

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
  {0, C9_9 , C8_9 , C7_9 }, // 25
  {0, C9_10, C8_10, C7_10}, // 26
  {0, C9_11, C8_11, C7_11}, // 27
  {0, C9_12, C8_12, C7_12}, // 28

  {0, C1_1 , C3_2 , C4_2 }, // 1
  {0, C1_9 , C3_10, C4_10}, // 17
  {0, C1_10, C2_10, C4_11}, // 18
  {0, C1_15, C2_15, C3_15}, // 23

  {0, C1_2 , C2_2 , C4_3 }, // 2
  {0, C1_11, C2_11, C3_11}, // 19
  {0, C1_14, C2_14, C3_14}, // 22
  {0, C1_16, C2_16, C3_16}, // 24

  {0, C1_3 , C2_3 , C3_3 }, // 3
  {0, C1_6 , C2_6 , C3_6 }, // 6
  {0, C9_1 , C8_1 , C7_1 }, // 9

  {0, C1_4 , C2_4 , C3_4 }, // 4
  {0, C1_7 , C2_7 , C3_7 }, // 7
  {0, C9_2 , C8_2 , C7_2 }, // 10
  {0, C9_3 , C8_3 , C7_3 }, // 11

  {0, C1_5 , C2_5 , C3_5 }, // 5
  {0, C1_8 , C2_8 , C3_8 }, // 8
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |               modifier
 *    |              |                 | */
    {{0|(0<<4)},   {44.8*0, 21*0}, 0},
    {{0|(1<<4)},   {44.8*0, 21*1}, 0},
    {{0|(2<<4)},   {44.8*0, 21*2}, 0},
    {{0|(3<<4)},   {44.8*0, 21*3}, 0},

    {{1|(0<<4)},   {44.8*1, 21*0}, 0},
    {{1|(1<<4)},   {44.8*1, 21*1}, 0},
    {{1|(2<<4)},   {44.8*1, 21*2}, 0},
    {{1|(3<<4)},   {44.8*1, 21*3}, 0},

    {{2|(0<<4)},   {44.8*2, 21*0}, 0},
    {{2|(1<<4)},   {44.8*2, 21*1}, 0},
    {{2|(2<<4)},   {44.8*2, 21*2}, 0},
    {{2|(3<<4)},   {44.8*2, 21*3}, 0},

    {{3|(0<<4)},   {44.8*3, 21*0}, 0},
    {{3|(1<<4)},   {44.8*3, 21*1}, 0},
    {{3|(2<<4)},   {44.8*3, 21*2}, 0},

    {{4|(0<<4)},   {44.8*4, 21*0}, 0},
    {{4|(1<<4)},   {44.8*4, 21*1}, 0},
    {{4|(2<<4)},   {44.8*4, 21*2}, 0},
    {{4|(3<<4)},   {44.8*4, 21*3}, 0},

    {{5|(0<<4)},   {44.8*5, 21*0}, 0},
    {{5|(1<<4)},   {44.8*5, 21*1}, 0},
};


void matrix_init_kb(void)
{
    matrix_init_user();
#ifndef AUDIO_ENABLE
    // If we're not using the audio pin, drive it low
    sbi(DDRC, 6);
    cbi(PORTC, 6);
#endif

#ifdef ISSI_ENABLE
    issi_init();
#endif
#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif
}

void matrix_scan_kb(void)
{
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif
#ifdef ISSI_ENABLE
    // switch/underglow lighting update
    static uint32_t issi_device = 0;
    static uint32_t twi_last_ready = 0;
    if(twi_last_ready > 1000){
        // Its been way too long since the last ISSI update, reset the I2C bus and start again
        dprintf("TWI failed to recover, TWI re-init\n");
        twi_last_ready = 0;
        TWIInit();
        force_issi_refresh();
    }
    if(isTWIReady()){
        twi_last_ready = 0;
        // If the i2c bus is available, kick off the issi update, alternate between devices
        update_issi(issi_device, issi_device);
        if(issi_device){
            issi_device = 0;
        }else{
            issi_device = 3;
        }
    }else{
        twi_last_ready++;
    }
#endif
    matrix_scan_user();
}

void click(uint16_t freq, uint16_t duration){
#ifdef AUDIO_ENABLE
    if(freq >= 100 && freq <= 20000 && duration < 100){
        play_note(freq, 10);
        for (uint16_t i = 0; i < duration; i++){
            _delay_ms(1);
        }
        stop_all_notes();
    }
#endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    if (click_toggle && record->event.pressed){
        click(click_hz, click_time);
    }
    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
    return process_record_user(keycode, record);
}

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
#ifdef AUDIO_ENABLE
    int8_t sign = 1;
#endif
    if(id == LFK_ESC_TILDE){
        // Send ~ on shift-esc
        void (*method)(uint8_t) = (event->event.pressed) ? &add_key : &del_key;
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        if(layer_state == 0){
            method(shifted ? KC_GRAVE : KC_ESCAPE);
        }else{
            method(shifted ? KC_ESCAPE : KC_GRAVE);
        }
        send_keyboard_report();
    }else if(event->event.pressed){
        switch(id){
            case LFK_SET_DEFAULT_LAYER:
                // set/save the current base layer to eeprom, falls through to LFK_CLEAR
                eeconfig_update_default_layer(1UL << opt);
                default_layer_set(1UL << opt);
            case LFK_CLEAR:
                // Go back to default layer
                layer_clear();
                break;
#ifdef AUDIO_ENABLE
            case LFK_CLICK_FREQ_LOWER:
                sign = -1;  // continue to next statement
            case LFK_CLICK_FREQ_HIGHER:
                click_hz += sign * 100;
                click(click_hz, click_time);
                break;
            case LFK_CLICK_TOGGLE:
                if(click_toggle){
                    click_toggle = 0;
                    click(4000, 100);
                    click(1000, 100);
                }else{
                    click_toggle = 1;
                    click(1000, 100);
                    click(4000, 100);
                }
                break;
            case LFK_CLICK_TIME_SHORTER:
                sign = -1;  // continue to next statement
            case LFK_CLICK_TIME_LONGER:
                click_time += sign;
                click(click_hz, click_time);
                break;
#endif
        }
    }
}

void reset_keyboard_kb(){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    reset_keyboard();
}

void led_set_kb(uint8_t usb_led)
{
    led_set_user(usb_led);
}

// LFK lighting info
const uint8_t rgb_matrices[] = {0, 1};
const uint8_t rgb_sequence[] = {
    32,  1,  2,  3,
    31, 30,  5,  6,
    28, 27,  7,
    17, 18,  9,  8,
    19, 21, 11,
      22,   14, 12,

    16,         26,
     4,         25,
    13,         24,
          20

};
