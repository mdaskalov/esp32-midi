#pragma once

#include <utility>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Intervals
#define _P1  0  // Unison.
#define _P4  5  // Perfect fourth.
#define _P5  7  // Perfect fifth.
#define _P8  12 // Octave.
#define _P11 17 // Perfect eleventh.
#define _P12 19 // Perfect twelfth.
#define _P15 24 // Perfect fifteenth, double octave.

// Minor
#define _m2  1
#define _m3  3
#define _m6  8
#define _m7  10
#define _m9  13
#define _m10 15
#define _m13 20
#define _m14 22

// Major
#define _M2  2
#define _M3  4
#define _M6  9
#define _M7  11
#define _M9  14
#define _M10 16
#define _M13 21
#define _M14 23

// Diminished
#define _d1  -1
#define _d2  0
#define _d3  2
#define _d4  4
#define _d5  6
#define _d6  7
#define _d7  9
#define _d8  11
#define _d9  12
#define _d10 14
#define _d11 16
#define _d12 18
#define _d13 19
#define _d14 21
#define _d15 23

// Augmented
//#define _A1  1
#define _A2  3
#define _A3  5
#define _A4  6
#define _A5  8
#define _A6  10
#define _A7  12
#define _A8  13
#define _A9  15
#define _A10 17
#define _A11 18
#define _A12 20
#define _A13 22
#define _A14 24
#define _A15 25

