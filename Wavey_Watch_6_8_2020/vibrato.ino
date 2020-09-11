void vibrato()
{
  currentScreenMode = VIBRATO;

  static lv_obj_t *vibratoPage = lv_cont_create(NULL, NULL);
  lv_obj_set_size(vibratoPage, 240, 240);

  bool res = ttgo->bma->getAccel(acc);
  if (res == false) {
  } else {
    int axisX = acc.y; // These are the wrong way round (i.e. x = y, y = x. Should be able to reorient the Accelerometer axes to make more sense but leave for the time being
    int axisY = acc.x;

    axisY = constrain(axisY, 0, 500); //could get rid of this line maybe and just set more accurate values.

    // Map accelerometer values for MIDI
    int bendValue = map(axisX, -2000, 2000, 0, 16324);
    int expression = map(axisY, 0, 500, 10, 127);
    blePitchBend(bendValue, 0);
    bleControlChange(11, expression);

    // Map accelerometer values for display
    int positionX = map(axisX, 1050, -1050, -100, 100);
    int lineThickness = map(axisY, 0, 1000, 2, 100);

    // Create a chart to plot line on screen
    static lv_obj_t *vibratochart = lv_chart_create(vibratoPage, NULL);
    lv_obj_set_size(vibratochart, 240, 240);
    lv_obj_align(vibratochart, vibratoPage, LV_ALIGN_CENTER, 0, 0);
    lv_chart_set_range(vibratochart, -100, 100);
    lv_chart_set_div_line_count(vibratochart, 0, 0); //No divider lines. Could add for whole and half tone bend guides at some point?
    lv_chart_set_type(vibratochart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/
    lv_obj_set_style_local_line_width(vibratochart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, lineThickness);
    lv_obj_set_style_local_border_width(vibratochart, LV_CHART_PART_BG, LV_STATE_DEFAULT, 0);

    static lv_chart_series_t *vibratoLine = lv_chart_add_series(vibratochart, WAVEY_PINK);

    static bool initialised = false;
    if (initialised == false) {
      lv_chart_init_points(vibratochart, vibratoLine, 0); // Sets line through the middle of screen to start
      initialised = true;
    }

    //When a new value is added, old values are shifted up one to make way and then chart is refreshed.
    lv_chart_set_update_mode(vibratochart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_next(vibratochart, vibratoLine, positionX);
    lv_chart_refresh(vibratochart); /*Required after direct set*/

    lv_scr_load(vibratoPage);
  }
}
