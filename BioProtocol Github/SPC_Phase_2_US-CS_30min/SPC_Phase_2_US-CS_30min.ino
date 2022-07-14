#include <toneAC.h>

int Start = 0;
int End = 0;
int Y = 0;
int Z = 0;

long timeX[] = {300000,540000, 840000, 1020000,1260000,1500000}; 
long timeY[] = {510000,702000, 954000, 1098000,1335000, 1428000 };
int X = 0;

const int outPin1 = 8; //

long prevMillis;

void setup() {
   pinMode(38, INPUT);
 // pinMode(44, OUTPUT);
  pinMode(34, OUTPUT);

  pinMode(outPin1, OUTPUT);  
  digitalWrite(outPin1, LOW);
  Serial.begin(250000);

}

void loop() {

 Start = digitalRead(38); 
  

 if (Start && !End && Z == 0){
  prevMillis = millis();
//  digitalWrite(42, HIGH);
  digitalWrite(34, HIGH);
  Z = 1;
  Serial.println("Start");
  }

  if (Z == 1 && (millis() - prevMillis) > (long)(timeX[X])  && (millis() - prevMillis) < (long)(timeX[X])+ 10000){    
  toneAC(12000,10, 100, true); // TONE FREQUENCY = 12kHz
  Serial.println("Tone2");
  }
  
  if (Z == 1 && (millis() - prevMillis) > (long)(timeY[Y])  && (millis() - prevMillis) < (long)(timeY[Y])+ 1000){
    digitalWrite(outPin1, HIGH);
    Serial.println("Shock");
    }

 if (Z == 1 && (millis() - prevMillis) > (long)(timeX[X])+ 10000){
    X=X+1;
    noToneAC();
    digitalWrite(outPin1, LOW);
    Serial.println("CS STOP");
  }

 if (Z == 1 && (millis() - prevMillis) > (long)(timeY[Y])+ 1000){
    Y=Y+1;
    noToneAC();
    digitalWrite(outPin1, LOW);
    Serial.println("US STOP");
  }  

 if (Z == 1 && (millis() - prevMillis) > 1800000){   
     

  digitalWrite(34, LOW);
 }  

 End = Start;
}
