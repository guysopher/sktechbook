const int ENGINE_PIN = 9;
const int LED_PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ENGINE_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  for (int i=0; i <= 255; i+=2) {
    Serial.print("Engine output is: ");
    Serial.println(i);
    analogWrite(ENGINE_PIN, i);
    analogWrite(LED_PIN, i);
    delay(7);
  }
  for (int i=255; i >= 0; i-=2) {
    Serial.print("Engine output is: ");
    Serial.println(i);
    analogWrite(ENGINE_PIN, i);
    analogWrite(LED_PIN, i);
    delay(7);
  }
}
