#ifndef Motors_h
#define Motors_h

//@See: https://www.arduino.cc/en/Hacking/PinMapping2560
#define OS0  30 //digital pin 30
#define OS1  31 //digital pin 31
#define OS2  32 //digital pin 32
#define OS3  33 //digital pin 33

#define WALRUS  0
#define WATERMILL  1
#define WINDMILL  2

class Motors {

  private:
    uint16_t counter;

  public: Motors(void);
    bool enable;
    byte vWalrus;
    byte vWaterMill;
    byte vMill;
    uint16_t test;
    void setup();
    void reset();
    void calcSpeed( uint16_t results[3], uint16_t total );
    void handleInterrupt( uint16_t total );
    void motor(byte number, byte signal);
    void loop();
};
#endif
