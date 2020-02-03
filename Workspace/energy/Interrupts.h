#ifndef Interrupts_h
#define Interrupts_h

#define SECONDS 10 //0.1 sec
#define TEN_SEC 40
#define MINUTES 600
#define DEFAULT_INIT  50 //5 seconds initialisation
class Interrupts {

  private:
    //Create a sempahore
    bool lock;
 
  public: Interrupts(void);
    bool init;//is TRUE during 5 seconds after starting up
    bool flank; //10Hz
    bool sec_flank;//seconds
    bool min_flank;//minutes
    bool tensec_flank;//10 sec.
    void setup();
    void clear();
    void checkInitialisation();
    void block();//block while initialisation is active
    bool getLock();
    void setLock( bool lock );
    bool getFlank();
    bool getSecondsFlank();
    bool getMinutesFlank();
    bool getTenSecondsFlank();
    void reset();
    unsigned int getLoopCounter();
};
#endif
