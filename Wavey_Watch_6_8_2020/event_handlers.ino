void changeFundamental(lv_obj_t * slider, lv_event_t event)
{
  if (event == LV_EVENT_VALUE_CHANGED) {

    sm.setFundamental(lv_slider_get_value(slider));
    lv_label_set_text(fundamentalLabel, sm.getFundamentalName());
    DEBUG_PRINTLN(sm.getFundamentalName());
  }
}

void changeScale(lv_obj_t *slider, lv_event_t event)
{
  if (event == LV_EVENT_VALUE_CHANGED) {
    sm.setCurrentScale(lv_slider_get_value(slider));
    lv_label_set_text(scaleLabel, sm.getScaleName());
    DEBUG_PRINTLN(sm.getScaleName());
  }
}

void connectToBluetooth(lv_obj_t *button, lv_event_t event)
{
  if (event == LV_EVENT_CLICKED) {
    DEBUG_PRINTLN("Start advertising bluetooth");
    bluetoothSetup();
    loadWaitingPage();
  }
}

void connectToWifi(lv_obj_t *button, lv_event_t event)
{
  if (event == LV_EVENT_CLICKED) {
    DEBUG_PRINTLN("Connecting to Wifi network");
    loadWaitingPage();
    wifiSetup();
  }
}

void updateTapTempo() {
  static bool previouslyTouched = false;
  long beatInterval; // Was previously a static/global variable. Don't think it needs to be but if this no longer works try changing back?
  if (ttgo->touched() && !previouslyTouched) {
    tapTempo.update(HIGH);
    tapTempo.update(LOW);
    //    timerStop(timer);
    timerRestart(timer);
    beatInterval = tapTempo.getBeatLength() * 1000;
    timerAlarmWrite(timer, beatInterval / 24, true);
  }
  previouslyTouched = ttgo->touched();
}

void startVibrato(lv_obj_t * slider, lv_event_t event)
{
  if (event == LV_EVENT_CLICKED) {
    DEBUG_PRINTLN("Start Vibrato Mode");
    vibrato();
  }
}

void startAirharp(lv_obj_t * slider, lv_event_t event)
{
  if (event == LV_EVENT_CLICKED) {
    DEBUG_PRINTLN("Start Airharp");
    airharp();
  }
}

void startSendAll(lv_obj_t * slider, lv_event_t event)
{
  if (event == LV_EVENT_CLICKED) {
    DEBUG_PRINTLN("Start send all MIDI");
    //        sendAllMIDI();
  }
}

void startSettings(lv_obj_t * slider, lv_event_t event)
{
  if (event == LV_EVENT_CLICKED) {
    DEBUG_PRINTLN("Start settings");
    loadScalePage();
  }
}

void backToMidiMenu() {
  if (ttgo->power->isPEKShortPressIRQ()) {
    bleNoteOff(sm.getScaleNote(lastNote), 0, 0);
    bleNoteOff(sm.getScaleNote(currentNote), 0, 0);
    bleControlChange (123, 0);
    loadMIDIMenu();
  }
}

void powerConnected() {

}

void powerDisconnected() {

}

void lowPower() {

}

void startConnectionPage(lv_obj_t *button, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    DEBUG_PRINTLN("Connection page");
    loadConnectionPage();
  }
}
