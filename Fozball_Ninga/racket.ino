const int LASER[] = {A1, A2, A4, A5};

const int threshold[] = {800,800,250,800};

float speeds[] = {0,0};
long frontTime[] = {0,0};
long backTime[] = {0,0};
double diff = 0;

double getRacketSpeed(int player){
  int backLaserPin = player*2;
  int frontLaserPin = player*2+1;
  double res = -1;
  boolean hitBack = false;
  boolean hitFront = false;

  if (isLaserBlocked(backLaserPin)){
    backTime[player] = micros();
    hitBack = true;
  }else if (isLaserBlocked(frontLaserPin)){
    frontTime[player] = micros();
    diff = frontTime[player] - backTime[player];
    backTime[player] = 0;
    if (diff > 510000 || diff < 10000){
      res = 0;
    }else{
      res = (50000 / diff);
    }
    hitFront = true;
  }
  
  if (print_racket){
      Serial.print("back: ");
      Serial.print(hitBack);
      Serial.print("\t");
      Serial.print("backTime: ");
      Serial.print(backTime[player]);
      Serial.print("\t\t");
      Serial.print("front: ");
      Serial.print(hitFront);
      Serial.print("\t");
      Serial.print("frontTime: ");
      Serial.print(frontTime[player]);
      Serial.print("\t\t");
      Serial.print("diff: ");
      Serial.print(diff);
      Serial.print("\t");
      Serial.print("racket: ");
      Serial.print(res);
      Serial.print("\t");
      
    Serial.println("");
  }
  
  if (hitFront){
        delay(100);
  }
  return res;
}

boolean isLaserBlocked(int pin){
  int val = analogRead(LASER[pin]);
  if (print_racket && pin==2){
      Serial.print("val: ");
      Serial.print(val);
      Serial.print("\t");
      Serial.print("threshold[pin]: ");
      Serial.print(threshold[pin]);
      Serial.print("\t");
      Serial.print("res: ");
      Serial.print(val < threshold[pin]);
      Serial.print("\t");
      Serial.println("");
  }
  return val < threshold[pin];
}
