
#include "max7219.h"
const int data = 8;
const int latch = 9;
const int clock = 10;
bool state;


Max7219 max7219 (data,clock,latch);

int msec;
int sec;
int min;
int hour;

unsigned long old_secs;
unsigned long new_secs;


void setup(){

  state = false;
  pinMode(13,OUTPUT);
  pinMode(3,INPUT);

  digitalWrite(13,state);
  digitalWrite(3,1);

  Serial.begin(115200);

  max7219.boot();

  msec = 0;
  sec  = 0;
  min  = 0;
  hour = 0;

  old_secs = millis();
}

void loop(){

  new_secs = millis();
  if (new_secs > old_secs) {
    old_secs = new_secs;
    update();
  }

}

void update(){

  max7219.bar(1, digitalRead(3) ? 0 : msec );
  max7219.bar(2,sec);
  max7219.bar(3,min);
  max7219.bar(4,hour);

  msec ++;
  if (msec >= 1000){
    sec ++;
    msec -= 1000;
  }

  if (sec >= 60){
    min ++;
    sec -= 60;
  }

  if (min >= 60){
    min -= 60;
    hour ++;
  }

}
