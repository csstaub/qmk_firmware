#include QMK_KEYBOARD_H

// Layer names
enum custom_layers {
    _BASE,
    _SYM_L,
    _SYM_R,
    _ACC,
    _MDA,
    _NAV,
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
    K_FENCE,
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
#define MAC_BUL LOPT(KC_8)  // •
#define MAC_PI LOPT(KC_P)  // π
#define MAC_GRV LOPT(KC_GRV)  // grave dead key (è, à, ù, …)
#define MAC_CIR LOPT(KC_I)  // circumflex dead key (ê, â, î, …)

// Layer-tap keys (opposite-hand activation: right thumb → left layer, left thumb → right layer)
#define LT_ENT  LT(_MDA, KC_ENT)
#define LT_ESC  LT(_NAV, KC_ESC)
#define LT_BSPC LT(_SYM_R, KC_BSPC)
#define LT_SPC  LT(_SYM_L, KC_SPC)
#define LT_DIA  MO(_ACC)

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ Keymaps                                                                │
// └─────────────────────────────────────────────────────────────────────────┘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  KC_A,    HM_S,    HM_D,    HM_F,    HM_G,                               HM_H,    HM_J,    HM_K,    HM_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,          XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OS_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    LT_DIA,  LT_ESC,  LT_BSPC,                   LT_SPC,  LT_ENT,  LT_DIA
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYM_R] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_PLUS, KC_7,    KC_8,    KC_9,    KC_LPRN, KC_ASTR,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_MINS, KC_4,    KC_5,    KC_6,    KC_RPRN, KC_SLSH,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, KC_0,    KC_1,    KC_2,    KC_3,    K_PRNS,  QK_LLCK,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYM_L] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_EQL,  KC_LCBR, KC_AMPR, KC_PIPE, KC_UNDS, KC_LBRC,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSLS, KC_RCBR, KC_DLR,  KC_PERC, KC_CIRC, KC_RBRC,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     QK_LLCK, K_CURLY, KC_EXLM, KC_AT,   KC_HASH, K_BRACK, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MDA] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_F14,  KC_F15,  _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_MUTE, QVOLD,   QVOLU,   _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     QK_LLCK, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, QK_LLCK,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ACC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MAC_Q,   _______, K_EACU,  MAC_GRV, _______,                            _______, K_UDIA,  MAC_CIR, K_ODIA,  MAC_PI,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     K_FENCE, K_ADIA,  _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, MAC_C,   _______, MAC_BUL, _______,          _______, _______, _______, _______, _______, K_UPDIR, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
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
            case K_FENCE:
                SEND_STRING("``````");
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                return false;
            case K_UPDIR:
                SEND_STRING("../");
                return false;
            case LT_BSPC:
                if (record->tap.count
                    && ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    tap_code(KC_DEL);
                    set_mods(mods);
                    return false;
                }
                break;
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
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is(_SYM_L)) {
        set_color_range(led_min, led_max, HSV_PINK);
    } else if (layer_state_is(_SYM_R)) {
        set_color_range(led_min, led_max, HSV_PINK);
    } else if (layer_state_is(_MDA)) {
        set_color_range(led_min, led_max, HSV_GOLD);
    } else if (layer_state_is(_NAV)) {
        set_color_range(led_min, led_max, HSV_GOLD);
    } else if (layer_state_is(_ACC)) {
        set_color_range(led_min, led_max, HSV_RED);
    }

    return false;
}
