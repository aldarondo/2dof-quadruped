void modeManual()
{
  static int pos = 0;
  if (Serial.available()) {
    char ch = Serial.read();
    
    if (isDigit(ch)) {
      pos = pos * 10 + ch - '0';
    } else if (ch == ' ') {
      delay(DELAY_STEP);
    } else if (ch >= 'a' && ch <= 'a' + SERVOS) {
      servoObjects[ch - 'a'].write(pos);
      pos = 0;
    }
  }
}
