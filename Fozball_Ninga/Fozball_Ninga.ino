
boolean print_prox = false;
boolean print_racket = false;
boolean print_json = true;
const int player1 = 0;
const int player2 = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int i = 0;

void loop() {
  
  int player = 0;
  
//  Serial.println(analogRead(A4));
//  delay(1);
//  return;
  
  for (player=0; player < 2; player++){
 
    float prox = calcProx(player);
    float sped = getRacketSpeed(player);
    
    if (print_json){
  //    String json = printf("{player:%d,speed:%'.2f,prox:%'.2f}", player, sped, prox);
      //Serial.println(json);
      Serial.print(player);
      Serial.print(",");
      Serial.print(sped);
      Serial.print(",");
      Serial.print(prox);
      Serial.print("****");
      delay(500);
    }
  }
  if (print_prox || print_racket){
        Serial.println("");
  }
}


