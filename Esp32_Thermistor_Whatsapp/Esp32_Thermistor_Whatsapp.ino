#define led_red 13
#define led_blue 14

// which analog pin to connect
#define THERMISTORPIN A0         
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// the value of the 'other' resistor
#define SERIESRESISTOR 10000  

int samples[NUMSAMPLES];

//whatsapp
#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "Pixel_AG";
const char* password = "amelia123";

// +international_country_code + phone number
// Portugal +351, example: +351912345678
String phoneNumber = "+13158792557";
String apiKey = "1533365";

void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.begin(115200);
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);

  digitalWrite(led_red,LOW);
  digitalWrite(led_blue,LOW);
//
//   Send Message to WhatsAPP
  sendMessage("The temperature is");
}

void loop() {
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
//  Serial.print("Average analog reading "); 
//  Serial.println(average);
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
 
  Serial.print("Thermistor resistance "); 
  Serial.println(average);

if (average>=30000){
  digitalWrite(led_red, HIGH);
  digitalWrite(led_blue,LOW);
  sendMessage(average);
}
else{
  digitalWrite(led_blue, HIGH);
  digitalWrite(led_red, LOW);
  sendMessage(average);
}


delay(300);
}
