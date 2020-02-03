Calendar::Calendar() {}

void Calendar::setup( ) {
  day = 0; //01 January
}

byte Calendar::next( ) {
  day++;
  day %= YEAR;
  Serial.print( F("Day: ") ); Serial.println( day );
  return day;
}

byte Calendar::daysInMonth( Months month ) {
  byte days = 31;
  switch ( month ) {
    case FEBRUARY:
      days = 29;
      break;
    case APRIL:
    case JUNE:
    case SEPTEMBER:
    case NOVEMBER:
      days = 30;
      break;
    default:
      break;
  }
  return days;
}

byte Calendar::calmod( uint16_t stp ) {
  int cmp = 0;
  int prev = cmp;
  int index = JANUARY;
  uint16_t scaled = 1 + ( YEAR + stp ) % YEAR;
  byte daycount = 1;
  do {
    cmp += daysInMonth( index );
    daycount = scaled - prev;
    prev = cmp;
    index++;
  }
  while (( scaled > cmp ) && ( index <= DECEMBER ));
  return daycount;
}

Calendar::Months Calendar::calMonth( uint16_t stp ) {
  int cmp = 0;
  int prev = cmp;
  int index = JANUARY;
  uint16_t scaled = 1+( YEAR + stp ) % YEAR;
  do {
    cmp += daysInMonth( index );
    prev = cmp;
    index++;
  }
  while (( scaled > cmp ) && ( index <= DECEMBER ));
  return index - 1;//compensate for last index++
}

void Calendar::printDate( char data[] ) {
  printDate( data, day );
}

void Calendar::printDate( char data[], int stp ) {
  int cmp = daysInMonth( JANUARY );
  int daycount = calmod( stp );
  Calendar::Months month = calMonth( stp );
  Serial.print(F("Day: ")); Serial.print( daycount ); Serial.print(F(" Month: ")); Serial.print( month ); Serial.print(F(" Date: ")); Serial.println( data );
  switch ( month ) {
    case JANUARY:
      sprintf(data, CJAN, daycount);
      break;
    case FEBRUARY:
      sprintf(data, CFEB, daycount);
      break;
    case MARCH:
      sprintf(data, CMAR, daycount);
      break;
    case APRIL:
      sprintf(data, CAPR, daycount);
      break;
    case MAY:
      sprintf(data, CMAY, daycount);
      break;
    case JUNE:
      sprintf(data, CJUN, daycount);
      break;
    case JULY:
      sprintf(data, CJUL, daycount);
      break;
    case AUGUST:
      sprintf(data, CAUG, daycount);
      break;
    case SEPTEMBER:
      sprintf(data, CSEP, daycount);
      break;
    case OCTOBER:
      sprintf(data, COCT, daycount);
      break;
    case NOVEMBER:
      sprintf(data, CNOV, daycount);
      break;
    case DECEMBER:
      sprintf(data, CDEC, daycount);
      break;
    default:
      break;
  }
}

String Calendar::printWeek() {
  char data[6];
  printDate( data, day );
  String text = String(data);
  text += "-";
  printDate( data, ( day + 7 ) % YEAR );
  text += data;
  return text;
}

float Calendar::calcBookings() {
  float scaled = ( YEAR + day )% YEAR;
  float scale = 2 * PI * (scaled/YEAR );
    Serial.print(F("Day: ")); Serial.print( day ); Serial.print(F(", Scale: ")); Serial.println( scale );
  float bookings = 20 + MAX_PERCENT * ( 1 - cos( scale )); //<20,120>
  return (bookings < MAX_PERCENT) ? bookings : MAX_PERCENT;
}
void Calendar::loop() {
  bookings = calcBookings();
}
