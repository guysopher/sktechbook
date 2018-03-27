/*************************************************
 * Filename: SOMODuino
 * Created: 18 April 2010
 * Author: Doyle Maleche -> maleche1 at comcast dot net
 * Description: Arduino code to test the SOMO-14D with Serial
 * Modifed code from 4dsystems to work with Arduino
 * Version: 0.1
 **************************************************/
// 
// Use HyperTerminal or any Terminal program to benefit from the screen refresh
// This code is works with the Arduino
// Please let me know of any updates you may add so I can learn from it.

// Refactored to function as an add-on h file, hopefully to become a library one day
// Zvika Markfeld, April 19, 2011
#include <Arduino.h>

//const unsigned int SOMO_MIN_VOLUME = 0; // Minimum volume
//const unsigned int SOMO_MAX_VOLUME = 7; // Max Volume 

#define SOMO_MIN_VOLUME 0
#define SOMO_MAX_VOLUME 7

const unsigned int PlyPse = 0xfffe; // Play or Pause
const unsigned int Stop= 0xFFFF; // Stop

int pinClock = 2;
int pinData = 3;
int pinBusy = 4;
int pinReset = 5;

/**********************************************************************************
 * Reset
 **********************************************************************************/

void somo_reset()
{
  Serial.println("SOMO: Resetting");
  digitalWrite(pinReset,LOW);
  delay(50);
  digitalWrite(pinReset,HIGH);
}

/**********************************************************************************
 * Init
 **********************************************************************************/

void somo_init() {
  pinMode(pinData,OUTPUT); // set pin 4 to output for Data
  pinMode(pinClock,OUTPUT); // set pin 3 to output for data
  pinMode(pinReset,OUTPUT); // set pin 7 to allow software reset
  pinMode(pinBusy,INPUT); // set pin 6 to monitor while Song is playing
  somo_reset();
}

void somo_init(int clock, int data, int busy, int reset) {
  pinClock = clock;
  pinData = data;
  pinBusy = busy;
  pinReset = reset;
  somo_init();
}


/**********************************************************************************
 * Send Sequence
 **********************************************************************************/

void somo_send_data(int ThisSong)
{
  int TheSong = ThisSong;
  int ClockCounter=0;
  int ClockCycle=15;//0x0f;

  digitalWrite(pinClock,HIGH); // Hold (idle) for 300msec to prepare data start
  delay(300); 
  digitalWrite(pinClock,LOW); //Hold for 2msec to signal data start
  delayMicroseconds(2000); //2msec delay

  while(ClockCounter <= ClockCycle)
  { 
    digitalWrite(pinClock,LOW); 
    if (TheSong & 0x8000)
    {
      digitalWrite(pinData,HIGH);
    }
    else
    {
      digitalWrite(pinData,LOW);
    }
    TheSong = TheSong << 1;
    delayMicroseconds(200); //Clock cycle period is 200 uSec - LOW
    digitalWrite(pinClock,HIGH);
    ClockCounter++;
    delayMicroseconds(200); //Clock cycle period is 200 uSec - HIGH
  }

  digitalWrite(pinData,LOW);
  digitalWrite(pinClock,HIGH); // Place clock high to signal end of data
}
  
/**********************************************************************************
 * Plays Stored Song by Number
 **********************************************************************************/

void somo_play_song(int songNumber)
{ 
  // somo_send_data(Stop);
  delay(5);
  if (songNumber >= 512 || songNumber <0){ // Warn if song number is not within range limit
    Serial.print(songNumber);
    Serial.println(" is not within 0 and 511");
  }
  else {
    Serial.print("-> Playing Song No.");
    Serial.println(songNumber);
    somo_send_data(songNumber);
  }
}

/**********************************************************************************
 * Play/Pause function, play or pause the Song
 **********************************************************************************/
void somo_pause_play()
{
  Serial.println("Play/Pause.");
  somo_send_data(PlyPse);
}

/**********************************************************************************
 * Stop Song
 **********************************************************************************/
void somo_stop()
{ 
  Serial.println("Stop.");
  somo_send_data(Stop);
}

/**********************************************************************************
 * Volume Control
 **********************************************************************************/
void somo_set_volume(int volume)
{
  // should be within the volume range
  if (volume > SOMO_MAX_VOLUME | volume < SOMO_MIN_VOLUME){ 
    Serial.print("can't set volume to: ");
    Serial.print(volume);
    Serial.println(", out of range");
  }
  else {
    Serial.print("setting volume to: ");
    Serial.println(volume);
    int tVol = 0xfff0 + volume; // Temp Volume
    somo_send_data(tVol);
  }
}


boolean somo_is_busy() {
  return digitalRead(pinBusy);
}

/**********************************************************************************
 * Cycle Through and play all sound files 
 **********************************************************************************/
void somo_cycle_songs()
{
  int Busy=0;
  long Start=0;
  for(int Song=0;Song< 512;Song++) //Start with file 0 end with file 511
  { 
    Start = 0; //Reset Start timer
    Serial.print("Cycle Song=");
    Serial.println(Song);
    Start = millis(); // Set Start timer to current clock cycle (internal to MCU)
    somo_send_data(Song); // Play current Song
    delay(50); // Wait for BUSY signal (LED) to initialize
    while(somo_is_busy());
    if (millis() - Start < 900){
      break;
    }
    // Test if we are at the last song
    // if the difference between the current MCU timer and Start timer is < 900ms,
    // we are at end or the Song is too short. Exit the FOR/LOOP 
  }
}



