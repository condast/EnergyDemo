View::View() {}

void View::setup() {
  Serial.println(F("ILI9341 Test!"));
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print(F("Display Power Mode: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print(F("MADCTL Mode: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print(F("Pixel Format: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print(F("Image Format: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print(F("Self Diagnostic: 0x")); Serial.println(x, HEX);

  Serial.println(F("Benchmark Time (microseconds)"));
  delay(10);
  tft.setRotation(45);
  //tft.setFont(&FreeSerif9pt7b);
  tft.fillScreen(ILI9341_BLACK);

  if (!ts.begin(40)) {
    Serial.println("Unable to start touchscreen.");
  }
  else {
    Serial.println("Touchscreen started.");
  }
  sliderValue = 0;
}

String View::vprinti( uint16_t size, int num ) {
  char data[size + 2];
  char format[4];
  String str = F("%"); str += size; str += F("d");
  str.toCharArray( format, size);
  //Serial.print( str ); Serial.print( F(": ")); Serial.println( size );
  sprintf(data, format, num);
  return String( data );
}

String View::vprintf( int pref, int suff, float value ) {
  char outstr[4];
  dtostrf(value, pref, suff, outstr);
  return String( outstr);
}

void View::drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size) {
  tft.drawChar( x, y, c, color, bg, size);
}

void View::prepare(uint16_t x, uint16_t y, uint16_t colour, uint8_t size, bool wrap) {
  tft.setCursor( x , y );
  tft.setTextColor( colour );
  tft.setTextSize( size );
  tft.setTextWrap( wrap );
}

void View::prepare(uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size, bool wrap) {
  prepare(x, y, colour, size, wrap );
  tft.setTextColor( colour, background );
}

void View::vprint( String str ) {
  tft.print( str );
}

void View::vprintln( String str ) {
  tft.println( str );
}

void View::toolbar( uint16_t y, uint16_t colour, uint8_t size, String str ) {
  toolbar( y, colour, size, false, str );
}

void View::toolbar( uint16_t y, uint16_t colour, uint8_t size, bool skipDirksen, String str ) {
  tft.fillRect( 0, y, 30, 30, DIRKSEN_RED_1);
  tft.drawBitmap(3, y + 3, home, 20, 20, ILI9341_WHITE);
  tft.fillRect( 30, y,  tft.width(), 15, DIRKSEN_RED_2);
  tft.fillRect( 30, y + 15, tft.width(), 15, DIRKSEN_RED_3);
  prepare( 35, y + 6, colour, size, false );
  vprint( str );
  if ( !skipDirksen )
    tft.drawBitmap(tft.width() - 22, y + 3, dirksen, 20, 24, ILI9341_WHITE);
}

void View::house( uint16_t x, uint16_t y, uint16_t background, uint16_t colour ) {
  tft.fillRect( x, y, 30, 30, background);
  tft.drawBitmap( x + 3, y + 3, home, 20, 20, colour);
}

void View::next( uint16_t x, uint16_t y, uint16_t colour ) {
  tft.drawBitmap(x, y, next_img, 46, 46, colour);
}

void View::simpleText( uint16_t x, uint16_t y, uint16_t colour, uint8_t size, char str[] ) {
  prepare(x, y, colour, size, true );
  tft.println( str );
}

void View::simpleText( uint16_t x, uint16_t y, uint16_t colour, uint8_t size, int pref, int suff, float value ) {
  prepare(x, y, colour, size, true );
  char outstr[3];
  dtostrf(value, pref, suff, outstr);
  tft.println( outstr );
}

void View::text( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size, String str ) {
  uint16_t length = size * str.length() * TEXT_OFFSET;
  uint16_t width = size * TEXT_OFFSET;
  tft.fillRoundRect( x, y, length + 2, width + 6, ROUNDING, background);
  tft.drawRoundRect( x, y, length + 2, width + 6, ROUNDING, ILI9341_BLACK);
  prepare(x + 2, y + 2, colour, size, false);
  tft.println( str );
}

void View::text( uint16_t x, uint16_t y, uint16_t colour, uint8_t size, String str ) {
  uint16_t length = size * str.length() * TEXT_OFFSET;
  uint16_t width = size * TEXT_OFFSET;
  tft.drawRoundRect( x, y, length + 2, width + 6, ROUNDING, ILI9341_BLACK);
  prepare(x + 2, y + 2, colour, size, true );
  tft.println( str );
}

void View::clearText( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size, byte str_size ) {
  uint16_t length = size * str_size * TEXT_OFFSET + 2;
  uint16_t width = size * TEXT_OFFSET;
  tft.fillRect( x + 1, y + 1, length, width + 4, background);
}

void View::refreshText( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size, uint8_t str_size, char str[] ) {
  clearText(x, y, background, colour, size, str_size);
  text( x, y, colour, size, str);
}

void View::labelText( uint16_t x, uint16_t y, uint16_t colour, uint16_t labelColour, uint8_t size, String label, String str ) {
  uint16_t width = size * TEXT_OFFSET;
  prepare( x, y, labelColour, size, true );
  vprint( label );
  text( x + 10, y + width + 4, colour, ILI9341_BLACK, 2, str );
}

void View::labelText( uint16_t x, uint16_t y, uint16_t colour, uint16_t labelColour, uint8_t size, String label, String str, String unit ) {
  labelText( x, y, colour, labelColour, size, label, str );
  uint16_t length = ( str.length() + 7 ) * TEXT_OFFSET;
  uint16_t width = size * TEXT_OFFSET;
  prepare( x + length + 2, y + width + 6, labelColour, size, true );
  vprint( unit );
}

void View::refreshLabelText( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size, uint8_t str_size, char str[] ) {
  uint16_t width = size * TEXT_OFFSET;
  refreshText( x + 10, y + width + 4, background, colour, size, str_size, str);
}

void View::simpleLabelText( uint16_t x, uint16_t y, uint16_t colour, uint16_t labelColour, uint8_t size, String label, String str ) {
  uint16_t width = label.length() * size * TEXT_OFFSET;
  prepare( x, y, labelColour, size, true );
  vprint( label );
  text( x + width + 10, y, colour, labelColour, 2, str );
}

void View::refreshSimpleLabelText( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size, String label, uint8_t str_size, char str[] ) {
  uint16_t width = label.length() * size * TEXT_OFFSET;
  refreshText( x + width + 10, y, background, colour, size, str_size, str);
}

void View::menu( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint16_t rounding, uint8_t size, String label ) {
  tft.fillRoundRect( x, y, BUTTON_SIZE, BUTTON_SIZE, rounding, background);
  prepare( x + 60, y + 15, colour, size, false );
  vprint( label );
}

void View::menuSelect( uint16_t x, uint16_t y, uint16_t background, uint16_t rounding ) {
  tft.fillRoundRect( x, y, BUTTON_SIZE, BUTTON_SIZE, rounding, background);
}

void View::simpleSlider( uint16_t x, uint16_t y, uint8_t length, uint8_t width, uint16_t background, uint16_t colour, uint8_t size, uint16_t value  ) {
  tft.drawRoundRect( x, y, length, width, ROUNDING, colour);
  tft.fillRoundRect( x+2, y + 1, value + ROUNDING, width, ROUNDING, colour);
  tft.fillRoundRect( x + value, y + 1, (length - value-2), width - 2, ROUNDING, background);
  prepare( x + length + 15, y, colour, size, true );
  tft.print( value );
}

int View::refreshSimpleSlider( uint16_t x, uint16_t y, uint8_t length, uint8_t width, uint16_t background, uint16_t colour, uint8_t size, uint16_t max  ) {
  int value = readSlider( x, y, length, width );
  int result = -1;
  if ( value >= 0 ) {
 
    tft.fillRoundRect( x+2, y + 1, value + ROUNDING, width, ROUNDING, colour);
    tft.fillRoundRect( x + value, y + 1, (length - value), width - 2, ROUNDING, background);
    clearText(x + length + 15, y, background, colour, size, 4);
    prepare( x + length + 15, y, colour, size, true );
    result = ( value * max)/length;
    tft.print(result );
    Serial.print(F("SLIDER: ")); Serial.print( value ); Serial.print(F(" Length: ")); Serial.print( length ); Serial.print(F(" max: ")); Serial.print( max ); Serial.print(F(" Result: ")); Serial.println( result );
  }
  return result;
}

void View::slider( uint16_t x, uint16_t y, uint8_t length, uint8_t width, uint16_t background, uint16_t colour, uint8_t size, uint16_t min, uint16_t max, uint16_t value  ) {
  prepare( x, y, background, size, true );
  vprint( vprinti( 2, min ));

  uint16_t slidepos = x + 4 * size * TEXT_OFFSET;
  prepare( slidepos + length + 2, y, background, size, true );
  vprint( F("200"));//vprinti( 3, max ));
  Serial.println( vprinti( 3, max ));
  tft.drawRoundRect( slidepos, y, length, width, ROUNDING, background);
  refreshSlider( x, y, length, width, background, colour, size );
}

void View::refreshSlider( uint16_t x, uint16_t y, uint8_t length, uint8_t width, uint16_t background, uint16_t colour, uint8_t size  ) {
  uint16_t slidepos = x + 1 + 4 * size * TEXT_OFFSET;
  int value = readSlider( x, y, length, width );
  if ( value >= 0 ) {
    tft.fillRoundRect( slidepos, y + 1, value + ROUNDING, width, ROUNDING, colour);
    tft.fillRoundRect( slidepos + value, y + 1, (length - value), width - 2, ROUNDING, background);
  }
}
/**
   Returns the difference between the touched x position and the beginning of the slider (between 0, length),
   or -1 if the slider was not touched
*/
int View::readSlider( uint16_t x, uint16_t y, uint8_t length, uint8_t width ) {
  int result = xTouched;
  if ( result < 0 )
    return result;
  int xpos = result;
  if (( xpos < x ) || ( xpos > x + length ))
    return -1;
  result = yTouched;
  if ( result < 0 )
    return result;
  result = (( result < y ) || ( result > y + width ));
  if ( result < 0 )
    return result;
  //Serial.print( F("READ SLIDER: ")); Serial.println( result );
  xTouched = -1;
  yTouched = -1;
  return xpos - x;
}

void View::table( uint16_t x, uint16_t y, uint16_t height, uint16_t rows, uint16_t columns, uint16_t background, uint16_t rounding ) {
  uint16_t rowHeight = height / rows;
  for ( int i = 0; i < rows; i++) {
    tft.drawRoundRect( x, y + i * rowHeight, tft.width(), rowHeight, rounding, background);
  }
  uint16_t width = (tft.width() - 30 - 2 * x) / columns;
  uint16_t xpos = x + 30;
  tft.drawLine( xpos, y, xpos, y + height, background);
  for ( int i = 1; i < columns; i++) {
    xpos += width;
    tft.drawLine( xpos, y, xpos, y + height, background);
  }
}

void View::clearTable( uint16_t x, uint16_t y, uint16_t height, uint16_t rows, uint16_t columns, uint16_t background, bool skipFirstColumn ) {
  uint16_t rowHeight = height / rows;
  uint16_t width = (tft.width() - 30 - 2 * x) / columns;
  uint16_t xpos = 0;
  uint16_t ypos = y + 2;
  Serial.print("Width: "); Serial.println(width);
  for ( int i = 0; i < rows; i++) {
    xpos = skipFirstColumn ? x + 30 : x + 2;
    for ( int j = 0; j < columns; j++) {
      tft.fillRect( xpos, ypos, width - 6, rowHeight - 4, background);
      Serial.print("Clear ( "); Serial.print(xpos); Serial.print(","); Serial.print(ypos); Serial.println(")");
      xpos += width;
    }
    ypos += rowHeight;
  }
}

void View::sunWidget( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size ) {
  uint16_t radius = size / 2;
  tft.fillCircle( x + radius, y + radius, radius - 7, colour);
  uint16_t beams = 8;
  float phi = 2 * PI / beams;
  for ( int i = 0; i < beams; i++) {
    byte length = radius - 3;
    tft.drawLine( x + radius - 1, y + radius, x - 1 + radius + length * sin(i * phi), y + radius + length * cos(i * phi), colour);
    tft.drawLine( x + radius, y + radius, x + radius + (radius - 1)*sin(i * phi), y + radius + (radius - 1)*cos(i * phi), colour);
    tft.drawLine( x + radius + 1, y + radius, x + 1 + radius + length * sin(i * phi), y + radius + length * cos(i * phi), colour);
  }
}

void View::rainWidget( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size  ) {
  uint16_t offset = (size / 3) - 3;
  uint16_t xpos = x + 6;
  for ( int i = 0; i < 3; i++) {
    uint16_t ypos = y + 5;
    tft.drawLine( xpos,     ypos, xpos + 2, ypos + 3, colour);
    tft.drawLine( xpos + 1, ypos, xpos + 3, ypos + 3, colour);
    ypos += offset;
    if ( i < 2 ) {
      tft.drawLine( xpos + offset / 2,     ypos, xpos + offset / 2 + 2, ypos + 3, colour);
      tft.drawLine( xpos + offset / 2 + 1, ypos, xpos + offset / 2 + 3, ypos + 3, colour);
    }
    ypos += offset;
    tft.drawLine( xpos,     ypos, xpos + 2, ypos + 3, colour);
    tft.drawLine( xpos + 1, ypos, xpos + 3, ypos + 3, colour);
    xpos = xpos + offset;
  }
}

void View::windWidget( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size  ) {
  byte radius = size / 2;
  byte offset = radius - 10;
  tft.fillCircle( x + radius, y + radius, radius - 7, colour);
  tft.fillCircle( x + radius - offset - 2, y + radius, offset, colour);
  tft.fillCircle( x + radius + offset + 2, y + radius, offset, colour);
  tft.fillRect( x + radius - offset - 2, y + 2 * radius - 10, radius + 2, 4, colour );
}

void View::celsiusWidget( uint16_t x, uint16_t y, uint16_t background, uint16_t colour, uint8_t size, char chr  ) {
  tft.drawCircle( x + 7, y + 7, 2, colour);
  drawChar(x + 12, y + 8, chr, colour, background, size);
}

/**
   Get the event associated with the location
   NOTE: for touch screen, the (0,0) is top right
*/
byte View::getEvent() {
  byte result = NONE;
  if (!ts.touched())
    return result;
  TS_Point p = ts.getPoint();
  xTouched = tft.width() - p.y;
  yTouched = p.x;
  if ( p.y > tft.width() - TOUCH_OFFSET ) {
    if (p.x < TOUCH_OFFSET )
      result = HOME;
    else if (p.x < 2 * TOUCH_OFFSET )
      result = MENU_1;
    else if (p.x < 3 * TOUCH_OFFSET )
      result = MENU_2;
    else if (p.x < 4 * TOUCH_OFFSET )
      result = MENU_3;
  } else if (( p.y < TOUCH_OFFSET ) && (p.x > tft.height() - TOUCH_OFFSET )) {
    result = NEXT;
  }
  //Serial.print("("); Serial.print(p.x); Serial.print(","); Serial.print(p.y); Serial.print("):"); Serial.println( result);
  //Serial.println(  tft.width() );
  //Serial.print("("); Serial.print(xTouched); Serial.print(","); Serial.print(yTouched); Serial.println("):");
  return result;
}
