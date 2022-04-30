#pragma once

#include <Arduino.h>

#include <string>
#include <vector>

using namespace std;

class MusicStaff {
  public:
    static const int MIN_BASS_NOTE = 36;
    static const int MAX_BASS_NOTE = 61;
    static const int MIN_TREBLE_NOTE = 57;
    static const int MAX_TREBLE_NOTE = 82;
  private:
    bool useBassClef = false;
    int charSizeEqual = 480;
    int charSizeHyphen = 0; // 32
    int paddingLength = 11;
  public:
    int keySignature = 0;

    MusicStaff(int len) {
      paddingLength = len;
    }

    string keySignatureToString() {
      string res;
      if (keySignature != 0) {
        // 0x03bx -> CE Bx     // bass flat  (x -> 0-7)
        // 0x03cx -> CF 8x     // bass sharp
        // 0x1f0x -> E1 BC 8x  // flat
        // 0x1f8x -> E1 BE 8x  // sharp
        if (useBassClef) {
          res.push_back(keySignature < 0 ? '\xCE' : '\xCF');
          res.push_back(keySignature < 0 ? (char)(0xB0 - keySignature) : (char)(0x80 + keySignature));
        }
        else {
          res.push_back('\xE1');
          res.push_back(keySignature < 0 ? '\xBC' : '\xBE');
          res.push_back(keySignature < 0 ? ('\x80' - keySignature) : ('\x80' + keySignature));
          // res.push_back('\xC2');
          // res.push_back(keySignature < 0 ? ('\xA7' - keySignature) : ('\xA0' + keySignature));
        }
        // int hyphenCnt = 0;
        // switch (keySignature) {
        //   case -2:
        //   case  2:
        //     hyphenCnt = 1; break;
        //   case -3:
        //   case -4:
        //   case  3:
        //   case  4:
        //     hyphenCnt = 2; break;
        //   case -5:
        //   case  5:
        //     hyphenCnt = 3; break;
        //   case -6:
        //   case  6:
        //     hyphenCnt = 4; break;
        //   case -7:
        //   case  7:
        //     hyphenCnt = 5; break;
        // };
      }
      return res;
    }

    int keySignatureCharWidth() {
      switch (keySignature) {
        case  0: return 0;
        case -1:
        case  1: return 1 * charSizeEqual + 0 * charSizeHyphen; // 480
        case -2:
        case  2: return 2 * charSizeEqual + 1 * charSizeHyphen; // 992
        case -3:
        case -4:
        case  3:
        case  4: return 3 * charSizeEqual + 2 * charSizeHyphen; // 1504
        case -5:
        case  5: return 4 * charSizeEqual + 3 * charSizeHyphen; // 2016
        case -6:
        case  6: return 5 * charSizeEqual + 4 * charSizeHyphen; // 2528
        case -7:
        case  7: return 6 * charSizeEqual + 5 * charSizeHyphen; // 3040
      };
      return 0;
    }

    int flatValue(int note, bool &flat) {
      switch (note % 12) {
        case  0: flat=false; return 0;  // C
        case  1: flat=true;  return 1;  // Db
        case  2: flat=false; return 1;  // D
        case  3: flat=true;  return 2;  // Eb
        case  4: flat=false; return 2;  // E
        case  5: flat=false; return 3;  // F
        case  6: flat=true;  return 4;  // Gb
        case  7: flat=false; return 4;  // G
        case  8: flat=true;  return 5;  // Ab
        case  9: flat=false; return 5;  // A
        case 10: flat=true;  return 6;  // Bb
        case 11: flat=false; return 6;  // B
      };
      return -1;
    }

    int sharpValue(int note, bool &sharp) {
      switch (note % 12) {
        case  0: sharp=false; return 0; // C
        case  1: sharp=true;  return 0; // C#
        case  2: sharp=false; return 1; // D
        case  3: sharp=true;  return 1; // D#
        case  4: sharp=false; return 2; // E
        case  5: sharp=false; return 3; // F
        case  6: sharp=true;  return 3; // F#
        case  7: sharp=false; return 4; // G
        case  8: sharp=true;  return 4; // G#
        case  9: sharp=false; return 5; // A
        case 10: sharp=true;  return 5; // A#
        case 11: sharp=false; return 6; // B
      };
      return -1;
    }

