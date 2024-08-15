#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <PZEM004Tv30.h>
#include <PCF8574.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <NTPClient.h>


#define WIFI_SSID "KOSTTA"
#define WIFI_PASSWORD "kostta2023"

#define MQTT_SERVER "192.168.1.4"
#define MQTT_PORT 1883
#define MQTT_USER "ariq"
#define MQTT_PASSWORD "1234"

#define PZEM_RX_PIN 12 // D6
#define PZEM_TX_PIN 13 // D7
#define redled 0
#define yellowled 1
#define greenled 2
#define buzzer 3
const int relaypin = 14; // D5
PCF8574 io(0x20);

String RELAY_NORMAL = "NORMAL";
String RELAY_WARNING = "WARNING";
String RELAY_TRIP_WARNING = "TRIP_WARNING";
String RELAY_TRIP_SHORTCIRCUIT = "TRIP_SHORTCIRCUIT";
String RELAY_OVERLOAD = "OVERLOAD";

String RelayStatusFloat;

// set considered OverLoad & Short Circuit values
const float warningOL = 500;
const float OLcurrent = 800;
const float warningSC = 2000;
const float SCcurrent = 3000;
// time multiplier setting
const float K = 0.5;
// normal inverse constant values
const float A = 0.14;
const float B = 0.02;
// delay timer for sensor

unsigned long prevmillis = 0;
unsigned long Delayforsensor = 2000;

#define TZ_INFO "UTC7"

// Dummy sensor and relay values
SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

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
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void turngreenon() {
  io.write(yellowled, LOW);
  io.write(redled, LOW);
}

void turnyellowon() {
  io.write(greenled, LOW);
  io.write(redled, LOW);
}

void turnredon() {
  io.write(greenled, LOW);
  io.write(yellowled, LOW);
}

void setup() {
  Serial.begin(115200); // Ubah baud rate ke 115200
  io.begin();
  pinMode(relaypin, OUTPUT);
  
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - prevmillis > Delayforsensor || prevmillis == 0) {
    prevmillis = millis();

    // Dummy sensor data
    float currentz = pzem.current() - 0.034;
    //float currentz = random(0, 4000) / 1000.0; // Dummy current value in Amperes

    // Hold relay values
    String RelayStatus;
    float TimeDelay;
    int timestamp;

    // Checking data validation
    if (isnan(currentz)) {
      Serial.println("Error reading current");
      Serial.println("Possible causes:");
      Serial.println("- Poor connection between PZEM004T and ESP8266");
      Serial.println("- Faulty PZEM004T module");
      Serial.println("- Incorrect baud rate settings");
      return;
    }

    Serial.print("Current: ");
    Serial.print(currentz, 2);

    // Current values are multiple by 1000 to make it relevant to real cases (kiloAmperes)
    if (currentz < warningOL / 1000.0) { // Normal State
      io.write(greenled, HIGH);
      io.write(redled, LOW);
      io.write(yellowled, LOW);
      digitalWrite(relaypin, HIGH);
      Serial.print("Current: ");
      Serial.print(currentz * 1000, 2);
      Serial.println("A");
      RelayStatusFloat = RELAY_NORMAL;
      RelayStatus = "Normal";
      TimeDelay = 0;
    } 
    else if ((warningOL / 1000.0 <= currentz) && (currentz < OLcurrent / 1000.0)) {
      io.write(greenled, HIGH);
      io.write(redled, LOW);
      io.write(yellowled, LOW);
      digitalWrite(relaypin, HIGH);
      Serial.print("Current: ");
      Serial.print(currentz * 1000, 2);
      Serial.println("A");
      RelayStatusFloat = RELAY_WARNING;
      RelayStatus = "Warning (Overload)";
      TimeDelay = 0;
      io.write(buzzer, LOW);  delay(500);
      io.write(buzzer, HIGH); delay(500);
      io.write(buzzer, LOW);  delay(500);
      io.write(buzzer, HIGH); delay(500);
      io.write(buzzer, LOW);  delay(500);
      io.write(buzzer, HIGH); delay(500);
      io.write(buzzer, LOW);
    } 
    else if ((warningSC / 1000.0 <= currentz) && (currentz < SCcurrent / 1000.0)) {
      io.write(greenled, LOW);
      io.write(redled, LOW);
      io.write(yellowled, HIGH);
      double current2 = currentz / 0.8; // Use original values to calculate delay
      double OLdelay = K * (A / (pow(current2, B) - 1));
      Serial.print("Current reached: ");
      Serial.print(currentz * 1000, 2);
      Serial.println("A");
      Serial.print("Delay: ");
      Serial.print(OLdelay, 2);
      Serial.println("s");
      Serial.println("Relay is ACTIVATED to secure Overload");
      RelayStatusFloat = RELAY_TRIP_WARNING;
      RelayStatus = "Trip, Warning (Short Circuit)";
      TimeDelay = OLdelay;
      delay(OLdelay * 1000);
      digitalWrite(relaypin, LOW);
      io.write(buzzer, LOW);  delay(500);
      io.write(buzzer, HIGH); delay(2000);
      io.write(buzzer, LOW);  delay(500);
      io.write(buzzer, HIGH); delay(2000);
      io.write(buzzer, LOW);  delay(500);
    } 
    else if (currentz >= SCcurrent / 1000.0) {
      io.write(greenled, LOW);
      io.write(redled, HIGH);
      io.write(yellowled, LOW);
      float SCdelay = 500;
      Serial.print("Current reached: ");
      Serial.print(currentz * 1000, 2);
      Serial.println("A");
      Serial.print("Delay: ");
      Serial.print(SCdelay / 1000, 2);
      Serial.println("s");
      RelayStatusFloat = RELAY_TRIP_SHORTCIRCUIT;
      RelayStatus = "TRIP (Short Circuit)";
      TimeDelay = SCdelay / 1000;
      delay(SCdelay);
      digitalWrite(relaypin, LOW);
    } 
    else {
      io.write(greenled, LOW);
      io.write(redled, LOW);
      io.write(yellowled, HIGH);
      double current2 = currentz / 0.8; // Use original values to calculate delay
      double OLdelay = K * (A / (pow(current2, B) - 1));
      Serial.print("Current reached: ");
      Serial.print(currentz * 1000, 2);
      Serial.println("A");
      Serial.print("Delay: ");
      Serial.print(OLdelay, 2);
      Serial.println("s");
      Serial.println("Relay is ACTIVATED to secure Overload");
      RelayStatusFloat = RELAY_OVERLOAD;
      RelayStatus = "TRIP (Overload)";
      TimeDelay = OLdelay;
      delay(OLdelay * 1000);
      digitalWrite(relaypin, LOW);
    }

    // Prepare data for MQTT
    String payload = "{";
    payload += "\"id\": \"ESP8266Client\",";
    payload += "\"current\": " + String(currentz * 1000, 2) + ",";
    payload += "\"relay_status\": \"" + String(RelayStatusFloat) + "\",";
    payload += "\"timestamp\": " + String(timestamp);
    payload += "}";

    Serial.print("Publishing message: ");
    Serial.println(payload);

    client.publish("Proteksi_Listrik", payload.c_str());

    //Serial.println("Wait 3s");
    //delay(3000);
  }
}
