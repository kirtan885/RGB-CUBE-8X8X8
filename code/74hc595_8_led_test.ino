// =============================================
// 74HC595 + PN2222A Transistor Test
// Arduino Uno - Single Block with 8 LEDs
//
// D10 = LATCH
// D11 = DATA
// D13 = CLOCK
// =============================================

const int LATCH = 10;
const int DATA  = 11;
const int CLK   = 13;

void setup() {
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLK, OUTPUT);

  sendByte(0b00000000);  // Start with all LEDs OFF
}

void sendByte(byte value) {
  digitalWrite(LATCH, LOW);

  shiftOut(DATA, CLK, MSBFIRST, value);

  digitalWrite(LATCH, HIGH);
  delayMicroseconds(10);
  digitalWrite(LATCH, LOW);
}

void loop() {

  // Test 1: Turn all LEDs ON
  sendByte(0b11111111);
  delay(1500);

  // Test 2: Turn all LEDs OFF
  sendByte(0b00000000);
  delay(800);

  // Test 3: Running-light test
  for (int i = 0; i < 8; i++) {
    sendByte(1 << i);
    delay(150);
  }

  sendByte(0);
  delay(400);

  // Test 4: Binary counter, 0 to 255
  for (int value = 0; value < 256; value++) {
    sendByte((byte)value);
    delay(80);
  }

  delay(500);

  // Test 5: Bouncing LED
  for (int i = 0; i < 7; i++) {
    sendByte(1 << i);
    delay(100);
  }

  for (int i = 7; i >= 0; i--) {
    sendByte(1 << i);
    delay(100);
  }

  sendByte(0);
  delay(400);
}
