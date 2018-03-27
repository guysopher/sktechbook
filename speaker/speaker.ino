/*
 * PotDimmer 
 * ---------
 * 
 * Use a potentiometer to adjust the brightness of an PWM'd LED
 * 
 */

int potPin = A2;    // select the input pin for the potentiometer
int speakerPin = 9;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor
int notes[] = {261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493};

void setup() {
  pinMode(speakerPin, OUTPUT);  // declare the speakerPin as an OUTPUT
 Serial.begin(9600);
}

void loop() {
  //val = analogRead(potPin)/(1024/sizeof(notes));    // read the value from the sensor
  val = analogRead(potPin);    // read the value from the sensor
  int index = map(val, 0, 1023, 0, 12);
  Serial.println(index);
  if (val == 0){
    noTone(speakerPin);
  }else{
    tone(speakerPin, notes[index-1]);    // turn the speakerPin on
  }
}
