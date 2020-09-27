/* Sketch to send message to MQTT Broker on Cloud */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
const char* ssid = "Dumbledore";
const char* password = "";
const char* mqtt_server = "3.214.158.175";
int mqtt_port = 1883;

const int outputPin =  D3;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = String(ESP.getChipId());
    if (client.connect(clientId.c_str())) {Serial.println("connected");}
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(outputPin, OUTPUT);
  
  //setup WiFi connection
  setup_wifi();

  //setup MQTT connection
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // tell NodeMCU which function to call when  there is an incoming message
}

void loop() {
  if (!client.connected()) {reconnect();}
  client.loop();

  String msg = "Talking to MQTT";
  Serial.println("Sending Message: ");
  client.publish("outTopic", msg.c_str());

  delay(2000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {Serial.print((char)payload[i]);}
  Serial.println();

  payload[length] = '\0'; // terminate the incoming list of charas as a String

  // act on the incoming command
  if(strcmp(((char *)payload), "on") == 0) {digitalWrite(outputPin,LOW);}
  else if(strcmp(((char*)payload),"off")==0){digitalWrite(outputPin,HIGH);}
  else{Serial.println("Other message");}
}
