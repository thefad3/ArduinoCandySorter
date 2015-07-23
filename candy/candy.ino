int redPin=9;
int greenPin=10;
int bluePin=11;
#include <TimerOne.h>
#include <ColorRecognition.h>
#include <ColorRecognitionTCS230.h>

  ColorRecognitionTCS230* tcs230 = ColorRecognitionTCS230::getInstance();
  
  

//Define the color Sensor and the Read Values.
// LOW - LOW = RED
//LOW - HIGH = Blue
//HIGH - HIGH = Green
int S2=7;
int S3=8;
int outPin=3;

//Defining colors returned by the output.
int rColorStrength;
int gColorStrength;
int bColorStrength;

unsigned int pulseWidth;


void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(outPin, INPUT);
  tcs230->initialize(3, 7, 8);
  // Show something white to it during 4 seconds.
  tcs230->adjustWhiteBalance();
  
}

void loop() {


//  //Red - low + low
//  digitalWrite(S2, LOW);
//  digitalWrite(S3, LOW);
//  pulseWidth = pulseIn(outPin, LOW);
//  //Range returns 102400, soooo divide by 400 hunned.
//  rColorStrength = pulseWidth/400. -1;
//  rColorStrength = (255- rColorStrength);
//  
//
//  
//  //Green - high + high
//  digitalWrite(S2, HIGH);
//  digitalWrite(S3, HIGH);
//  pulseWidth = pulseIn(outPin, LOW);
//  //Range returns 102400, soooo divide by 400 hunned.
//  gColorStrength = pulseWidth/400. -1;
//  gColorStrength = (255- gColorStrength);
//
//
//  
//
//  //Blue - low + high
//  digitalWrite(S2, LOW);
//  digitalWrite(S3, HIGH);
//  pulseWidth = pulseIn(outPin, LOW);
//  //Range returns 102400, soooo divide by 400 hunned.
//  bColorStrength = pulseWidth/400. -1;
//  bColorStrength = (255 - bColorStrength);
//
//  
//  
//
//  Serial.print("Red: ");
//  Serial.println(rColorStrength);
//  
//  Serial.print("Blue: ");
//  Serial.println(bColorStrength);
//
//  Serial.print("Green: ");
//  Serial.println(gColorStrength);

    int colorRed = tcs230->getRed();
    int colorGreen = tcs230->getGreen();
    int colorBlue = tcs230->getBlue();
    
    if(colorRed>colorGreen && colorRed>colorBlue){
      colorRed = 255;
      colorGreen = 0;
      colorBlue = 0;
    }
//    if(colorRed>colorBlue && colorRed>colorGreen){
//      colorRed = 255;
//      colorBlue = colorBlue/2;
//      colorGreen = 0;
//    }

    
    if(colorGreen>colorRed && colorGreen>colorBlue){
      colorGreen = 255;
      colorRed = 0;
      colorBlue = 0;
    }
//    if(colorGreen>colorBlue && colorGreen>colorRed){
//      colorGreen = 255;
//      colorBlue = colorBlue/2;
//      colorRed = 0;
//    }  

    
    if(colorBlue>colorRed && colorBlue>colorGreen){
      colorBlue = 255;
      colorRed = 0;
      colorGreen = 0;
    }  
//
//    if(colorBlue>colorGreen && colorGreen>=colorRed){
//      colorBlue = 255;
//      colorGreen = colorGreen/2;
//      colorRed = 0;
//    }

    analogWrite(redPin, colorRed);
    analogWrite(greenPin, colorGreen);
    analogWrite(bluePin, colorBlue);

    
  delay(2000);
}






