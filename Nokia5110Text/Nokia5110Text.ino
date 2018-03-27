#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pin 7       - Serial clock out (SCLK)
// pin 6       - Serial data out (DIN)
// pin 5       - Data/Command select (D/C)
// pin 4/GND   - LCD chip select (CS)
// pin 3/RESET - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup() {
  display.begin();
  display.setContrast(15);
  display.clearDisplay();
  display.display();
}


void loop() {  
  // text display tests
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(WHITE, BLACK); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  delay(1000);
}

