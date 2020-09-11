void sendAllOSC() {

  currentScreenMode = OSC;

  static lv_obj_t *oscPage = lv_cont_create(NULL, NULL);
  lv_obj_set_size(oscPage, 240, 240);

  bool res = ttgo->bma->getAccel(acc);
  if (res == false) {
  } else {
    int axisX = acc.y; // These are the wrong way round (i.e. x = y, y = x. Should be able to reorient the Accelerometer axes to make more sense but leave for the time being
    int axisY = acc.x;

    // Map accelerometer values for line position on x axis
    short int positionX = map(axisX, -500, 500, 0, 240);

    // Map accelerometer values for line position on y axis
    short int positionY = map(axisY, -500, 500, 0, 240);

    DEBUG_PRINT(acc.y); DEBUG_PRINTLN(acc.x); DEBUG_PRINTLN(acc.y);     

    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_bg_opa(&style_line, LV_STATE_DEFAULT, 70);
    lv_style_set_bg_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_BLUE);

    // Create line object
    static lv_obj_t *xline = lv_obj_create(oscPage, NULL);
    lv_obj_set_size(xline, 240, 20);
    lv_obj_align(xline, oscPage, LV_ALIGN_CENTER, 0, 0);
    //    lv_obj_add_style(xline, LV_LINE_PART_MAIN, &style_line);
    lv_obj_set_pos(xline, 0, positionX);
    lv_obj_set_style_local_border_width(xline, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_opa(xline, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 200);
    lv_obj_set_style_local_bg_color(xline, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, WAVEY_PINK);

    static lv_obj_t *yline = lv_obj_create(oscPage, NULL);
    lv_obj_set_size(yline, 20, 240);
    lv_obj_align(yline, oscPage, LV_ALIGN_CENTER, 0, 0);
    //    lv_obj_add_style(yline, LV_LINE_PART_MAIN, &style_line);
    lv_obj_set_pos(yline, positionY, 0);
    lv_obj_set_style_local_border_width(yline, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_opa(yline, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 200);
    lv_obj_set_style_local_bg_color(yline, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, WAVEY_GREEN);

    int16_t x, y;
    if (ttgo->getTouch(x, y)) {

    }

    Serial.println(x);
    sendMessageViaOSC();
    lv_scr_load(oscPage);
  }
}
