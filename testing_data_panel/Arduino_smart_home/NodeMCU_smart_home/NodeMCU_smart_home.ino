#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

#define WIFI_SSID "KOSTTA"
#define WIFI_PASSWORD "kostta2023"

#define MQTT_SERVER "192.168.1.14"
#define MQTT_PORT 1883
#define MQTT_USER "ariq"
#define MQTT_PASSWORD "1234"

WiFiClient espClient;
PubSubClient client(espClient);

// Initialize software serial for communication with Arduino Uno
SoftwareSerial arduinoSerial(D7, D8); // RX, TX

String roomLockStatus = "UNLOCK";
String mainLockStatus = "UNLOCK";
int dimmerValue = 0;
int ldrValue = 0;
int mq2Value = 0;
String lampStatus = "OFF";

void setup() {
  Serial.begin(115200);
  arduinoSerial.begin(9600);

  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  // Ensure MQTT connection
  reconnect();
}

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

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Received message on topic ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);

  // Send commands to Arduino Uno
  if (String(topic) == "kontrol/room_lock") {
    arduinoSerial.print("ROOM_LOCK:");
    arduinoSerial.println(message);
    roomLockStatus = message;
    Serial.print("Room Lock: ");
    Serial.println(roomLockStatus);
  } else if (String(topic) == "kontrol/main_lock") {
    arduinoSerial.print("MAIN_LOCK:");
    arduinoSerial.println(message);
    mainLockStatus = message;
    Serial.print("Main Lock: ");
    Serial.println(mainLockStatus);
  } else if (String(topic) == "kontrol/dimmer") {
    arduinoSerial.print("DIMMER:");
    arduinoSerial.println(message);
    dimmerValue = message.toInt();
    Serial.print("Dimmer: ");
    Serial.print(map(dimmerValue, 0, 255, 0, 100));
    Serial.println("%");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      client.subscribe("kontrol/room_lock");
      client.subscribe("kontrol/main_lock");
      client.subscribe("kontrol/dimmer");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishStatus() {
  String payload = "{";
  payload += "\"id\": \"ESP8266Client\",";
  payload += "\"room_lock_status\": \"" + roomLockStatus + "\",";
  payload += "\"main_lock_status\": \"" + mainLockStatus + "\",";
  payload += "\"dimmer_value\": " + String(dimmerValue) + ",";
  payload += "\"ldr_value\": " + String(ldrValue) + ",";
  payload += "\"mq2_value\": " + String(mq2Value) + ",";
  payload += "\"lamp_status\": \"" + lampStatus + "\"";
  payload += "}";

  Serial.print("Publishing message: ");
  Serial.println(payload);

  client.publish("home/status", payload.c_str());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Simulate sensor readings
  ldrValue = random(0, 100);
  mq2Value = random(0, 100);

  // Receive data from Arduino Uno
  if (arduinoSerial.available()) {
    String data = arduinoSerial.readStringUntil('\n');
    if (data.startsWith("LDR:")) {
      ldrValue = data.substring(4).toInt();
    } else if (data.startsWith("MQ2:")) {
      mq2Value = data.substring(4).toInt();
    } else if (data.startsWith("LAMP:")) {
      lampStatus = (data.substring(5).toInt() == LOW) ? "ON" : "OFF";
    }
  }

  // Publish status every 5 seconds
  static unsigned long lastPublish = 0;
  if (millis() - lastPublish > 5000) {
    lastPublish = millis();
    publishStatus();
  }
}
