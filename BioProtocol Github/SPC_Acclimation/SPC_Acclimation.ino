
#include <Wire.h>/dev
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int S;
int E;
int S2;
int E2;
int MAG;
int ENDMAG;

int Entry;
int Exit;

int END = 0;

int light= 34;


//int redPin = 42;
//int greenPin = 40;
//int bluePin = 41;
int PINMAG = 25;

int StartLick = 0;


int lickLive = 0; 

int IN_MAG = 0;

int StartingVariable = 0;

int lick_left = 0;


unsigned long ArduinoStart;
unsigned long current_time;
unsigned long STARTER;
unsigned long CountDown;
unsigned long ECOULE;
unsigned long NOW;
unsigned long STARTPLAY;
unsigned long TIMEOUT;



void setup() {
 Serial.begin(250000);
pinMode(38, INPUT);
//pinMode(39, INPUT);
pinMode(25, INPUT);
digitalWrite(25, HIGH);
  ArduinoStart = millis();
 // pinMode(redPin, OUTPUT);
 // pinMode(greenPin, OUTPUT);
 // pinMode(bluePin, OUTPUT);  
 // pinMode(light, OUTPUT);

  while (!Serial);        

    if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
      while (1);
  }


}

void loop() {
currtouched = cap.touched();

  
S = digitalRead(38);
//S2 = digitalRead(39);

if (S & !E & StartingVariable == 0) {
StartingVariable = StartingVariable + 1;
//digitalWrite(redPin, HIGH);
//digitalWrite(bluePin, LOW);
// digitalWrite(light,HIGH);
Serial.print("START");
Serial.println();
STARTER = millis() - ArduinoStart;
}
 
if (StartingVariable > 0 && StartingVariable <2) {
 
/*  
 if (S2 & !E2 && StartingVariable == 1) {
StartingVariable = 2;
}
  */
  
 MAG = digitalRead(PINMAG) ; 
 
  if ( MAG == LOW) { 
IN_MAG = 1;
  }
  else{
    IN_MAG = 0;  
  }

current_time = millis() - STARTER;  


if (MAG && !ENDMAG){
    Entry = 1;
    Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(Entry);
    Serial.print(';');
    Serial.print(Exit);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
    Entry = 0;
}
if (!MAG && ENDMAG){
    Exit = 1;
    Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(Entry);
    Serial.print(';');
    Serial.print(Exit);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
    Exit = 0;
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
    Serial.print(Entry);
    Serial.print(';');
    Serial.print(Exit);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
    lickLive = 0; 
  }
  
  else {

  lickLive = 0;

  }
lasttouched = currtouched;

delay(5);

ENDMAG = MAG ;

}

/*
if (current_time < 1800000 && StartingVariable == 2 && END == 0) { 
  END = 1;
digitalWrite(bluePin, LOW);
digitalWrite(redPin, LOW);

digitalWrite(greenPin, HIGH);

    Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(Entry);
    Serial.print(';');
    Serial.print(Exit);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println(); }

if (END == 1 && S & !E) {   

StartingVariable = 3;


}

*/
  if (current_time >= 1800000 || StartingVariable == 3) {
    END = 1;
    Serial.print(current_time);
    Serial.print(';');
    Serial.print(lick_left);
    Serial.print(';');
    Serial.print(lickLive);
    Serial.print(';');
    Serial.print(IN_MAG);
    Serial.print(';');
    Serial.print(Entry);
    Serial.print(';');
    Serial.print(Exit);
    Serial.print(';');
    Serial.print(END);
    Serial.print(';');
    Serial.println();
    
//  digitalWrite(bluePin, HIGH);  
//  digitalWrite(greenPin, LOW);
//digitalWrite(redPin, LOW);  
digitalWrite(light,LOW);
  StartingVariable = 0;
  StartLick = 0;
  lickLive = 0;
  IN_MAG = 0;
  lick_left = 0;
//  etat = 0;
  ArduinoStart = 0;
  current_time = 0;
  END = 0;
}
E = S;
//E2 = S2;
}
