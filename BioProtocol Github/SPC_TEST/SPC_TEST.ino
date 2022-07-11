#include <toneAC.h>

#include <Wire.h>/dev
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int X;
int V;


int Next;

int TRIAL = 0;

int END = 0;

int S;
int E;
int S2;
int E2;
int MAG;
int ENDMAG;
int Trigger = 0;
int ToneZ = 0;

int light= 34;

int K = 34;
int valK = 0;

int redPin = 42;
int greenPin = 40;
int bluePin = 41;
int PINMAG = 25;

int StartLick = 0;


int lickLive = 0; 

int IN_MAG = 0;

int StartingVariable = 0;

int lick_left = 0;


unsigned long ArduinoStart;
unsigned long current_time;
unsigned long current_time2;
unsigned long STARTER;
unsigned long CountDown;
unsigned long CountDown2;
unsigned long ECOULE;
unsigned long ECOULE2;
unsigned long NOW;
unsigned long STARTPLAY;
unsigned long TIMEOUT;
unsigned long FearStart;
unsigned long FEAR;
unsigned long MEASURE;
unsigned long CS;
unsigned long ToneOFF;


void setup() {
 Serial.begin(250000);
pinMode(38, INPUT);
pinMode(39, INPUT);
pinMode(25, INPUT);
digitalWrite(25, HIGH);
  ArduinoStart = millis();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  pinMode(light, OUTPUT);

  while (!Serial);        

    if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
      while (1);
  }


}

