#include <LedControl.h>

// LedControl(DIN, CLK, CS, liczba modułów)
// DIN → 11, CLK → 13, CS → 10
LedControl lc = LedControl(11, 13, 10, 1);

byte smileOpen[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

byte smileClosed[8] = {
  B00111100,
  B01000010,
  B10000001,
  B10100101,
  B10000001,
  B10011001,
  B01000010,
  B00111100
};

void showImage(byte image[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, image[row]);
  }
}

void setup() {
  lc.shutdown(0, false);   // włącza moduł
  lc.setIntensity(0, 5);   // jasność 0-15
  lc.clearDisplay(0);
}

void loop() {
  showImage(smileOpen);
  delay(1000);

  showImage(smileClosed);
  delay(200);

  showImage(smileOpen);
  delay(1000);
}
