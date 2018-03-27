
String svg = "m10,15c0,5 100,5 100,0";//c7.07515,1.71527 13.75711,3.98692 20,5c5.92253,0.96109 12.10701,1.08099 16,2c4.35251,1.02748 7.70267,4.54137 11,6";//c3.77065,1.66801 8,3 12,5c4,2 9.06134,4.82462 15,7c5.05659,1.85226 9.05165,4.35927 13,5c3.12144,0.50655 5.81265,2.2068 8,4c2.78833,2.28587 9.29402,2.46718 12,9c0.76538,1.84776 6.22885,5.72961 11,10c4.21509,3.77267 8,7 12,11c4,4 7.69254,8.186 9,10c3.30762,4.58908 8.09943,6.81242 12,9c8.22827,4.6147 10.90634,7.10341 12,8c2.78833,2.28587 5.07193,4.95328 7,8c3.1181,4.92722 6.72961,9.22885 11,14c3.77267,4.21509 7.724,7.22272 11,11c3.70639,4.2735 8.2771,7.228 12,9c4.51468,2.14886 8.70547,5.34619 11,7c3.62799,2.6149 7.70267,4.54135 11,6c3.77063,1.66803 8.0769,2.73145 12,4c5.12396,1.65686 8.57111,3.67947 13,6c2.80109,1.46762 5.88495,2.27432 8,3c4.82303,1.65482 9,1 11,1c1,0 2,0 4,0c1,0 2,0 3,0l2,0l1,0l1,0";

void drawSVG(){
  
    Serial.println("Drawing SVG");    

  while (svg.length() > 0){
    
    String type = svg.substring(0,1);
    svg = svg.substring(1);
    
    int next = svg.length();
    int c = svg.indexOf("c");
    if (c!=-1 && c<next) next=c;
    int l = svg.indexOf("l");
    if (l!=-1 && l<next) next=l;
    int m = svg.indexOf("m");
    if (m!=-1 && m<next) next=m;

    String data = svg.substring(0,next);
    svg = svg.substring(next);
    
    drawSection(type, data);
      
  }

}

void drawSection(String type, String data){

  if (debug){
    Serial.print("Drawing Section: ");    
    Serial.print(type);    
    Serial.print(" | ");    
    Serial.println(data);    
  }
  float x[3];
  float y[3];
  
  for (int i=0; i<3; i++){
    
    //parse each set of x,y
    int nextX = data.indexOf(",");
    int nextY = data.indexOf(" ");
    char nums[16];
      if (nextY > 0){
        data.substring(0,nextX).toCharArray(nums, 5);
        x[i] = atof(nums);
        data.substring(nextX+1, nextY).toCharArray(nums, 5);
        y[i] = atof(nums);
        data = data.substring(nextY+1);
      }else if (data.length() > 0){
        data.substring(0,nextX).toCharArray(nums, 5);
        x[i] = atof(nums);
        data.substring(nextX+1).toCharArray(nums, 5);
        y[i] = atof(nums);
        data = "";
      }else{
        x[i] = -1;
        y[i] = -1;
      }
      
      if (debug){
        Serial.print("Parsing: ");    
        Serial.print(nextX);    
        Serial.print(" | ");    
        Serial.print(nextY);    
        Serial.print(" | ");    
        Serial.println(data);    
      }
  }
     
  if (debug){
    if (type == "m"){
      Serial.print("move to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "l"){
      Serial.print("line to ");    
      Serial.print(x[0]);    
      Serial.print(",");    
      Serial.print(y[0]);    
      Serial.println(" ");    
    } else if (type == "c"){
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
  if (type == "m"){
    goTo(x[0], y[0]);
  } else if (type == "l"){
    lineTo(x[0], y[0]);
  } else if (type == "c"){
    curveTo(x[0], y[0], x[1], y[1], x[2], y[2]);
 }
  
}

