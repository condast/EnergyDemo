IntroView::IntroView() {}

void IntroView::setup() {
  tft.fillScreen( ILI9341_WHITE );
  view.toolbar( 0, ILI9341_WHITE, 2, S_INTRO_TITLE );
  view.menu( 5, 40, DIRKSEN_RED_1, DARK_GREEN, ROUNDING, 2, S_MENU_1);
  view.menu( 5, 75, DIRKSEN_RED_1, DARK_GREEN, ROUNDING, 2, S_MENU_2);
  view.menu( 5, 110, DIRKSEN_RED_1, DARK_GREEN, ROUNDING, 2, S_MENU_3);
}
