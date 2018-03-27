const int p_button = 2;
const int p_led_r = 3;
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

boolean isThereLight = false;

void setup(){
  pinMode(p_button, INPUT_PULLUP);
  pinMode(p_led_r, OUTPUT);
  pinMode(p_led_g, OUTPUT);
  pinMode(p_led_b, OUTPUT);
  pinMode(p_speaker, OUTPUT);
  Serial.begin(9600);
}

void loop(){

  if (sensor1 < 0){
    shutdownRGB();
    delay(1000);//start only after 1 sec
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

  int active = (digitalRead(p_button) == LOW);
  pitch = map(sensor1, minLight1, maxLight1, 0, 12); 
  duration = map(sensor2, minLight2, maxLight2, 0, 5) * 20; 
  interval = map(sensor3, minLight3, maxLight3, 0, 5) * 20; 

  monitor();
  
  if (active){
    if (!isThereLight){
      red = map(random(0,255), 0, 255, 5, 16) * 16; 
      green = map(random(0,255), 0, 255, 5, 16) * 16; 
      blue = map(random(0,255), 0, 255, 5, 16) * 16; 
      lightRGB(red, green, blue);
    }
    tone(p_speaker, notes[pitch], duration);
    delay(interval);
  }else{
    shutdownRGB();
  }
}

void monitor(){
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

  /*
  Serial.print("sensor 1: ");
  Serial.print(sensor1);
  Serial.print(" | sensor 2: ");
  Serial.print(sensor2);
  Serial.print(" | sensor 3: ");
  Serial.print(sensor3);
  Serial.print(" || ");
  */

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
