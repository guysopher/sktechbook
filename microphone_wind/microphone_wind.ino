#include "Statistic.h"  // without trailing s

Statistic myStats; 

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
float sensorValue = 512;  // variable to store the value coming from the sensor

int avg = 0;
int stdev = 0;
int n = 100;


void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = smooth(sensorValue, analogRead(sensorPin));    
  // turn the ledPin on
  Serial.print(variance(sensorValue));
  Serial.print("\t");
  Serial.println(sensorValue);
  delay(10);
}

float smooth(float old_val, float new_val){
  float loops = 1;
  float res = (old_val * (loops-1) / loops) + (new_val / loops);
  return res;
}

int samples[n];
int pointer = 0;

int variance(int val){

  pointer = pointer % n;
  samples[pointer] = val;
  
  //calc avg
  int total = 0;
  for (int i=0; i<n; i++){
    total += samples[i];
  }
  avg = total / n;
  
  //calc stdev
  
  
  int sumx2 = n * (pow(stdev,2) + pow(avg,2)); 
  int sumx = n * avg;
  
  avg = (sumx + val) / (n+1);
  stdev = sqrt( ((n+1)*(pow(val, 2) + sumx2) - pow((val + sumx), 2)) / (pow((n+1),2)));
  return stdev;
}


