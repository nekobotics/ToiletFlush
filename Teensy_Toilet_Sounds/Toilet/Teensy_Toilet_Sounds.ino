// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 1-3: First "Hello World" program, play a music file
//
// WAV files for this and other Tutorials are here:
// http://www.pjrc.com/teensy/td_libs_AudioDataFiles.html

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=81.19999694824219,162.1999969482422
AudioPlaySdWav           playSdWav2;     //xy=140.1999969482422,279.1999969482422
AudioMixer4              mixer1;         //xy=331.1999702453613,187.20001220703125
AudioMixer4              mixer2; //xy=393.1999702453613,273.1999855041504
AudioOutputI2S           i2s1;           //xy=656.1999969482422,201.1999969482422
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=391.1999969482422,383.1999969482422
// GUItool: end automatically generated code


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN   14  // Teensy 4 ignores this, uses pin 13


#define ShowerInput 40
#define ToiletInput 41
bool ToiletPull = false;
// Use these with the Teensy 3.5 & 3.6 & 4.1 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13


void setup() {
  pinMode(ShowerInput,INPUT);
  pinMode(ToiletInput,INPUT);
  
  
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
}

void loop() {
  if(digitalRead(ShowerInput) == HIGH && playSdWav1.isPlaying() == false){
    //Serial.println("Start playing");
    playSdWav1.play("Shower.WAV");
    delay(10); // wait for library to parse WAV info
  }
  else if (digitalRead(ShowerInput) == LOW){
    playSdWav1.stop();
  }

  if(digitalRead(ToiletInput) == HIGH && playSdWav2.isPlaying() == false && ToiletPull == false){
    //Serial.println("Start playing");
    playSdWav2.play("Flush.WAV");
    delay(10); // wait for library to parse WAV info
    ToiletPull = true;
  }
  else if(digitalRead(ToiletInput) == LOW && playSdWav2.isPlaying() == false){
    ToiletPull = false;
  }


}




