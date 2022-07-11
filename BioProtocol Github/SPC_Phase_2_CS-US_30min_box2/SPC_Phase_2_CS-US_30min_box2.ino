#include <toneAC.h>

int Start = 0;
int End = 0;
int Y = 0;
int Z = 0;

long time[] = {300000,540000, 780000, 1020000,1260000,1500000}; // 4,5/10,5/18/25,5
//long time[] = {3000,1260000, 2160000, 3060000};
int X = 0;

const int outPin1 = 8; // 8 for Box 2

long prevMillis;

void setup() {
   pinMode(38, INPUT);
  pinMode(42, OUTPUT);
  pinMode(34, OUTPUT);

  pinMode(outPin1, OUTPUT);  
//  pinMode(light, OUTPUT);
  digitalWrite(outPin1, LOW);
  Serial.begin(250000);

}

void loop() {

 Start = digitalRead(38); 
  
 //  digitalWrite(light,HIGH);

 if (Start && !End && Z == 0){
  prevMillis = millis();
  digitalWrite(42, HIGH);
  digitalWrite(34, HIGH);
  Z = 1;
  Serial.println("Start");
  }

  if (Z == 1 && (millis() - prevMillis) > (long)(time[X])  && (millis() - prevMillis) < (long)(time[X])+ 10000){  
  Y = 1;   
  toneAC(12000,10, 100, true); // TONE FREQUENCY = 12kHz
  //digitalWrite(outPin1, LOW);
  Serial.println("Tone2");
  }
  
  if (Z == 1 && (millis() - prevMillis) > ((long)(time[X]) + 9000)  && (millis() - prevMillis) < (long)(time[X])+ 10000){
    digitalWrite(outPin1, HIGH);
    Serial.println("Shock");
    }

 if (Y == 1 && Z == 1 && (millis() - prevMillis) > (long)(time[X])+ 10000){
    X = X+1;
    Y = 0;
    digitalWrite(outPin1, LOW);
    Serial.println("STOP");
  }

 if (Z == 1 && (millis() - prevMillis) > 1800000){   
     

  digitalWrite(42, LOW);
 }  

 End = Start;
}
