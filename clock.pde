
#include "max7219.h"
const int data = 8;
const int latch = 9;
const int clock = 10;
bool state;


Max7219 max7219 (data,clock,latch);

void setup(){

  state = false;
  pinMode(13,OUTPUT);
  digitalWrite(13,state);
  Serial.begin(115200);

  max7219.boot();
}
void loop(){

  state = ! state;
  digitalWrite(13,state);

  max7219.digit(0, state);

  delay(500);

}
