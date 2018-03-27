double curveStartX = 0;
double curveStartY = 0;

double curveLastX = 0;
double curveLastY = 0;

double curveNextX = 0;
double curveNextY = 0;

void curveTo(double x1, double y1, double x2, double y2, double x3, double y3){

  //save the starting point of the curve
  curveStartX = curX;
  curveStartY = curY;

  curveLastX = 0;
  curveLastY = 0;

  curveNextX = 0;
  curveNextY = 0;

  //divide the movement into sections (by increasing the t param between 0 and 1)
  for (double t=tStep; t<1.01; t+=tStep){
   
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

double calcCurve(double x1, double x2, double x3, double t){
  // Calc the next x or y coords according to bezier curve
  // http://en.wikipedia.org/wiki/B%C3%A9zier_curve#Cubic_B.C3.A9zier_curves
  double t1 = 1-t;
  double x = x1*3*pow(t1,2)*t + x2*3*t1*pow(t,2) + x3*pow(t,3);
  return x;
} 
