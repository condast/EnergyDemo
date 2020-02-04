Model::Model() {
}

void Model::setup() {
  solar.setup(DEFAULT_SAMPLES);
  useage.setup( HOUSES_AREA1, HOUSES_AREA2, HOUSES_AREA3 );
  tft.fillScreen(ILI9341_BLACK);
}

/**
 * The generated energy of the areas in MJoule (0-100)
 */
uint16_t Model::genArea( Areas area ) {
  long result = 0;
  switch ( area ) {
    case AREA1:
      result = E_SOLAR_HOUSE * HOUSES_AREA1 * ( solar.get(1) + solar.get(2));
      break;
    case AREA2:
      result = E_SOLAR_HOUSE * HOUSES_AREA2 *( solar.get(3) + solar.get(4)+ solar.get(5));
      break;
    case AREA3:
      result = E_SOLAR_HOUSE * HOUSES_AREA3 * (solar.get(6) + solar.get(7)+ solar.get(8)+ solar.get(9));
      break;
    case THEME_PARK:
      result = E_THEME_PARK * solar.get(10);
      break;
    case RECEPTION:
      result = E_RECEPTION * solar.get(11);
      break;
    case WIND_PARK:
      result = E_WIND_PARK * ( solar.get(12));
      break;
    case SOLAR_PARK:
      result = E_SOLAR_PARK * ( solar.get(13) + solar.get(14)+ solar.get(15));
      break;
    default:
      break;
  }
  return result/SCALE_FACTOR;
}

uint16_t Model::useArea( Areas area ) {
  long result = 0;
  long useage = calendar.bookings;
  switch ( area ) {
    case AREA1:
      result = E_SOLAR_HOUSE * HOUSES_AREA1 * useage;
      break;
    case AREA2:
      result = E_SOLAR_HOUSE * HOUSES_AREA2 *useage;
      break;
    case AREA3:
      result = E_SOLAR_HOUSE * HOUSES_AREA3 * useage;
      break;
    case THEME_PARK:
      result = E_THEME_PARK * useage;
      break;
    case RECEPTION:
      result = E_RECEPTION * useage;
      break;
    case WIND_PARK:
      result = 0;
      break;
    case SOLAR_PARK:
      result = 0;
      break;
    default:
      break;
  }
  return result/SCALE_FACTOR;
}

int Model::calculateEnergy(){
  int energy_sun = genArea( Areas::AREA1) + genArea( Areas::AREA2) + genArea( Areas::AREA3) + genArea( Areas::THEME_PARK) + genArea( Areas::RECEPTION) + genArea( Areas::SOLAR_PARK);
  uint16_t bookings = calendar.bookings;
  uint16_t en_day = weather.sun * energy_sun * 0.4;//daytime
  uint16_t wind = ( weather.wind < 6 )?weather.wind * 100/6:( weather.wind < 8 )?100:0;
  uint16_t en_night = genArea( Areas::WIND_PARK)*wind/100 - (useArea( Areas::AREA1) + useArea( Areas::AREA2) + useArea( Areas::AREA3))*0.25;//quarter use in the evening
  uint16_t en_theme = (( weather.temp < 20 )? weather.rain: 5)*useArea( Areas::THEME_PARK )/100;
  return en_day + en_night - en_theme;
}

uint16_t Model::scale( uint16_t length ) {
  return ( tft.height() * length ) / (MODEL_LENGTH + MODEL_OFFSET);
}

void Model::drawRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color ) {
  tft.drawRect( scale( x ), scale( y ), scale( length ), scale( width ), color);
}

void Model::fillRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color ) {
  tft.fillRect( scale( x ), scale( y ), scale( length ), scale( width ), color);
}

void Model::drawRoundedRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color ) {
  tft.drawRoundRect( scale( x ), scale( y ), scale( length ), scale( width ), ROUNDING, color);
}

void Model::fillRoundedRect( uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color ) {
  tft.fillRoundRect( scale( x ), scale( y ), scale( length ), scale( width ), ROUNDING, color);
}

void Model::loop() {
  solar.loop();
  motors.enable = true;
  motors.vMill = 30;
  motors.vWalrus = 0;
  motors.vWaterMill = 30;

  Serial.print(F("Solar "));
  for ( int i = 0; i < NR_OF_PANELS; i++) {
    Serial.print(F("(")); Serial.print( i ); Serial.print(F(", ")); Serial.print( solar.get( i )); Serial.print(F(")"));
  }
  Serial.println();
}
