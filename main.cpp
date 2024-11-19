#include <Arduino.h>
const int hallpin1 = 32; //1
const int hallpin2 = 33; //2
const int hallpin3 = 25; //3
const int hallpin4 = 27; //4
const int hallpin5 = 35; //5
const int driverpin1 = 26;
const int driverpin2 = 4; //!!!

const int buttonpin = 14;

unsigned long lastTriggerTime1 = 0;
unsigned long lastTriggerTime2 = 0;
unsigned long timeDifference23 = 0;
unsigned long timeDifference45 = 0;

const float distance23 = 0.02;
const float distance34 = 0.02; // Distance between hallpin3 and hallpin4 in meters

const unsigned long fireduration = 2000;  // max on-time in milliseconds
const unsigned long fireCooldown = 10000; // Cooldown period for fire in milliseconds
unsigned long driverpinOnTime = 0; // Store the time when driverpin1 was turned on

void setup() {
  Serial.begin(921600);
  
  pinMode(driverpin1, OUTPUT);
  pinMode(driverpin2, OUTPUT);
  pinMode(hallpin1, INPUT);
  pinMode(hallpin2, INPUT);
  pinMode(hallpin3, INPUT);
  pinMode(hallpin4, INPUT);
  pinMode(hallpin5, INPUT);
  pinMode(buttonpin, INPUT);
}

void fire(int sensorValue1, int sensorValue3) {
  if (sensorValue1 == LOW) {
    // Fire coil 1!!!
    digitalWrite(driverpin1, HIGH);
    digitalWrite(driverpin2, LOW);
  } 
  else if(sensorValue3 == LOW) {
    // Fire coil 2!!!
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, HIGH);
  }
  else {
    // no hall signal
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
  }
}

void speed(int microtime, int sensorValue2, int sensorValue3, int sensorValue4, int sensorValue5) {
  if (sensorValue2 == LOW && lastTriggerTime2 == 0 && sensorValue3 == HIGH) {
    lastTriggerTime2 = microtime;
  }

  if (sensorValue3 == LOW && lastTriggerTime2 != 0) {
    timeDifference23 = microtime - lastTriggerTime2;

    if(timeDifference23 > 1) {
      float speed23 = (distance23 / (timeDifference23 / 1000000.00)); // Speed in m/s
      Serial.println("---------------------------------");
      Serial.print("Speed between hallpin1 and hallpin2: ");
      Serial.print(speed23);
      Serial.println(" m/s");
    }
    lastTriggerTime2 = 0; // Reset the trigger time for the next cycle
  }

  if(sensorValue4 == LOW && lastTriggerTime1 == 0 && sensorValue5 == HIGH) {
    lastTriggerTime1 = microtime;
  }

  if (sensorValue5 == LOW && lastTriggerTime1 != 0) {
    timeDifference45 = microtime - lastTriggerTime1;

    if(timeDifference45 > 1) {
      float speed34 = (distance34 / (timeDifference45 / 1000000.00)); // Speed in m/s
      Serial.print("Speed between hallpin4 and hallpin5: ");
      Serial.print(speed34);
      Serial.println(" m/s");
    }
    lastTriggerTime1 = 0; // Reset the trigger time for the next cycle
  }

}

void loop() { 
  unsigned long millitime = millis();
  unsigned long microtime = micros();

  int sensorValue1 = digitalRead(hallpin1);
  int sensorValue2 = digitalRead(hallpin2);
  int sensorValue3 = digitalRead(hallpin3);  
  int sensorValue4 = digitalRead(hallpin4);
  int sensorValue5 = digitalRead(hallpin5);
  int buttonValue = digitalRead(buttonpin);

  if (sensorValue1 == LOW) {
    if(driverpinOnTime == 0) {
      driverpinOnTime = millis(); // Record the time when driverpin1 is turned on
    }
  } else {
    speed(microtime, sensorValue2, sensorValue3, sensorValue4, sensorValue5);
  }

  if(millitime - driverpinOnTime <= fireduration) {
    fire(sensorValue1, sensorValue3);
  } else if(millitime - driverpinOnTime < fireCooldown) {
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    // On cooldown
  }
  else {
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    // Awaiting input
    driverpinOnTime = 0;
  }
  
  if(buttonValue == HIGH) {
    Serial.print(millitime);
    Serial.print(",");
    Serial.print(sensorValue1);
    Serial.print(",");
    Serial.print(sensorValue2);
    Serial.print(",");
    Serial.print(sensorValue3);
    Serial.print(",");
    Serial.print(sensorValue4);
    Serial.print(",");
    Serial.println(sensorValue5);
  }
}