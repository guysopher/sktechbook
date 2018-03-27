int m1 = 1;
int m2 = -1;

void goTo(double x1, double y1){
  //start at the current location  
  if (print_lines){
    Serial.print("m");    
    Serial.print(x1);    
    Serial.print(",");    
    Serial.print(y1);    
  }
  
  //make sure we're not drawing
  chalkUp();
  
  //turn to the new angle
  double nextA = calcAngle(x1, y1);
  turn(nextA - curA);
  
  //go to the new position
  double distance = calcDistance(x1, y1);
  forward(distance);
  
  //update current position and angle
  curX += x1;
  curY += y1;
  curA = nextA;
 
  if (print_parsing){
    Serial.print("Current position: (");    
    Serial.print(curX);    
    Serial.print(",");    
    Serial.print(curY);    
    Serial.println(") "); 
  }
}

void lineTo(double x1, double y1){

  //x, y are relative to the current position
  
  if (print_parsing){
    Serial.print("Drawing Line to: ");    
    Serial.print(x1);    
    Serial.print(",");    
    Serial.print(y1);    
    Serial.println(" "); 
  }
  
  if (print_lines){
    Serial.print("l");    
    Serial.print(x1);    
    Serial.print(",");    
    Serial.print(y1);    
  }
   
  //turn to the new angle
  double nextA = calcAngle(x1, y1);
  turn(nextA - curA);
  
  //make sure we're drawing
  chalkDown();
  
  //go to the new position
  double distance = calcDistance(x1, y1);
  forward(distance);
  
  //update current position and angle
  curX += x1;
  curY += y1;
  curA = nextA;
 
  if (print_parsing){
    Serial.print("Current position: (");    
    Serial.print(curX);    
    Serial.print(",");    
    Serial.print(curY);    
    Serial.println(") "); 
  } 
 
}

double calcDistance(double x, double y){
  double z = sqrt(pow(x,2) + pow(y,2));
  return z;
}

double calcAngle(double x, double y){
  double a = atan2(y, x);
  return a;
}

void turn(double angle){
  
  //find the fastest way to turn
  if (angle > pi){
    angle -= (2*pi);
  }else if (angle < ((-1)*pi)){
    angle += (2*pi);
  }

  int steps = angle * stepsToAngleConv;
  if (print_movement){
    Serial.print("Turning ");
    Serial.print(angle);
    Serial.print(" rads => ");
    Serial.print(steps);
    Serial.print(" steps");
    Serial.println(" ");
  } 
  if (allow_movement){
    int dir = 1;
    if (steps < 0){
      steps *= -1;
      dir = -1;
    }
    for (int s=0; s < steps; s++){
      motor1.step(m1 * dir * 1);
      motor2.step(m2 * dir * (-1));
    }
  }
}

void forward(double distance){

  int steps = distance * stepsToDistanceConv;
  if (print_movement){
    Serial.print("Advancing ");
    Serial.print(distance);
    Serial.print(" milimeters => ");
    Serial.print(steps);
    Serial.print(" steps");
    Serial.println(" ");
  } 
  if (allow_movement){
    for (int s=0; s < steps; s++){
      motor1.step(m1 * 1);
      motor2.step(m2 * 1);
    }
  }
}
