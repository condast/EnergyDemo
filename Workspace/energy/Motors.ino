Motors::Motors() {}

void Motors::setup() {
  pinMode(A14, OUTPUT);
  for ( int i = 0; i < 3; i++) {
    pinMode(OS0 + i, OUTPUT);
    digitalWrite(OS0 + i, LOW);
  }
  counter = 0;
  test = 0;
  reset();
}

void Motors::reset() {
  enable = false;
  vMill = 0;
  vWalrus = 0;
  vWaterMill = 0;
  motor(0,LOW);
}

void Motors::motor(byte number, byte signal) {
  digitalWrite(A14, signal);
  digitalWrite(OS2, HIGH);
  digitalWrite(OS3, HIGH);
  switch ( number ) {
    case 1:
      digitalWrite(OS0, HIGH);
      digitalWrite(OS1, LOW);
      break;
    case 2:
      digitalWrite(OS0, LOW);
      digitalWrite(OS1, HIGH);
      break;
    case 3:
      digitalWrite(OS0, HIGH);
      digitalWrite(OS1, HIGH);
      break;
    default:
      digitalWrite(A14, LOW);
      digitalWrite(OS0, LOW);
      digitalWrite(OS1, LOW);
      digitalWrite(OS2, LOW);
      digitalWrite(OS3, LOW);
      break;
  }
}

void Motors::calcSpeed( uint16_t results[3], uint16_t total ) {
  uint16_t duration = vWalrus + vWaterMill + vMill;
  float max = (duration > 255) ? duration : 255;
  results[0] = (vWalrus * total) / max;
  results[1] = (vWaterMill * total) / max;
  results[2] = (vMill * total) / max;
}

void Motors::handleInterrupt( uint16_t total ) {
  if (!enable)
    return;
  uint16_t results[3];
  calcSpeed( results, total );
  if ( counter < results[0]) {
    if ( results[0] > 0 ) {
      motor(WALRUS, HIGH);
    }
  } else if ( counter < results[0] + results[1] ) {
    if ( results[1] > 0 ) {
      motor(WATERMILL, HIGH);
    }
  } else if ( counter < results[0] + results[1] + results[2]) {
    if ( results[2] > 0 ) {
      motor(WINDMILL, HIGH);
    }
  }
  if ( counter >= total ) {
    motor(WALRUS, LOW);
    motor(WATERMILL, LOW);
    motor(WINDMILL, LOW);
    counter = 0;
  } else {
    counter++;
  }
}

void Motors::loop() {
}
