#include QMK_KEYBOARD_H

enum layer_names {
    _QW,
	_CL
};


#define L_SQBRC   LALT(KC_LBRC)
#define R_SQBRC   LALT(KC_RBRC)
#define L_BRC     LALT(KC_QUOT)
#define R_BRC     LALT(KC_BSLS)

#define FN_TILDE  TD(TD_TILDE)
#define FN_AT     TD(TD_AT)
#define FN_DOLLAR TD(TD_DOLLAR)
#define FN_PIPE   TD(TD_PIPE)

#define L_CLCK    LSFT_T(KC_CAPS)
#define R_CLCK    RSFT_T(KC_CAPS)

// Tap Dance Definitions
enum tapdance {
    TD_TILDE = 0,
	TD_AT,
	TD_DOLLAR,
	TD_PIPE,
};

/* void dance_tap_with_mod_key_finished(qk_tap_dance_state_t *state, void *user_data) { */
void dance_tap_double_mod_finished(uint8_t count, uint16_t kc1, uint16_t kc2, uint16_t kc_mod) {
	if (count == 1) {
		register_code16(kc1);
	} else {
		register_code16(kc_mod);
		register_code16(kc2);
	}
}

void dance_tap_double_mod_reset(uint8_t count, uint16_t kc1, uint16_t kc2, uint16_t kc_mod) {
	if (count == 1) {
		unregister_code16(kc1);
	} else {
		unregister_code16(kc_mod);
		unregister_code16(kc2);
	}
}

void dance_tilde_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_finished(state->count, KC_SCLN, KC_SCLN, KC_ALGR);
}

void dance_tilde_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_reset(state->count, KC_SCLN, KC_SCLN, KC_ALGR);
}

void dance_at_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_finished(state->count, KC_A, KC_2, KC_ALGR);
}

void dance_at_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_reset(state->count, KC_A, KC_2, KC_ALGR);
}

void dance_dollar_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_finished(state->count, KC_S, KC_4, KC_RSFT);
}

void dance_dollar_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_reset(state->count, KC_S, KC_4, KC_RSFT);
}

void dance_pipe_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_finished(state->count, KC_L, KC_1, KC_ALGR);
}

void dance_pipe_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_tap_double_mod_reset(state->count, KC_L, KC_1, KC_ALGR);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ñ, twice for ~
    [TD_TILDE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tilde_finished, dance_tilde_reset),
    // Tap once for a, twice for @
    [TD_AT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_at_finished, dance_at_reset),
    // Tap once for s, twice for $
    [TD_DOLLAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dollar_finished, dance_dollar_reset),
    // Tap once for l, twice for |
    [TD_PIPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_pipe_finished, dance_pipe_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: QWERTY */
  [_QW] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  MO(1),    KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     L_SQBRC,  R_SQBRC,  R_BRC,              KC_PGUP,
    KC_ESC,   FN_AT,    FN_DOLLAR,KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     FN_PIPE,  FN_PIPE,  L_BRC,                        KC_ENT,   KC_PGDN,
    L_CLCK,   MO(1),    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  R_CLCK,             KC_UP,    KC_END,
    KC_LCTL,  KC_LALT,  KC_LGUI,                        KC_SPC,   KC_SPC,   KC_SPC,                     KC_LGUI,  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /* 1: Custom */
  [_CL] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET,    _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  BL_DEC,   BL_TOGG,  BL_INC,   BL_STEP,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  ),
};
