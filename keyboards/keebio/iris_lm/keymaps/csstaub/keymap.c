#include QMK_KEYBOARD_H
#include "transactions.h"

// Layer names
enum custom_layers {
    _BASE,
    _LAYER_L,
    _LAYER_R,
    _LAYER_M,
    _LAYER_A
};

// Custom keycodes for layer text macros
enum custom_keycodes {
    K_UDIA = SAFE_RANGE,
    K_ODIA,
    K_ADIA,
    K_EACU,
    K_CURLY,
    K_BRACK,
    K_PRNS,
    K_UPDIR,
};

// Home row mod aliases
#define HM_G    HYPR_T(KC_G)
#define HM_S    LALT_T(KC_S)
#define HM_D    LCTL_T(KC_D)
#define HM_F    LGUI_T(KC_F)
#define HM_J    RGUI_T(KC_J)
#define HM_K    RCTL_T(KC_K)
#define HM_L    RALT_T(KC_L)
#define HM_H    HYPR_T(KC_H)

// Quarter volume up/down
#define QVOLD LSFT(LOPT(KC_KB_VOLUME_DOWN))
#define QVOLU LSFT(LOPT(KC_KB_VOLUME_UP))

// macOS single-chord special characters
#define MAC_C LOPT(KC_C)  // ç
#define MAC_Q LOPT(KC_Q)  // œ

// Layer keys
#define LAYER_0 TO(_BASE)
#define LAYER_M TO(_LAYER_M)

// Layer-tap keys (opposite-hand activation: right thumb → left layer, left thumb → right layer)
#define LT_SPC  LT(_LAYER_L, KC_SPC)
#define LT_BSPC LT(_LAYER_R, KC_BSPC)
#define LT_GRV  LT(_LAYER_A, KC_GRV)
#define LT_QUOT LT(_LAYER_A, KC_QUOT)

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ Keymaps                                                                │
// └─────────────────────────────────────────────────────────────────────────┘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LT_GRV,  KC_A,    HM_S,    HM_D,    HM_F,    HM_G,                               HM_H,    HM_J,    HM_K,    HM_L,    KC_SCLN, LT_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RGHT,          KC_UP,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OS_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LEFT, KC_ESC,  LT_BSPC,                   LT_SPC,  KC_ENT,  KC_DOWN
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LAYER_R] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT, QK_MAKE, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_LPRN, KC_7,    KC_8,    KC_9,    KC_PLUS, KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_RPRN, KC_4,    KC_5,    KC_6,    KC_ASTR, KC_SLSH,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          QVOLU,   KC_0,    KC_1,    KC_2,    KC_3,    K_PRNS,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, LAYER_M, QVOLD
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LAYER_L] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, QK_MAKE, QK_BOOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_EQL,  KC_LCBR, KC_AMPR, KC_PIPE, KC_UNDS, KC_LBRC,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TILD, KC_RCBR, KC_DLR,  KC_PERC, KC_CIRC, KC_RBRC,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, K_CURLY, KC_EXLM, KC_AT,   KC_HASH, K_BRACK, KC_F15,           _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_F14,  LAYER_M, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LAYER_M] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MS_BTN2, MS_UP,   MS_BTN1, MS_BTN3, _______,                            _______, _______, _______, _______, _______, RM_TOGG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MS_LEFT, MS_DOWN, MS_RGHT, MS_BTN4, MS_BTN5,                            MS_WHLL, MS_WHLU, MS_WHLD, MS_WHLR, _______, AC_TOGG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, OS_TOGG,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, LAYER_0, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LAYER_A] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MAC_Q,   _______, K_EACU,  _______, _______,                            _______, K_UDIA,  _______, K_ODIA,  _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, K_ADIA,  _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, MAC_C,   _______, _______, KC_END,           KC_PGUP, _______, _______, _______, _______, K_UPDIR, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_HOME, _______, _______,                   _______, _______, KC_PGDN
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
};

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ Chordal Hold                                                            │
// └─────────────────────────────────────────────────────────────────────────┘

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L',                'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L',                'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L',                'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', 'R', 'R',
                 'L', 'L', 'L',                'R', 'R', 'R'
);

#define MOD_MASK_LEFT  0x0F
#define MOD_MASK_RIGHT 0xF0

