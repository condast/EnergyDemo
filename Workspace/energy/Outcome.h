#ifndef Outcome_h
#define Outcome_h

#define S_CALCULATED  F("Calculated: ")
#define S_MEASURED    F("Measured: ")
#define S_OUTCOME     F("Outcome: ")

#define O_TEXT_1 F("Prediction based on the\nbookings and the weather\nis very complicated.\nThis requires smart\nsolutions to get\nan optimal result.")
#define O_TEXT_2 F("The placement of a transformer\nis very important\n because longer cables\nwith higher currents\ngive more losses.")

class Outcome{

  public: Outcome(void);
    void setup();
    void setup( uint16_t entered );
};
#endif
