#include <ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHT_pin D5

DHT dht (DHT_pin,DHTTYPE);

const char* ssid="Redmi";
const char* pass="qwert@1234";

void setup(){

  Serial.begin (115200);
  WiFi.begin(ssid,pass);

  while(WiFi.status()!=WL_CONNECTED){
    delay(100);
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  delay(100);
  dht.begin();
  delay(100);
  
}
void loop(){

  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;

    float h=dht.readHumidity();
    float t= dht.readTemperature();

    Serial.println("temperature =");
    Serial.print(t);
    Serial.println("humidity =");
    Serial.print(h);
    delay(800);

    String url = "https://dipzz.eu-gb.mybluemix.net/red/#flow/8c5a42f4.48a66";
    String api = "/data";
    url += api;
    
    

    
    }
}
