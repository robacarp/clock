#ifndef MAX7219_CPP
#define MAX7219_CPP

#include "WProgram.h"
#include "max7219.h"

Max7219::Max7219(int data, int clock, int latch){
  _data = data;
  _clock = clock;
  _latch = latch;
}

void Max7219::boot(){

  pinMode(_data, OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_latch, OUTPUT);

  shutdown(false);
  test(false);
  intensity(0xf);
  decode(false);
  scan_limit(4);

  set_display( 0 );

}

void Max7219::send_bit(bool bit){
  digitalWrite(_clock, false);

  digitalWrite(_data, bit);

  digitalWrite(_clock, true);
}

void Max7219::send_word(unsigned int byte){
  unsigned int mask = 0x1 << 15;

  digitalWrite(_latch, false);

  //mask will be zero when it shifts the 1 off the end
  while (mask){
    //pull off the current bit and send it
    if (mask & byte){
      send_bit(true);
    } else {
      send_bit(false);
    }

    //increment the mask
    mask = mask >> 1;
  }

  //latch it, baby!
  digitalWrite(_latch, true);
}

void Max7219::set_register(byte address, byte data){
  unsigned int word = address;
  word = word << 8;
  word = word | data;
  //Serial.print("set register: ");
  //Serial.print(address,BIN);
  //Serial.print(" ");
  //Serial.println(data,BIN);

  send_word(word);
}

void Max7219::test       ( bool on         ) { set_register(0x0f, on         ); }
void Max7219::decode     ( bool on         ) { set_register(0x09, on         ); }
void Max7219::intensity  ( byte brightness ) { set_register(0x0a, brightness ); }
void Max7219::shutdown   ( bool enabled    ) { set_register(0x0c, !enabled   ); }
void Max7219::scan_limit ( byte count      ) { set_register(0x0b, count      ); }

void Max7219::set_display( byte state ){

  for (int i=0; i<9; i++)
    set_register(i,state);

}

//TODO: this isn't really correct when used with a common anode 7seg.
void Max7219::digit(int digit, int value){
  digit ++;
  byte data;
  switch(value){
  case 1: data = B110000; break;
  case 2: data = B1101101; break;
  case 3: data = B1111001; break;
  case 4: data = B110011; break;
  case 5: data = B1011011; break;
  case 6: data = B11111; break;
  case 7: data = B1110000; break;
  case 8: data = B1111111; break;
  case 9: data = B1110011; break;
  default: data = 0;
  }
  set_register(digit, data);
}

void Max7219::bar(int digit, int value){ set_register(digit, value); }

#endif
