void setup() {

  Serial.begin(115200);

  //Setup T-Watch
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->begin();
  ttgo->openBL();
  ttgo->lvgl_begin();
  ttgo->motor_begin();
  ttgo->power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);
  ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ | AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_IRQ, true);
  ttgo->power->clearIRQ();

  //Creates interrupt for detecting charging cable connection/removal and side button presses
  pinMode(AXP202_INT, INPUT_PULLUP);
  attachInterrupt(AXP202_INT, [] {
    irq = true;
  }, FALLING);

  // Start accelerometer
  if (!ttgo->bma->begin()) {
    DEBUG_PRINTLN("Failed to connect to accelerometer");
    while (1);
  }
  ttgo->bma->enableAccel();

  //Set initial fundamental, scale and tempo values
  sm.setFundamental(48);
  sm.setCurrentScale(MAJOR);
  tapTempo.setMaxBPM(120);
  tapTempo.setTotalTapValues(10);

  // Interrupt timer for midi clock & timed notes/arpeggiator functions
  //  timer = timerBegin(0, 80, true); //timer 0, prescaled to milliseconds, true = counts up
  //  timerAttachInterrupt(timer, &isr, true);
  //  timerAlarmWrite(timer, 500000 / 24, true); //times are in microseconds. timer deafults to 120 bpm
  //  timerAlarmEnable(timer);

  // in arpeggiated/timed note modes, this task checks for interrupt flag on Core 0 loop to trigger note ASAP without having to wait for core 1 tasks to finish.
  xTaskCreatePinnedToCore(
    checkNoteInterrupt, /* Function to implement the task */
    "checkNote", /* Name of the task */
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    0,  /* Priority of the task */
    &checkNote,  /* Task handle. */
    0); /* Core where the task should run */

  DEBUG_PRINTLN("Setup Complete");

  styleSetup();
  //    loadScalePage();
  //  loadWaitingPage();
  loadConnectionPage();
  //  loadMIDIMenu();
  //  sendAllOSC();

}
