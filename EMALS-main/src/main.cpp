#include <Arduino.h>
const int hallpin1 = 27;
const int hallpin2 = 25;
const int hallpin3 = 33;
const int hallpin4 = 32;
const int driverpin = 26;

unsigned long lastTriggerTime1 = 0;
unsigned long lastTriggerTime2 = 0;
unsigned long timeDifference12 = 0;
unsigned long timeDifference23 = 0;
unsigned long timeDifference34 = 0;

const float distance12 = 0.05; // Distance between hallpin1 and hallpin2 in meters
const float distance23 = 0.02;
const float distance34 = 0.05; // Distance between hallpin3 and hallpin4 in meters

const unsigned long fireduration = 1500;  // max on-time in milliseconds
const unsigned long fireCooldown = 5000; // Cooldown period for fire in milliseconds
unsigned long driverpinOnTime = 0; // Store the time when driverpin was turned on

void setup() {
  Serial.begin(921600);
  
  pinMode(driverpin, OUTPUT);
  pinMode(hallpin1, INPUT);
  pinMode(hallpin2, INPUT);
  pinMode(hallpin3, INPUT);
  pinMode(hallpin4, INPUT);
}

void fire(int sensorValue) {
  if (sensorValue == LOW) {
    Serial.println("Fire!");
    digitalWrite(driverpin, HIGH);
  } else {
    Serial.println("No hallsignal");
    digitalWrite(driverpin, LOW);
  }
}

void loop() { 
  int sensorValue = digitalRead(hallpin1);

  if (sensorValue == LOW) {
    if(driverpinOnTime == 0) {
      Serial.println('5');
      driverpinOnTime = millis(); // Record the time when driverpin is turned on
    }
  }

  if(millis() - driverpinOnTime <= fireduration) {
    fire(sensorValue);
  } else if(millis() - driverpinOnTime < fireCooldown) {
    digitalWrite(driverpin, LOW);
    Serial.println("on cooldown");
  }
  else {
    digitalWrite(driverpin, LOW);
    Serial.println("awaiting input");
    driverpinOnTime = 0;
  }
}