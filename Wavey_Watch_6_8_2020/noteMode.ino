void airharp() {

  currentScreenMode = AIRHARP;

  DEBUG_PRINTLN("Airharp Mode");

  static lv_obj_t *notePage = lv_cont_create(NULL, NULL);
  lv_obj_set_size(notePage, 240, 240);

  bool res = ttgo->bma->getAccel(acc);
  if (res == false) {
  } else {
    int axisX = acc.y; //smooth y values so ball movement isn't too jerky
    int axisY = smooth(acc.x) + 500; //offset of 1010 so we only have positive values
    Serial.print(acc.x); Serial.print("    "); Serial.print(acc.y); Serial.print("    "); Serial.println(acc.z);
    // Map accelerometer values for MIDI pitchbend/vibrato and send
    int bendValue = map(axisX, -2000, 2000, 0, 16324);
    blePitchBend(bendValue, 0);

    // Map accelerometer values for ball position on x axis
    int positionX = map(axisX, 500, -500, 120, -120);

    // Map accelerometer values for ball position on y axis
    byte noteRange = 12;
    currentNote = map(axisY, 1010, 0, 0, noteRange);
    int maxHeight = 1000 / noteRange;
    int ballHeight = axisY % maxHeight;
    ballHeight = map(ballHeight, maxHeight, 0, 120, -120);

    // Create ball object
    static lv_obj_t *ball = lv_obj_create(notePage, NULL);
    lv_obj_set_size(ball, 40, 40);
    lv_obj_align(ball, notePage, LV_ALIGN_CENTER, ballHeight, positionX);
    //    lv_obj_set_pos(ball, ballHeight, positionX);
    lv_obj_set_style_local_radius(ball, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);


    // Send ble MIDI and pulse vibration motor on new note
    if (currentNote != lastNote) {
      ttgo->motor->onec(10);
      bleNoteOff(sm.getScaleNote(lastNote), 0, 0);
      bleNoteOn(sm.getScaleNote(currentNote), 80, 0);
      lastNote = currentNote;
    }
  }
  lv_scr_load(notePage);
}

//void timedNoteMode() {
//  Accel acc;
//  bool res = ttgo->bma->getAccel(acc);
//  byte noteRange = 12;
//  int axisX = acc.y;
//  int axisY = acc.x + 1010; //offset of 1010 so we only have positive values
//  axisY = smooth(axisY);
//  int maxHeight = 2020 / noteRange;
//  int ballHeight = axisY % maxHeight;
//  int noteOnThreshold = 150;
//  static int previousValue;
//  currentNote = map(axisY, 2020, 0, 0, noteRange);
//  int positionX = map(axisX, -1050, 1050, 240, 0);
//  int expressionValue = map(positionX, noteOnThreshold, 0, 0, 127);
//  byte circleSize;
//  expressionValue = constrain(expressionValue, 0, 127);
//
//  if (expressionValue != previousValue) {
//    bleControlChange(11, expressionValue);
//    previousValue = expressionValue;
//  }
//
//  if (clockCount <= 3) {
//    circleSize = 30;
//  } else {
//    circleSize = 20;
//  }
//
//  if (res == false) {
//  } else {
//    bufferSprite.fillSprite(TFT_BLACK);
//    ballHeight = map(ballHeight, 0, maxHeight, 240, 0);
//    bufferSprite.drawLine(0, noteOnThreshold, 240, noteOnThreshold, TFT_WHITE);
//    bufferSprite.fillCircle(ballHeight, positionX, circleSize, colours[currentNote]);
//    printBPM();
//
//    if (positionX > noteOnThreshold && noteIsOn == true) {
//      //      DEBUG_PRINTLN("Note Switched Off");
//      bleNoteOff(sm.getScaleNote(lastNote), 0, 0);
//      noteIsOn = false;
//    } else if (positionX <= noteOnThreshold) {
//      //      DEBUG_PRINTLN("Note Switched On");
//      noteIsOn = true;
//    }
//  }
//}
