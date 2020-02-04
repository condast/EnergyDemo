#ifndef Model_h
#define Model_h

#include "Useage.h"
#include "Solar.h"

//SCALE
#define MODEL_LENGTH  80 //cm
#define MODEL_WIDTH  80 //cm
#define MODEL_OFFSET 40
#define ROUNDING 5

//MODEL
#define HOUSES_AREA1  200
#define HOUSES_AREA2  80
#define HOUSES_AREA3  200

//ENERGY
#define MAX_ENERGY    500 //MWh
#define E_SOLAR_HOUSE 2     //kwH per house
#define E_RECEPTION   10    //kwh
#define E_THEME_PARK  15    //kwh
#define E_SOLAR_PARK  15    //kwh
#define E_WIND_PARK   15    //kwh
#define SCALE_FACTOR  1000  //scale the readings from the solar panels
//VIEW
#define TEXT_OFFSET 6;

static Solar solar;
static Useage useage;

class Model {

  public: Model();
    enum Areas {
      AREA1 = 1,
      AREA2 = 2,
      AREA3 = 3,
      THEME_PARK = 4,
      RECEPTION = 5,
      WIND_PARK = 6,
      SOLAR_PARK = 7
    };
    uint16_t gen_area1;
    uint16_t use_area1;
    uint16_t gen_area2;
    uint16_t use_area2;
    uint16_t gen_area3;
    uint16_t use_area3;
    uint16_t gen_theme;
    uint16_t use_theme;
    uint16_t gen_solar;
    uint16_t gen_wind;

    void setup();
    void fillRoundedRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color );
    uint16_t genArea( Areas area );
    uint16_t useArea( Areas area );
    int calculateEnergy( );
    void loop();

  private:
    uint16_t scale( uint16_t length );
    void drawRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color );
    void fillRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color );
    void drawRoundedRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color );

};
#endif
