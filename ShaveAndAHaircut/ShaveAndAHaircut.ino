#define PIEZO_PIN A0
#define SPEAKER_PIN 9

const int historyLength = 100;
const int silenceLength = 50;
const int requiredTapLength = 0;
const int silenceThreshold = 20;

int tap = 0;
int history[historyLength];
long tapTimes[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long delays[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long sequenseVAL[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
long sequenseTrials[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int i = 0;
int d = 0;
int s = 0;
boolean going = false;
boolean answered = false;

boolean isTap = false;
int tapLength = 0;
int taps = 0;
long lastTap = 0;

const int notes[] = {523,392,392,415,392,493,523};
const int song[] = {0,332,188,211,397,680,318};
const int songLength = 5;
const int fullLength = 7;
const int maxDiv = 200;
const int noteDuration = 100;

void setup() {
  Serial.begin(9600);
  delay(7000);
}

void loop() {
  tap = analogRead(PIEZO_PIN);
  
  history[i] = tap;

  if (millis() - lastTap > 10000) start();

  if (isTap) {
    
    isTap=false;
    lastTap = millis();
    
    tone(SPEAKER_PIN, notes[d], noteDuration);
    delay(noteDuration);
    
    if (d==0) tapTimes[d] = millis();
    
    d++;
    taps++;
    tapTimes[d] = millis();
    delays[d] = tapTimes[d] - tapTimes[d-1];
    tapLength = 0;
    
    Serial.print("TAP! #");  
    Serial.print(taps);  
    Serial.print(" rhythm ");  
    Serial.print(delays[d]);  
    Serial.print(" song's rhythm: ");
    Serial.print(song[d-1]);
    Serial.println("");  

//    learn();
    
    if (taps % songLength == 0) {
      if (isSong()){
        answer();
      }else{
        fail();
      }
      start();
    }
    //Serial.println("");  

  }

  if (isSilent()){
    if (tapLength>requiredTapLength){
      isTap=true;
    }else{
      isTap=false;
    }
    tapLength = 0;
  }else{
    isTap=false;
    tapLength++;
  }

  //advance history index
  i = (i + 1) % historyLength;
 
  if (!going) start();
}

void fail(){
  
  delay(400);
  tone(SPEAKER_PIN, 500, 300);
  delay(1000);
  answered = false;
}

void answer(){

  answered = true;

  Serial.println("");
  Serial.println("           /------------------------\\          ");
  Serial.println("                   HALF PRICE :)                ");
  Serial.println("           \\------------------------/          ");
  Serial.println("");

  for (int n=songLength; n<fullLength; n++){
    delay(song[n]);
    tone(SPEAKER_PIN, notes[n], noteDuration);
  }
  delay(1500);
  
}

boolean isSong(){
  int div = 0;
  for (int l=0; l < songLength; l++){
    div += abs(delays[l+1] - song[l]);
  }  
  Serial.print("diff: ");
  Serial.print(div);
  Serial.print("/");
  Serial.print(maxDiv);
  if ((div > maxDiv)) Serial.print(" - Try Harder..!");
  Serial.println("");
  
  return (div <= maxDiv);
}

void learn(){
  sequenseVAL[d] = ((sequenseVAL[d]*sequenseTrials[d]) + delays[d]) / (sequenseTrials[d]+1);
  sequenseTrials[d]++;

  Serial.print(" | learned: ");
  Serial.print(sequenseVAL[d]);
  Serial.print(" trials: ");
  Serial.print(sequenseTrials[d]);
  
}

void start(){

  noTone(SPEAKER_PIN);
  
  d = 0;
  taps = 0;
  going = true;
  isTap=false;
  lastTap = millis();
  
  Serial.println("");
  Serial.println("");
  Serial.println("-----------------------------------------");
  Serial.println("----------| REPEAT AFTER ME! |-----------");
  Serial.println("-----------------------------------------");
  Serial.println("Shave and a haircut...");

  demo();
}

void demo(){
  
  delay(300);

  //if (answered) return;
  
  for (int n=0; n<songLength; n++){
    tone(SPEAKER_PIN, notes[n], noteDuration);
    delay(song[n+1]);
  }
  delay(noteDuration);
  
}

boolean isSilent(){

  for (int l=0; l < silenceLength; l++){
    if ((int)(history[(i-l+historyLength) % historyLength]) > silenceThreshold) {
      return false;
    }
  }
  return true;
  
}


