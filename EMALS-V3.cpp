#include <Arduino.h>
const int hallpin1 = 27;
const int hallpin2 = 25;
const int hallpin3 = 33;
const int driverpin = 26;
const int buttonpin = 14;

unsigned long lastTriggerTime2 = 0;
unsigned long timeDifference23 = 0;

const float distance23 = 0.02; // Distance between hallpin2 and hallpin3 in meters

const unsigned long fireduration = 1000;  // max on-time in milliseconds
const unsigned long fireCooldown = 10000; // Cooldown period in milliseconds
unsigned long driverpinOnTime = 0;

void setup() {
  Serial.begin(921600);
  
  pinMode(driverpin, OUTPUT);
  pinMode(hallpin1, INPUT);
  pinMode(hallpin2, INPUT);
  pinMode(hallpin3, INPUT);
  pinMode(buttonpin, INPUT);
}

void fire(int sensorValue) {
  if (sensorValue == LOW) {
    // Fire!!!
    digitalWrite(driverpin, HIGH);
  } else {
    // No hall signal, no fire
    digitalWrite(driverpin, LOW);
  }
}

void speed(int microtime, int sensorValue2, int sensorValue3) {
  if (sensorValue2 == LOW && lastTriggerTime2 == 0 && sensorValue3 == HIGH) {
    lastTriggerTime2 = microtime;
  }

  if (sensorValue3 == LOW && lastTriggerTime2 != 0) {
    timeDifference23 = microtime - lastTriggerTime2;

    if(timeDifference23 > 1) {
      float speed23 = (distance23 / (timeDifference23 / 1000000.00)); // Speed in m/s
      Serial.print("Speed between hallpin1 and hallpin2: ");
      Serial.print(speed23);
      Serial.println(" m/s");
      Serial.print("Time difference (hallpin1 to hallpin2): ");
      Serial.print(timeDifference23 / 1000.00); // Time in milliseconds
      Serial.println(" ms");

    }
    lastTriggerTime2 = 0; // Reset the trigger time
  }
}

void loop() { 
  unsigned long millitime = millis();
  unsigned long microtime = micros();

  int sensorValue1 = digitalRead(hallpin1);
  int sensorValue2 = digitalRead(hallpin2);
  int sensorValue3 = digitalRead(hallpin3);  
  int buttonValue = digitalRead(buttonpin);

  if (sensorValue1 == LOW) {
    if(driverpinOnTime == 0) {
      driverpinOnTime = millis(); // Record the time when driverpin is turned on
    }
  } else {
    speed(microtime, sensorValue2, sensorValue3);
  }

  if(millitime- driverpinOnTime <= fireduration) {
    fire(sensorValue1);
  } else if(millitime - driverpinOnTime < fireCooldown) {
    digitalWrite(driverpin, LOW);
    // On cooldown
  }
  else {
    digitalWrite(driverpin, LOW);
    // Await input
    driverpinOnTime = 0;
  }
  
  // Log hall sensor values for troubleshooting
  if(buttonValue == HIGH) {
    Serial.print(millitime);
    Serial.print(",");
    Serial.print(sensorValue1);
    Serial.print(",");
    Serial.print(sensorValue2);
    Serial.print(",");
    Serial.println(sensorValue3);
  }

}