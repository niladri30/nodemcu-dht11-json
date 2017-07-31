/*
 *  Simple HTTP POST webclient to send JSON fromat Data to cloud
 *  Author - Niladri  
 */

#include <ESP8266WiFi.h>

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11

//const char* ssid     = "niladri";
//const char* password = "niladri11";


//const char* host = "posttestserver.com";    This is used for Test, to check if the json message gets posted to the server
const char* host = "xxx.xx.xx.xxx";           //  My Stingray instance or 
DHT dht(DHTPIN, DHTTYPE);

//String PostData = "Hello --- niladri";   

void setup() {
  Serial.begin(115200);
  //Serial.begin(9600);                     You can change if the dht11 doesn't send the data properly
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;
  
  char t_buffer[10];
  char h_buffer[10];
  float h = dht.readHumidity();
  String humid=dtostrf(h,0,2,h_buffer);
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  String temp=dtostrf(t,0,2,t_buffer);
  

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 1128;                     //My Stingray Port, it can be the port where your HTTP service is running
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/HttpProtocolAdapter/London/ingest";
  String postData = "{\"organizationId\": \"marvel\",\"deviceType\": \"Building\",\"assetId\": \"oscorp_dht11\",\"haName\": \"Wilson Building\",\"deviceId\": \"oscorp_device1\",\"site\": \"Kents Hill\",\"region\": \"South East England\",\"country\": \"Something\",\"latitude\": 51.518111,\"longitude\": -0.087496,\"eventTime\": \"2017-07-12T12:33:33.752Z\",\"properties\": {\"temperature\":" + temp + ",\"humidity\":" + humid + "}}";
  Serial.println(postData);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  //client.print(String("POST ") + url + " HTTP/1.1\r\n" +
              // "Host: " + host + "\r\n" + 
              // "Connection: close\r\n\r\n");
  client.println("POST /HttpProtocolAdapter/London/ingest HTTP/1.1");
  client.println("Host: xxx.xx.xx.xxx");
  client.println("Cache-Control: no-cache");
  //client.println("Content-Type: application/json;");
  //client.println("Content-Type: application/x-www-form-urlencoded;");
  client.println("Content-Type: text/plain");
  client.print("Content-Length: ");
  client.println(postData.length());
  client.println();
  client.println(postData);
  delay(10000);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}