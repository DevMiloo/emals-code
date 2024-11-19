const int buttonpin = 27;
const int driverpin = 26;
int buttonState = 0;

void setup() {
  Serial.begin(256000);
  pinMode(buttonpin, INPUT);
  pinMode(driverpin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonpin);
  Serial.print(buttonState);
  Serial.println();

  if (buttonState == HIGH) {
    digitalWrite(driverpin, LOW);
  } else {
    digitalWrite(driverpin, HIGH);
  }
}
