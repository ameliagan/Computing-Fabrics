#reference: [Rui Santos](https://RandomNerdTutorials.com/esp32-send-messages-whatsapp/)

#include <ESP_CapSense.h>
CapacitiveSensor SensorLeft = CapacitiveSensor(4,33);
CapacitiveSensor SensorRight = CapacitiveSensor(12,32);

#define led_red 13
#define led_blue 14
#define SAMPLING_TIME       1.5     // in seconds (I found that 1.5 seconds is about the time I do a gesture)
#define SAMPLING_FREQ_HZ    50       // Sampling frequency (Hz)
#define SAMPLING_PERIOD_MS  1000 / SAMPLING_FREQ_HZ   // Sampling period (ms)
#define NUM_SAMPLES         SAMPLING_TIME * SAMPLING_FREQ_HZ

long valLeft;
long valRight;
bool state_on = 0;
int counter=1; 
int time_out=1;
int led_max;

//whatsapp
#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "Iphone";
const char* password = "iphone123";

// +international_country_code + phone number
// Portugal +351, example: +351912345678
String phoneNumber = "+351912345678";
String apiKey = "1233365";

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
    Serial.print("
