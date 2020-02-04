Lights::Lights() {}

void Lights::setup() {
  enable = false;
  pinMode(A14, OUTPUT);
  for ( int i = 0; i < 3; i++) {
    pinMode(LS0 + i, OUTPUT);
    digitalWrite(LS0 + i, LOW);
  }
  mask = 0x01FF;
  Serial.println(F("WAIT"));
  interrupt.block();
  Serial.println(F("SETUP LIGHTS COMPLETE"));
}

void Lights::led(byte number, bool signal) {
  digitalWrite(A14, signal);
  delay(50);
  switch ( number ) {
    case 0:
      digitalWrite(LS0, LOW);
      digitalWrite(LS1, LOW);
      digitalWrite(LS2, LOW);
      digitalWrite(LS3, LOW);
      break;
    case 1:
      digitalWrite(LS0, HIGH);
      digitalWrite(LS1, LOW);
      digitalWrite(LS2, LOW);
      digitalWrite(LS3, LOW);
      break;
    case 2:
      digitalWrite(LS0, LOW);
      digitalWrite(LS1, HIGH);
      digitalWrite(LS2, LOW);
      digitalWrite(LS3, LOW);
      break;
    case 3:
      digitalWrite(LS0, HIGH);
      digitalWrite(LS1, HIGH);
      digitalWrite(LS2, LOW);
      digitalWrite(LS3, LOW);
      break;
    case 4:
      digitalWrite(LS0, LOW);
      digitalWrite(LS1, LOW);
      digitalWrite(LS2, HIGH);
      digitalWrite(LS3, LOW);
      break;
    case 5:
      digitalWrite(LS0, HIGH);
      digitalWrite(LS1, LOW);
      digitalWrite(LS2, HIGH);
      digitalWrite(LS3, LOW);
      break;
    case 6:
      digitalWrite(LS0, LOW);
      digitalWrite(LS1, HIGH);
      digitalWrite(LS2, HIGH);
      digitalWrite(LS3, LOW);
      break;
    case 7:
      digitalWrite(LS0, HIGH);
      digitalWrite(LS1, HIGH);
      digitalWrite(LS2, HIGH);
      digitalWrite(LS3, LOW);
      break;
    case 8:
      digitalWrite(LS0, LOW);
      digitalWrite(LS1, LOW);
      digitalWrite(LS2, LOW);
      digitalWrite(LS3, HIGH);
      break;
    case 9:
      digitalWrite(LS0, HIGH);
      digitalWrite(LS1, LOW);
      digitalWrite(LS2, LOW);
      digitalWrite(LS3, HIGH);
      break;
    case 15:
      digitalWrite(LS0, HIGH);
      digitalWrite(LS1, HIGH);
      digitalWrite(LS2, HIGH);
      digitalWrite(LS3, HIGH);
      break;
    default:
      digitalWrite(A14, LOW);
      digitalWrite(LS0, LOW);
      digitalWrite(LS1, LOW);
      digitalWrite(LS2, LOW);
      digitalWrite(LS3, LOW);
      break;
  }
}

void Lights::handleInterrupt() {
  if (!enable)
    return;
  uint16_t shift = 1;
  if ( mask == 0 ) {
    led(15, LOW);
  } else {
    for (int i = 0; i < 7; i++) {
      bool result = shift & mask;
      if ( result )
        led(i, result);
      shift <<= 1;
    }
  }
}
