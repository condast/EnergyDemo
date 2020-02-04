Wizard::Wizard() {}

void Wizard::setup() {
  step = MENU;
  option = ModelView::Options::BARE;
  view.setup();
  lights.enable = true;
  introView.setup();
}

void Wizard::home() {
  step = MENU;
  option = ModelView::Options::BARE;
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
  Serial.println(step);
  switch ( step ) {
    case Steps::MENU:
      //Serial.println( step );
      motors.reset();
      lights.enable;
      lights.mask = random(1,512);
      break;
    case Steps::EXPLANATION:
      //Serial.println(F("Explanation"));
      break;
    case Steps::MODEL:
      //Serial.println(F("Model"));
      modelView.loop();
      break;
    case Steps::FACTS:
      Serial.println("FACTS");
      factsView.loop();
      break;
    case Steps::OUTCOME:
      break;
    default:
      Serial.println("STOP");
      motors.reset();
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
  switch ((Steps)step ) {
    case Wizard::Steps::MENU:
      switch ( event ) {
        case View::Event::MENU_1:
          option = ModelView::Options::CALENDAR;
          textView.setup( DARK_BLUE, S_MENU_1, TEXT_1);
          next();
          break;
        case View::Event::MENU_2:
          option = ModelView::Options::TRANSFORMER;
          textView.setup( DARK_BLUE, S_MENU_2, TEXT_2);
          next();
          break;
        case View::Event::MENU_3:
          option = ModelView::Options::BARE;
          modelView.setup( option );
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
          modelView.setup( option );
          step = Steps::MODEL;
          break;
        default:
          break;
      }
      break;
    case Steps::MODEL:
      lights.enable = false;
      Serial.print(F("MODEL: ")); Serial.println( event );
      modelView.handleEvent( view.xTouched, view.yTouched );
      switch ( event ) {
        case View::Event::HOME:
          introView.setup();
          home();
          break;
        case View::Event::NEXT:
          if ( option == ModelView::Options::CALENDAR ) {
            factsView.setup();
            factsView.loop( 7 );
            step = Steps::FACTS;
          } else {
            outcome.setup();
            step = Steps::OUTCOME;
          }
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
          outcome.setup( factsView.result );
          step = Steps::OUTCOME;
          break;
        default:
          break;
      }
      break;
    case Steps::OUTCOME:
      switch ( event ) {
        case View::Event::HOME:
        case View::Event::NEXT:
          introView.setup();
          home();
          break;
        default:
          break;
      }
      break;
    default:
      Serial.print(F("EVENT: ")); Serial.println( event );
      break;
  }
  result = ( event != View::Event::NEXT) ? event : View::Event::NONE;
}
