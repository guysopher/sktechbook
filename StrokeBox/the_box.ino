
boolean print_ldrs = false;
boolean print_delays = false;

void setup() {
  servo_setup();
  Serial.begin(9600);
}

void loop() {
  //readLdrs();
  
  open_box();
  delay(1000);
  
  close_box();
  delay(1000);
  
}

void whenStroke(){
  Serial.println("STROKE"); 
}
