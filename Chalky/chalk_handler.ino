boolean drawing = false;

void chalkDown(){
  drawing = true;
  //lower the chalk
  digitalWrite(ledPin, HIGH);
  if (print_movement){
    Serial.println("Chalk Down");
  }
}

void chalkUp(){
  drawing = false;
  //raise the chalk
  digitalWrite(ledPin, LOW);
  if (print_movement){
    Serial.println("Chalk Up");
  }
}

