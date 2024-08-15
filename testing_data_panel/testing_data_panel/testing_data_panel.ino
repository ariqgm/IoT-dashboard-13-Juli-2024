#define MQTT_MAX_PACKET_SIZE 512 // Set ukuran sesuai kebutuhan Anda
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define WIFI_SSID "KOSTTA"
#define WIFI_PASSWORD "kostta2023"

#define MQTT_SERVER "192.168.1.14"
#define MQTT_PORT 1883
#define MQTT_USER "adi"
#define MQTT_PASSWORD "1234"

WiFiClient espClient;
PubSubClient client(espClient);

const int ledPin = D1; // Pin untuk LED

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Matikan LED pada awalnya

  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // Connecting to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
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
    // Attempt to connect
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

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  // Control LED based on message
  if (String(topic) == "esp8266/led") {
    if (message == "on") {
      digitalWrite(ledPin, HIGH);
       // Turn LED on
       Serial.print("LED NYALA");
    } else if (message == "off") {
      digitalWrite(ledPin, LOW); // Turn LED off
      Serial.print("LED MATIII COYYY");
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Generate dummy data
  float tegangan = random(220, 240);
  float teganganS = random(220, 240);
  float teganganT = random(220, 240);
  float tegline1 = sqrt(3) * tegangan;
  float tegline2 = sqrt(3) * teganganS;
  float tegline3 = sqrt(3) * teganganT;
  float arus = random(1, 10);
  float arusS = random(1, 10);
  float arusT = random(1, 10);
  float powerFactorR = random(90, 100) / 100.0;
  float powerFactorS = random(90, 100) / 100.0;
  float powerFactorT = random(90, 100) / 100.0;
  float dayaaktif = tegangan * arus * powerFactorR + teganganS * arusS * powerFactorS + teganganT * arusT * powerFactorT;
  float dayareaktif = tegangan * arus * sin(acos(powerFactorR)) + teganganS * arusS * sin(acos(powerFactorS)) + teganganT * arusT * sin(acos(powerFactorT));
  float freqR = 50.0;
  float freqS = 50.0;
  float freqT = 50.0;
  float kwH = dayaaktif / 1000.0;
  float energi = kwH * 3600000;
  float tagihan = kwH * 1467.28;

  // Prepare and send data in smaller payloads
  String payload1 = "{";
  payload1 += "\"tegangan\": " + String(tegangan, 2) + ",";
  payload1 += "\"teganganS\": " + String(teganganS, 2) + ",";
  payload1 += "\"teganganT\": " + String(teganganT, 2);
  payload1 += "}";

  String payload2 = "{";
  payload2 += "\"tegline1\": " + String(tegline1, 2) + ",";
  payload2 += "\"tegline2\": " + String(tegline2, 2) + ",";
  payload2 += "\"tegline3\": " + String(tegline3, 2);
  payload2 += "}";

  String payload3 = "{";
  payload3 += "\"arus\": " + String(arus, 2) + ",";
  payload3 += "\"arusS\": " + String(arusS, 2) + ",";
  payload3 += "\"arusT\": " + String(arusT, 2);
  payload3 += "}";

  String payload4 = "{";
  payload4 += "\"powerFactorR\": " + String(powerFactorR, 2) + ",";
  payload4 += "\"powerFactorS\": " + String(powerFactorS, 2) + ",";
  payload4 += "\"powerFactorT\": " + String(powerFactorT, 2);
  payload4 += "}";

  String payload5 = "{";
  payload5 += "\"dayaaktif\": " + String(dayaaktif, 2) + ",";
  payload5 += "\"dayareaktif\": " + String(dayareaktif, 2) + ",";
  payload5 += "\"freqR\": " + String(freqR, 2) + ",";
  payload5 += "\"freqS\": " + String(freqS, 2) + ",";
  payload5 += "\"freqT\": " + String(freqT, 2);
  payload5 += "}";

  String payload6 = "{";
  payload6 += "\"kwH\": " + String(kwH, 2) + ",";
  payload6 += "\"energi\": " + String(energi, 2) + ",";
  payload6 += "\"tagihan\": " + String(tagihan, 2);
  payload6 += "}";

  //Serial.print("Publishing message 1: ");
  //Serial.println(payload1);
  if (client.publish("Status_Daya_Beban_Listrik/part1", payload1.c_str())) {
    //Serial.println("Publish successful");
  } else {
    Serial.println("Publish failed");
  }

  //Serial.print("Publishing message 2: ");
  //Serial.println(payload2);
  if (client.publish("Status_Daya_Beban_Listrik/part2", payload2.c_str())) {
    //Serial.println("Publish successful");
  } else {
    Serial.println("Publish failed");
  }

  //Serial.print("Publishing message 3: ");
  //Serial.println(payload3);
  if (client.publish("Status_Daya_Beban_Listrik/part3", payload3.c_str())) {
    //Serial.println("Publish successful");
  } else {
    Serial.println("Publish failed");
  }

  //Serial.print("Publishing message 4: ");
  //Serial.println(payload4);
  if (client.publish("Status_Daya_Beban_Listrik/part4", payload4.c_str())) {
    //Serial.println("Publish successful");
  } else {
    Serial.println("Publish failed");
  }

  //Serial.print("Publishing message 5: ");
  //Serial.println(payload5);
  if (client.publish("Status_Daya_Beban_Listrik/part5", payload5.c_str())) {
    //Serial.println("Publish successful");
  } else {
    Serial.println("Publish failed");
  }

  //Serial.print("Publishing message 6: ");
  //Serial.println(payload6);
  if (client.publish("Status_Daya_Beban_Listrik/part6", payload6.c_str())) {
    //Serial.println("Publish successful");
  } else {
    Serial.println("Publish failed");
  }

  delay(3000); // Publish data every 5 seconds
}