static const char *noteNames[2][12] = {
  {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"},
  {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}
};

static vector<pair<const char *, vector<int>>> chords = {
  // Major
  { "",                { _P1, _M3, _P5 } },                        // major (M ^)
  { "sus2",            { _P1, _M2, _P5 } },                        // suspended second
  { "sus4",            { _P1, _P4, _P5 } },                        // suspended fourth (sus)
  { "add2",            { _P1, _M2, _M3, _P5 } },
  { "add9",            { _P1, _M3, _P5, _M9 } },                   // (2 add9 add2)
  { "addb9",           { _P1, _M3, _P5, _m9 } },
  { "4",               { _P1, _P4, _m7, _m10 } },                  // (quartal)
  { "b5",              { _P1, _M3, _d5 } },
  { "6",               { _P1, _M3, _P5, _M6 } },                   // sixth (add6 add13 M6)
  { "6sus4",           { _P1, _P4, _P5, _M6 } },
  { "6/9",             { _P1, _M2, _M3, _P5, _M6 } },
  { "6/9",             { _P1, _M3, _P5, _M6, _M9 } },              // sixth/ninth (69 M69)
  { "6/9/11",          { _P1, _M3, _P5, _M6, _M9, _P11 } },
  { "6/9/#11",         { _P1, _M3, _P5, _M6, _M9, _A11 } },
  { "6/#11",           { _P1, _M3, _P5, _M6, _A11 } },             // (M6b5 6#11 6b5)
  { "9sus4",           { _P1, _M2, _P4, _P5 } },                   // (sus24 sus4add9)
  { "9sus4",           { _P1, _M2, _P4, _P5, _m7 } },
  { "11",              { _P1, _P5, _m7, _M9, _P11 } },             // eleventh
  { "11/b9",           { _P1, _P5, _m7, _m9, _P11 } },
  { "7/9/13",          { _P1, _M2, _M3, _P5, _M6, _m7 } },
  { "7/9/13",          { _P1, _M3, _P5, _m7, _M9, _M13 } },        // dominant thirteenth
  { "7/9/13",          { _P1, _M3, _m7, _M9, _M13 } },             // (13no5)
  { "7/9/13sus4",      { _P1, _P4, _P5, _m7, _M9, _M13 } },        // (13sus)
  { "13b5",            { _P1, _M3, _d5, _M6, _m7, _M9 } },
  { "Maj7",            { _P1, _M3, _M7 } },                        // major seventh
  { "Maj7",            { _P1, _M3, _P5, _M7 } },                   // major seventh (Δ ma7 maj7 Maj7 ^7)
  { "Maj7sus4",        { _P1, _P4, _P5, _M7 } },                   // (M7sus4)
  { "Maj7/b5",         { _P1, _M3, _d5, _M7 } },                   // (M7b5)
  { "Maj7/#5",         { _P1, _M3, _A5, _M7 } },                   // augmented seventh Maj7+5 +maj7 ^7#5)
  { "Maj7/#5sus4",     { _P1, _P4, _A5, _M7 } },
  { "Maj7/b6",         { _P1, _M3, _m6, _M7 } },                   // major seventh flat sixth (^7b6)
  { "Maj7/b9",         { _P1, _m2, _M3, _P5, _M7 } },              // P1, m2, M3, P5, m7
  { "Maj7/b9",         { _P1, _M3, _P5, _M7, _m9 } },
  { "Maj7/9",          { _P1, _M3, _P5, _M7, _M9 } },              // major ninth (Δ9 ^9)
  { "Maj7/9/11",       { _P1, _M3, _P5, _M7, _M9, _P11} },
  { "Maj7/9/11/13",    { _P1, _M3, _P5, _M7, _M9, _P11, _M13} },
  { "Maj7/9/13",       { _P1, _M3, _P5, _M7, _M9, _M13 } },        // major thirteenth (Maj13 ^13)
  { "Maj7/#9/#11",     { _P1, _M3, _P5, _M7, _A9, _A11 } },
  { "Maj7/11",         { _P1, _M3, _P4, _P5, _M7 } },
  { "Maj7#11",         { _P1, _M3, _P5, _M7, _A11 } },             // major seventh sharp eleventh ( Δ#4 Δ#11 M7#11 ^7#11 maj#4)
  { "Maj7/13",         { _P1, _M3, _P5, _M6, _M7 } },
  { "Maj7/9/13",       { _P1, _M3, _P5, _M6, _M7, _M9 } },
  { "Maj7/9",          { _P1, _M2, _M3, _P5, _M7 } },              // P1, M2, M3, d5, P5, M7
  { "Maj7/9sus4",      { _P1, _M2, _P4, _P5, _M7 } },
  { "Maj7/9sus4",      { _P1, _P4, _P5, _M7, _M9 } },
  { "Maj9/b5",         { _P1, _M3, _d5, _M7, _M9 } },
  { "Maj9/#5",         { _P1, _M3, _A5, _M7, _M9 } },              // (Maj9#5)
  { "Maj9/#5sus4",     { _P1, _P4, _A5, _M7, _M9 } },
  { "Maj7/9/#11",      { _P1, _M3, _P5, _M7, _M9, _A11 } },        // major sharp eleventh (lydian) (Δ9#11 ^9#11)
  { "Maj7/9/11",       { _P1, _M2, _M3, _P4, _P5, _M7 } },
  { "Maj7/9/13",       { _P1, _M2, _M3, _P5, _M6, _M7 } },
  { "Maj7/9/#11/13",   { _P1, _M3, _P5, _M7, _M9, _A11, _M13 } },  // Maj13#11 M13+4 M13#4)

  // Minor
  // - normal
  { "m",               { _P1, _m3, _P5 } },                        // minor (min -)
  { "madd4",           { _P1, _m3, _P4, _P5 } },
  { "madd9",           { _P1, _m3, _P5, _M9 } },
  { "m6",              { _P1, _m3, _P5, _M6 } },                   // minor sixth (-6)
  { "m7",              { _P1, _m3, _m7 } },                        // minor seventh
  { "m7",              { _P1, _m3, _P5, _m7 } },                   // minor seventh (min7 mi7 -7)
  { "m7/11",           { _P1, _m3, _P5, _m7, _P11 } },             // (m7add4)
  { "mb6/b9",          { _P1, _m3, _m6, _m9 } },
  { "m6/9",            { _P1, _m3, _P5, _M6, _M9 } },              // (m69 -69)
  { "m6/9",            { _P1, _M2, _m3, _P5, _M6 } },
  { "m7/#5",           { _P1, _m3, _m6, _m7 } },
  { "m7/b5",           { _P1, _m3, _d5, _m7 } },                   // half-diminished (ø -7b5 h7 h)
  { "m7/9",            { _P1, _M2, _m3, _P5, _m7 } },
  { "m7/9/11",         { _P1, _M2, _m3, _P4, _P5, _m7 } },
  { "m7/9/13",         { _P1, _M2, _m3, _P5, _M6, _m7 } },
  { "m7/11",           { _P1, _m3, _P4, _P5, _m7 } },
  { "m7/13",           { _P1, _m3, _P5, _M6, _m7 } },
  { "m9",              { _P1, _m3, _P5, _m7, _M9 } },              // minor ninth ( -9)
  { "m9/b5",           { _P1, _M2, _m3, _d5, _m7 } },
  { "m9/#5",           { _P1, _m3, _m6, _m7, _M9 } },
  { "mMaj7",           { _P1, _m3, _P5, _M7 } },                   // minor/major seventh (m/ma7 m/maj7 mM7 mMaj7 m/M7 -Δ7 mΔ -^7)
  { "mMaj7/b5",        { _P1, _m3, _d5, _M7 } },                   // (oM7)
  { "mMaj7/b6",        { _P1, _m3, _P5, _m6, _M7 } },
  { "mMaj7/b9",        { _P1, _m2, _m3, _P5, _M7 } },              // P1, m2, M3, P5, m7
  { "mMaj7/9",         { _P1, _M2, _m3, _P5, _M7 } },
  { "mMaj7/9",         { _P1, _m3, _P5, _M7, _M9 } },              // minor/major ninth (mM9 mMaj9 -^9)
  { "mMaj7/9/11",      { _P1, _M2, _m3, _P4, _P5, _M7 } },
  { "mMaj7/9/13",      { _P1, _M2, _m3, _P5, _M6, _M7 } },
  { "mMaj7/11",        { _P1, _m3, _P4, _P5, _M7 } },
  { "mMaj7/13",        { _P1, _m3, _P5, _M6, _M7 } },
  { "mMaj9/b6",        { _P1, _m3, _P5, _m6, _M7, _M9 } },
  { "madd9",           { _P1, _M2, _m3, _P5 } },
  { "m7/9/11",         { _P1, _m3, _P5, _m7, _M9, _P11 } },        // minor eleventh ( -11)
  { "m11",             { _P1, _m3, _A5, _m7, _M9, _P11 } },
  { "m7/9/13",         { _P1, _m3, _P5, _m7, _M9, _M13 } },        // minor thirteenth (-13)

  // Augmented
  { "aug",             { _P1, _M3, _A5 } },                        // augmented (+ +5 ^#5)
  { "aug#9",           { _P1, _M3, _A5, _A9 } },                   // (+add#9)
  { "aug7",            { _P1, _M3, _A5, _m7 } },                   // (7#5 +7 7+ 7aug)
  { "aug7/b9/#11",     { _P1, _M3, _A5, _m7, _m9, _A11 } },        // (7#5b9#11)
  { "aug7/9",          { _P1, _M3, _A5, _m7, _M9 } },              // (9+ 9#5)
  { "aug7/9",          { _P1, _M3, _m7, _M9, _m13 } },
  { "aug7/#9",         { _P1, _M3, _A5, _m7, _A9 } },              // (7#9#5 7alt)
  { "aug9",            { _P1, _M3, _A5, _M9 } },                   // (+add9)

  // Diminished
  { "dim",             { _P1, _m3, _d5 } },                        // diminished (° o)
  { "dim7",            { _P1, _m3, _d5, _d7 } },                   // diminished seventh (°7 o7)

  // Dominant
  { "7",               { _P1, _M3, _m7 } },                        // (7no5)
  { "7",               { _P1, _M3, _P5, _m7 } },                   // dominant seventh (dom)
  { "7",               { _P1, _M3, _m7, _m9 } },                   // altered (alt7)
  { "7add6",           { _P1, _M3, _P5, _m7, _M13 } },             // (67 7add13)
  { "7sus4",           { _P1, _P4, _P5, _m7 } },                   // suspended fourth seventh (7sus)
  { "7/b9sus4",        { _P1, _P4, _P5, _m7, _m9 } },              // suspended fourth flat ninth (phryg 7b9sus 7b9sus4)
  { "7/b9/b13sus4",    { _P1, _P4, _P5, _m7, _m9, _m13 } },        // (7b9b13sus4)
  { "7/b13",           { _P1, _M3, _m7, _m13 } },
  { "7/b5",            { _P1, _M3, _d5, _m7 } },
  { "7/#5sus4",        { _P1, _P4, _A5, _m7 } },
  { "7/#5/b9",         { _P1, _m2, _M3, _m6, _m7 } },
  { "7/#5/b9",         { _P1, _M3, _A5, _m7, _m9 } },              // (7b9#5)
  { "7/b6",            { _P1, _M3, _P5, _m6, _m7 } },
  { "7/b9",            { _P1, _M3, _P5, _m7, _m9 } },              // dominant flat ninth
  { "7/b9",            { _P1, _m2, _M3, _P5, _m7 } },
  { "7/#9",            { _P1, _M3, _P5, _m7, _A9 } },              // dominant sharp ninth
  { "7/b9/#11",        { _P1, _M3, _P5, _m7, _m9, _A11 } },        // (7b5b9 7b9b5)
  { "7/b9/#11/b13",    { _P1, _M3, _P5, _m7, _m9, _A11, _m13 } },  // (7b9#11b13 7b5b9b13)
  { "7/b9/#11/13",     { _P1, _M3, _P5, _m7, _m9, _A11, _M13 } },  // (13b9#11)
  { "7/b9/b13",        { _P1, _M3, _P5, _m7, _m9, _m13 } },
  { "7/b9/13",         { _P1, _M3, _P5, _m7, _m9, _M13 } },        // (13b9)
  { "7/b9/#9",         { _P1, _M3, _P5, _m7, _m9, _A9 } },
  { "7/9/11",          { _P1, _M2, _M3, _P4, _P5, _m7 } },
  { "7/9/b5",          { _P1, _M3, _d5, _m7, _M9 } },
  { "7/9/#11",         { _P1, _M3, _A5, _m7, _M9, _A11 } },
  { "7/9/#11",         { _P1, _M3, _P5, _m7, _M9, _A11 } },        // (9+4 9#4)
  { "7/9/#11",         { _P1, _M2, _M3, _d5, _P5, _m7 } },
  { "7/9/b13",         { _P1, _M2, _M3, _P5, _m6, _m7 } },
  { "7/#9",            { _P1, _m3, _M3, _P5, _m7 } },
  { "7/#9/#11",        { _P1, _M3, _P5, _m7, _A9, _A11 } },        // (7b5#9 7#9b5)
  { "7/#9/#11/13",     { _P1, _M3, _P5, _m7, _A9, _A11, _M13 } },  // (13#9#11)
  { "7/#9/#11/b13",    { _P1, _M3, _P5, _m7, _A9, _A11, _m13 } },
  { "7/#9/13",         { _P1, _M3, _P5, _m7, _A9, _M13 } },        // (13#9)
  { "7/#9/b13",        { _P1, _M3, _P5, _m7, _A9, _m13 } },
  { "7/11",            { _P1, _M3, _P4, _P5, _m7 } },
  { "7/#11/b13",       { _P1, _M3, _P5, _m7, _A11, _m13 } },       // (7b5b13)
  { "7/#11",           { _P1, _M3, _P5, _m7, _A11 } },             // lydian dominant seventh (7#4)
  { "7/13",            { _P1, _M3, _P5, _M6, _m7 } },
  { "7/9/#11/b13",     { _P1, _M3, _P5, _m7, _M9, _A11, _m13 } },  // (9b5b13)
  { "7/9/#11/13",      { _P1, _M3, _P5, _m7, _M9, _A11, _M13 } },  // (13#11 13+4 13#4)
  { "7/9",             { _P1, _M3, _m7, _M9 } },                   // (9no5)
  { "7/9",             { _P1, _M2, _M3, _P5, _m7 } },
  { "7/9",             { _P1, _M3, _P5, _m7, _M9 } },              // dominant ninth
  { "7/9sus4",         { _P1, _P4, _P5, _m7, _M9 } },              // (9sus)
  // Other
  { "5",               { _P1, _P5 } },                             // fifth
//  { "m#5",             { _P1, _m3, _A5 } },                        // minor augmented (-#5 m+)
};

class ChordRecognizer {
  public:
  int keySignature = 0;

  ChordRecognizer() {}

  int getNoteOctave(int note) {
    return (note/12) - 2;
  }

  const char *getNoteName(int note) {
    return noteNames[keySignature < 0 ? 1 : 0][note % 12];
  }

  string getNotes(const vector<int> &notes) {
    stringstream ss;
    bool first = true;
    for(auto note:notes) {
      if (first)
        first = false;
      else
        ss << ", ";
      ss << getNoteName(note) << getNoteOctave(note);

    }
    return ss.str();
  }

  int getInterval(int n1, int n2) {
    int diff = abs(n2-n1);
    return (diff <= 25) ? diff : -1;
  }

  string getKey() {
    static const char *sharpCircle[] = { "C", "G", "D",  "A",  "E",  "B",  "F#", "C#" };
    static const char *flatCircle[] =  { "C", "F", "Bb", "Eb", "Ab", "Db", "Gb", "Cb" };
    return keySignature < 0 ? flatCircle[-keySignature] : sharpCircle[keySignature];
  }

  string getChord(const vector<int> &sortedNotes) {
    int size = sortedNotes.size();
    if (size == 0)
      return getKey();
    for (int inversion = 0; inversion < size; inversion++) {
      vector<int> intervals;
      int idx = inversion;
      int addOctave = 0;
      int rootNote = sortedNotes[idx];
      for (int i = 0; i < size; i++) {
        int note = sortedNotes[idx++]+addOctave;
        int interval = getInterval(note,rootNote);
        intervals.push_back(interval);
        if (idx >= size) {
          idx = 0;
          addOctave += (interval > 12) ? 24 : 12; // add one or two octaves
        }
      }
      for (auto chord:chords) {
        if (intervals == chord.second) {
          dumpChord(rootNote, chord);
          return getNoteName(rootNote)+string(chord.first);
        }
      }
    }
    return getNotes(sortedNotes);
  }

  void dumpChord(int rootNote, const pair<const char *, vector<int>> &chord) {
    Serial.printf("%s%s: ",noteNames[keySignature < 0 ? 1 : 0][rootNote % 12],chord.first);
    for (auto interval:chord.second) {
      Serial.printf("%d ",interval);
    }
    Serial.printf("( ");
    for (auto interval:chord.second) {
      int note = rootNote+interval;
      Serial.printf("%s%d ",getNoteName(note),getNoteOctave(note));
    }
    Serial.printf(")\n");
  }
};
