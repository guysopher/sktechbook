#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "0123456789";
int wait = 1000; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

void screen_setup() {

  matrix.setIntensity(1); // Use a value between 0 and 15 for brightness

}

void drawDigit(int digit) {

  matrix.fillScreen(LOW);

  int x = 1;
  int y = (matrix.height() - 8) / 2; // center the text vertically

  matrix.drawChar(x, y, tape[digit], HIGH, LOW, 1);
  matrix.write(); // Send bitmap to display
  delay(wait);

}


