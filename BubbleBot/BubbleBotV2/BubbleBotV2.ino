#include <Servo.h> 

#define UP_DOWN_SERVO_PIN 9
#define OPEN_CLOSE_SERVO_PIN 10
#define FAN_PIN 11

#define DOWN_POSITION 50
#define UP_POSITION 165

#define OPEN_POSITION 110
#define CLOSED_POSITION 160

#define ARMS_OPENING_DURATION 1000
#define BUBBLES_PER_LIFT 2

Servo up_down_servo;
Servo open_close_servo;
 
int pos = 0;
 
void setup() { 
  up_down_servo.attach(UP_DOWN_SERVO_PIN);
  open_close_servo.attach(OPEN_CLOSE_SERVO_PIN);
  up_down_servo.write(DOWN_POSITION);
  open_close_servo.write(CLOSED_POSITION);
  
  pinMode(FAN_PIN, OUTPUT);
}

void loop() {
  arms_up();
  turn_fan(HIGH);
  for(int i = 0; i < BUBBLES_PER_LIFT; ++i) {
    arms_open();
    delay(ARMS_OPENING_DURATION);
    arms_close();
    delay(250);
  }
  delay(1000);  
  turn_fan(LOW);
  arms_down();
  delay(2500); 
}

void arms_open() {
  for(pos = CLOSED_POSITION; pos > OPEN_POSITION; pos -= 1) {
    open_close_servo.write(pos);
    delay(15);
  } 
}

void arms_close() {
  for(pos = OPEN_POSITION; pos <= CLOSED_POSITION; pos+=1) {
    open_close_servo.write(pos);
    delay(15);
  } 
}

void arms_up() {
  for(pos = DOWN_POSITION; pos < UP_POSITION; pos += 1) {
    up_down_servo.write(pos);
    delay(15);
  } 
}

void arms_down() {
  for(pos = UP_POSITION; pos >= DOWN_POSITION; pos-=1) {
    up_down_servo.write(pos);
    delay(15);
  } 
}

void turn_fan(boolean on) {
  digitalWrite(FAN_PIN, on);
}


/////////////////////////////////////////////////
// TESTS
/////////////////////////////////////////////////

void up_down_servo_test() { 
  arms_up();
  delay(1000);
  arms_down();
  delay(1000);
}

void open_close_servo_test() { 
  delay(1000);
  arms_open();
  delay(1000);
  arms_close();
  delay(1000);
}

