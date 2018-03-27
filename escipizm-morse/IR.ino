#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 11;
int BUTTON_PIN = 12;
int STATUS_PIN = 13;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void ir_setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode(BUTTON_PIN, INPUT);
  pinMode(STATUS_PIN, OUTPUT);
}

// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long codeValue; // The code value if not raw
//unsigned int rawCodes[RAWBUF]; // The durations if raw
int codeLen; // The length of the code
int toggle = 0; // The RC5/6 toggle state

// Stores the code for later playback
// Most of this code is just logging


unsigned int btnPower[68] = {8800, 4550, 450, 700, 450, 1750, 450, 650, 500, 650, 400, 750, 400, 650, 500, 650, 400, 650, 450, 1800, 450, 650, 450, 1800, 450, 1800, 450, 1750, 450, 1800, 450, 1750, 450, 1750, 500, 1800, 400, 650, 500, 1750, 450, 1800, 450, 1750, 500, 650, 450, 650, 450, 650, 450, 700, 400, 1800, 450, 700, 400, 700, 450, 650, 450, 1800, 400, 1800, 450, 1750, 500};
void sendPower() {
    // Assume 38 KHz
    irsend.sendRaw(btnPower, 68, 38);
    Serial.println("Sent power");
}

unsigned int btnSkip[68] = {8800,4600,400,700,450,1750,450,650,500,650,400,750,400,700,450,650,400,700,450,1800,450,700,400,1800,400,1800,500,1750,450,1800,450,1800,450,1800,450,650,450,650,450,1800,450,650,450,650,500,650,450,650,450,650,450,1800,450,1800,450,650,450,1800,450,1800,450,1750,450,1800,500,1750,450};
void sendSkip() {
    // Assume 38 KHz
    irsend.sendRaw(btnSkip, 68, 38);
    Serial.println("Sent Skip");
}

unsigned int btnSelect[68] = {8750,4550,500,700,400,1900,300,750,400,700,450,650,450,700,400,750,400,650,450,1750,500,650,400,1850,450,1750,450,1800,400,1900,350,1800,450,1750,450,1950,300,1800,450,650,450,1800,450,700,400,700,400,700,450,700,400,650,450,700,450,1750,450,700,400,1800,450,1850,400,1800,400,1800,450};
void sendSelect() {
    // Assume 38 KHz
    irsend.sendRaw(btnSelect, 68, 38);
    Serial.println("Sent Select");
}

unsigned int btnRight[68] = {8750,4700,350,650,450,1800,450,650,450,700,450,750,350,650,450,650,500,700,400,1750,450,700,450,1750,450,1800,450,1800,450,1800,400,1800,450,1800,450,650,500,600,450,700,450,1800,400,700,450,650,500,650,400,700,450,1750,450,1800,450,1800,450,650,500,1750,450,1750,450,1800,450,1800,450};
void sendRight() {
    // Assume 38 KHz
    irsend.sendRaw(btnRight, 68, 38);
    Serial.println("Sent Right");
}

unsigned int btnPrev[68] = {8850,4550,500,650,400,1800,500,650,400,650,500,650,500,650,400,750,400,650,500,1750,450,700,450,1750,450,1850,400,1800,500,1750,450,1800,400,1800,500,700,400,1800,500,1700,500,650,500,650,400,700,450,650,500,700,350,1850,450,650,400,750,400,1800,450,1750,550,1750,450,1800,400,1800,500};
void sendPrev() {
    // Assume 38 KHz
    irsend.sendRaw(btnPrev, 68, 38);
    Serial.println("Sent Prev");
}


void ir_send(int command) {

    Serial.println("Pressed, sending");
    digitalWrite(STATUS_PIN, HIGH);

    if (command == 0) {
      sendPower();
    }else if (command == 1){

      sendSkip();
    }else if (command == 2){

      sendSelect();
    }else if (command == 3){

      sendRight();
    }else if (command == 4){

      sendPrev();
    }


    
//    sendPrev();
    digitalWrite(STATUS_PIN, LOW);
    delay(50); // Wait a bit between retransmissions
  
//  else if (irrecv.decode(&results)) {
//    digitalWrite(STATUS_PIN, HIGH);
//    storeCode(&results);
//    irrecv.resume(); // resume receiver
//    digitalWrite(STATUS_PIN, LOW);
//  }
//  lastButtonState = buttonState;
}
