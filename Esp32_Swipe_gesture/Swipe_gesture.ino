#include <ESP_CapSense.h>
CapacitiveSensor SensorLeft = CapacitiveSensor(4,33);
CapacitiveSensor SensorRight = CapacitiveSensor(12,32);

#define led_red 13
#define led_blue 14

long valLeft;
long valRight;
bool state_on = 0;
int counter=1; 
int time_out=1;
int led_max;

void setup()
{
Serial.begin(115200);
pinMode(led_red, OUTPUT);
pinMode(led_blue, OUTPUT);

digitalWrite(led_red,LOW);
digitalWrite(led_blue,LOW);
}

void loop()
{

time_out++; 

valLeft = SensorLeft.capacitiveSensor(30);
valRight = SensorRight.capacitiveSensor(30);

Serial.print("Left: ");
Serial.print(valLeft);
Serial.print(" Right: ");
Serial.print(valRight);
Serial.println(" ");



if (valLeft<=3000 && valRight >=3000){
  digitalWrite(led_red, HIGH);
  digitalWrite(led_blue,LOW);
}
else if(valRight<=3000 && valLeft>=3000){
  digitalWrite(led_blue, HIGH);
  digitalWrite(led_red, LOW);
}
else{
  digitalWrite(led_red,LOW);
  digitalWrite(led_blue,LOW);
}

//hover over right is right led, hover over left is blue led
//
//if(valLeft>=1000 && valRight >=1000){
//  if (valLeft > valRight){
//  digitalWrite(led_blue,HIGH);
//  digitalWrite(led_red,LOW);
//  }
//  else{
//  digitalWrite(led_red,HIGH);
//  digitalWrite(led_blue,LOW);
//  }
//}
//else{
//  digitalWrite(led_red,LOW);
//  digitalWrite(led_blue,LOW);
//  }

delay(500);
}
