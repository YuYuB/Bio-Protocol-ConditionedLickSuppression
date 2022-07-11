#include <toneAC.h>

int Start = 0;
int End = 0;
int Y = 0;
int Z = 0;

long timeX[] = {300000,530000, 760000, 990000,1220000,1450000}; // 5/8,83/12,66/16,5/20,33/24,16/ minutes
long timeY[] = {510000,702000, 953000, 1100000,1335000, 1430000 }; // 
int X = 0;

const int outPin1 = 23; // 8 for Box 2

long prevMillis;

void setup() {
   pinMode(38, INPUT);
 // pinMode(44, OUTPUT);
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
//  digitalWrite(42, HIGH);
  digitalWrite(34, HIGH);
  Z = 1;
  Serial.println("Start");
  }

  if (Z == 1 && (millis() - prevMillis) > (long)(timeX[X])  && (millis() - prevMillis) < (long)(timeX[X])+ 10000){    
  toneAC(12000,10, 100, true); // TONE FREQUENCY = 12kHz
  //digitalWrite(outPin1, LOW);
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
