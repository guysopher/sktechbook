/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int player1 = 13;     // the number of the pushbutton pin
const int led1 =  9;      // the number of the LED pin
const int player2 = 12;     // the number of the pushbutton pin
const int led2 =  8;      // the number of the LED pin
const int ball = 2;
// variables will change:
int p1, p2 = 0;         // variable for reading the pushbutton status
boolean gameover = true;

void setup() {
  // initialize the LED pin as an output:
  pinMode(led1, OUTPUT);      
  pinMode(led2, OUTPUT);      
  pinMode(ball, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(player1, INPUT_PULLUP);     
  pinMode(player2, INPUT_PULLUP);     

  digitalWrite(led1, HIGH);  
  digitalWrite(led2, HIGH);  
  digitalWrite(ball, HIGH);  
}

void loop(){
  
  Serial.begin(9600);

  p1 = digitalRead(player1);
  p2 = digitalRead(player2);

  if (gameover){
    gameover=false;
    startGame();
  }
  
  gameover = true;
  if (p1==LOW){
    threeBlinks(led1);
    delay(1000);
  }else if (p2==LOW){
    threeBlinks(led2);
    delay(1000);
  }else{
    gameover=false;
  }
  
}

void threeBlinks(int ledPin){
  digitalWrite(ledPin, LOW);
  delay(250);  
  digitalWrite(ledPin, HIGH);
  delay(250);  
  digitalWrite(ledPin, LOW);
  delay(250);  
  digitalWrite(ledPin, HIGH);
  delay(250);  
  digitalWrite(ledPin, LOW);
  delay(250);  
  digitalWrite(ledPin, HIGH);
}

void startGame(){
  digitalWrite(led1, HIGH);  
  digitalWrite(led2, HIGH);  
  digitalWrite(ball, HIGH);  
  
  threeBlinks(ball);

  delay(random(1000,3000));  
  digitalWrite(ball, LOW);
  delay(200);  
  digitalWrite(ball, HIGH);
}

void light(int ledPin, int buttonState){
  if (buttonState == HIGH) {     
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }
} 


