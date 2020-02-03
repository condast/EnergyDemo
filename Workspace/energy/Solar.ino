Solar::Solar() {}

void Solar::setup( int smpl) {
  pinMode(A15, INPUT);
  for ( int i = 0; i < 3; i++) {
    pinMode(SS0 + i, OUTPUT);
    digitalWrite(SS0 + i, LOW);
  }
  samples = smpl;
  counter = 0;
}

uint16_t Solar::read(byte number) {
  switch ( number ) {
    case 0:
      digitalWrite(SS0, LOW);
      digitalWrite(SS1, LOW);
      digitalWrite(SS2, LOW);
      digitalWrite(SS3, LOW);
      break;
    case 1:
      digitalWrite(SS0, HIGH);
      digitalWrite(SS1, LOW);
      digitalWrite(SS2, LOW);
      digitalWrite(SS3, LOW);
      break;
    case 2:
      digitalWrite(SS0, LOW);
      digitalWrite(SS1, HIGH);
      digitalWrite(SS2, LOW);
      digitalWrite(SS3, LOW);
      break;
    case 3:
      digitalWrite(SS0, HIGH);
      digitalWrite(SS1, HIGH);
      digitalWrite(SS2, LOW);
      digitalWrite(SS3, LOW);
      break;
    case 4:
      digitalWrite(SS0, LOW);
      digitalWrite(SS1, LOW);
      digitalWrite(SS2, HIGH);
      digitalWrite(SS3, LOW);
      break;
    case 5:
      digitalWrite(SS0, HIGH);
      digitalWrite(SS1, LOW);
      digitalWrite(SS2, HIGH);
      digitalWrite(SS3, LOW);
      break;
    case 6:
      digitalWrite(SS0, LOW);
      digitalWrite(SS1, HIGH);
      digitalWrite(SS2, HIGH);
      digitalWrite(SS3, LOW);
      break;
    case 7:
      digitalWrite(SS0, HIGH);
      digitalWrite(SS1, HIGH);
      digitalWrite(SS2, HIGH);
      digitalWrite(SS3, LOW);
      break;
    case 8:
      digitalWrite(SS0, LOW);
      digitalWrite(SS1, LOW);
      digitalWrite(SS2, LOW);
      digitalWrite(SS3, HIGH);
      break;
    case 15:
      digitalWrite(SS0, HIGH);
      digitalWrite(SS1, HIGH);
      digitalWrite(SS2, HIGH);
      digitalWrite(SS3, HIGH);
      break;
    default:
      digitalWrite(A15, LOW);
      digitalWrite(SS0, LOW);
      digitalWrite(SS1, LOW);
      digitalWrite(SS2, LOW);
      digitalWrite(SS3, LOW);
      break;
  }
  int result = 0;
  for ( int i = 0; i < samples; i++) {
    delay( READ_DELAY );
    result += analogRead(A15);
  }
  values[number]=result/samples; 
  return values[number];
}

uint16_t Solar::get(byte number) {
  return values[number];
}

void Solar::loop() {
  read( counter++ );
  counter%=NR_OF_PANELS;
}
