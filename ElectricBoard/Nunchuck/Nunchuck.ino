#include <Wire.h>
#include "WiiChuck.h"

WiiChuck chuck = WiiChuck();

void setup() {
  Serial.begin(9600);
  chuck.begin();
  pinMode(9, OUTPUT);
}

void loop() {
  delay(20);
  chuck.update();
  Serial.print(chuck.readRoll());
  Serial.print(",\t");  
  Serial.print(chuck.readPitch());
  Serial.print(",\t");  
  Serial.print((int)chuck.readAccelX());
  Serial.print(",\t");  
  Serial.print((int)chuck.readAccelY());
  Serial.print(",\t");  
  Serial.print((int)chuck.readAccelZ());
  Serial.print(",\t");  
  Serial.print((int)chuck.zPressed());
  Serial.print(",\t");  
  Serial.print((int)chuck.cPressed());
  Serial.print(",\t");  
  Serial.print((int)chuck.readJoyX());
  Serial.print(",\t");  
  Serial.print((int)chuck.readJoyY());
  Serial.println();
    
}

