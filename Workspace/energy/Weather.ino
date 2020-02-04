Weather::Weather() {}

void Weather::setup() {
  temp = 0;//<-15, +35>
  rain = 0;//0-100%
  wind = 0;//0-11 Beaufort
}

float Weather::calcTemperature() {
  uint16_t rand = random( -5, 5);
  float scale = 2*PI*(( calendar.day + COLD_OFFSET) % YEAR )/YEAR;
  temp = 10 + 20 * ( 1 - cos( scale )); //<-10,30>
  //Serial.print( scale ); Serial.print( " " ); Serial.println( temp);
  return ( temp + rand );
}

byte Weather::calcRain() {
  byte rand = random( 20 );
  float scale = 2*PI*calendar.day/YEAR;
  rain = MAX_PERCENT * 0.4 * (1 + cos( scale )); //<0,80>
  sun = MAX_PERCENT - rain;
  Serial.print( scale ); Serial.print( " " ); Serial.println( rain );
  return ( rain + rand ) % MAX_PERCENT;
}

byte Weather::calcWind() {
  byte storm = random( 0, MAX_PERCENT);
  byte rand = random( 0, WIND_POWER);
  return ( storm < 95 ) ? rand : ( storm * STORM / MAX_PERCENT);
}

void Weather::loop() {
  calcTemperature();
  rain = calcRain();
  wind = calcWind();
  Serial.println();
}
