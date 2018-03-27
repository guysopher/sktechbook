#include <IRremote.h>

int RECV_PIN = 3;

IRrecv irrecv(RECV_PIN);

decode_results results;

long numbers[] = {16738455,16724175,16718055,16743045,16716015,16726215,16734885,16728765,16730805,16732845};

void remote_setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

int getDigit() {
  if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
    int digit = reverseLookup(results.value);
    if (digit >= 0){
      return digit;
    }
  }
  return -1;
}

int reverseLookup(long val){
  for (int i=0; i<10; i++) {
     if (val == numbers[i]) {
       return i;
     }
  }
    return -1;
}
