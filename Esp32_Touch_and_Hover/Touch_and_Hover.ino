// ref code: https://github.com/henryc804/3.173_Fall22/blob/main/PSET5/esp32_capsense_lowpass/esp32_capsense_lowpass.ino

#include <ESP_CapSense.h>

const int relayPin = 13;

CapacitiveSensor   cs_4_33 = CapacitiveSensor(4,33);

float xn1 = 0;
//float yn1 =0;
//int k = 0;

void setup() {
  cs_4_33.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin (115200);
  pinMode (relayPin, OUTPUT);
}

void loop() {
  int xn =  cs_4_33.capacitiveSensor(30);

  if(xn>=3501){
    digitalWrite(relayPin, HIGH);
    Serial.println("touched");
//    Serial.println(xn);
    delay(50);
    digitalWrite(relayPin, LOW);
    delay(50);
  }
   else if(xn>=1000 && xn<=3500){
    digitalWrite(relayPin, HIGH);
    Serial.println("hover");
//    Serial.println(xn);
    delay(500);
    digitalWrite(relayPin, LOW);
    delay(500);
  }
  else{
    digitalWrite(relayPin, LOW);
//    Serial.println(xn);
    Serial.println("nothing");
  }
  
//  delay(100);
  }
