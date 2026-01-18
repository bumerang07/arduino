#include <IRremote.h>
#include <Servo.h>

#define IR_PIN 2
#define SERVO_PIN 9

// Twoje kody
#define CH_MINUS 0xBA45FF00
#define CH_PLUS  0xB847FF00
#define PLAY     0xB946FF00

Servo s;

int posClosed = 0;   // ustaw pod mechanikę
int posOpen   = 180;  // ustaw pod mechanikę
bool isOpen = false;

void moveServoSmooth(int from, int to) {
  int step = (to > from) ? 1 : -1;
  for (int p = from; p != to; p += step) {
    s.write(p);
    delay(5);
  }
  s.write(to);
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  s.attach(SERVO_PIN);
  s.write(posClosed);
}

void loop() {

  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(code, HEX);

    int current = s.read();

    if (code == CH_PLUS) {
      moveServoSmooth(current, posOpen);
      isOpen = true;
    } else if (code == CH_MINUS) {
      moveServoSmooth(current, posClosed);
      isOpen = false;
    } else if (code == PLAY) {
      if (isOpen) moveServoSmooth(current, posClosed);
      else        moveServoSmooth(current, posOpen);
      isOpen = !isOpen;
    }

    IrReceiver.resume();
  }
}
