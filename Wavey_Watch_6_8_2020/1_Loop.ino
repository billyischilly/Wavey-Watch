// There are loops running on both cores of the ESP32...

// Core 1...
// Main Loop
void loop() {

  switch (currentScreenMode) {
    case AIRHARP:
      airharp();
      break;
    case VIBRATO:
      vibrato();
      break;
    case OSC:
      sendAllOSC();
      break;
    case MIDI_MENU:
//      loadMIDIMenu();
      break;
    default:
      delay(5);
      break;
  }

  lv_task_handler();

  //  updateTapTempo();

  if (irq) {
    irq = false;
    ttgo->power->readIRQ();
    if (ttgo->power->isPEKShortPressIRQ()) { //Short button presses take you back one screen.
      if (currentScreenMode == VIBRATO || AIRHARP || SEND_ALL_MIDI || SCALE_SETTINGS) backToMidiMenu();
      if (currentScreenMode == MIDI_MENU) currentScreenMode = CONNECT_MENU;
    }
    if (ttgo->power->isPEKLongtPressIRQ()) Serial.println("Long Press Detected");
    if (ttgo->power->isVbusPlugInIRQ()) powerConnected();
    if (ttgo->power->isVbusRemoveIRQ()) powerDisconnected();
    if (ttgo->power->isVbusLowVHOLDIRQ()) lowPower();
    ttgo->power->clearIRQ();
  }

  delay(10);

}

// Core 0
// This core should be left relatively clear to check interrupt flags and send bluetooth messages.
void checkNoteInterrupt( void * parameter) { //This acts as a continuous loop on Core 0
  for (;;) {
    if (midiClock == true) {
      portENTER_CRITICAL(&timerMux);
      clockCount++;
      if (clockCount > 24) clockCount = 0;
      bleClock();
      midiClock = false;
      portEXIT_CRITICAL(&timerMux);

      if (clockCount == 0) {
        if (noteIsOn == true) {
          bleNoteOff(sm.getScaleNote(lastNote), 0, 0);
          bleNoteOn(sm.getScaleNote(currentNote), 80, 0);
          ttgo->motor->onec(20);
          lastNote = currentNote;
        }
      }
    }
  }
}
