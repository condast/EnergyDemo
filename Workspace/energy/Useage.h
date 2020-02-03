#ifndef Useage_h
#define Useage_h

#define MAX_USE_AREA1 600 //kWH  
#define MAX_USE_AREA2 400 //kWH  
#define MAX_USE_AREA3 400 //kWH  
#define MAX_USE_THEME_PARK 50 //kWH  
#define MIN_USE_RECEPTION_DESK 10 //kWH  
#define MAX_USE_RECEPTION_DESK 30 //kWH  

class Useage {

  private:
    byte houses1;
    byte houses2;
    byte houses3;
    uint16_t calcArea1();
    uint16_t calcArea2();
    uint16_t calcArea3();
    uint16_t calcThemePark();
    uint16_t calcReception();

  public: Useage(void);
    uint16_t area1;
    uint16_t area2;
    uint16_t area3;
    uint16_t reception;
    uint16_t themePark;

    void setup( byte houses1, byte houses2, byte houses3 );
    void loop();
};
#endif
