# ESP32 MIDI
ESP32 MIDI client and chord recognizer

This sketch uses the [MusiQwik](https://www.fontspace.com/musiqwik-font-f3722) font to show the MIDI notes. The font file `font.vlw` should be in the SPIFFS partition.  

To upload the font use following PlatformIO command:
```
pio run --target uploadfs --environment core2
```
In VS Code use: PlatformIO -> Project Tasks -> Upload Filesystem Image

Alternatively define `UPLOAD_FONT` when building the image (uncomment following line in `platformio.ini`)
```
;	-DUPLOAD_FONT
```
