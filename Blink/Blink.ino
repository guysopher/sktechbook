/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int led = 13;
const int CYCLE= 5000;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

int i=0;

// the loop routine runs over and over again forever:
void loop() {
  i++;
  if (i>CYCLE){
    i=0;
  }
  if (i % CYCLE == 0){
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  if (i % CYCLE == (CYCLE/2)){
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }    
  delay(1); 

}
