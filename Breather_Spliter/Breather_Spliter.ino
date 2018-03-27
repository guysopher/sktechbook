#include <Servo.h> 
 
const int threshold = 300;
const int samples = 40; 
const int triggers = 3;
const int blockingPeriod = 2000;

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

const int servo1 = 73;
const int servo2 = 155;

int flowing = 0;
int stopped = 0;
int flowStatus = -1;
float sensorValue = 0;
int output = 0;
int i = 0;
long lastSwitch = millis();
boolean is1 = true;
boolean blocked = false;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(servo1);
}

// the loop routine runs over and over again forever:
void loop() {
  // read [samples] times the value of the sensor:
  sensorValue += analogRead(A0);
  // print out the value you read:
  if (i>=samples) { 
    output = sensorValue / samples;
    output = output - 512; //center the reading
    output = abs(output);  //make it positive
    output = 512 - output; //make it so that higher = more wind

    //print a line that represents the amount of wind
    int line = map(output, 0, 512, 1,100);
    Serial.print("output: ");
    Serial.print(output);
    Serial.print("\t");
    Serial.print("flowStatus: ");
    Serial.print(flowStatus);
    
    
    //check if switching is required
    if (output > threshold){ // if above threshold => air is flowing
      stopped = 0;
      if (flowing < 1000) flowing += 1;
    }else{ //not flowing
      flowing = 0;
      if (stopped < 1000) stopped += 1;
    }

    Serial.print("\t");
    Serial.print("flowing: ");
    Serial.print(flowing);
    Serial.print("\t");
    Serial.print("stopped: ");
    Serial.print(stopped);
  
    Serial.print("\t |");
    for (int p=0; p<line; p++){
      Serial.print('-');
    }

    Serial.println();

    //needs at leats [triggers] of the same status to decide
    if (stopped >= triggers && flowStatus!=-1){
      //no air for 3 rounds and status is flowing 
      flowStatus = -1; //change status to stopped
      switchServo(); //switch servo when status is changed from flowing to stopped
    }else if (flowing >= triggers && flowStatus!=1){
      //air flowing for 3 rounds and status is stopped 
      flowStatus = 1; //change status to stopped
    } 
    

    i=0;
    sensorValue = 0;
    output = 0;
  }
  i++;  
 
  //do not allow switching within 2 secs (20 switches per minute max)
  if (blocked && ((millis() - lastSwitch) > blockingPeriod)) {
     blocked = false;
    Serial.println("-------------------------------------------------------------------");
    Serial.println("---------------------| BLOCKING PERIOD OVER |----------------------");
    Serial.println("-------------------------------------------------------------------");
  }else if (blocked){
    //make sure the servo is in the right place
    if (is1){
      myservo.write(servo1);
    }else{
      myservo.write(servo2);
    }
  }
  
 delay(1);        // delay in between reads for stability
}

void switchServo(){
  if (blocked) return;
 
  Serial.println("<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<");
  Serial.println("                            SWITICHING!                            ");
  Serial.println(">->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->");
  lastSwitch = millis();
  blocked = true;
  if (is1){
    moveServo(servo1, servo2);
    is1 = false;
  }else{
    moveServo(servo2, servo1);
    is1 = true;
  }
}

void moveServo(int from, int to){
 
  //move the servo slowly to make sure it doesn't go crazzzzy 
  int dir = 1;
  if (from > to) dir = -1;

  for (int i=from; i!=to; i+=dir){
    myservo.write(i);
    delay(6);
  }
}

void printWait(int secs){
  while (secs > 0){
    Serial.println(secs);
    secs--;
    delay(1000);
  }
}
