static lv_style_t scaleStyle; //Not put a lot of thought into these styles. Could just do all styling locally
static lv_style_t pageStyle;
lv_style_t buttonStyle;
lv_style_t style_ripple;

const lv_color_t WAVEY_GREEN = lv_color_hex(0xa3d39c);
const lv_color_t WAVEY_PINK = lv_color_hex(0xF2385A);
const lv_color_t DEEP_PINK = lv_color_hex(0xF2385A);
const lv_color_t DARK_BLUE = lv_color_hex(0x306073);
const lv_color_t MEDIUM_BLUE = lv_color_hex(0x639AA6);
const lv_color_t LIGHT_BLUE = lv_color_hex(0xB0D1D9);
const lv_color_t BROWN = lv_color_hex(0x8C673A);

void styleSetup() {
  /*Ripple on press*/
  lv_style_init(&style_ripple);
  lv_style_set_transition_time(&style_ripple, LV_STATE_PRESSED, 100);
  lv_style_set_transition_time(&style_ripple, LV_STATE_DEFAULT, 0);
  lv_style_set_transition_delay(&style_ripple, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_opa(&style_ripple, LV_STATE_DEFAULT, LV_OPA_100);
  lv_style_set_bg_opa(&style_ripple, LV_STATE_PRESSED, LV_OPA_80);
  lv_style_set_border_width(&style_ripple, LV_STATE_DEFAULT, 0);
  lv_style_set_outline_width(&style_ripple, LV_STATE_DEFAULT, 0);
  lv_style_set_transform_width(&style_ripple, LV_STATE_DEFAULT, 0);
  lv_style_set_transform_height(&style_ripple, LV_STATE_DEFAULT, 0);
  lv_style_set_radius(&style_ripple, LV_STATE_DEFAULT, 20);
  lv_style_set_text_font(&style_ripple, LV_STATE_DEFAULT, LV_THEME_DEFAULT_FONT_SMALL);
}
