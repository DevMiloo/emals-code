#include <Arduino.h>
const int hallpin1 = 32; //1
const int hallpin2 = 33; //2
const int hallpin3 = 25; //3
const int hallpin4 = 27; //4
const int hallpin5 = 35; //5
const int driverpin1 = 26;
const int driverpin2 = 4; //!!!
const int driverpin3 = 17;
const int driverpin4 = 16;
const int driverpin5 = 13;

const int buttonpin = 14;

unsigned long lastTriggerTime1 = 0;
unsigned long lastTriggerTime2 = 0;
unsigned long lastTriggerTime3 = 0;
unsigned long lastTriggerTime4 = 0;
unsigned long lastTriggerTime5 = 0;
unsigned long timeDifference12 = 0;
unsigned long timeDifference23 = 0;
unsigned long timeDifference34 = 0;
unsigned long timeDifference45 = 0;

const float distance12 = 0.03; // Distance between hallpin1 and hallpin2 in meters
const float distance23 = 0.03;
const float distance34 = 0.03; // Distance between hallpin3 and hallpin4 in meters
const float distance45 = 0.03;

const unsigned long fireduration = 1000;  // max on-time in milliseconds
const unsigned long fireCooldown = 10000; // Cooldown period for fire in milliseconds
unsigned long driverpinOnTime = 0; // Store the time when driverpin1 was turned on

void setup() {
  Serial.begin(921600);
  
  pinMode(driverpin1, OUTPUT);
  pinMode(driverpin2, OUTPUT);
  pinMode(driverpin3, OUTPUT);
  pinMode(driverpin4, OUTPUT);
  pinMode(driverpin5, OUTPUT);
  pinMode(hallpin1, INPUT);
  pinMode(hallpin2, INPUT);
  pinMode(hallpin3, INPUT);
  pinMode(hallpin4, INPUT);
  pinMode(hallpin5, INPUT);
  pinMode(buttonpin, INPUT);
}

void fire(int sensorValue1, int sensorValue2, int sensorValue3, int sensorValue4, int sensorValue5) {
  if (sensorValue1 == LOW) {
    // Serial.println("Fire!");
    digitalWrite(driverpin1, HIGH);
    digitalWrite(driverpin2, LOW);
    digitalWrite(driverpin3, LOW);
    digitalWrite(driverpin4, LOW);
    digitalWrite(driverpin5, LOW);
  } 
  else if(sensorValue2 == LOW) {
    // Serial.println("Fire!");
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, HIGH);
    digitalWrite(driverpin3, LOW);
    digitalWrite(driverpin4, LOW);
    digitalWrite(driverpin5, LOW);
  }
  else if(sensorValue3 == LOW) {
    // Serial.println("Fire!");
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    digitalWrite(driverpin3, HIGH);
    digitalWrite(driverpin4, LOW);
    digitalWrite(driverpin5, LOW);
  }
  else if(sensorValue4 == LOW) {
    // Serial.println("Fire!");
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    digitalWrite(driverpin3, LOW);
    digitalWrite(driverpin4, HIGH);
    digitalWrite(driverpin5, LOW);
  }
  else if(sensorValue5 == LOW) {
    // Serial.println("Fire!");
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    digitalWrite(driverpin3, LOW);
    digitalWrite(driverpin4, LOW);
    digitalWrite(driverpin5, HIGH);
  }
  else {
    // Serial.println("No hallsignal");
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    digitalWrite(driverpin3, LOW);
    digitalWrite(driverpin4, LOW);
    digitalWrite(driverpin5, LOW);
  }
}

// void speed(int microtime, int sensorValue1, int sensorValue2, int sensorValue3, int sensorValue4, int sensorValue5) {
//   if (sensorValue2 == LOW && lastTriggerTime2 == 0 && sensorValue3 == HIGH) {
//     lastTriggerTime2 = microtime;
//   }

//   if (sensorValue3 == LOW && lastTriggerTime2 != 0) {
//     timeDifference23 = microtime - lastTriggerTime2;

//     if(timeDifference23 > 1) {
//       float speed23 = (distance23 / (timeDifference23 / 1000000.00)); // Speed in meters per second
//       Serial.println("---------------------------------");
//       Serial.print("Speed between hallpin1 and hallpin2: ");
//       Serial.print(speed23);
//       Serial.println(" m/s");
//       // Serial.print("Time difference (hallpin1 to hallpin2): ");
//       // Serial.print(timeDifference23 / 1000.00); // Time in milliseconds
//       // Serial.println(" ms");

