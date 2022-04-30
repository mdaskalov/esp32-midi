#include "globals.h"

#include <set>
#include <vector>

using namespace std;

#ifndef CORE2
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // Invoke custom library
#endif

bool demo = false;
auto chord = chords.begin();
int demoRootNote = 60; //C3

int w = TFT_WIDTH;
int h = TFT_HEIGHT;

static portMUX_TYPE notesMutex = portMUX_INITIALIZER_UNLOCKED;
set<int> notes;
vector<int> sortedNotes;

MusicStaff *staff = new MusicStaff(STAFF_LEN);
ChordRecognizer *chordRecognizer = new ChordRecognizer();

TaskHandle_t hStaffTask;
TaskHandle_t hBluetoothTask;

void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity, uint16_t timestamp) {
  //Serial.printf("Received note on : channel %d, note %d, velocity %d (timestamp %dms)\n", channel, note, velocity, timestamp);
  portENTER_CRITICAL(&notesMutex);;
  notes.insert(note);
  portEXIT_CRITICAL(&notesMutex);
  BLEMidiServer.noteOn(0,note,velocity);
  xTaskNotifyGive(hStaffTask);
}

void onNoteOff(uint8_t channel, uint8_t note, uint8_t velocity, uint16_t timestamp) {
  //Serial.printf("Received note off : channel %d, note %d, velocity %d (timestamp %dms)\n", channel, note, velocity, timestamp);
  portENTER_CRITICAL(&notesMutex);
  notes.erase(note);
  portEXIT_CRITICAL(&notesMutex);
  BLEMidiServer.noteOff(0,note,velocity);
  xTaskNotifyGive(hStaffTask);
}

static void staffTask(void *context) {
  bool updated = true;
  while (true) {
    // wait few ticks after first notification to get all simultaneously pressed keys
    uint32_t ulNotificationValue = ulTaskNotifyTake(pdFALSE,pdMS_TO_TICKS(updated ? 10 : 200));
    if (ulNotificationValue > 0) {
      updated = true;
    }
    else if (updated) { // update only on timeout
      sortedNotes.clear();
      portENTER_CRITICAL(&notesMutex);
      copy(notes.begin(),notes.end(),std::back_inserter(sortedNotes));
      portEXIT_CRITICAL(&notesMutex);
      draw();
      updated = false;
    }
  }
}

void allNotesOff() {
  for (int ch=0; ch <= 15; ch++)
    BLEMidiServer.controlChange(ch,0x7b,0); // all notes off
}

void demoNextChord() {
  for (auto note:notes)
    BLEMidiServer.noteOff(0,note,90);
  notes.clear();

  //chordRecognizer->dumpChord(demoRootNote,*chord);

  for (auto interval:chord->second) {
    int note = interval + demoRootNote;
    BLEMidiServer.noteOn(0,note,90);
    notes.insert(note);
  }

  sortedNotes.clear();
  copy(notes.begin(),notes.end(),std::back_inserter(sortedNotes));
  draw();

  chord++;
  if (chord ==chords.end())
    chord = chords.begin();
}

void setup() {
  Serial.begin(115200);

  init();

  tftMessage(NAME " MIDI chords");

  spinlock_initialize(&notesMutex);
  xTaskCreatePinnedToCore(staffTask, "staffTask", 4096, NULL, 2, &hStaffTask, 1);

  Serial.println("Initializing BLE MIDI client");
  BLEMidiClient.begin(NAME " client");
  BLEMidiClient.setNoteOnCallback(onNoteOn);
  BLEMidiClient.setNoteOffCallback(onNoteOff);
  BLEMidiServer.begin(NAME " server");
  BLEMidiServer.setOnConnectCallback([]() {
    Serial.println("Server connected...");
    allNotesOff();
  });
  BLEMidiServer.setOnDisconnectCallback([]() {
    Serial.println("Server disconnected...");
  });
  // BLEMidiClient.enableDebugging();  // Uncomment to see debugging messages from the library
  // BLEMidiServer.enableDebugging();

  Serial.println("Initialized.");
  if (demo) {
    delay(1000);
    tftMessage("Demo mode");
  }
  delay(1000);
  tftMessage("");
  xTaskNotifyGive(hStaffTask);
}

void loop() {
#ifdef CORE2
  M5.update();

  if (M5.BtnA.wasPressed()) {
    Serial.println("btnA");
    updateKeySignature(staff->keySignature-1);
  }
  if (M5.BtnB.wasPressed()) {
    if (demo)
      demoNextChord();
    else {
      Serial.println("btnB pressed");
      BLEMidiClient.noteOn(0,60,100);
      notes.insert(60);
    }
  }
  if (M5.BtnB.wasReleased()) {
    if (!demo) {
      Serial.println("btnB released");
      BLEMidiClient.noteOff(0,60,100);
      notes.erase(60);
    }
  }
  if (M5.BtnC.wasPressed()) {
    Serial.println("btnC");
    updateKeySignature(staff->keySignature+1);
  }
#else
  btn1.loop();
  btn2.loop();
  btn1.setTapHandler([&](Button2 &b) {
    Serial.println("btn1");
    updateKeySignature(staff->keySignature-1);
  });
  btn2.setTapHandler([&](Button2 &b) {
    Serial.println("btn2");
    updateKeySignature(staff->keySignature+1);
  });
#endif
  if (!demo && !BLEMidiClient.isConnected()) {
    Serial.println("Scanning for BlE MIDI devices");
    int nDevices = BLEMidiClient.scan();
    Serial.printf("Found %d device(s)\n",nDevices);
    if (nDevices > 0) {
      Serial.println("Connecting to the first device");
      tftMessage("Connecting...");
      if (BLEMidiClient.connect(0)) {
        Serial.println("Client connected...");
        tftMessage("Connected");
        #ifdef CORE2
          M5.Axp.SetLed(BLEMidiClient.isConnected());
        #endif
        delay(1000);
        tftMessage("");
        xTaskNotifyGive(hStaffTask);
      }
      else {
        Serial.println("Connection failed");
        tftMessage("Failed");
      }
    }
  }
  // for (auto ch:chords) {
  //   Chord chord = Chord(60, ch.second);
  //   Serial.printf("chord: C%s -> %s\n",ch.first.c_str(), chord.notation().c_str());
  // }
}
