#include <ESP_CapSense.h>
CapacitiveSensor Sensor = CapacitiveSensor(4,33);

#define led_red 13
#define led_blue 14

long val;
bool state_on = 0;
int counter=1; 
int time_out=1;

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

  val = Sensor.capacitiveSensor(30);
  Serial.println(val);

  if (val >= 1000 && state_on == 0){
    counter++;
    state_on =1;
    time_out = 1;
    delay(50);
  }
  else if(val <=1000 && state_on==1){
    state_on=0;
    delay(50);
  }

  if(time_out>40){
    Serial.println(" ");
    Serial.println("counter: ");
    Serial.println(counter);

    if(counter==2){ //one click
      digitalWrite(led_red,HIGH); 
      digitalWrite(led_blue,LOW);
    }
    else if(counter==3){ //two clicks
      digitalWrite(led_blue, HIGH);
      digitalWrite(led_red, LOW); 
    }

    counter=1;
    time_out=1;
    delay(10);
  }

  delay(50);
}
