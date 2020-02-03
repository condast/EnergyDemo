#ifndef Solar_h
#define Solar_h

#define DEFAULT_SAMPLES 10
#define READ_DELAY 50
#define NR_OF_PANELS 16

//@See: https://www.arduino.cc/en/Hacking/PinMapping2560
#define SS0  34 //digital pin 34
#define SS1  35 //digital pin 35
#define SS2  36 //digital pin 36
#define SS3  37 //digital pin 37

class Solar {

  private:
    uint16_t values[NR_OF_PANELS];
    byte samples;
    byte counter;
    uint16_t read(byte number);

  public: Solar(void);
    void setup( int samples );
    uint16_t get(byte number);
    void loop();
};
#endif
