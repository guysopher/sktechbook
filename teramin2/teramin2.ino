const int p_button1 = 4;
const int p_button2 = 2;
const int p_button3 = 3;
const int p_led_r = 9;
const int p_led_g = 5;
const int p_led_b = 6;
const int p_sensor1 = A2;
const int p_sensor2 = A1;
const int p_sensor3 = A0;
const int p_speaker = 13;

const int notes[] = {261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493};

int pitch = 0;
int duration = 0;
int interval = 0;

int red = 0;
int green = 0;
int blue = 0;

int maxLight1 = 0;
int minLight1 = 1023;
int maxLight2 = 0;
int minLight2 = 1023;
int maxLight3 = 0;
int minLight3 = 1023;

int sensor1 = -1;
int sensor2 = -1;
int sensor3 = -1;

boolean active1 = false;
boolean active2 = false;
boolean active3 = false;

boolean isThereLight = false;

double startTime = 0;
double startLight = 0;

void setup(){
  pinMode(p_button1, INPUT);
  pinMode(p_button2, INPUT);
  pinMode(p_button3, INPUT);
  pinMode(p_led_r, OUTPUT);
  pinMode(p_led_g, OUTPUT);
  pinMode(p_led_b, OUTPUT);
  pinMode(p_speaker, OUTPUT);
  Serial.begin(9600);
}

void loop(){

  if (sensor1 < 0){
    //shutdownRGB();
  }

  sensor1 = analogRead(p_sensor1);
  sensor2 = analogRead(p_sensor2);
  sensor3 = analogRead(p_sensor3);
  
  //find the min/max light
  if (sensor1 < minLight1) {minLight1=sensor1;}
  if (sensor1 > maxLight1) {maxLight1=sensor1;}
  if (sensor2 < minLight2) {minLight2=sensor2;}
  if (sensor2 > maxLight2) {maxLight2=sensor2;}
  if (sensor3 < minLight3) {minLight3=sensor3;}
  if (sensor3 > maxLight3) {maxLight3=sensor3;}

  active1 = (digitalRead(p_button1) == LOW);
  active2 = (digitalRead(p_button2) == LOW);
  active3 = (digitalRead(p_button3) == LOW);

  duration = map(sensor1, minLight1, maxLight1, 5, 10) * 20; 
  pitch = map(sensor2, minLight2, maxLight2, 2, 12); 
  interval = map(sensor3, minLight3, maxLight3, 5, 10) * 20; 

  monitor();
  
  lightIfNeeded(active1, p_led_r);
  lightIfNeeded(active2, p_led_g);
  lightIfNeeded(active3, p_led_b);
  
  if (millis()-startTime < duration){
    tone(p_speaker, notes[pitch]);
  }else if (millis()-startTime < duration + interval){
    noTone(p_speaker);
  }else{
    startTime = millis();
  }
}

void lightIfNeeded(boolean active, int pin){
  digitalWrite(pin, !active);
}

void monitor(){

//  Serial.print("random: ");
//  Serial.print(random(1,100));

/*
  Serial.print("min/max 1: ");
  Serial.print(minLight1);
  Serial.print("/");
  Serial.print(maxLight1);
  Serial.print(" | min/max 2: ");
  Serial.print(minLight2);
  Serial.print("/");
  Serial.print(maxLight2);
  Serial.print(" | min/max 3: ");
  Serial.print(minLight3);
  Serial.print("/");
  Serial.print(maxLight3);
  Serial.print(" || ");
  
  Serial.print("sensor 1: ");
  Serial.print(sensor1);
  Serial.print(" | sensor 2: ");
  Serial.print(sensor2);
  Serial.print(" | sensor 3: ");
  Serial.print(sensor3);
  Serial.print(" || ");
  

  Serial.print("active 1: ");
  Serial.print(active1);
  Serial.print(" | active 2: ");
  Serial.print(active2);
  Serial.print(" | active 3: ");
  Serial.print(active3);
  Serial.print(" || ");
  

  Serial.print("red: ");
  Serial.print(red);
  Serial.print(" | green: ");
  Serial.print(green);
  Serial.print(" | blue: ");
  Serial.print(blue);
  Serial.print(" || ");

  Serial.print("pitch: ");
  Serial.print(pitch);
  Serial.print(" | duration: ");
  Serial.print(duration);
  Serial.print(" | interval: ");
  Serial.print(interval);
  Serial.println("");

*/
}

void shutdownRGB(){
  lightRGB(255,255,255);
  isThereLight = false;
}

void lightRGB(int R, int G, int B){
  analogWrite(p_led_r, R);
  analogWrite(p_led_g, G);
  analogWrite(p_led_b, B);
  isThereLight = true;
}
