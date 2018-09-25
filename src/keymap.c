#include QMK_KEYBOARD_H

#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum {
    LAYER_MAIN = 0,
    LAYER_NUMBERS,
    LAYER_MACROS,
    LAYER_BLANK
};

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    EPRM,
    VRSN,
    RGB_AEGRN,
    PHP_ARROW,
    M_GIT,
    M_CLEAR,
    M_CBLCK,
    M_CC,
    M_PUSH,
    M_EXIT
};

//Tap Dance Declarations
enum {
    TD_ESC_CAPS = 0,
    TD_LEFT_HOME,
    TD_DOWN_PGDN,
    TD_UP_PGUP,
    TD_RIGHT_END,
};

#define MK_LCSHFT LCTL(KC_LSHIFT)
#define MK_ADQUO  ALT_T(KC_DQUO)
#define MK_TERM   LCTL(LALT(KC_T))
#define TD_LFTHM  TD(TD_LEFT_HOME)
#define TD_DNPGDN TD(TD_DOWN_PGDN)
#define TD_UPPGUP TD(TD_UP_PGUP)
#define TD_RTEND  TD(TD_RIGHT_END)

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Esc, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
    [TD_DOWN_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
    [TD_UP_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
    [TD_RIGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_END),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /** Keymap 0: Basic layer
     *
     * ,--------------------------------------------------.         ,--------------------------------------------------.
     * |   F12  |   1  |   2  |   3  |   4  |   5  |  [   |         |   ]  |   6  |   7  |   8  |   9  |   0  |   -    |
     * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  |  {   |         |  }   |   Y  |   U  |   I  |   O  |   P  |   \    |
     * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
     * |CtrlShft|   A  |   S  |   D  |   F  |   G  |------|         |------|   H  |   J  |   K  |   L  |   '  | Enter  |
     * |--------+------+------+------+------+------|  (   |         |  )   |------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |      |         |      |   N  |   M  |   ,  |   .  |   /  | RShift |
     * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
     *   | Ctrl |  Gui |  Alt | `/```|   =  |                                     |   $  | Left | Down |  Up  | Right|
     *   `----------------------------------'                                     `----------------------------------'
     *                                        ,-------------.     ,-------------.
     *                                        |  -   | Esc  |     | Del  |  ->  |
     *                                 ,------|------|------|     |------+------+------.
     *                                 |      |      | TT1  |     |      |      |      |
     *                                 | Space|Enter |------|     |------|  ;   |Space |
     *                                 |      |      | TT2  |     |  "   |      |      |
     *                                 `--------------------'     `--------------------'
     */
    [LAYER_MAIN] = LAYOUT_ergodox(
            KC_F12,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_LBRC,
            KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LCBR,
            MK_LCSHFT,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
            KC_LSHIFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LPRN,
            KC_LCTL,    KC_LGUI,  KC_LALT,  M_CBLCK,  KC_EQUAL,
                                                                KC_MINUS, KC_ESCAPE,
                                                                          TT(1),
                                                    KC_SPACE,   KC_ENTER, TT(2),

            KC_RBRC,    KC_6,     KC_7,     KC_8,      KC_9,      KC_0,       KC_BSPACE,
            KC_RCBR,    KC_Y,     KC_U,     KC_I,      KC_O,      KC_P,       KC_BSLASH,
                        KC_H,     KC_J,     KC_K,      KC_L,      KC_QUOTE,   KC_ENTER,
            KC_RPRN,    KC_N,     KC_M,     KC_COMMA,  KC_DOT,    KC_SLASH,   KC_RSHIFT,
                                  KC_DLR,   TD_LFTHM,  TD_DNPGDN, TD_UPPGUP,  TD_RTEND,
            KC_DELETE,  PHP_ARROW,
            _______,
            KC_DQUO,    KC_SCLN,  KC_SPACE
      ),

    /** Keymap 1: Symbols & Numbers
     *
     * ,--------------------------------------------------.         ,--------------------------------------------------.
     * | On/Off |      |      |  F10 |  F11 |  F12 |      |         |  -   |  *   |  /   |  Num |      |      |        |
     * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
     * | Animat |      |      |  F7  |  F8  |  F9  |      |         |  +   |  7   |  8   |  9   |      |      |        |
     * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
     * |        |      |      |  F4  |  F5  |  F6  |------|         |------|  4   |  5   |  6   |      |      |        |
     * |--------+------+------+------+------+------|      |         | Enter|------+------+------+------+------+--------|
     * |                  |      |      |  F1  |  F2  |  F3  |      |         |      |  1   |  2   |  3   |      |      |        |
     * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
     *   |      | Dim  |Bright| Hue- | Hue+ |                                     |  0   |  .   |      |      |      |
     *   `----------------------------------'                                     `----------------------------------'
     *                                        ,-------------.     ,-------------.
     *                                        |      |      |     |      |      |
     *                                 ,------|------|------|     |------+------+------.
     *                                 |      |      |      |     |      |      |      |
     *                                 |      |      |------|     |------|      |      |
     *                                 |      |      |      |     |      |      |      |
     *                                 `--------------------'     `--------------------'
     */
    [LAYER_NUMBERS] = LAYOUT_ergodox(
            RGB_TOG,    _______,  _______,  KC_F10,   KC_F11,   KC_F12,   _______,
            RGB_MOD,    _______,  _______,  KC_F7,    KC_F8,    KC_F9,    _______,
            RGB_AEGRN,  _______,  _______,  KC_F4,    KC_F5,    KC_F6,
            RGB_SAI,    _______,  _______,  KC_F1,    KC_F2,    KC_F3,    _______,
            RGB_SAD,    RGB_VAD,  RGB_VAI,  RGB_HUD,  RGB_HUI,
                                                              _______,  _______,
                                                                        _______,
                                                    _______,  _______,  _______,

            KC_PMNS,  KC_PAST,  KC_PSLS,  KC_NLCK,  _______,  _______,  _______,
            KC_PPLS,  KC_P7,    KC_P8,    KC_P9,    _______,  _______,  _______,
                      KC_P4,    KC_P5,    KC_P6,    _______,  _______,  _______,
            KC_PENT,  KC_P1,    KC_P2,    KC_P3,    _______,  _______,  _______,
                                KC_P0,    KC_PDOT,  _______,  _______,  _______,
            _______,  _______,
            _______,
            _______,  _______,  _______
      ),

    /** Keymap 2: Macros
     *
     * ,--------------------------------------------------.         ,--------------------------------------------------.
     * |        |      |      |      |  CC# |      |      |         |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
     * |        |      |      | Exit |      | Term |      |         |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
     * |        |      |      |      |      | Git  |------|         |------|      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
     * |        |      |      |Clear |      | Push |      |         |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                     |      |      |      |      |      |
     *   `----------------------------------'                                     `----------------------------------'
     *                                        ,-------------.     ,-------------.
     *                                        |      |      |     |      |      |
     *                                 ,------|------|------|     |------+------+------.
     *                                 |      |      |      |     |      |      |      |
     *                                 |      |      |------|     |------|      |      |
     *                                 |      |      |      |     |      |      |      |
     *                                 `--------------------'     `--------------------'
     */
    [LAYER_MACROS] = LAYOUT_ergodox(
            _______, _______, _______, _______, M_CC,    _______, _______,
            _______, _______, _______, M_EXIT,  _______, MK_TERM, _______,
            _______, _______, _______, _______, _______, M_GIT,
            _______, _______, _______, M_CLEAR, _______, M_PUSH, _______,
            _______, _______, _______, _______, _______,
                                                         _______, _______,
                                                                  _______,
                                                _______, _______, _______,

            // right hand
            _______,  _______, _______, _______, _______, _______, _______,
            _______,  _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______, _______,
            _______,  _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,
            _______,  _______,
            _______,
            _______,  _______, _______
       ),

    /** Keymap Blank
     *
     * ,--------------------------------------------------.          ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |         |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |         |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |------|         |------|      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |         |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                     |      |      |      |      |      |
     *   `----------------------------------'                                     `----------------------------------'
     *                                        ,-------------.     ,-------------.
     *                                        |      |      |     |      |      |
     *                                 ,------|------|------|     |------+------+------.
     *                                 |      |      |      |     |      |      |      |
     *                                 |      |      |------|     |------|      |      |
     *                                 |      |      |      |     |      |      |      |
     *                                 `--------------------'     `--------------------'
     */
    [LAYER_BLANK] = LAYOUT_ergodox(
            _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______,
                                                         _______, _______,
                                                                  _______,
                                                _______, _______, _______,

            // right hand
            _______,  _______, _______, _______, _______, _______, _______,
            _______,  _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______, _______,
            _______,  _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,
            _______,  _______,
            _______,
            _______,  _______, _______
       ),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case 0:
            if (record->event.pressed) {
              SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            break;
    }
    return MACRO_NONE;
};

void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t code_timer;

    if (record->event.pressed) {
        code_timer = timer_read();
        switch (keycode) {
            // dynamically generate these.
            case EPRM:
                eeconfig_init();
                return false;
            case VRSN:
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
            case RGB_AEGRN:
                rgblight_mode(1);
                rgblight_sethsv_noeeprom(105, 57, 69);
                return false;
            case PHP_ARROW:
                SEND_STRING("->");
                return false;
            case M_GIT:
                SEND_STRING("git commit -am \"");
                return false;
            case M_CLEAR:
                SEND_STRING("clear\n");
                return false;
            case M_CC:
                // Test card
                SEND_STRING("4111111111111111");
                return false;
            case M_PUSH:
                SEND_STRING("git push origin HEAD\n");
                return false;
            case M_EXIT:
                SEND_STRING(SS_LCTRL("ad"));
                return false;
            case M_CBLCK:
                SEND_STRING("`");
                return false;
        }
    }
    else {
          if (timer_elapsed(code_timer) > TAPPING_TERM) {
              switch (keycode) {
                  case M_CBLCK:
                      // Hold
                      SEND_STRING("``");
                      return true;
              }
          }
          else {
            // Tap
          }
    }
    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 0:
            #ifdef RGBLIGHT_COLOR_LAYER_0
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
            #endif
            break;
        case 1:
            ergodox_right_led_1_on();
            #ifdef RGBLIGHT_COLOR_LAYER_1
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
            #endif
            break;
        case 2:
            ergodox_right_led_2_on();
            #ifdef RGBLIGHT_COLOR_LAYER_2
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
            #endif
            break;
        case 3:
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_3
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
            #endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            #ifdef RGBLIGHT_COLOR_LAYER_4
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
            #endif
        break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_5
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
            #endif
        break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_6
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
            #endif
        break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_7
              rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
            #endif
            break;
        default:
            break;
    }
    return state;
};
