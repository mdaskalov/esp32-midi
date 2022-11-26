#pragma once

#include <BLEMidi.h>

#include "MusicStaff.hpp"
#include "ChordRecognizer.hpp"

#ifdef CORE2
  #include <M5Core2.h>

  #define tft M5.Lcd

  #define NAME        "Core2"

  #define ROTATION    1
  #define TXT_SIZE    2

  #define STAFF_LEN   17
#endif

#ifdef LILYGO
#include "Arduino.h"
#include "TFT_eSPI.h" // patched version
#include <Button2.h>
  #define NAME        "LILYGO"

  #define BUTTON_1    PIN_BUTTON_1
  #define BUTTON_2    PIN_BUTTON_2

  #define ROTATION    3
  #define TXT_SIZE    2

  #define STAFF_LEN   17
#else
  #include <SPI.h>
  #include <TFT_eSPI.h>
  #include <Button2.h>

  #define NAME        "ESP32"

  #define BUTTON_1    35
  #define BUTTON_2    0

  #define ROTATION    3
  #define TXT_SIZE    2

  #define STAFF_LEN   11
#endif

#define STAFF_TOP_MARGIN  25
#define STAFF_BTM_MARGIN  6
#define STAFF_HEIGHT      110
#define CHORD_HEIGHT      32
#define TEXT_HEIGHT       16

#define FONT_NAME         "font"

void tftMessage(const char *msg);
void updateKeySignature(int sig);
void draw();

void init();
