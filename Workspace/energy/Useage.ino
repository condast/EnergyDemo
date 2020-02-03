Useage::Useage() {}

void Useage::setup( byte houses1, byte houses2, byte houses3) {
  area1 = 0;
  area2 = 0;
  area3 = 0;
  reception = 0;
  themePark = 0;
}

uint16_t Useage::calcArea1() {
  return MAX_USE_AREA1 * weather.temp / MAX_PERCENT;
}

uint16_t Useage::calcArea2() {
  return MAX_USE_AREA2 * weather.temp / MAX_PERCENT;
}

uint16_t Useage::calcArea3() {
  return MAX_USE_AREA3 * weather.temp / MAX_PERCENT;
}

uint16_t Useage::calcThemePark() {
  uint16_t result = MAX_THEME_PARK * weather.rain/ MAX_PERCENT;
  return result;
}

uint16_t Useage::calcReception() {
  return MIN_USE_RECEPTION_DESK + ( MAX_USE_RECEPTION_DESK - MIN_USE_RECEPTION_DESK ) * weather.temp / MAX_PERCENT;
}

void Useage::loop( ) {
  calcArea1();
  calcArea2();
  calcArea3();
  calcThemePark();
  calcReception();
}
