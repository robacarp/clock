#include "max7219.h"

//Wire must be included here as well as in the ds1307.cpp
#include "Wire.h"
#include "ds1307.h"

const int data = 8;
const int latch = 9;
const int clock = 10;
bool state, read_next;

Max7219 max7219 (data,clock,latch);
ds1307 rtc;

unsigned long old_secs;
unsigned long new_secs;

byte hour, min, sec, dow, dom, mon, year;

void tick(){ sec ++; }

void setup(){
  Serial.begin(115200);

  state = false;
  pinMode(13,OUTPUT);
  pinMode(3,INPUT);

  digitalWrite(13,state);
  digitalWrite(3,1);

  max7219.boot();

  old_secs = millis();
  read_next = true;

  attachInterrupt( 1, tick, FALLING );

  rtc.set(
      12, 34, 56,
      1, 1, 1, 10
    );

}

void loop(){
  if (true || read_next){
    read_clock();
    if (sec >= 60 || min >= 60 || hour >= 24)
      zero_clock();
    read_next = false;
  }

  if (sec >= 60){
    min ++;
    sec -= 60;
  }

  if (min >= 60){
    hour ++;
    min -= 60;
    read_next = true;
  }

  if (hour >= 24){
    hour -= 24;
    dow ++;
    dom ++;
  }


  new_secs = millis();
  if (new_secs - old_secs > 500) {
    old_secs = new_secs;
    update();
    print_time();
    digitalWrite(13, state);
    state = ! state;
  }

}

void update(){

  max7219.bar(1, sec);
  max7219.bar(2, min);
  max7219.bar(3, hour);
  max7219.bar(4, dom);

}

void read_clock(){
  rtc.get_time( &sec, &min, &hour, &dow, &dom, &mon, &year );
}

void zero_clock(){
  Serial.println("Setting Clock.");
  rtc.set( 0,0,0, 1,1,1,10);
}

void print_time(){
  Serial.print( hour , DEC);
  Serial.print(":");
  Serial.print( min , DEC);
  Serial.print(":");
  Serial.print( sec , DEC);

  Serial.print(" ");
  Serial.print( dow , DEC);
  Serial.print(" ");
  Serial.print( year , DEC);
  Serial.print(" ");
  Serial.print( mon , DEC);
  Serial.print(" ");
  Serial.println( dom , DEC);
}

