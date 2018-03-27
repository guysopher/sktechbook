const int ldrPins[] = {A0,A1,A2};
float res[3];
float avg = 10;

int defaultDelay = 5;

int rounds = 0;
int hSize = 100;
float history[100][3];
int hPointer = 0;

int threshold[] = {800, 850, 900};
int delays[] = {250, 30};

int strokeDelay = 400;
int strokeDelayStd = 300;
long t[3];

boolean firstRoundComplete = false;

void readLdrs(){

  for (int i=0; i<3; i++){
    res[i] = (res[i] * ((avg-1)/avg)) + (analogRead(ldrPins[i]) / avg);

    if (rounds++ >= avg){
      rounds = 0;
      
      if (print_ldrs){
        Serial.print("ldr-");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(res[i]);
        Serial.print("\t");
      }
      
      history[hPointer][i] = res[i];
      hPointer = (hPointer+1)%hSize;
      //mark history full (can measure strokes)
      if (hPointer==0){firstRoundComplete = true;}
      
      if (isHidden(res[i], i)){
        t[i] = millis();

        if (print_delays){
          Serial.print("t-");
          Serial.print(i);
          Serial.print(": ");
          Serial.print(t[i]);
          Serial.print("\t");
        }
    
      }
    }  
    
  }

  if (rounds >= avg){
    if (isStroke()){
      whenStroke();
    }
  
    if (print_delays){
      Serial.print("delay 1: ");
      Serial.print(t[1] - t[2]);
      Serial.print("\t");
      Serial.print("delay 2: ");
      Serial.print(t[0] - t[1]);
      Serial.print("\t");
    }
    
    if (print_ldrs || print_delays){
      Serial.println(); 
    }
  }

  delay(defaultDelay);
}


boolean isStroke(){
    
    if (abs(t[1] - t[2] - strokeDelay) > strokeDelayStd){
      return false;
    }
    if (abs(t[0] - t[1] - strokeDelay) > strokeDelayStd){
      return false;
    }
    
    //init the t values
    t[0] = 0;
    t[1] = 0;
    t[2] = 0;
    return true;

}

boolean isStroke2(){
  
  if (!firstRoundComplete) {return false;}
  
  boolean stroke = true;
  int p = 0;

  //check if ldr1 if hidden
  p = hPointer;
  if (!isHidden(p, 2)){
    return false;
  }

  //move at delay1
  p = (p+delays[0])%hSize;
  //check if ldr2 if hidden
  if (!isHidden(p, 1)){
    return false;
  }

  //move at delay1
  p = (p+delays[1])%hSize;
  //check if ldr3 if hidden
  if (!isHidden(p, 0)){
    return false;
  }

  return true; 
  
}

boolean isHidden(float val, int idx){
  return (val > threshold[idx]);
}

boolean isHidden2(int pointer, int idx){
  return (history[pointer][idx] > threshold[idx]);
}
