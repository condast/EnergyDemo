TextView::TextView() {}

void TextView::setup( uint16_t colour, String title, String text ) {
  tft.fillScreen( ILI9341_WHITE );
  view.toolbar( 0, ILI9341_WHITE, 2, title );
  
  view.prepare( 1, 40, colour, 2, true );
  view.vprint( text );

  view.text( 10, 190, DIRKSEN_RED_1, 2, calendar.printWeek());
  view.next( tft.width()-50, tft.height()-50, DIRKSEN_RED_1);
}
