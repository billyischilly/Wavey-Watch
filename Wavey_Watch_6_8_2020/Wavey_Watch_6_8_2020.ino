/* Wavey Watch
    TO DO:
    1. Vibrato page - remove border, map line width to expression, rainbow colours(?)
    2. RTP Midi and OSC menu
    3. Work out why bluetooth and WIFI connections are dropped and how to reconnect without restarting
    4. Two Hand mode functionality
    5. Connect Menu and Waiting pages look a bit poop
    6. Airharp Mode add colours, smooth y axis more, full 360 mapping
    7. Add some kind of charging indicators
*/

#include <Arduino.h>
#include "config.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h> /// https://github.com/CNMAT/OSC
#include <OSCBundle.h> /// https://github.com/CNMAT/OSC
#include <ArduinoTapTempo.h>
#include <ScaleManager.h>
#include "lvgl_styles.h"

TTGOClass *ttgo;

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x)     Serial.print (x)
#define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#endif

enum screenMode {
  CHOOSE_HAND,
  CONNECT_MENU,
  MIDI_MENU,
  OSC_MENU,
  AIRHARP,
  VIBRATO,
  SEND_ALL_MIDI,
  OSC,
  SCALE_SETTINGS
};

screenMode currentScreenMode = CONNECT_MENU;

static lv_obj_t *fundamentalLabel;
static lv_obj_t *scaleLabel;

ScaleManager sm(true);
ArduinoTapTempo tapTempo;

Accel acc;

byte currentNote;
byte lastNote;
bool noteIsOn;

volatile bool midiClock;
volatile byte clockCount = 0;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
bool irq = false;

void IRAM_ATTR isr() {
  portENTER_CRITICAL(&timerMux);
  midiClock = true;
  portEXIT_CRITICAL(&timerMux);
}

TaskHandle_t checkNote;
