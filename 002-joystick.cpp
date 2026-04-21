int xPin = A0;
int yPin = A1;
int swPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(swPin, INPUT_PULLUP);
}

void loop() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int buttonState = digitalRead(swPin);

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Przycisk: ");

  if (buttonState == LOW) {
    Serial.println("WCIŚNIĘTY");
  } else {
    Serial.println("puszczony");
  }

  delay(200);
}
