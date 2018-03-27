float curveStartX = 0;
float curveStartY = 0;

float curveLastX = 0;
float curveLastY = 0;

float curveNextX = 0;
float curveNextY = 0;

void curveTo(float x1, float y1, float x2, float y2, float x3, float y3){

  //save the starting point of the curve
  curveStartX = curX;
  curveStartY = curY;

  curveLastX = 0;
  curveLastY = 0;

  curveNextX = 0;
  curveNextY = 0;

  //divide the movement into sections (by increasing the t param between 0 and 1)
  for (float t=0; t<1; t+=tStep){
   
    //save the last x,y coords
    curveLastX = curveNextX;
    curveLastY = curveNextY;
   
    //calc the next x,y coords
    curveNextX = calcCurve(x1, x2, x3, t);
    curveNextY = calcCurve(y1, y2, y3, t);
    
    //make the line relavite to the current position
    curveNextX - curveLastX;
    
    //draw a line to the next coords
    lineTo((curveNextX - curveLastX), (curveNextY - curveLastY));
  }
}

float calcCurve(float x1, float x2, float x3, float t){
  // Calc the next x or y coords according to bezier curve
  // http://en.wikipedia.org/wiki/B%C3%A9zier_curve#Cubic_B.C3.A9zier_curves
  float t1 = 1-t;
  float x = x1*3*pow(t1,2)*t + x2*3*t1*pow(t,2) + x3*pow(t,3);
  return x;
} 
