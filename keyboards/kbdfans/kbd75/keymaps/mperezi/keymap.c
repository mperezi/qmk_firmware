#include QMK_KEYBOARD_H

#include "keymap_spanish.h"

enum layer_names {
  _ISO,
  _ANSI
};

#define FN_TILDE  TD(TD_TILDE)
#define FN_AT     TD(TD_AT)
#define FN_DOLLAR TD(TD_DOLLAR)
#define FN_PIPE   TD(TD_PIPE)
#define FN_EXCL   TD(TD_EXCL)

#define L_CLCK    LSFT_T(KC_CAPS)
#define R_CLCK    RSFT_T(KC_CAPS)

#define ES_BLSH   ALGR(KC_NUBS)

// Tap Dance Definitions
enum tapdance {
  TD_TILDE,
  TD_AT,
  TD_DOLLAR,
  TD_PIPE,
  TD_EXCL,
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
    // Tap once for i, twice for !
    case FN_EXCL:
      if (count == 1) {
        SEND_STRING(SS_TAP(X_I));
      } else {
        SEND_STRING(SS_RSFT(SS_TAP(X_1)));
      }
      break;
  }
  reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TILDE] = ACTION_TAP_DANCE_FN(tap_dance_fn),
  [TD_AT] = ACTION_TAP_DANCE_FN(tap_dance_fn),
  [TD_DOLLAR] = ACTION_TAP_DANCE_FN(tap_dance_fn),
  [TD_PIPE] = ACTION_TAP_DANCE_FN(tap_dance_fn),
  [TD_EXCL] = ACTION_TAP_DANCE_FN(tap_dance_fn),
};

/* https://docs.qmk.fm/#/feature_led_indicators?id=example-led_update_user-implementation */
bool led_update_user(led_t led_state) {
    static uint8_t prev_caps_state = 0;
    static uint8_t saved_mode = 0;
    static HSV saved_hsv = { 0, 0, 0 };

    if (prev_caps_state != led_state.caps_lock) {
      if (led_state.caps_lock != 0) {
        saved_mode = rgblight_get_mode();
        saved_hsv = rgblight_get_hsv();
        rgblight_mode(RGBLIGHT_MODE_BREATHING + 3);
        rgblight_sethsv_red();
      } else {
        rgblight_mode(saved_mode);
        rgblight_sethsv(saved_hsv.h, saved_hsv.s, saved_hsv.v);
      }
      prev_caps_state = led_state.caps_lock;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: ISO ES */
  [_ISO] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_SLCK,  KC_PSCR,    KC_INS,
    ES_BLSH,  ES_1,     ES_2,     ES_3,     ES_4,     ES_5,     ES_6,     ES_7,     ES_8,     ES_9,     ES_0,     ES_QUOT,  ES_IEXL,  KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   ES_Q,     ES_W,     ES_E,     ES_R,     ES_T,     ES_Y,     ES_U,     ES_I,     ES_O,     ES_P,     ES_GRV,   ES_PLUS,  ES_RCBR,            KC_DEL,
    LT(_ANSI, KC_ESC),   ES_A,     ES_S,     ES_D,     ES_F,     ES_G,     ES_H,     ES_J,     ES_K,     ES_L,     FN_TILDE, ES_ACUT,                      KC_ENT,   RGB_HUI,
    KC_LSFT,   KC_GRV,   ES_Z,     ES_X,     ES_C,     ES_V,     ES_B,     ES_N,     ES_M,     ES_COMM,  ES_DOT,   ES_MINS,  R_CLCK,            KC_UP,    RGB_SAI,
    KC_LCTL,  KC_LALT,  KC_LGUI,                   KC_SPC,   KC_SPC,  KC_SPC,                           KC_LGUI,  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /* 1: ANSI */
  [_ANSI] = LAYOUT(
    _______,   _______,     _______,     _______,     _______,     _______,     _______,     _______,          _______,         _______,         _______,           _______,  _______,   _______,   _______,   _______,
    _______,   _______,     _______,     _______,     _______,     _______,     _______,     _______,          RSFT(ES_8),      RSFT(ES_9),      _______,           _______,  _______,   _______,   RESET,     _______,
    _______,   _______,     _______,     _______,     _______,     _______,     _______,     LALT(ES_ACUT),    LALT(ES_RCBR),   LALT(ES_GRV),    LALT(ES_PLUS),     _______,  _______,   _______,              _______,
    _______,   LALT(ES_2),  RSFT(ES_4),  _______,     _______,     _______,     KC_LEFT,     KC_DOWN,          KC_UP,           KC_RGHT,         _______,           _______,                        _______,   RGB_HUD,
    _______,   _______,     _______,     _______,     _______,     _______,     _______,     _______,          _______,         _______,         _______,           _______,  _______,              RGB_VAI,   RGB_SAD,
    _______,   _______,     _______,                          _______,   _______,   _______,                                                     _______,           _______,  _______,   RGB_RMOD,  RGB_VAD,   RGB_MOD
  ),
};
