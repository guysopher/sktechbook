/*
  TeleduinoSerial.pde - TeleduinoSerial example
  Version 328-0.6.7
  Nathan Kennedy 2012
  http://www.teleduino.org

  This sketch is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <EEPROM.h>
#include <Servo.h>
#include <Wire.h>
#include <Teleduino328.h>

// User configurable variables
long serialBaud = 9600;

// Other required variables
byte data[257];
byte dataLength;
byte hexStage;
unsigned long lastRefresh = 0;
byte stage = 0;

void setup()
{
  // Load presets
  Teleduino.loadPresets();
  
  // Start serial port
  Serial.begin(serialBaud);
}

void loop()
{
  // What we need to do depends on which 'stage' we are at
  switch(stage)
  {
    case 0: // Wait for start byte
      if(Serial.available())
      {
        char c = Serial.read();
        if(c == '?')
        {
          stage++;
        }
      }
      break;
    case 1: // Reset variables
      dataLength = 0;
      hexStage = 0;
      stage++;
      break;
    case 2: // Instruction byte
      if(Serial.available())
      {
        char c = Serial.read();
        if(c == '?')
        {
          stage = 1;
          break;
        }
        else if(c == '\r' || c == '\n' || c == '.')
        {
          stage = 0;
          break;
        }
        if(!hexStage)
        {
          data[0] = Teleduino.hexDecode(c) * 16;
        }
        else
        {
          data[0] += Teleduino.hexDecode(c);
        }
        hexStage = !hexStage;
        if(!hexStage)
        {
          stage++;
        }
      }
      break;
    case 3: // Data length byte
      if(Serial.available())
      {
        char c = Serial.read();
        if(c == '?')
        {
          stage = 1;
          break;
        }
        else if(c == '\r' || c == '\n' || c == '.')
        {
          stage = 0;
          break;
        }
        if(!hexStage)
        {
          data[1] = Teleduino.hexDecode(c) * 16;
        }
        else
        {
          data[1] += Teleduino.hexDecode(c);
        }
        hexStage = !hexStage;
        if(!hexStage)
        {
          stage++;
        }
      }
      break;
    case 4: // Data
      if(Serial.available())
      {
        char c = Serial.read();
        if(c == '?')
        {
          stage = 1;
          break;
        }
        else if(c == '\r' || c == '\n' || c == '.')
        {
          if(dataLength == data[1])
          {
            stage++;
            break;
          }
          else
          {
            stage = 0;
            break;
          }
        }
        if(!hexStage)
        {
          data[2 + dataLength] = Teleduino.hexDecode(c) * 16;
        }
        else
        {
          data[2 + dataLength] += Teleduino.hexDecode(c);
        }
        hexStage = !hexStage;
        if(!hexStage)
        {
          dataLength++;
        }
      }
      break;
    case 5: // Execute instruction and return result
      Teleduino.instruction(data);
      Serial.write('!');
      for(int i = 0; i < data[1] + 2; i++)
      {
        Serial.write(Teleduino.hexEncode(data[i] / 16));
        Serial.write(Teleduino.hexEncode(data[i] % 16));
      }
      Serial.println();
      stage = 0;
      break;
  }
  
  // Process refreshes every 50ms
  if(millis() - lastRefresh >= 50)
  {
    Teleduino.pinTimers();
    Teleduino.shiftRegisterTimers();
    Teleduino.shiftRegisters();
    lastRefresh = millis();
  }
  
  // Check to see if reset has been requested
  Teleduino.checkReset();
}