// Send a macOS dead-key + base letter sequence (e.g., Opt+U for diaeresis,
// Opt+E for acute). Honor a held Shift or active caps word for capitalization.
static void send_macos_dead(uint16_t dead_key, uint16_t base_letter) {
    uint8_t saved = get_mods();
    bool capitalize = (saved & MOD_MASK_SHIFT)
                   || (get_oneshot_mods() & MOD_MASK_SHIFT)
                   || is_caps_word_on();
    clear_mods();
    clear_oneshot_mods();
    tap_code16(dead_key);
    if (capitalize) register_mods(MOD_BIT(KC_LSFT));
    tap_code(base_letter);
    if (capitalize) unregister_mods(MOD_BIT(KC_LSFT));
    set_mods(saved);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case K_UDIA:
                send_macos_dead(LOPT(KC_U), KC_U);
                return false;
            case K_ODIA:
                send_macos_dead(LOPT(KC_U), KC_O);
                return false;
            case K_ADIA:
                send_macos_dead(LOPT(KC_U), KC_A);
                return false;
            case K_EACU:
                send_macos_dead(LOPT(KC_E), KC_E);
                return false;
            case K_CURLY:
                SEND_STRING("{}");
                tap_code16(KC_LEFT);
                return false;
            case K_BRACK:
                SEND_STRING("[]");
                tap_code16(KC_LEFT);
                return false;
            case K_PRNS:
                SEND_STRING("()");
                tap_code16(KC_LEFT);
                return false;
            case K_UPDIR:
                SEND_STRING("../");
                return false;
        }
    }

    // When a mod-tap settles as hold, check if opposite hand has active mods.
    // If so, override to tap — we never intentionally chord cross-hand mods.
    // Hand comes from chordal_hold_layout: the mod byte lies for Hyper, which
    // is always 0x0F (all left mods) regardless of physical side.
    if (IS_QK_MOD_TAP(keycode) && record->event.pressed && !record->tap.count) {
        char hand = pgm_read_byte(&chordal_hold_layout[record->event.key.row][record->event.key.col]);
        uint8_t active = get_mods();
        bool opposite_held = (hand == 'R') ? (active & MOD_MASK_LEFT) : (active & MOD_MASK_RIGHT);

        if (opposite_held) {
            tap_code(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
            return false;
        }
    }

    return true;
}

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ Key Overrides                                                           │
// └─────────────────────────────────────────────────────────────────────────┘

const key_override_t shift_bspc_to_del  = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &shift_bspc_to_del,
};

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ Split Caps Word Sync                                                    │
// └─────────────────────────────────────────────────────────────────────────┘

static bool caps_word_synced = false;

static void caps_word_sync_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    const bool *val = (const bool *)in_data;
    caps_word_synced = *val;
}

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ RGB Lighting                                                            │
// └─────────────────────────────────────────────────────────────────────────┘

static void set_color_range(uint8_t led_min, uint8_t led_max, uint8_t h, uint8_t s, uint8_t v) {
    (void)s;
    (void)v;
    hsv_t hsv = {.h = h, .s = rgb_matrix_get_sat(), .v = rgb_matrix_get_val()};
    rgb_t rgb = hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL);
    transaction_register_rpc(USER_SYNC_CAPS_WORD, caps_word_sync_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static bool last_caps_word = false;
        bool current = is_caps_word_on();
        if (current != last_caps_word) {
            last_caps_word = current;
            transaction_rpc_send(USER_SYNC_CAPS_WORD, sizeof(current), &current);
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool caps_active = is_keyboard_master() ? is_caps_word_on() : caps_word_synced;
    if (caps_active) {
        set_color_range(led_min, led_max, HSV_PURPLE);
        return false;
    }

    if (layer_state_is(_LAYER_L)) {
        set_color_range(led_min, led_max, HSV_PINK);
    } else if (layer_state_is(_LAYER_R)) {
        set_color_range(led_min, led_max, HSV_PINK);
    } else if (layer_state_is(_LAYER_M)) {
        set_color_range(led_min, led_max, HSV_GOLD);
    } else if (layer_state_is(_LAYER_A)) {
        set_color_range(led_min, led_max, HSV_RED);
    }

    return false;
}

