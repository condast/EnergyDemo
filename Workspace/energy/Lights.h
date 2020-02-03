#ifndef Lights_h
#define Lights_h

//@See: https://www.arduino.cc/en/Hacking/PinMapping2560
#define LS0  30 //digital pin 30
#define LS1  31 //digital pin 31
#define LS2  32 //digital pin 32
#define LS3  33 //digital pin 33

class Lights {

  public: Lights(void);
    uint16_t mask;
    void setup();
    void led(byte number, bool signal);
    void handleInterrupt();
};
#endif
