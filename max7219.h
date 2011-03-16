#ifndef MAX7219_H
#define MAX7219_H

#include "WProgram.h"
class Max7219 {
  public:
    Max7219(int data, int latch, int clock);
    void boot();
    void send_bit(bool bit);
    void send_word(unsigned int byte);
    void set_register(byte address, byte data);
    void digit(int digit, int value);
    void bar(int digit, int value);
    void test(bool on);
    void intensity(byte brightness);
    void shutdown(bool enabled);
    void decode(bool decode);
    void scan_limit(byte count);
    void set_display( byte state );

  private:
    int _data, _latch, _clock;
    bool _clock_state;
};

#endif