void loop() {
currtouched = cap.touched();

  
S = digitalRead(38);
S2 = digitalRead(39);

if (S & !E & StartingVariable == 0) {
StartingVariable = StartingVariable + 1;
digitalWrite(redPin, HIGH);
digitalWrite(bluePin, LOW);
digitalWrite(greenPin, LOW);
 digitalWrite(light,HIGH);
Serial.print("START");
//Serial.print(StartingVariable);
Serial.println();
STARTER = millis() - ArduinoStart;
}
 
if (StartingVariable > 0 && StartingVariable <2) {
 
  
 if (S2 & !E2 && StartingVariable == 1) {
StartingVariable = 2;
}

 MAG = digitalRead(PINMAG) ; 

 current_time = millis() - STARTER;
    
 if ( MAG == LOW) { // Mouse is inside the mag 
IN_MAG = 1;
if (Next == 0){
ECOULE = (millis()-STARTER) - CountDown; } // Countdown 5s when inside mag
 if (X == 0 && ECOULE >= 5000 && Trigger == 0) {Next = 1; Trigger = 1 ; TIMEOUT = millis();X = 1; V = 1; CS = millis()-STARTER;TRIAL = TRIAL + 1;
 Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(FearStart);
    Serial.print(';');
    Serial.print(FEAR);
    Serial.print(';');
    Serial.print(TRIAL);
    Serial.print(';');
    Serial.print(CS);
    Serial.print(';');
    Serial.print(ToneOFF);
    Serial.print(';');
    Serial.print(MEASURE);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
 CS = 0;
 }// Mouse is inside the mag for 5 consecutive seconds
  }   
  
  else{
     StartLick = 0;
    CountDown = current_time;
  IN_MAG = 0;
  }
  

  
if (Trigger == 1 && ((millis()-TIMEOUT)<10000)){
toneAC(12000,10, 100, true);
ToneZ = 1;
Next = 1;
}  

if (ToneZ == 1 && ((millis()-TIMEOUT)>10000)){
  ToneOFF = millis()-STARTER;
Trigger = 0;
ToneZ = 0;

Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(FearStart);
    Serial.print(';');
    Serial.print(FEAR);
    Serial.print(';');
    Serial.print(TRIAL);
    Serial.print(';');
    Serial.print(CS);
    Serial.print(';');
    Serial.print(ToneOFF);
    Serial.print(';');
    Serial.print(MEASURE);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
    ToneOFF = 0;

    if(TRIAL ==5){
      StartingVariable = 2;
    }
}  

if (X == 1 && MAG == HIGH){
X = 2;                          
FearStart = millis()-STARTER;

} 

/*
if (X == 2 && MAG == LOW && !ENDMAG == HIGH){
X = 3;
FEAR = (millis()-STARTER)-FearStart;
TRIAL = TRIAL + 1;
} 
*/

if (MAG && !ENDMAG){
  
  Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(FearStart);
    Serial.print(';');
    Serial.print(FEAR);
    Serial.print(';');
    Serial.print(TRIAL);
    Serial.print(';');
    Serial.print(CS);
    Serial.print(';');
    Serial.print(ToneOFF);
    Serial.print(';');
    Serial.print(MEASURE);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
    

}
if (!MAG && ENDMAG){

  if (X == 2){
    FEAR = (millis()-STARTER)-FearStart;
  }
Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(FearStart);
    Serial.print(';');
    Serial.print(FEAR);
    Serial.print(';');
    Serial.print(TRIAL);
    Serial.print(';');
    Serial.print(CS);
    Serial.print(';');
    Serial.print(ToneOFF);
    Serial.print(';');
    Serial.print(MEASURE);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();

if (X == 2 && ToneZ == 0){
    X = 0;  
  FEAR = 0;
  FearStart = 0;
  
    Next = 0;
  }
    
}

  
if ((currtouched & _BV(11)) && !(lasttouched & _BV(11)) ) {
    lickLive = 1;
    lick_left += 1;
     Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(FearStart);
    Serial.print(';');
    Serial.print(FEAR);
    Serial.print(';');
    Serial.print(TRIAL);
    Serial.print(';');
    Serial.print(CS);
    Serial.print(';');
    Serial.print(ToneOFF);
    Serial.print(';');
    Serial.print(MEASURE);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
    lickLive = 0;
  
  }
  
  else {
  lickLive = 0;
  /*
    Serial.print(current_time);
    Serial.print(',');
    Serial.print(lick_left);
    Serial.print(',');
    Serial.print(lickLive);
    Serial.print(',');
    Serial.print(IN_MAG);
    Serial.print(',');
    Serial.print(FEAR);
    Serial.print(',');
    Serial.println();

    */
  }





lasttouched = currtouched;
delay(10);



ENDMAG = MAG ;
}
  
if (current_time < 1800000 && StartingVariable == 2) { 
  END = 1;
digitalWrite(bluePin, LOW);
digitalWrite(redPin, LOW);
 digitalWrite(light,LOW);
     Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(FearStart);
    Serial.print(';');
    Serial.print(FEAR);
    Serial.print(';');
    Serial.print(TRIAL);
    Serial.print(';');
    Serial.print(CS);
    Serial.print(';');
    Serial.print(ToneOFF);
    Serial.print(';');
    Serial.print(MEASURE);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();

 StartingVariable = 0;
  Trigger = 0;
  StartLick = 0;
  lickLive = 0;
  IN_MAG = 0;
  lick_left = 0;
  ArduinoStart = 0;
  current_time = 0;
  FearStart = 0;
  FEAR = 0;
  X = 0;
  TRIAL = 0;
  END = 0;
  S = 0;
  V = 0;

digitalWrite(greenPin, HIGH);
//if (S & !E) {   

//StartingVariable = 3;

//}


}

  if (current_time >= 1800000 || StartingVariable == 3) {
    END = 1;
  digitalWrite(bluePin, HIGH);  
  digitalWrite(greenPin, LOW);
digitalWrite(redPin, LOW);  
 digitalWrite(light,LOW);

     Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(FearStart);
    Serial.print(';');
    Serial.print(FEAR);
    Serial.print(';');
    Serial.print(TRIAL);
    Serial.print(';');
    Serial.print(CS);
    Serial.print(';');
    Serial.print(ToneOFF);
    Serial.print(';');
    Serial.print(MEASURE);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
 
  StartingVariable = 0;
  Trigger = 0;
  StartLick = 0;
  lickLive = 0;
  IN_MAG = 0;
  lick_left = 0;
  ArduinoStart = 0;
  current_time = 0;
  FearStart = 0;
  FEAR = 0;
  X = 0;
  TRIAL = 0;
  END = 0;
  S = 0;
  V = 0;
  
}
E = S;
E2 = S2;
}





