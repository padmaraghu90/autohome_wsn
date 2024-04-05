#include <Arduino.h>
#include <PubSubClient.h>
#include <rpcWiFi.h>
#include <SPI.h>
#include <string>
#include <HTTPClient.h>

using namespace std;

// WiFi credentials
const char *SSID = "JioFiber-UnkTm_5G";
const char *PASSWORD = "saibaba32";

const char* serverName = "http://api.thingspeak.com/update"; //Domain Name for HTTP POST Request
String apiKey = "1S38F6BZWQP1I23B"; //"Write API Key" from ThingSpeak

// Use WiFiClient class to create TCP connections
WiFiClient client;

void connectWiFi()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connecting to WiFi..");
        WiFi.begin(SSID, PASSWORD);
        delay(500);
    }

    Serial.println("Connected!");
}

void setup()
{
	Serial.begin(9600);

	while (!Serial)
		; // Wait for Serial to be ready

  connectWiFi();

}

void loop()
{
  Serial.print("Connecting to ");
  Serial.println(serverName); //print server IP address


  // Uncomment this after connecting to DHT22 sensor
  /*
  int t = dht.readTemperature(); //Assign variable to store temperature
  int h = dht.readHumidity(); //Assign variable to store humidity
  */
  int t = 30;
  int h = 30;

  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  // Data to send with HTTP POST
  String httpRequestData = "api_key=" + apiKey + "&field1=" + String(t) + "&field2=" + String(h);           
  // Send HTTP POST request
  int httpResponseCode = http.POST(httpRequestData);
      
  
     
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
        
  // Free resources
  http.end();

  //wait 10 seconds to send the next POST request
  Serial.println("Waiting...");
  delay(100000);
}