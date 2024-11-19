const int hallpin1 = 27;
const int hallpin2 = 25;
const int hallpin3 = 33;
const int driverpin = 26;

unsigned long lastTriggerTime2 = 0;
unsigned long timeDifference23 = 0;

const float distance23 = 0.02; // Distance between hallpin2 and hallpin3 in meters

void setup() {
  Serial.begin(921600);

  pinMode(driverpin, OUTPUT);
  pinMode(hallpin1, INPUT);
  pinMode(hallpin2, INPUT);
  pinMode(hallpin3, INPUT);
}

void loop() {
  speed();
  fire();
}

void fire() {
  int sensorValue = digitalRead(hallpin1);

  if (sensorValue == LOW) {
    digitalWrite(driverpin, HIGH);  // Turn on the output when hallpin detects a magnet
  } else {
    digitalWrite(driverpin, LOW);   // Turn off the output when hallpin does not detect a magnet
  }
}

void speed() {
  int sensorValue2 = digitalRead(hallpin2);
  int sensorValue3 = digitalRead(hallpin3);

  unsigned long currentTime = micros();

  if (sensorValue2 == LOW && lastTriggerTime2 == 0 && sensorValue3 == HIGH) {
    lastTriggerTime2 = currentTime;
    Serial.println(sensorValue2);
  }

  if (sensorValue3 == LOW && lastTriggerTime2 != 0) {
    timeDifference23 = currentTime - lastTriggerTime2;

    if(timeDifference23 > 1000) {
      float speed23 = (distance23 / (timeDifference23 / 1000000.0)); //Speed in m/s
      Serial.print("Speed between hallpin1 and hallpin2: ");
      Serial.print(speed23);
      Serial.println(" m/s");
      Serial.print("Time difference (hallpin1 to hallpin2): ");
      Serial.print(timeDifference23 / 1000.0); Time in milliseconds
      Serial.println(" ms");

    }
    lastTriggerTime2 = 0;
    Serial.println(sensorValue3);

  }
}
