#ifndef DS1307_CPP
#define DS1307_CPP

#include "ds1307.h"
#include "WProgram.h"
#include "Wire.h"


ds1307::ds1307(){
  Wire.begin();
  _address = 0x68;
}

void ds1307::set(
    byte sec, byte min, byte hour,
    byte dow, byte dom,
    byte mon, byte year
  ){

  Wire.beginTransmission(0x68);
  Wire.send(0);
  Wire.send(ds1307::encode(sec) & 0xff); //second. Force the "go" bit on, lest someone stop the clock...
  Wire.send(ds1307::encode(min));
  Wire.send(ds1307::encode(hour) & 0x3f); //hour. Force it into 24 hr mode.

  Wire.send(ds1307::encode(dow)); //weekday
  Wire.send(ds1307::encode(dom)); //day of month
  Wire.send(ds1307::encode(mon)); //month
  Wire.send(ds1307::encode(year)); //year
  Wire.send(0x10); //enable 1Hz output
  Wire.endTransmission();
}


int ds1307::get_time(byte *second, byte *minute, byte *hour, byte *week_day, byte *month_day, byte *month, byte *year){
  Wire.beginTransmission(_address);
  Wire.send( 0x00 );
  Wire.endTransmission();

  Wire.requestFrom(_address,7);
  *second    = ds1307::decode(Wire.receive() & 0x7f);
  *minute    = ds1307::decode(Wire.receive());
  *hour      = ds1307::decode(Wire.receive() & 0x3f);
  *week_day  = ds1307::decode(Wire.receive());
  *month_day = ds1307::decode(Wire.receive());
  *month     = ds1307::decode(Wire.receive());
  *year      = ds1307::decode(Wire.receive());

  return *second;
}


#endif
