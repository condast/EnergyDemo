#ifndef Generator_h
#define Generator_h

#define MAX_AREA1 600 //kWH  
#define MAX_AREA2 400 //kWH  
#define MAX_AREA3 400 //kWH  
#define MAX_THEME_PARK 50 //kWH  
#define MAX_RECEPTION_DESK 30 //kWH  
#define MAX_WIND_PARK 800 //kWH 
#define MAX_SOLAR_PARK 700 //kWH 

class Generator {

  private:
    byte houses1;
    byte houses2;
    byte houses3;
    uint16_t calcArea1();
    uint16_t calcArea2();
    uint16_t calcArea3();
    uint16_t calcThemePark();
    uint16_t calcReception();
    uint16_t calcSolarPark();
    uint16_t calcWindPark();

  public: Generator(void);
    uint16_t solar;
    uint16_t wind;
    uint16_t area1;
    uint16_t area2;
    uint16_t area3;
    uint16_t reception;
    uint16_t themePark;

    void setup( byte houses1, byte houses2, byte houses3 );
    void loop();
};
#endif