//     }
//     lastTriggerTime2 = 0; // Reset the trigger time for the next cycle
//   }

//   if(sensorValue4 == LOW && lastTriggerTime1 == 0 && sensorValue5 == HIGH) {
//     lastTriggerTime1 = microtime;
//   }

//   if (sensorValue5 == LOW && lastTriggerTime1 != 0) {
//     timeDifference45 = microtime - lastTriggerTime1;

//     if(timeDifference45 > 1) {
//       float speed34 = (distance34 / (timeDifference45 / 1000000.00)); // Speed in meters per second
//       Serial.print("Speed between hallpin4 and hallpin5: ");
//       Serial.print(speed34);
//       Serial.println(" m/s");
//       // Serial.print("Time difference (hallpin4 to hallpin5): ");
//       // Serial.print(timeDifference45 / 1000.00); // Time in milliseconds
//       // Serial.println(" ms");
//     }
//     lastTriggerTime1 = 0; // Reset the trigger time for the next cycle
//   }

// }

// void speed(int microtime, int sensorValue1, int sensorValue2, int sensorValue3, int sensorValue4, int sensorValue5) {
//   static unsigned long lastTriggerTime[5] = {0, 0, 0, 0, 0};
//   static float distances[4] = {distance12, distance23, distance34, distance45}; // Assuming these distances are defined elsewhere

//   int sensorValues[5] = {sensorValue1, sensorValue2, sensorValue3, sensorValue4, sensorValue5};

//   for (int i = 0; i < 4; i++) {
//     if (sensorValues[i] == LOW && lastTriggerTime[i] == 0 && sensorValues[i + 1] == HIGH) {
//       lastTriggerTime[i] = microtime;
//     }

//     if (sensorValues[i + 1] == LOW && lastTriggerTime[i] != 0) {
//       unsigned long timeDifference = microtime - lastTriggerTime[i];

//       if (timeDifference > 1) {
//         float speed = (distances[i] / (timeDifference / 1000000.00)); // Speed in meters per second
//         Serial.print("Speed between hallpin");
//         Serial.print(i + 1);
//         Serial.print(" and hallpin");
//         Serial.print(i + 2);
//         Serial.print(": ");
//         Serial.print(speed);
//         Serial.println(" m/s");
//       }
//       lastTriggerTime[i] = 0; // Reset the trigger time for the next cycle
//     }
//   }
// }
void speed(int microtime, int sensorValue1, int sensorValue2, int sensorValue3, int sensorValue4, int sensorValue5) {
  static unsigned long lastTriggerTime[4] = {0, 0, 0, 0};
  static float distances[4] = {distance12, distance23, distance34, distance45}; // Assuming these distances are defined elsewhere

  int sensorValues[5] = {sensorValue1, sensorValue2, sensorValue3, sensorValue4, sensorValue5};

  for (int i = 0; i < 4; i++) {
    if (sensorValues[i] == LOW && lastTriggerTime[i] == 0 && sensorValues[i + 1] == HIGH) {
      lastTriggerTime[i] = microtime;
    }

    if (sensorValues[i + 1] == LOW && lastTriggerTime[i] != 0) {
      unsigned long timeDifference = microtime - lastTriggerTime[i];

      if (timeDifference > 1) {
        float speed = (distances[i] / (timeDifference / 1000000.00)); // Speed in meters per second
        Serial.print("Speed between hallpin");
        Serial.print(i + 1);
        Serial.print(" and hallpin");
        Serial.print(i + 2);
        Serial.print(": ");
        Serial.print(speed);
        Serial.println(" m/s");
      }
      lastTriggerTime[i] = 0; // Reset the trigger time for the next cycle
    }
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
    speed(microtime, sensorValue1, sensorValue2, sensorValue3, sensorValue4, sensorValue5);
  }

  if(millitime - driverpinOnTime <= fireduration) {
    fire(sensorValue1, sensorValue2, sensorValue3, sensorValue4, sensorValue5);
  } else if(millitime - driverpinOnTime < fireCooldown) {
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    digitalWrite(driverpin3, LOW);
    digitalWrite(driverpin4, LOW);
    digitalWrite(driverpin5, LOW);
    // Serial.println("on cooldown");
  }
  else {
    digitalWrite(driverpin1, LOW);
    digitalWrite(driverpin2, LOW);
    digitalWrite(driverpin3, LOW);
    digitalWrite(driverpin4, LOW);
    digitalWrite(driverpin5, LOW);
    // Serial.println("awaiting input");
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