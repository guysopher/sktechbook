#include <remote_hadler.ino>
#include <screen_hadler.ino>

int received_digit = -1;

void setup() {
  Serial.begin(9600);
  remote_setup();
  screen_setup();
}

void loop() {
  received_digit = getDigit();
  Serial.println(received_digit);
  if (received_digit >= 0){
    drawDigit(received_digit);
  }
}


