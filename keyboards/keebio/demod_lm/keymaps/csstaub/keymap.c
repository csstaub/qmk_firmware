#include QMK_KEYBOARD_H

// Layer names
enum custom_layers {
    _NAV,
    _NUMPAD,
};

#define LDSK LCTL(KC_LEFT)
#define RDSK LCTL(KC_RIGHT)
#define MSCT LCTL(KC_UP)
#define QVOLD LSFT(LOPT(KC_KB_VOLUME_DOWN))
#define QVOLU LSFT(LOPT(KC_KB_VOLUME_UP))

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ Keymaps                                                                │
// └─────────────────────────────────────────────────────────────────────────┘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base layer: navigation and media (pink)
  [_NAV] = LAYOUT_numpad_5x4(
  //┌────────┬────────┬────────┬────────┐
     TG(_NUMPAD),KC_MUTE, QVOLD,   QVOLU,
  //├────────┼────────┼────────┼────────┤
     LDSK,    MSCT,    RDSK,
  //├────────┼────────┼────────┤        │
     KC_LABK, KC_UP,   KC_RABK, KC_PGUP,
  //├────────┼────────┼────────┼────────┤
     KC_LEFT, KC_DOWN, KC_RGHT,
  //├────────┴────────┼────────┤        │
     KC_SPC,           KC_F,    KC_PGDN
  //└─────────────────┴────────┴────────┘
  ),

  // Numpad layer (cyan)
  [_NUMPAD] = LAYOUT_numpad_5x4(
  //┌────────┬────────┬────────┬────────┐
     TG(_NUMPAD),KC_PSLS, KC_PAST, KC_PMNS,
  //├────────┼────────┼────────┼────────┤
     KC_P7,   KC_P8,   KC_P9,
  //├────────┼────────┼────────┤        │
     KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
  //├────────┼────────┼────────┼────────┤
     KC_P1,   KC_P2,   KC_P3,
  //├────────┴────────┼────────┤        │
     KC_P0,            KC_PDOT, KC_PENT
  //└─────────────────┴────────┴────────┘
  ),
};

// ┌─────────────────────────────────────────────────────────────────────────┐
// │ RGB Lighting                                                            │
// │   Base (nav) = pink                                                     │
// │   Numpad     = cyan                                                     │
// └─────────────────────────────────────────────────────────────────────────┘

static void set_color_all(uint8_t led_min, uint8_t led_max, uint8_t h, uint8_t s, uint8_t v) {
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
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == _NAV) {
        set_color_all(led_min, led_max, HSV_PINK);
    }
    return false;
}
