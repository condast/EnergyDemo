#ifndef Calendar_h
#define Calendar_h

#define YEAR 366 //leap year in 2020
#define OFFSET 40 //bring the coldest day to february

#define MAX_PERCENT 100
#define WIND_POWER 7 //Beaufort
#define STORM 11 //Beaufort

const char CJAN[]= "%d Jan";
const char CFEB[]= "%d Feb";
const char CMAR[]= "%d Mar";
const char CAPR[]= "%d Apr";
const char CMAY[]= "%d May";
const char CJUN[]= "%d Jun";
const char CJUL[]= "%d Jul";
const char CAUG[]= "%d Aug";
const char CSEP[]= "%d Sep";
const char COCT[]= "%d Oct";
const char CNOV[]= "%d Nov";
const char CDEC[]= "%d Dec";

class Calendar {

  public: Calendar(void);

    enum Months {
      JANUARY=1,
      FEBRUARY=2,
      MARCH=3,
      APRIL=4,
      MAY=5,
      JUNE=6,
      JULY=7,
      AUGUST=8,
      SEPTEMBER=9,
      OCTOBER=10,
      NOVEMBER=11,
      DECEMBER=12
    };

    byte day;
    float bookings;
    void setup();
    byte next();
    void printDate( char data[] );
    void printDate( char data[], int step );
    String printWeek();
    void loop();

  private: byte daysInMonth( Months month );
    String str = String(50);
    float calcBookings();

    //calculates the modulo of the day over the months, 
    //so day 32 would be February 1st
    byte calmod( uint16_t day );
    Months calMonth( uint16_t day );
};
#endif
