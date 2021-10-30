// CopperCloud IoTech Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,LDR,100K RESISTOR


#include <ESP8266WiFi.h>
 
String apiKey = "JZBHKEV1YI1EJDH7";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "iot-coppercloud";     // replace with your wifi ssid and wpa2 key
const char *pass =  "coppercloud";
const char* server = "api.thingspeak.com";

int sensorPin = A0; 
float sensorValue = 0;

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  //sensorValue = (analogRead(sensorPin)* 280.0) / 1023.0;
  
  long sensorValue = analogRead(A0);
  int percent = map(sensorValue, 0, 1023, 0, 100);

  if (client.connect(server,80)) {   //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(percent);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    
    Serial.print("Daylight %: ");
    Serial.print(sensorValue);
    Serial.println("  Send to Thingspeak.");
  }
  client.stop();
 
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds TT
  delay(15000);
}
