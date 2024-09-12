#include <Arduino.h>

int voltagevalue = 0;
float voltage;
float hallbeginvalue;
float hallfinishvalue;
float R1 = 20000.0;
float R2 = 5100.0;
const int Pin = 27;
float voltagecal = 0.50;
// const int hallbegin = 25;
// const int hallfinish = 26;
unsigned long millitime;

void setup(){
  Serial.begin(921600);
  pinMode(Pin, OUTPUT);
//   pinMode(hallbegin, INPUT);
//   pinMode(hallfinish, INPUT);
}

void loop(){
  millitime = millis();
  // int64_t microtime = esp_timer_get_time(); 
  voltagevalue = analogRead(Pin);
//   hallbeginvalue = digitalRead(hallbegin);
//   hallfinishvalue = digitalRead(hallfinish);
  voltage = voltagevalue * (3.3/4096)*((R1 + R2)/R2) + voltagecal;
  // Serial.print("Voltage");
//   Serial.print(", ");
//   Serial.print(hallbeginvalue);
//   Serial.print(", ");
//   Serial.print(hallfinishvalue);
  Serial.print(millitime);
  Serial.print(", ");
  Serial.println(voltage);
  delay(1);
}