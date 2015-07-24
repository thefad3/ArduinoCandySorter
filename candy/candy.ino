#include <TimerOne.h>
 
#define S0     6   
#define S1     5
#define S2     4
#define S3     3
#define OUT    2

int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int   g_count = 0;    // count the frequecy
int   g_array[3];     // store the RGB value
int   g_flag = 0;     // filter of RGB queue
float g_SF[3];        // save the RGB Scale factor
 
 
// Init TSC230 and setting Frequency.
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
 
  digitalWrite(S0, LOW);  
  digitalWrite(S1, HIGH); 
}
 
// Select the filter color 
void TSC_FilterColor(int Level01, int Level02)
{
  if(Level01 != 0)
    Level01 = HIGH;
 
  if(Level02 != 0)
    Level02 = HIGH;
 
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}
 
void TSC_Count()
{
  g_count ++ ;
}
 
void TSC_Callback()
{
  switch(g_flag)
  {
    case 0: 
         Serial.println("->WB Start");
         TSC_WB(LOW, LOW);              //Filter without Red
         break;
    case 1:
         Serial.print("->Frequency R=");
         Serial.println(g_count);
         g_array[0] = g_count;
         TSC_WB(HIGH, HIGH);            //Filter without Green
         break;
    case 2:
         Serial.print("->Frequency G=");
         Serial.println(g_count);
         g_array[1] = g_count;
         TSC_WB(LOW, HIGH);             //Filter without Blue
         break;
 
    case 3:
         Serial.print("->Frequency B=");
         Serial.println(g_count);
         Serial.println("->WB End");
         g_array[2] = g_count;
         TSC_WB(HIGH, LOW);             //Clear(no filter)   
         break;
   default:
         g_count = 0;
         break;
  }
}
 
void TSC_WB(int Level0, int Level1)      //White Balance
{
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
  Timer1.setPeriod(1000000);             
}
 
void setup()
{
  TSC_Init();
  Serial.begin(9600);
  Timer1.initialize();             
  Timer1.attachInterrupt(TSC_Callback);  
  attachInterrupt(0, TSC_Count, RISING);  
 
  delay(4000);
 
  for(int i=0; i<3; i++)
    Serial.println(g_array[i]);
 
  g_SF[0] = 255.0/ g_array[0];     //R Scale factor
  g_SF[1] = 255.0/ g_array[1] ;    //G Scale factor
  g_SF[2] = 255.0/ g_array[2] ;    //B Scale factor

  
  Serial.println(g_SF[0]);
  Serial.println(g_SF[1]);
  Serial.println(g_SF[2]);
 
}
 
void loop()
{
   g_flag = 0;
   Serial.println("FUCKING COLORS!");
   for(int i=0; i<3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));

    Serial.println("FUCKING END");
    int r = int(g_array[0] * g_SF[0]);
    int g = int(g_array[1] * g_SF[1]);
    int b = int(g_array[2] * g_SF[2]);

   if( fudge(r,255) && fudge(g,255) && fudge(b,255)){
      Serial.println(".");


   }else if( fudge(r,285) && fudge(g,285) && fudge(b,275)){
      Serial.println("\t\t YELLOW!!!!!"); 
   }else if( fudge(r,255) && fudge(g,260) && fudge(b,271)){
      Serial.println("\t\t BLUE!!!!!"); 
   }else if( fudge(r,261) && fudge(g,250) && fudge(b,261)){
      Serial.println("\t\t RED!!!!!"); 
   }
   delay(4000);
 
}



boolean fudge(int num1, int num2){
  if(num1 > (num2*0.95) && num1 < (num2*1.05)){
    return true;
  }else{
    return false;
  }
}

