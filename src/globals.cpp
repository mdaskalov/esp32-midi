#include "globals.h"

#ifdef UPLOAD_FONT
extern const uint8_t fontFileData[] asm("_binary_data_font_vlw_start");
extern const uint8_t fontFileDataEnd[] asm("_binary_data_font_vlw_end");
#endif

extern int w;
extern int h;

extern vector<int> sortedNotes;

extern MusicStaff *staff;
extern ChordRecognizer *chordRecognizer;

extern TaskHandle_t hBluetoothTask;
extern TaskHandle_t hStaffTask;

#ifndef CORE2
extern TFT_eSPI tft;
#endif

TFT_eSprite staffSprite = TFT_eSprite(&tft);
TFT_eSprite chordSprite = TFT_eSprite(&tft);

void tftMessage(const char *msg) {
  tft.fillRect(0,h / 2 - TEXT_HEIGHT / 2,w,TEXT_HEIGHT,TFT_BLACK);
  tft.drawString(msg, w / 2, h / 2);
}

void updateKeySignature(int sig) {
  if (sig < -7 || sig > 7)
    return;
  staff->keySignature = sig;
  chordRecognizer->keySignature = sig;
  Serial.printf("KeySignature: %d\n",staff->keySignature);
  xTaskNotifyGive(hStaffTask);
}

void draw() {
  string staffStr = staff->getStaff(sortedNotes);
  #ifdef CORE2
  staffSprite.fillRect(0,0,w,STAFF_TOP_MARGIN,TFT_BLACK);
  staffSprite.fillRect(0,STAFF_HEIGHT-STAFF_BTM_MARGIN,w,STAFF_BTM_MARGIN,TFT_BLACK);
  #else
  staffSprite.fillSprite(TFT_BLACK);
  #endif
  staffSprite.drawString(staffStr.c_str(), 0, STAFF_TOP_MARGIN);
  staffSprite.pushSprite(0, 0);
  string chordStr = chordRecognizer->getChord(sortedNotes);
  chordSprite.fillSprite(TFT_BLACK);
  chordSprite.drawString(chordStr.c_str(), w / 2, CHORD_HEIGHT / 2);
  chordSprite.pushSprite(0,h  - CHORD_HEIGHT );
}

void uploadFontFile(String &fontFileName) {
#ifdef UPLOAD_FONT
  Serial.println("Uploading font file...");
  tftMessage("Preparing...");

  size_t fontFileSize = fontFileDataEnd - fontFileData;

  fs::File fontFile = SPIFFS.open(fontFileName, "w");
  Serial.printf("File size: %d\n",fontFileSize);

  size_t ofs = 0;
  while (ofs < fontFileSize) {
    size_t write = fontFileSize - ofs > 2048 ? 2048 : fontFileSize - ofs;
    size_t written = fontFile.write(fontFileData+ofs,write);
    if (written == 0) {
      Serial.println("Write error");
      break;
    }
    ofs += written;
  }
  for (int i=0; i<100; i++) {
    Serial.printf("0x%02X,%c",fontFileData[i],i%16 == 15 ? '\n' : ' ');
  }
  Serial.println("");
  fontFile.close();
  Serial.println("Font file created.");
#endif
}

void loadFont() {
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS not initialized...");
    tftMessage("Initializing...");
    SPIFFS.format();
    SPIFFS.begin();
    tftMessage("Done.");
  }

  String fontFileName = "/" FONT_NAME ".vlw";
  if (SPIFFS.exists(fontFileName))
    Serial.println("Font file found.");
  else
    uploadFontFile(fontFileName);

  staffSprite.loadFont(FONT_NAME,false);
}

void init() {
#ifdef CORE2
  M5.begin(true,false,false);
  M5.Axp.SetLcdVoltage(3300);
  M5.Axp.SetLed(0);
#else
  tft.init();
#endif
  tft.setRotation(ROTATION);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(TXT_SIZE);
  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);

  w = tft.width();
  h = tft.height();

  loadFont();

  staffSprite.createSprite(w,STAFF_HEIGHT);
  staffSprite.setTextDatum(TL_DATUM);
  staffSprite.setTextWrap(false);

  chordSprite.createSprite(w,CHORD_HEIGHT);
  chordSprite.setTextSize(3);
  chordSprite.setTextDatum(MC_DATUM);
  chordSprite.setTextWrap(false);
}