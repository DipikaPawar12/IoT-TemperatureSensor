#include <ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHT_pin D5 //Difine your uno's connected pin to DHT11

DHT dht (DHT_pin,DHTTYPE);

const char* ssid="Redmi";//Your hotspot name
const char* pass=" ";//Your wifi password

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

    String url = "https://dipzz.eu-gb.mybluemix.net/red/#flow/8c5a42f4.48a66";//Enter your cloud link
    String api = "/data";
    url += api;
    
    String param1 = "?temp=" + String(t);
    url += param1;
    String param2 = "&hum=" + String(h);
    url += param2;
    Serial.print("HTTP GET : ");
    Serial.println(url);

    http.begin(url);                              //Specify request destination

    int httpCode = http.GET();                    //Send the request

    if (httpCode > 0) {                           //Check the returning code
      String payload = http.getString();          //Get the request response payload
      Serial.println(payload);                    //Print the response payload
    }

    http.end();   //Close connection
    }

    delay(10000);    //Send a request every 30 seconds

    
    }
}