    void adjustAccidentals(int note, bool &isSharp, bool &isFlat, bool &isNatural) {
      if (keySignature != 0) {
        int circleSharp[] =        {  6,  1,  8,  3, 10,  5,  0 }; // F#, C#, G#, D#, A#, E#, B#
        int circleSharpNatural[] = {  5,  0,  7,  2,  9,  4, 11 }; // F,  C,  G,  D,  A,  E,  B
        int circleFlat[] =         { 10,  3,  8,  1,  6, 11,  4 }; // Bb, Eb, Ab, Db, Gb, Cb, F
        int circleFlatNatural[] =  { 11,  4,  9,  2,  7,  0,  5 }; // B,  E,  A,  D,  G,  C,  F
        int max = abs(keySignature);
        if (max > 7)
          max = 7;
        int noteValue = note % 12;
        for (int idx=0; idx < max; idx++) {
          if (keySignature > 0) {
            if (noteValue == circleSharp[idx]) {
              isSharp = false;
              break;
            }
            if (noteValue == circleSharpNatural[idx]) {
              isNatural = true;
              break;
            }
          }
          else {
            if (noteValue == circleFlat[idx]) {
              isFlat = false;
              break;
            }
            if (noteValue == circleFlatNatural[idx]) {
              isNatural = true;
              break;
            }
          }
        }
      }
    }

    string noteToString(int note) {
      //        Unicode - UTF-8
      // flat    u+00E0 - C3 A0
      // note    u+0070 - 70
      // sharp   u+00D0 - C3 90
      // natural u+00F0 - C3 B0
      string res;

      if (!useBassClef && ((note < MIN_TREBLE_NOTE) || (note > MAX_TREBLE_NOTE)))
        return res;

      if (useBassClef &&((note < MIN_BASS_NOTE) || (note > MAX_BASS_NOTE)))
        return res;

      bool flat=false;
      bool sharp=false;
      bool natural=false;
      int octave = note / 12;
      int octaveOfs = useBassClef ? 3 : 5;
      int ofs = (octave-octaveOfs)*7+(useBassClef ? 0 : 2)+(keySignature < 0 ? flatValue(note,flat) : sharpValue(note,sharp));
      adjustAccidentals(note,sharp,flat,natural);
      if (flat) {
        res.push_back('\xC3');
        res.push_back(ofs +0xA0);
      }
      if (sharp) {
        res.push_back('\xC3');
        res.push_back(ofs +0x90);
      }
      if (natural) {
        res.push_back('\xC3');
        res.push_back(ofs +0xB0);
      }
      res.push_back(ofs +0x70);
      //res.push_back('=');
      return res;
    }

    int mostlyBassNotes(const vector<int> &notes) {
      if (notes.size() == 0) {
        return useBassClef;
      }
      int bassNotes = 0;
      for (auto note:notes) {
        int octave = note / 12;
        if (octave < 5)
          bassNotes++;
      }
      if (bassNotes > 0 && useBassClef)
        bassNotes++;
      return bassNotes > notes.size() / 2;
    }

    string stringPadding(int size) {
      string result;
      int paddingWithEqual = size / charSizeEqual;
      //int paddingWithHyphen = (size - paddingWithEqual*charSizeEqual) / charSizeHyphen;
      if (paddingWithEqual > 0) {
        result += string(paddingWithEqual,'=');
      }
      // if (paddingWithHyphen > 0) {
      //   result += string(paddingWithHyphen,'-');
      // }
      return result;
    }

    string getStaff(const vector<int> &notes) {
      useBassClef = mostlyBassNotes(notes);
      string res(useBassClef ? "'¯=" : "'&=");
      res += keySignatureToString();
      int totalSize = paddingLength * charSizeEqual;

      for (auto note:notes) {
        string noteText = noteToString(note);
        if (!noteText.empty()) {
          res += noteText + "=";
          int equalCount = noteText.size() > 1 ? 4 : 3; // includes accent or not
          totalSize -= equalCount * charSizeEqual;
        }
      }
      res += stringPadding(totalSize - keySignatureCharWidth());
      res.push_back('!');
      res.push_back(' ');

      //Serial.println(res.c_str());
      return res;
    }
};