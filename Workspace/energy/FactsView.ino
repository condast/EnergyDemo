FactsView::FactsView() {}

void FactsView::setup() {
  tft.fillScreen( ILI9341_WHITE );
  view.toolbar( 0, ILI9341_WHITE, 2, true, S_COLUMNS );

  view.table( 0, 30, 150, 5, 7, DIRKSEN_RED_1, 10);
  view.sunWidget( 0, 31, DARK_GREEN, SUN_YELLOW, 30 );
  view.rainWidget( 0, 62, DARK_GREEN, ILI9341_BLACK, 30 );
  view.windWidget( 0, 90, DARK_GREEN, GRAY, 30 );
  view.celsiusWidget( 0, 150, ILI9341_WHITE, ILI9341_BLACK, 2, 'C' );
  view.house( 0, 120, ILI9341_WHITE, DIRKSEN_RED_1 );

  view.simpleSlider( 30, tft.height() - 40, 200, 30, ILI9341_WHITE, DIRKSEN_RED_1, 2, 0);
  view.next( tft.width() - 40, tft.height() - 40, DIRKSEN_RED_1);
}

void FactsView::loop( uint16_t days ) {
  uint16_t xpos = 35;
  view.clearTable( 0, 30, 150, 5, 7, ILI9341_WHITE, true);
  for ( int i = 0; i < 7; i++ ) {
    weather.loop();
    view.simpleText( xpos, 33,  DIRKSEN_RED_1, 2, 2, 0, weather.sun );
    view.simpleText( xpos, 65,  DIRKSEN_RED_1, 2, 2, 0, weather.rain );
    view.simpleText( xpos, 93,  DIRKSEN_RED_1, 2, 2, 0, weather.wind );
    view.simpleText( xpos, 123, DIRKSEN_RED_1, 2, 2, 0, calendar.bookings );
    view.simpleText( xpos, 153, DIRKSEN_RED_1, 2, 2, 0, weather.temp );
    xpos += 41;
    calendar.loop();
    calendar.next();
  }
  view.simpleSlider( 30, tft.height() - 40, 200, 30, ILI9341_WHITE, DIRKSEN_RED_1, 2, 0);
}

void FactsView::loop() {
  view.refreshSimpleSlider( 30, tft.height() - 40, 200, 30, ILI9341_WHITE, DIRKSEN_RED_1, 2 );
}
