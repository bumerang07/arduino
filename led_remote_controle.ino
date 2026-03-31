#include <IRremote.h>

int IR_PIN = 2;

int R = 9;
int G = 10;
int B = 6;

// wartości kolorów
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// stare wartości kolorów
int oldRedValue = 0;
int oldGreenValue = 0;
int oldBlueValue = 0;

// krok zmiany
int step = 15;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {


  if (IrReceiver.decode()) {

    int przycisk = IrReceiver.decodedIRData.command;

    if (przycisk == 0) {
      IrReceiver.resume();
      return;
    }

    Serial.print("Naciśnięto przycisk: ");
    Serial.println(przycisk);

    // 🔴 CZERWONY (CH- / CH+)
    if (przycisk == 69) { // CH-
      redValue -= step;
    }
    if (przycisk == 70) { // CH+
      redValue += step;
    }

    // 🟢 ZIELONY (PREV / NEXT)
    if (przycisk == 68) { // PREV
      greenValue -= step;
    }
    if (przycisk == 64) { // NEXT
      greenValue += step;
    }

    // 🔵 NIEBIESKI (VOL- / VOL+)
    if (przycisk == 7) { // VOL-
      blueValue -= step;
    }
    if (przycisk == 21) { // VOL+
      blueValue += step;
    }

    // ograniczenia 0–255
    redValue = constrain(redValue, 0, 255);
    greenValue = constrain(greenValue, 0, 255);
    blueValue = constrain(blueValue, 0, 255);
    
    Serial.print("R:");
    Serial.print(redValue);
    Serial.print(" G:");
    Serial.print(greenValue);
    Serial.print(" B:");
    Serial.println(blueValue);

    // ustaw kolor
    analogWrite(R, redValue);
    analogWrite(G, greenValue);
    analogWrite(B, blueValue);

    IrReceiver.resume();
  }
}
