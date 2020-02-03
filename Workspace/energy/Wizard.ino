Wizard::Wizard() {}

void Wizard::setup() {
  Serial.println(F("SETUP WIZARD"));
  step = MENU;
  view.setup();
  Serial.println(F("MODEL SETUP COMPLETE"));
  introView.setup();
  Serial.println(F("WIZARD SETUP COMPLETE"));
}

void Wizard::home() {
  step = MENU;
}

byte Wizard::next() {
  switch ( step ) {
    case Steps::OUTCOME:
      break;
    default:
      step += 1;
      break;
  }
}

void Wizard::update() {
  // See if there's any  touch data for us
  switch ( step ) {
    case Wizard::Steps::MENU:
      //Serial.println( step );
      break;
    case Steps::EXPLANATION:
      //Serial.println(F("Explanation"));
      break;
    case Steps::MODEL:
      //Serial.println(F("Model"));
      modelView.loop();
      break;
    case Steps::FACTS:
      break;
    case Steps::OUTCOME:
      break;
    default:
      break;
  }
}

void Wizard::loop() {
  // See if there's any  touch data for us
  byte event = view.getEvent();
  if ( event == View::Event::NONE )
    return;
  //Serial.print(F("TOUCHED: ")); Serial.print( event );Serial.print(F(" RESULT: ")); Serial.println( result );
  if ( event == result )
    return;
  //Serial.print(F("TOUCHED AGAIN: ")); Serial.print( event ); Serial.print( F("="));
  //Serial.println( ( event != result ) && ( View::Event::NONE  != event ));

  //Serial.println( step );
  switch ( step ) {
    case Wizard::Steps::MENU:
      switch ( event ) {
        case View::Event::MENU_1:
          textView.setup( DARK_BLUE, S_MENU_1, TEXT_1);
          next();
          break;
        case View::Event::MENU_2:
          textView.setup( DARK_BLUE, S_MENU_2, TEXT_2);
          next();
          break;
        case View::Event::MENU_3:
          modelView.setup( ModelView::Options::SLIDER);
          step = Steps::MODEL;
          Serial.print(F("STEP: ")); Serial.println( step );
          break;
        default:
          break;
      }
      break;
    case Steps::EXPLANATION:
      switch ( event ) {
        case View::Event::HOME:
          introView.setup();
          wizard.home();
          break;
        case View::Event::NEXT:
          modelView.setup( ModelView::Options::CALENDAR);
          wizard.next();
          break;
        default:
          break;
      }
      break;
    case Steps::MODEL:
      Serial.print(F("MODEL: ")); Serial.println( event );
      switch ( event ) {
        case View::Event::HOME:
          introView.setup();
          home();
          break;
        case View::Event::NEXT:
          factsView.setup();
          factsView.loop( 7 );
          next();
          break;
        default:
          break;
      }
      break;
    case Steps::FACTS:
      Serial.print(F("FACTS: ")); Serial.println( event );
      factsView.loop();
      switch ( event ) {
        case View::Event::HOME:
          introView.setup();
          home();
          break;
        case View::Event::NEXT:
          //outcomeView.setup();
          next();
          break;
        default:
          break;
      }
      break;
    case Steps::OUTCOME:
      switch ( event ) {
        case View::Event::HOME:
          introView.setup();
          home();
          break;
        default:
          break;
      }
      break;
    default:
      introView.setup();
      break;
  }
  result = ( event !=View::Event::NEXT)?event: View::Event::NONE;
}
