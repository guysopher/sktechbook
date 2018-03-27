#define CONTACT_PIN 8
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

const int seq_1[] = {0,0,1,0,1,1,1};
const int seq_2[] = {0,1,0,0,1,1,0};
const int seq_3[] = {1,0,0,0,0,0,1};
const int seq_4[] = {0,0,0,1,0,0,1};

const int interval[] = {0,332,188,211,397,680,318};
const int notes[] = {523,392,392,415,392,493,523};
const int song[] = {0,332,188,211,397,680,318};
const int songLength = 5;
const int fullLength = 7;
const int maxDiv = 200;
const int noteDuration = 10;

int tapDuration = 0;
int tapType = -1;
const int longTap = 400;
const int shortTap = 100;
int pointer = 0;
bool skipTap = false;
int curSeq = 1;
bool validSeqs[] = {true, true, true, true, true};

void setup() {
  Serial.begin(9600);
  pinMode(CONTACT_PIN, INPUT_PULLUP);           // set pin to input
  initGame();
}

void loop() {

  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  tap = !digitalRead(CONTACT_PIN);

  if (tap) {
    //first - make a sound when there is contact
    tone(SPEAKER_PIN, 700, noteDuration);
    //delay(noteDuration);    
  } else if (millis() - lastTap > 5000) {
    restartGame();
  }
  
  if (!isTap && tap) {
    //new pulse

    isTap = true;
    lastTap = millis();
    
  } else if (isTap && !tap) {
    //end of pulse
    isTap = false;
    tapDuration = millis() - lastTap;

    if (abs(tapDuration - longTap) < 150) {
      Serial.print("Long Tap: ");
      Serial.print(tapDuration);  
      tapType = 1;  
      skipTap = false;
    } else if (abs(tapDuration - shortTap) < 80) {
      Serial.print("Short Tap: ");  
      Serial.print(tapDuration);  
      tapType = 0;  
      skipTap = false;
    } else if (abs(tapDuration) > 50){
      Serial.print("Strange Tap: ");  
      Serial.print(tapDuration);  
      tapType = -1;
      skipTap = false;
    } else {
      //probably a misread or debounce
      skipTap = true;
    }

    if (!skipTap) {      
      
      if (checkSeqs(tapType, pointer)) {
        Serial.println("Tap is Good!");
        pointer++;  
        Serial.print("Total good taps: ");
        Serial.println(pointer);
  
        if (pointer == 7) {
          winGame();
        }
      } else {
        Serial.println("Tap is Bad");
        loseGame();  
      }
  
    }
    
  }
  
}

void initGame() {
  Serial.println("-------------| MORSE INIT |-------------");  
  tone(SPEAKER_PIN, 800, 200);
  delay(200);
  tone(SPEAKER_PIN, 600, 200);
  delay(200);
  tone(SPEAKER_PIN, 400, 200);
  delay(200);
  resetGame(); 
}

void winGame() {
  int winningSeq = getValidSeq();
  digitalWrite((winningSeq + 2), HIGH);
  Serial.println("-------------| VICTORY |-------------");  
  Serial.print("----------------| ");
  Serial.print(winningSeq);  
  Serial.println(" |----------------");  
  Serial.println("-------------| VICTORY |-------------");  
  tone(SPEAKER_PIN, 700, 200);
  delay(200);
  tone(SPEAKER_PIN, 900, 200);
  delay(200);
  tone(SPEAKER_PIN, 1100, 200);
  delay(200);
  resetGame(); 
  
}

void loseGame() {
  Serial.println("------------| GAME OVER |------------");  
  tone(SPEAKER_PIN, 200, 500);
  delay(500);
  resetGame();
}

void restartGame() {
  Serial.println("------------| RESTART |------------");  
  tone(SPEAKER_PIN, 500, 60);
  delay(60);
  resetGame();
}

void resetGame() {
  pointer = 0;
  lastTap = millis();
  for (int i = 1; i <= 4; i++ ) {
    validSeqs[i] = true;
  }
}

int getValidSeq() {
  for (int i = 1; i <= 4; i++ ) {
    if (validSeqs[i]) {
      return i;
    }
  }
  return 0;
}

int searchSeq(int num, int _pointer) {
  if (num == 1) {
    return seq_1[_pointer];
  } else if (num == 2) {
    return seq_2[_pointer];
  } else if (num == 3) {
    return seq_3[_pointer];
  } else {
    return seq_4[_pointer];
  }
}

boolean checkSeqs(int _tapType, int _pointer) {
  boolean res = false;
  Serial.println();
  for (int i = 1; i <= 4; i++ ) {
    Serial.print(i);
    if (validSeqs[i] && _tapType == searchSeq(i, _pointer)) {
      Serial.print(": RIGHT | ");
      res = true;
    } else {
      Serial.print(": WRONG | ");
      validSeqs[i] = false;
    }
  }
  Serial.println();
  return res;
}


