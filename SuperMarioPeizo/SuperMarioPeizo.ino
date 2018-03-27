int const  C = 1911;
int const  C1 = 1804;
int const  D = 1703;
int const  Eb = 1607;
int const  E = 1517;
int const  F =1432;
int const  F1= 1352;
int const  G= 1276;
int const  Ab= 1204;
int const  A =1136;
int const  Bb =1073;
int const  B= 1012;
int const  c =955;
int const  c1 =902;
int const  d =851;
int const  eb= 803;
int const  e =758;
int const  f =716;
int const  f1 =676;
int const  g= 638;
int const  ab =602;
int const  a= 568;
int const  bb =536;
int const  b =506;
 
int const  p=0 ; //pause

int speaker = 6;   
long vel = 25000;
 
void setup() {
    pinMode(speaker, OUTPUT);
    delay(2000);
}
 
int melod[] = {e, e, e, c, e, g, G, c, G, E, A, B, Bb, A, G, e, g, a, f, g, e, c, d, B, c};
int ritmo[] = {6, 12, 12, 6, 12, 24, 24, 18, 18, 18, 12, 12, 6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6, 12};
 
void loop() {
    for (int i=0; i<24; i++) {
        int ton = melod[i];
        int tempo = ritmo[i];
 
        long tvalue = tempo * vel;
 
        playTone(ton, tvalue);
 
        delayMicroseconds(100000);
    }
    delay(10000);
}
 
void playTone(int tone_value, long tempo_value) {
     long tempo_position = 0;
     while (tempo_position < tempo_value) {
        digitalWrite(speaker, HIGH);
        delayMicroseconds(tone_value / 2);
 
        digitalWrite(speaker, LOW);
        delayMicroseconds(tone_value / 2);
 
        tempo_position += tone_value;
    }
}
