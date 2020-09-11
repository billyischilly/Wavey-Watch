void loadMIDIMenu() {

  currentScreenMode = MIDI_MENU;

  //Create page for setting scale
  lv_obj_t *midiMenu = lv_cont_create(NULL, NULL);
  DEBUG_PRINTLN("Midi Menu...");
  lv_obj_set_size(midiMenu, 240, 240);
  lv_obj_add_style(midiMenu, LV_OBJ_PART_MAIN, &pageStyle);

  //Create buttonStyle
  static lv_anim_path_t path_overshoot;
  lv_anim_path_init(&path_overshoot);
  lv_anim_path_set_cb(&path_overshoot, lv_anim_path_overshoot);

  static lv_anim_path_t path_ease_out;
  lv_anim_path_init(&path_ease_out);
  lv_anim_path_set_cb(&path_ease_out, lv_anim_path_ease_out);

  static lv_anim_path_t path_ease_in_out;
  lv_anim_path_init(&path_ease_in_out);
  lv_anim_path_set_cb(&path_ease_in_out, lv_anim_path_ease_in_out);

  //Create button to start airharp
  DEBUG_PRINTLN("Airharp button...");
  lv_obj_t *airharpButton = lv_btn_create(midiMenu, NULL);
  lv_obj_set_size(airharpButton, 110, 110);
  lv_obj_set_event_cb(airharpButton, startAirharp);
  lv_obj_add_style(airharpButton, LV_BTN_PART_MAIN, &style_ripple);
  lv_obj_set_style_local_value_str(airharpButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Airharp");
  lv_obj_set_style_local_value_font(airharpButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_FONT_SMALL);
  lv_obj_set_style_local_bg_color(airharpButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, DEEP_PINK);

  //Create button to start vibrato
  DEBUG_PRINTLN("Vibrato button...");
  lv_obj_t *vibratoButton = lv_btn_create(midiMenu, NULL);
  lv_obj_set_size(vibratoButton, 110, 110);
  lv_obj_set_event_cb(vibratoButton, startVibrato);
  lv_obj_add_style(vibratoButton, LV_BTN_PART_MAIN, &style_ripple);
  lv_obj_set_style_local_value_str(vibratoButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Vibrato");
  lv_obj_set_style_local_value_font(vibratoButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_FONT_SMALL);
  lv_obj_set_style_local_bg_color(vibratoButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, DARK_BLUE);

  //Create button to send all as midi
  DEBUG_PRINTLN("Send All MIDI button...");
  lv_obj_t *sendAllButton = lv_btn_create(midiMenu, NULL);
  lv_obj_set_size(sendAllButton, 110, 110);
  lv_obj_set_event_cb(sendAllButton, startSendAll);
  lv_obj_add_style(sendAllButton, LV_BTN_PART_MAIN, &style_ripple);
  lv_obj_set_style_local_value_str(sendAllButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Send All");
  lv_obj_set_style_local_value_font(sendAllButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_FONT_SMALL);
  lv_obj_set_style_local_bg_color(sendAllButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LIGHT_BLUE);

  //Create button to open settings
  DEBUG_PRINTLN("Settings button...");
  lv_obj_t *settingsButton = lv_btn_create(midiMenu, NULL);
  lv_obj_set_size(settingsButton, 110, 110);
  lv_obj_set_event_cb(settingsButton, startSettings);
  lv_obj_add_style(settingsButton, LV_BTN_PART_MAIN, &style_ripple);
  lv_obj_set_style_local_value_str(settingsButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_SETTINGS);
  lv_obj_set_style_local_bg_color(settingsButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, BROWN);

  lv_obj_align(airharpButton, midiMenu, LV_ALIGN_CENTER, -60, -60);
  lv_obj_align(vibratoButton, midiMenu, LV_ALIGN_CENTER, 60, -60);
  lv_obj_align(sendAllButton, midiMenu, LV_ALIGN_CENTER, -60, 60);
  lv_obj_align(settingsButton, midiMenu, LV_ALIGN_CENTER, 60, 60);

  lv_scr_load(midiMenu);
}

void loadScalePage() {

  currentScreenMode = SCALE_SETTINGS;

  //Create page for setting scale
  lv_obj_t *scalePage = lv_cont_create(NULL, NULL);
  DEBUG_PRINTLN("Scale Page...");
  lv_obj_set_size(scalePage, 240, 240);
  lv_obj_add_style(scalePage, LV_OBJ_PART_MAIN, &pageStyle);

  //Create slider to control fundamental
  DEBUG_PRINTLN("Fundamental Slider...");
  static lv_obj_t *fundamentalSlider = lv_slider_create(scalePage, NULL);
  lv_obj_set_width(fundamentalSlider, 200);
  lv_slider_set_range(fundamentalSlider, 48, 59);
  lv_slider_set_value(fundamentalSlider, sm.fundamental, LV_ANIM_OFF); //sets initial fundamental to fundamental set in setup()
  lv_obj_set_event_cb(fundamentalSlider, changeFundamental);
  lv_obj_set_style_local_bg_color(fundamentalSlider, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, WAVEY_PINK);
  lv_obj_set_style_local_border_color(fundamentalSlider, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, WAVEY_PINK);

  //..and a label for the fundamental slider
  DEBUG_PRINTLN("Fundamental Label...");
  fundamentalLabel = lv_label_create(scalePage, NULL);
  lv_label_set_text(fundamentalLabel, sm.getFundamentalName());
  lv_obj_set_style_local_text_font(fundamentalLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_48);
  lv_obj_set_auto_realign(fundamentalLabel, true); //labels will recentre themselves if they are longer/shorter than before

  // Create slider to control scale fundamental
  DEBUG_PRINTLN("Scale Slider...");
  lv_obj_t *scaleSlider = lv_slider_create(scalePage, NULL);
  lv_obj_set_width(scaleSlider, 200);
  lv_slider_set_range(scaleSlider, 0, 11);
  lv_slider_set_value(scaleSlider, sm.currentScale, LV_ANIM_OFF); //sets initial scale to 1 (Major).
  lv_obj_set_event_cb(scaleSlider, changeScale);
  lv_style_set_bg_color(&scaleStyle, LV_STATE_DEFAULT, WAVEY_GREEN);
  lv_style_set_border_color(&scaleStyle, LV_STATE_DEFAULT, WAVEY_GREEN);

  //..and a label for the scale slider
  DEBUG_PRINTLN("Scale Label...");
  scaleLabel = lv_label_create(scalePage, NULL);
  lv_label_set_text(scaleLabel, "Major");
  lv_obj_set_style_local_text_font(scaleLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_28);
  lv_obj_set_auto_realign(scaleLabel, true); //labels will recentre themselves if they are longer/shorter than before

  //Arrange elements on the page
  DEBUG_PRINTLN("Aligning objects on page...");
  lv_obj_align(fundamentalLabel, scalePage, LV_ALIGN_CENTER, 0, -50);
  lv_obj_align(fundamentalSlider, fundamentalLabel, LV_ALIGN_CENTER, 0, 40);
  lv_obj_align(scaleLabel, fundamentalSlider, LV_ALIGN_CENTER, 0, 50);
  lv_obj_align(scaleSlider, scaleLabel, LV_ALIGN_CENTER, 0, 30);

  lv_scr_load(scalePage);
  DEBUG_PRINTLN("Page complete!");
}

void loadConnectionPage() {

  currentScreenMode = CONNECT_MENU;

  lv_style_set_border_width(&buttonStyle, LV_STATE_DEFAULT, 0);

  lv_style_set_pad_inner(&buttonStyle, LV_STATE_DEFAULT, 20);
  lv_style_set_pad_top(&buttonStyle, LV_STATE_DEFAULT, 20);
  lv_style_set_pad_left(&buttonStyle, LV_STATE_DEFAULT, 5);
  lv_style_set_pad_right(&buttonStyle, LV_STATE_DEFAULT, 5);

  //Create page for choosing Wifi OSC or BLE Midi
  DEBUG_PRINTLN("Connection Page...");
  static lv_obj_t *connectionPage = lv_cont_create(NULL, NULL);
  lv_obj_set_size(connectionPage, 240, 240);

  //  //"Connect" label for top of the page
  //  DEBUG_PRINTLN("Connect label");
  //  lv_obj_t *connectLabel = lv_label_create(connectionPage, NULL);
  //  lv_label_set_text(connectLabel, "Connect");
  //  lv_obj_set_style_local_text_font(connectLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_38);

  //Create button to start airharp
  DEBUG_PRINTLN("Bluetooth MIDI button...");
  lv_obj_t *bluetoothButton = lv_btn_create(connectionPage, NULL);
  lv_obj_set_size(bluetoothButton, 110, 110);
  lv_obj_set_event_cb(bluetoothButton, connectToBluetooth);
  lv_obj_add_style(bluetoothButton, LV_BTN_PART_MAIN, &style_ripple);
  lv_obj_set_style_local_value_str(bluetoothButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_BLUETOOTH);
  lv_obj_set_style_local_bg_color(bluetoothButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, MEDIUM_BLUE );
  //Create button to connect to Bluetooth MIDI

  //Create button to start airharp
  DEBUG_PRINTLN("Wireless OSC button...");
  lv_obj_t *wifiButton = lv_btn_create(connectionPage, NULL);
  lv_obj_set_size(wifiButton, 110, 110);
  lv_obj_set_event_cb(wifiButton, connectToWifi);
  lv_obj_add_style(wifiButton, LV_BTN_PART_MAIN, &style_ripple);
  lv_obj_set_style_local_value_str(wifiButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_WIFI);
  lv_obj_set_style_local_bg_color(wifiButton, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, DEEP_PINK);
  //Create button to connect to Bluetooth MIDI

  //Arrange elements on the page
  DEBUG_PRINTLN("Aligning objects on page...");
  lv_obj_align(bluetoothButton, connectionPage, LV_ALIGN_CENTER, -60, 0);
  lv_obj_align(wifiButton, connectionPage, LV_ALIGN_CENTER, 60, 0);

  lv_scr_load(connectionPage);
  DEBUG_PRINTLN("Page complete!");
}

void loadHandSelection() {

  //  currentScreenMode = HAND_SELECT;
  //
  //  //  lv_style_set_border_width(&buttonStyle, LV_STATE_DEFAULT, 0);
  //  //
  //  //  lv_style_set_pad_inner(&buttonStyle, LV_STATE_DEFAULT, 20);
  //  //  lv_style_set_pad_top(&buttonStyle, LV_STATE_DEFAULT, 20);
  //  //  lv_style_set_pad_left(&buttonStyle, LV_STATE_DEFAULT, 5);
  //  //  lv_style_set_pad_right(&buttonStyle, LV_STATE_DEFAULT, 5);
  //
  //  //Create page for choosing Wifi OSC or BLE Midi
  //  DEBUG_PRINTLN("Hand Selection Page...");
  //  static lv_obj_t *handSelectionPage = lv_cont_create(NULL, NULL);
  //  lv_obj_set_size(handSelectionPage, 240, 240);
  //  //  lv_cont_set_layout(connectionPage, LV_LAYOUT_PRETTY_MID);
  //  //  lv_cont_set_style(connectionPage, LV_BTN_PART_MAIN, &pageStyle);
  //
  //  //"Connect" label for top of the page
  //  DEBUG_PRINTLN("Hand Select label");
  //  lv_obj_t *handSelectLabel = lv_label_create(connectionPage, NULL);
  //  lv_label_set_text(handSelectLabel, "One hand or Two");
  //  lv_obj_set_style_local_text_font(handSelectLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_38);
  //
  //  //Create one hand button
  //  DEBUG_PRINTLN("One Hand");
  //  lv_obj_t *oneHandButton = lv_btn_create(handSelectionPage, NULL);
  //  lv_obj_set_event_cb(oneHandButton, startConnectionPage);
  //  lv_obj_add_style(oneHandButton, LV_BTN_PART_MAIN, &buttonStyle);
  //  lv_label_set_text(oneHandButton, "One");
  //
  //  //Create two hands button
  //  DEBUG_PRINTLN("Two Hands");
  //  lv_obj_t *twoHandButton = lv_btn_create(handSelectionPage, NULL);
  //  lv_obj_set_event_cb(twoHandButton, startPairingPage);
  //  lv_obj_add_style(twoHandButton, LV_BTN_PART_MAIN, &buttonStyle);
  //  lv_label_set_text(twoHandButton, "Two");
  //
  //  //Arrange elements on the page
  //  DEBUG_PRINTLN("Aligning objects on page...");
  //  lv_obj_align(handSelectLabel, connectionPage, LV_ALIGN_CENTER, 0, -50);
  //  lv_obj_align(oneHandButton, connectionPage, LV_ALIGN_CENTER, -60, 50);
  //  lv_obj_align(twoHandButton, connectionPage, LV_ALIGN_CENTER, 60, 50);
  //
  //  lv_scr_load(connectionPage);
  //  DEBUG_PRINTLN("Page complete!");
}

void pairingPage() {

  //  //Create page for choosing Wifi OSC or BLE Midi
  //  DEBUG_PRINTLN("Two hand pairing page...");
  //  static lv_obj_t *pairingPage = lv_cont_create(NULL, NULL);
  //  lv_obj_set_size(pairingPage, 240, 240);
  //
  //  //"Connect" label for top of the page
  //  DEBUG_PRINTLN("Tap to pair label");
  //  lv_obj_t *tapToPairLabel = lv_label_create(pairingPage, NULL);
  //  lv_label_set_text(tapToPairLabel, "Tap dominant \n hand to start");
  //  lv_obj_set_style_local_text_font(handSelectLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_28);
  //  lv_obj_set_event_cb(pairingPage, connectToOtherWatch);

}
void loadWaitingPage() {

  currentScreenMode = CONNECT_MENU;

  //Create waiting page
  lv_obj_t *waitingPage = lv_cont_create(NULL, NULL);
  DEBUG_PRINTLN("Waiting Page...");
  lv_obj_set_size(waitingPage, 240, 240);

  //Waiting label for top of the page
  DEBUG_PRINTLN("Waiting label...");
  lv_obj_t *waitingLabel = lv_label_create(waitingPage, NULL);
  lv_obj_set_style_local_text_font(waitingLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_18);
  lv_label_set_text(waitingLabel, "Connect to watch \n from your device");

  DEBUG_PRINTLN("Creating spinner...");
  lv_obj_t *bluetoothLoading = lv_spinner_create(waitingPage, NULL);
  lv_obj_set_size(bluetoothLoading, 120, 120);
  //  lv_obj_set_style_local_line_color(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, WAVEY_PINK);
  //  lv_obj_set_style_local_bg_color(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, LIGHT_BLUE);
  lv_obj_set_style_local_line_width(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, 20);
  lv_obj_set_style_local_line_color(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, DARK_BLUE);
  lv_obj_set_style_local_line_rounded(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, true);


  lv_obj_set_style_local_pad_top(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_pad_bottom(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_pad_left(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_pad_right(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_pad_inner(bluetoothLoading, LV_SPINNER_PART_INDIC, LV_STATE_DEFAULT, 0);

  //  lv_obj_set_style_local_bg_color(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, LIGHT_BLUE);
  //  lv_obj_set_style_local_line_color(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, LIGHT_BLUE);
  lv_obj_set_style_local_line_width(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, 20);
  lv_obj_set_style_local_border_width(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_outline_width(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_line_color(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, WAVEY_PINK);
  lv_obj_set_style_local_border_color(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, BROWN);
  lv_obj_set_style_local_outline_color(bluetoothLoading, LV_SPINNER_PART_BG, LV_STATE_DEFAULT, WAVEY_GREEN);
  lv_spinner_set_type(bluetoothLoading, LV_SPINNER_TYPE_CONSTANT_ARC);
  //Arrange elements on the page
  DEBUG_PRINTLN("Aligning objects on page...");
  lv_obj_align(waitingLabel, waitingPage, LV_ALIGN_CENTER, 0, -50);
  lv_obj_align(bluetoothLoading, waitingPage, LV_ALIGN_CENTER, 0, 50);

  lv_scr_load(waitingPage);
  DEBUG_PRINTLN("Page complete!");
}
