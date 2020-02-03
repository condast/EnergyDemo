Generator::Generator() {}

void Generator::setup( byte hs1, byte hs2, byte hs3) {
  houses1 = hs1;
  houses2 = hs2;
  houses3 = hs3;
  solar = 0;
  wind = 0;
  area1 = 0;
  area2 = 0;
  area3 = 0;
  reception = 0;
  themePark = 0;
}

uint16_t Generator::calcArea1() {
  return MAX_AREA1 * (1 - weather.rain) / MAX_PERCENT;
}

uint16_t Generator::calcArea2() {
  return MAX_AREA2 * (1 - weather.rain) / MAX_PERCENT;
}

uint16_t Generator::calcArea3() {
  return MAX_AREA3 * (1 - weather.rain) / MAX_PERCENT;
}

uint16_t Generator::calcThemePark() {
  return MAX_THEME_PARK * (1 - weather.rain) / MAX_PERCENT;
}

uint16_t Generator::calcReception() {
  return MAX_RECEPTION_DESK * (1 - weather.rain) / MAX_PERCENT;
}

uint16_t Generator::calcSolarPark() {
  return MAX_SOLAR_PARK * (1 - weather.rain) / MAX_PERCENT;
}

uint16_t Generator::calcWindPark() {
  return MAX_WIND_PARK * weather.wind / MAX_PERCENT;
}

void Generator::loop( ) {
  calcArea1();
  calcArea2();
  calcArea3();
  calcThemePark();
  calcReception();
  calcSolarPark();
  calcWindPark();
}
