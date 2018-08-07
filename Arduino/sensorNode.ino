#include <ESP8266WiFi.h>            // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h>           // Allows us to connect to, and publish to the MQTT broker

const int ledPin = LED_BUILTIN;     // Use the built-in led for visual feedback that motion has been sensed
const int inputPin = 13;            // GPIO pin #13
int pirState = LOW;                 // we start, assuming no motion detected
int val = 0;                        // variable for reading the pin status
#define SENSORID "Motion_Sensor_1"  // Sensor Node ID Syntax: <SensorType>_Sensor_<ID#>

const char* ssid = "MyPi";          // Wireless access point being broadcast by Pi
const char* wifi_password = "raspberry";  //Password to log into Pi's network, specific to our Pi

const char* mqtt_server = "192.168.0.166";  // Static IP configured for connecting to our specific Pi
const char* mqtt_topic = "motion";          // Topic being published to for motion sensor nodes
const char* clientID = "ESP_1";             // Sensor Node ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  digitalWrite(ledPin, HIGH);       // Switch the on-board LED off to start with
  Serial.begin(115200);             // Begin Serial on 115200

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_password);  // Connect to the WiFi

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  } 
}

void loop() {
  val = digitalRead(inputPin);
  if (val == HIGH) {
    // Turn light on when motion has been sensed
    digitalWrite(ledPin, LOW);
    if (pirState == LOW) {
      // PUBLISH to the MQTT Broker
      if (client.publish(mqtt_topic, SENSORID)) {
        Serial.println("Motion detected and message sent!");
      }
      // client.publish will return a boolean value depending on whether it succeded or not.
      // If the message failed to send, try again, as the connection may have broken.
      else {
        Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
        client.connect(clientID);
        delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
        client.publish(mqtt_topic, SENSORID);
      }
      pirState = HIGH;
    }
  }
  else {
    // Turn light off after PIR timing delay has ended
    digitalWrite(ledPin, HIGH);
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
