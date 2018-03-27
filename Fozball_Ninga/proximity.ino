
const int PROX[] = {A0, A3};

const float samples = 5;
int proxIdx[] = {0,0};

float maxProx = 100;
float minProx = 5;

float prox[] = {0,0};

float calcProx(int player){

  prox[player] = (analogRead(PROX[player]));
 
  if (print_prox){
      Serial.print("prox: ");
      Serial.print((prox[player]));
      Serial.print("\t");
      proxIdx[player]=0;
  }
  
  return prox[player];

}


float proximityToCentimenters(float analogData){
  //float distance = 41.543 * pow((analogData + 0.30221), -1.5281);
  float distance=(6762 / (analogData - 9)) - 4;
  
  return analogData; 
}
