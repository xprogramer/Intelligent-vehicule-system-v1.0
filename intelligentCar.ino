#include<Arduino.h>
#include "Nokia_5110_lcd.h"

const int trigPin = 11;
const int echoPin = 12;
const int buzzerPin = 13;

#define ms2cm(microseconds) microseconds/29/2


void log_distance(byte per)
{
  byte cpt = 0;
  while(per >= 100)
  {
      per -= 100;
      cpt++;
  }
  printNum2(cpt,20);
  cpt = 0;
  while(per >= 10)
  {
      per -= 10;
      cpt++;
  }
  printNum2(cpt,32);
  printNum2(per,44);
  setCursor(60,2);
  printChar(0x38, 0x44, 0x44, 0x44, 0x20);
  printChar(0x7F, 0x02, 0x04, 0x02, 0x7F);
}



void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  LCD_setup();
  
  Serial.begin(9600);
}

void loop()
{
  long duration, cm;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  cm = ms2cm(duration);

  if(cm <= 300)
  {
      tone(buzzerPin, 1900,300);
      if(cm > 40)
      {
        clear();
        log_distance(cm);
      }
      else
      {
        clear();
        setCursor(30,2);
        printChar(0x20, 0x54, 0x54, 0x54, 0x78);
        printChar(0x01, 0x01, 0x7f, 0x01, 0x01);
        printChar(0x01, 0x01, 0x7f, 0x01, 0x01);
      }
      Serial.println(cm);
      delay(cm*5);
  }
  else
  {
    log_distance(0);
  }
}

