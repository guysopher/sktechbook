/*
  Teleduino328.h - Teleduino328 library
  Version 328-0.6.7
  Nathan Kennedy 2012
  http://www.teleduino.org

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef Teleduino328_h
#define Teleduino328_h

#include <Arduino.h>
#include <EEPROM.h>
#include <Servo.h>
#include <Wire.h>

// Used for TeleduinoClass::getFreeMemory()
extern unsigned int __data_start;
extern unsigned int __data_end;
extern unsigned int __bss_start;
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

typedef struct
{
  byte mode;
  byte expireAction;
  unsigned long expireTime;
} Pin;

typedef struct
{
  Servo servo;
  byte position;
} ServoInstance;

typedef struct
{
  byte clockPin;
  byte dataPin;
  byte enablePin;
  byte latchPin;
  byte outputs[32];
} ShiftRegister;

typedef struct
{
  byte shiftRegister;
  byte action;
  unsigned long expireTime;
  byte outputs[32];
} ShiftRegisterTimer;

class TeleduinoClass
{
  protected:
    boolean _reset;
    Pin _pins[22];
    ServoInstance _servoInstances[6];
    ShiftRegister _shiftRegisters[2];
    ShiftRegisterTimer _shiftRegisterTimers[8];
    byte _statusLedPin;
    char _version[17];
  boolean _wireDefined;
  public:
    TeleduinoClass();
    boolean checkAnalogPin(byte);
    boolean checkDigitalPin(byte);
    boolean checkPwmPin(byte);
    void checkReset();
    boolean definePinMode(byte, byte);
    int getFreeMemory();
    byte hexDecode(byte);
    byte hexEncode(byte, boolean);
    byte hexEncode(byte);
    void instruction(byte*);
    void loadPresets();
    void pinTimers();
    void reset();
    boolean setDigitalOutput(byte, byte, unsigned int);
    boolean setDigitalOutput(byte, byte);
    void setStatusLed(unsigned int, boolean, long);
    void setStatusLed(unsigned int, boolean);
    void setStatusLed(unsigned int, long);
    void setStatusLed(unsigned int);
    boolean setStatusLedPin(byte);
    void shiftRegisters();
    void shiftRegisterTimers();
};

extern TeleduinoClass Teleduino;

#endif
