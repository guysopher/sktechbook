#include <math.h>
#include <Stepper.h>

const float pi = 3.14159;

int buttonPin = 12;
int ledPin = 13;

int in1Pin1 = 11, in2Pin1 = 10, in3Pin1 = 9, in4Pin1 = 8;
int in1Pin2 = 7, in2Pin2 = 6, in3Pin2 = 5, in4Pin2 = 4;
Stepper motor1(64, in1Pin1, in3Pin1, in4Pin1, in2Pin1);
Stepper motor2(64, in1Pin2, in3Pin2, in4Pin2, in2Pin2);


boolean print_parsing = false;
boolean print_lines = true;
boolean print_movement = false;

boolean allow_movement = true;

int buttonState;

boolean testConversions = false;

double tStep = 0.05;

double stepsToAngleConv = 2000/pi;
double stepsToDistanceConv = 1000/215 * 5; //by measurements + make the drawing 4 times larger;


double curX = 0; //current X coord
double curY = 0; //current Y coord
double curA = 0; //current angle

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  motor1.setSpeed(300);
  motor2.setSpeed(300);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);      

  Serial.println("READY");  
}



void loop() {

  chalkUp();

  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {     
    if (testConversions){
      //set stepsToDistanceConv = 1000 (units: steps/mm)
      //measure the distance (in mm) the robot passes 
      //set stepsToDistanceConv = 1000/mm
      forward(1); 
      //set stepsToAngleConv = 1000 (units: steps/radians)
      //measure the angle (in radians) the robot turns 
      //set stepsToAngleConv = 1000/radians
      turn(1);
    }else{
      drawSVG();  
      delay(3000);
    }
  }

  delay(500);
}
