#ifndef Weather_h
#define Weather_h

#define COLD_OFFSET 40 //bring the coldest day to february

class Weather {

  public: Weather(void);
    float temp;
    byte sun;
    byte rain;
    byte wind;
    void setup( );
    void loop();

  private: float calcTemperature();
    byte calcRain();
    byte calcWind();
};
#endif
