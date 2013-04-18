#ifndef DS1307_H
#define DS1307_H

#include "WProgram.h"

class ds1307 {

  public:
    ds1307();
    void set(
      byte sec, byte min, byte hour,
      byte dow, byte dom,
      byte mon, byte year
    );
    int get_time(byte *sec, byte *min, byte *hour, byte *dow, byte *dom, byte *mon, byte *year);

  private:
    byte _second, _minute, _hour, _week_day, _month_day, _month, _year;
    short _address;
    static byte decode(byte bcd) { return (bcd / 16 * 10) + (bcd % 16); }
    static byte encode(byte dec) { return (dec / 10 * 16) + (dec % 10); }
//    static byte decode(byte bcd) { return bcd; }

};

#endif
