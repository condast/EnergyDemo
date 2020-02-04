ModelView::ModelView() {}

void ModelView::setup( Options opt) {
  setup( opt, true );
}

void ModelView::setup( Options opt, bool nxt) {
  option = opt;
  next = nxt;
  model.setup();
  x = DEFAULT_XPOS;
  y = DEFAULT_YPOS;
  xpress = 0; ypress = 0;

  view.toolbar( 0, ILI9341_WHITE, 2, S_MODEL_TITLE );

  uint16_t energy = model.genArea( Model::Areas::AREA1 );
  model.fillRoundedRect( x, y, 42, 37, ILI9341_GREEN);//area 1 (luxury)
  view.labelText( x + 5, y + 20, ILI9341_WHITE, DARK_GREEN, 2, S_GEN, view.vprinti(4, energy ));

  energy = model.useArea( Model::Areas::AREA1 );
  dtostrf(energy, 4, 0, outstr);
  view.labelText( x + 5, y + 55, ILI9341_WHITE, DARK_GREEN, 2, S_USED, outstr );

  energy = model.genArea( Model::Areas::AREA2 );
  model.fillRoundedRect(x + 1, y + 47, 42, 40, ILI9341_GREEN); //area 2 (left/down)
  view.labelText( x + 5, y + 110, ILI9341_WHITE, DARK_GREEN, 2, S_GEN, view.vprinti(4, energy ));

  energy = model.useArea( Model::Areas::AREA2 );
  dtostrf(energy, 4, 0, outstr);
  view.labelText( x + 5, y + 150, ILI9341_WHITE, DARK_GREEN, 2, S_USED, outstr );

  energy = model.genArea( Model::Areas::AREA3 );
  model.fillRoundedRect( x + 47, y, 35, 45, ILI9341_GREEN); //area3
  view.labelText( x + 100, y + 20, ILI9341_WHITE, DARK_GREEN, 2, S_GEN, view.vprinti(4, energy ));

  energy = model.useArea( Model::Areas::AREA3 );
  dtostrf(energy, 4, 0, outstr);
  view.labelText( x + 100, y + 60, ILI9341_WHITE, DARK_GREEN, 2, S_USED, outstr );

  energy = model.genArea( Model::Areas::THEME_PARK ) + model.genArea( Model::Areas::RECEPTION );
  dtostrf(energy, 4, 0, outstr);
  model.fillRoundedRect( x + 85, y, 37, 50, ILI9341_BLUE); //theme park
  view.labelText( x + 175, y + 20, ILI9341_WHITE, DARK_BLUE, 2, S_GEN, view.vprinti(4, energy ));

  energy = model.useArea( Model::Areas::THEME_PARK ) + model.useArea( Model::Areas::RECEPTION );
  dtostrf(energy, 4, 0, outstr);
  view.labelText( x + 175, y + 60, ILI9341_WHITE, DARK_BLUE, 2, S_USED, outstr );
  model.fillRoundedRect( x + 90, y + 58, 30, 20, ILI9341_BLUE); //reception desk

  model.fillRoundedRect( x + 125, y, 33, 30, ILI9341_GREEN); //wind park
  view.labelText(        x + 255, y + 20, ILI9341_WHITE, DARK_GREEN, 2, S_GEN, view.vprinti(4, energy ));

  model.fillRoundedRect( x + 125, y + 35, 33, 43, ILI9341_GREEN); //solar park
  view.labelText(        x + 255, y + 90, ILI9341_WHITE, DARK_GREEN, 2, S_GEN, view.vprinti(4, energy ));

  switch ( option ) {
    case Options::CALENDAR:
      calendar.printDate(data);
      view.simpleText( x, y + 200, ILI9341_WHITE, 2, outstr );
      view.simpleLabelText( x + 95, y + 200, ILI9341_BLACK, ILI9341_WHITE, 2, S_BOOKINGS, view.vprintf(2, 2, calendar.bookings ));
      break;
    case Options::SLIDER:
      view.slider( x + 95, y + 200, 100, 25, ILI9341_WHITE, DIRKSEN_RED_1, 2, 0, 200, 0 );
      break;
    default:
      break;
  }

  if ( next )
    view.next( tft.width() - 50, tft.height() - 50, DIRKSEN_RED_1);
}

void ModelView::loop() {
  model.loop();

  //Area 1
  uint16_t energy = model.genArea( Model::Areas::AREA1 );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 5, y + 20, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  energy = model.useArea( Model::Areas::AREA1 );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 5, y + 55, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  //Area 2
  energy = model.genArea( Model::Areas::AREA2 );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 5, y + 110, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  energy = model.useArea( Model::Areas::AREA2 );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 5, y + 150, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  //Area 3
  energy = model.genArea( Model::Areas::AREA3 );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 100, y + 20, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  energy = model.useArea( Model::Areas::AREA3 );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 100, y + 60, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  //Theme Park
  energy = model.genArea( Model::Areas::THEME_PARK ) + model.genArea( Model::Areas::RECEPTION );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 175, y + 20, ILI9341_WHITE, DARK_BLUE, 2, 4, outstr);

  energy = model.useArea( Model::Areas::THEME_PARK );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 175, y + 60, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  energy = model.genArea( Model::Areas::WIND_PARK );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 255, y + 20, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  energy = model.genArea( Model::Areas::SOLAR_PARK );
  dtostrf(energy, 4, 0, outstr);
  view.refreshLabelText( x + 255, y + 90, ILI9341_WHITE, DARK_GREEN, 2, 4, outstr);

  switch ( option ) {
    case Options::CALENDAR:
      calendar.printDate(data);
      view.refreshText( x + 10, y + 200, ILI9341_BLACK, ILI9341_WHITE, 2, 6, data);

      dtostrf(calendar.bookings, 2, 1, outstr);
      view.refreshSimpleLabelText( x + 95, y + 200, ILI9341_BLACK, ILI9341_WHITE, 2, S_BOOKINGS, 6, outstr );
      calendar.loop();
      calendar.next();
      break;
    case Options::SLIDER:
      view.refreshSlider( x + 95, y + 200, 100, 25, ILI9341_WHITE, DIRKSEN_RED_1, 2 );
      break;
    default:
      break;
  }
}

void ModelView::handleEvent( uint16_t xp, uint16_t yp) {
  xpress = xp;
  ypress = yp;
  if ( option != ModelView::Options::TRANSFORMER )
    return;

  Serial.print(F(" MODEL EVENT (")); Serial.print( xp ); Serial.print(F(", ")); Serial.print( yp ); Serial.println(F(")"));
  loop();
  tft.fillCircle( xp, y, 10, ILI9341_WHITE);

}
