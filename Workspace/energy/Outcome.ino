Outcome::Outcome() {}

void Outcome::setup() {
  tft.fillScreen( ILI9341_WHITE );
  view.toolbar( 0, ILI9341_WHITE, 2, true, S_OUTCOME );
  view.prepare( 1, 50, DIRKSEN_RED_1, 2, true );
  view.vprint( O_TEXT_2 );

  view.house( tft.width() - 40, tft.height() - 40,  ILI9341_WHITE, DIRKSEN_RED_1 );
}

void Outcome::setup( uint16_t entered ) {
  tft.fillScreen( ILI9341_WHITE );
  view.toolbar( 0, ILI9341_WHITE, 2, true, S_OUTCOME );

  view.simpleLabelText( 2, 40, ILI9341_WHITE, DIRKSEN_RED_1, 2, S_CALCULATED, view.vprintf(2, 2, entered ));
  view.simpleLabelText( 2, 60, ILI9341_WHITE, DIRKSEN_RED_1, 2, S_MEASURED, view.vprintf(2, 2, model.calculateEnergy() ));

  view.prepare( 1, 100, DIRKSEN_RED_1, 2, true );
  view.vprint( O_TEXT_1 );

  view.house( tft.width() - 40, tft.height() - 40,  ILI9341_WHITE, DIRKSEN_RED_1 );
}
