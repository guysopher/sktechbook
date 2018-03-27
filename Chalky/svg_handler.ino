
//shalom
//String svg = "M247,27.5c0,78.294-58,79-58,0M218.5,86L218.5,28M124.067,18c16.555,0,6.816,13.976,0,13.976c-7.79,0-5.328,11.305,33.337,0C196.07,20.67,164.257,84.029,125.184,86M96.088,28c5.883,0,8.089,37.707,8.089,58.486M32.509,32.531c11.073-12.947,33.264-7.632,40.795-0.427c7.53,7.205,11.297,38.685,0,49.932c-11.298,11.248-32.635,10.092-40.795,0C24.351,71.944,24.351,42.07,32.509,32.531";
//chalky
//<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" id="Layer_1" x="0px" y="0px" width="640px" height="480px" viewBox="0 0 640 480" enable-background="new 0 0 640 480" xml:space="preserve">
//<path fill="#FFFFFF" stroke="#000000" stroke-miterlimit="10" d="M77.5,40c-47.449,0-47.449,47,0,47"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="97.5" y1="40" x2="97.5" y2="87"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="130.5" y1="40" x2="130.5" y2="87"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="97" y1="63.5" x2="130" y2="63.5"/>
//<path fill="none" stroke="#000000" stroke-miterlimit="10" d="M148,87.5c0-64.274,37-64.274,37,0"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="150" y1="63.5" x2="183" y2="63.5"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="206.5" y1="39" x2="206.5" y2="87"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="206" y1="87.5" x2="242" y2="87.5"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="252.5" y1="39" x2="252.5" y2="87"/>
//<path fill="none" stroke="#000000" stroke-miterlimit="10" d="M286.255,40C262.749,58.92,252.5,63,252.5,63  c0,10.949,20.617,23.397,33.755,23.397"/>
//<path fill="none" stroke="#000000" stroke-miterlimit="10" d="M308,39.5c0,34.821,34,36,34,0"/>
//<line fill="none" stroke="#000000" stroke-miterlimit="10" x1="324.5" y1="66" x2="324.5" y2="86"/>
//</svg>
String svg = "M77.5,40c-47.449,0-47.449,47,0,47M97.5,40L97.5,87M130.5,40L130.5,87M97,63.5L130,63.5M148,87.5c0-64.274,37-64.274,37,0M150,63.5L183,63.5M206.5,39L206.5,87M206,87.5L242,87.5M252.5,39L252.5,87M286.255,40C262.749,58.92,252.5,63,252.5,63  c0,10.949,20.617,23.397,33.755,23.397M308,39.5c0,34.821,34,36,34,0M324.5,66L324.5,86";

void drawSVG(){
  
  Serial.println("Drawing SVG");    

  while (svg.length() > 0){
    
    String type = svg.substring(0,1);
    svg = svg.substring(1);
    
    char opts[] = {'c','C','m','M','l','L'};
    
    int next = svg.length();
    for (int i=0; i < 6; i++){
      int c = svg.indexOf(opts[i]);
      if (c!=-1 && c<next) next=c;
    }

    String data = svg.substring(0,next);
    svg = svg.substring(next);
    
    drawSection(type, data);
      
  }

}

void drawSection(String type, String data){

  if (print_parsing){
    Serial.print("Drawing Section: ");    
    Serial.print(type);    
    Serial.print(" | ");    
    Serial.println(data);    
  }
  double x[3];
  double y[3];
  
  for (int i=0; i<3; i++){
    
    //parse each set of x,y
    char opts[] = {',',' ','-'};
    int nextX = data.length();
    for (int i=0; i < 3; i++){
      int c = data.indexOf(opts[i], 1);
      if (c!=-1 && c<nextX) nextX=c;
    }
    int nextY = data.length();
    for (int i=0; i < 3; i++){
      int c = data.indexOf(opts[i], (nextX+1));
      if (c!=-1 && c<nextY) nextY=c;
    }
    
    int skipX = 1;
    if (data[nextX]=='-') skipX = 0;
    int skipY = 1;
    if (data[nextY]=='-') skipY = 0;

    char nums[16];
    if (nextY > 0){
      data.substring(0,nextX).toCharArray(nums, 8);
      x[i] = atof(nums);
      data.substring(nextX+skipX, nextY).toCharArray(nums, 8);
      y[i] = atof(nums);
      data = data.substring(nextY+skipY);
    }else if (data.length() > 0){
      data.substring(0,nextX).toCharArray(nums, 8);
      x[i] = atof(nums);
      data.substring(nextX+skipX).toCharArray(nums, 8);
      y[i] = atof(nums);
      data = "";
    }else{
      x[i] = -1;
      y[i] = -1;
    }
    
    if (print_parsing){
      Serial.print("Parsing: ");    
      Serial.print(nextX);    
      Serial.print(" | ");    
      Serial.print(nextY);    
      Serial.print(" | ");    
      Serial.print(x[i]);    
      Serial.print(" | ");    
      Serial.print(y[i]);    
      Serial.print(" | ");    
      Serial.println(data);    
    }

    //normalize if needed
    if (type == "L" || type == "M" || type == "C"){
      x[i] -= curX;
      y[i] -= curY;
 
      if (print_parsing){
        Serial.print("Normalized: ");    
        Serial.print(nextX);    
        Serial.print(" | ");    
        Serial.print(nextY);    
        Serial.print(" | ");    
        Serial.print(x[i]);    
        Serial.print(" | ");    
        Serial.print(y[i]);    
        Serial.print(" | ");    
        Serial.println(data);    
     }
   }
  

  }
     
  if (print_parsing){
    if (type == "m" || type == "M"){
      Serial.print("move to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "l" || type == "L"){
      Serial.print("line to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "c" || type == "C"){
      Serial.print("curve to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.print(" ");    
      Serial.print(x[1]);    
      Serial.print(",");    
      Serial.print(y[1]);    
      Serial.print(" ");    
      Serial.print(x[2]);    
      Serial.print(",");    
      Serial.print(y[2]);    
      Serial.println(" ");    
    } 
  }

  //draw the section
  if (type == "m" || type == "M"){
    goTo(x[0], y[0]);
  } else if (type == "l" || type == "L"){
    lineTo(x[0], y[0]);
  } else if (type == "c" || type == "C"){
    curveTo(x[0], y[0], x[1], y[1], x[2], y[2]);
  }
 
  
}

