int m1 = 1;
int m2 = -1;

void goTo(float x1, float y1){
  //start at the current location  
  if (print_lines){
    Serial.print("m");    
    Serial.print(x1);    
    Serial.print(",");    
    Serial.print(y1);    
  }
  
  //make sure we're not drawing
  chalkDown();
  
  //turn to the new angle
  float nextA = calcAngle(x1, y1);
  turn(nextA - curA);
  
  //go to the new position
  float distance = calcDistance(x1, y1);
  forward(distance);
  
  //update current position and angle
  curX = x1;
  curY = y1;
  curA = nextA;
  
}

void lineTo(float x1, float y1){
  //start at the current location
  
  if (debug){
    Serial.print("Drawing Line to: ");    
    Serial.print(x1);    
    Serial.print(",");    
    Serial.print(y1);    
    Serial.println(" "); 
  }else if (print_lines){
    Serial.print("l");    
    Serial.print(x1);    
    Serial.print(",");    
    Serial.print(y1);    
  }
   
  //turn to the new angle
  float nextA = calcAngle(x1, y1);
  turn(nextA - curA);
  
  //make sure we're drawing
  chalkDown();
  
  //go to the new position
  float distance = calcDistance(x1, y1);
  forward(distance);
  
  //update current position and angle
  curX = x1;
  curY = y1;
  curA = nextA;
  
}

float calcDistance(float x, float y){
  float z = sqrt(pow(x,2) + pow(y,2));
  return z;
}

float calcAngle(float x, float y){
  float a = atan2(y, x);
}

void turn(float angle){
  int steps = angle * stepsToAngleConv;
  for (int s=0; s < steps; s++){
    motor1.step(m1 * 1);
    motor2.step(m2 * -1);
  }
}

void forward(float distance){
  int steps = distance * stepsToDistanceConv;
  for (int s=0; s < steps; s++){
    motor1.step(m1 * 1);
    motor2.step(m2 * 1);
  }
}
