int joyX = A0;
int joyY = A1;
int joyButton = 2;

int ledPin = 8;
int buzzerPin = 9;

void setup() {
  Serial.begin(9600);

  pinMode(joyButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int buttonState = digitalRead(joyButton);

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");
  Serial.println(buttonState);

  if (xValue < 300) {
    digitalWrite(ledPin, HIGH);
  } 
  else if (xValue > 700) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  } 
  else {
    digitalWrite(ledPin, LOW);
  }

  if (yValue < 300) {
    tone(buzzerPin, 500);
  } 
  else if (yValue > 700) {
    tone(buzzerPin, 1200);
  } 
  else {
    noTone(buzzerPin);
  }

  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 2000);
    delay(200);
    noTone(buzzerPin);
  }
}
