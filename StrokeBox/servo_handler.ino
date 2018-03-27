#include <Servo.h>

int servoPin = 8;
Servo servo;
int angle = 0; // servo position in degrees
void servo_setup() {
  servo.attach(servoPin);
}
void open_box(){
    servo.write(100);
    delay(15);
} 

void close_box(){
    servo.write(-50);
    delay(15);
} 

