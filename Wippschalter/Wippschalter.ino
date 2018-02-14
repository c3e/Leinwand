#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int schalterHoch = 13; //5
int schalterRunter = 15; //4
boolean valueHoch = 1;
boolean valueRunter = 1;
boolean valueHalt = 1;

 
const char* ssid = "foobar";
const char* password =  "";
const char* mqttServer = "";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {

  pinMode(schalterHoch, INPUT);
  pinMode(schalterRunter, INPUT);
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {

}

void auslesen() {
	if(digitalRead(schalterRunter) && !digitalRead(schalterHoch) && valueRunter) {
		client.publish("foobar/oben/lounge/leinwand", "down");
    valueRunter = 0;	
	}
	else if(!digitalRead(schalterRunter) && digitalRead(schalterHoch) && valueHoch) {
		client.publish("foobar/oben/lounge/leinwand", "up");
    valueHoch = 0;
	}
	else if(!digitalRead(schalterRunter) && !digitalRead(schalterHoch) && valueHalt) {
		client.publish("foobar/oben/lounge/leinwand", "halt");
    valueHalt  = 0;
	}

  if(!digitalRead(schalterRunter) && !valueRunter) {
    valueRunter = 1;
  }
  if(!digitalRead(schalterHoch) && !valueHoch) {
    valueHoch = 1;
  }
  if(digitalRead(schalterHoch) || digitalRead(schalterRunter) && !valueHalt) {
    valueHalt = 1;
  }

}
 
void loop() {
  
  client.loop();
  auslesen();
  delay(200);

}
