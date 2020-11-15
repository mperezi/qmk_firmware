#include QMK_KEYBOARD_H

#include "keymap_spanish.h"

enum layer_names {
  _QW,
  _CL
};

#define FN_TILDE  TD(TD_TILDE)
#define FN_AT     TD(TD_AT)
#define FN_DOLLAR TD(TD_DOLLAR)
#define FN_PIPE   TD(TD_PIPE)

#define L_CLCK    LSFT_T(KC_CAPS)
#define R_CLCK    RSFT_T(KC_CAPS)

// Tap Dance Definitions
enum tapdance {
  TD_TILDE,
  TD_AT,
  TD_DOLLAR,
  TD_PIPE,
};

void tap_dance_fn(qk_tap_dance_state_t *state, void *user_data) {
  int count = state->count;
  switch (state->keycode) {
    // Tap once for ñ, twice for ~, three times for ~/
    case FN_TILDE:
      if (count == 1) {
        SEND_STRING(SS_TAP(X_SCOLON));
      } else if (count == 2)  {
        SEND_STRING(SS_ALGR(SS_TAP(X_SCOLON)) SS_TAP(X_SPC));
      } else if (count == 3) {
        SEND_STRING(SS_ALGR(SS_TAP(X_SCOLON)) SS_RSFT(SS_TAP(X_7)));
      }
      break;
    // Tap once for a, twice for @
    case FN_AT:
      if (count == 1) {
        SEND_STRING(SS_TAP(X_A));
      } else {
        SEND_STRING(SS_ALGR(SS_TAP(X_2)));
      }
      break;
    // Tap once for s, twice for $
    case FN_DOLLAR:
      if (count == 1) {
        SEND_STRING(SS_TAP(X_S));
      } else {
        SEND_STRING(SS_RSFT(SS_TAP(X_4)));
      }
      break;
    // Tap once for l, twice for |
    case FN_PIPE:
      if (count == 1) {
        SEND_STRING(SS_TAP(X_L));
      } else {
        SEND_STRING(SS_ALGR(SS_TAP(X_1)));
      }
      break;
  }
  reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TILDE] = ACTION_TAP_DANCE_FN(tap_dance_fn),
  [TD_AT] = ACTION_TAP_DANCE_FN(tap_dance_fn),
  [TD_DOLLAR] = ACTION_TAP_DANCE_FN(tap_dance_fn),
  [TD_PIPE] = ACTION_TAP_DANCE_FN(tap_dance_fn)
};

uint8_t saved_rgb_mode;

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case L_CLCK:
    case R_CLCK:
        if (record->event.pressed) {
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                rgblight_mode(saved_rgb_mode);
            } else {
                saved_rgb_mode = rgblight_get_mode();
                rgblight_mode(RGBLIGHT_MODE_BREATHING + 3);
                rgblight_sethsv_orange();
            }
        }
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: QWERTY */
  [_QW] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  MO(1),    KC_DEL,
    KC_GRV,   ES_1,     ES_2,     ES_3,     ES_4,     ES_5,     ES_6,     ES_7,     ES_8,     ES_9,     ES_0,     ES_QUOT,  ES_IEXL,  KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   ES_Q,     ES_W,     ES_E,     ES_R,     ES_T,     ES_Y,     ES_U,     ES_I,     ES_O,     ES_P,     ES_LBRC,  ES_RBRC,  ES_RCBR,            KC_PGUP,
    KC_ESC,   FN_AT,    FN_DOLLAR,ES_D,     ES_F,     ES_G,     ES_H,     ES_J,     ES_K,     FN_PIPE,  FN_TILDE, ES_LCBR,                      KC_ENT,   KC_PGDN,
    L_CLCK,   MO(1),    ES_Z,     ES_X,     ES_C,     ES_V,     ES_B,     ES_N,     ES_M,     ES_COMM,  ES_DOT,   ES_MINS,  R_CLCK,             KC_UP,    KC_END,
    KC_LCTL,  KC_LALT,  KC_LGUI,                   KC_SPC,   LT(_CL, KC_SPC),   KC_SPC,                 KC_LGUI,  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /* 1: Custom */
  [_CL] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET,    _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  BL_DEC,   BL_TOGG,  BL_INC,   BL_STEP,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  ),
};
