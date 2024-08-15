#include <MQ2.h>
#include <SoftwareSerial.h>

const int LDR_PIN = A0;
const int MQ2_PIN = A1;
const int RELAY_PIN_LAMP = 2;
const int RELAY_PIN_ALARM = 3;
const int RELAY_PIN_ROOM_LOCK = 4;
const int RELAY_PIN_MAIN_LOCK = 5;
const int DIMMER_PIN = 6;

MQ2 mq2(MQ2_PIN);

// Initialize software serial for communication with NodeMCU
SoftwareSerial espSerial(7, 8); // RX, TX

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY_PIN_LAMP, OUTPUT);
  pinMode(RELAY_PIN_ALARM, OUTPUT);
  pinMode(RELAY_PIN_ROOM_LOCK, OUTPUT);
  pinMode(RELAY_PIN_MAIN_LOCK, OUTPUT);
  pinMode(DIMMER_PIN, OUTPUT);
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  mq2.begin();
  int mq2Value = mq2.readLPG();

  // Lampu ruang utama dikontrol oleh LDR
  if (ldrValue < (1023 * 0.3)) { // Lampu menyala jika intensitas < 30%
    digitalWrite(RELAY_PIN_LAMP, LOW); // Lampu menyala
  } else if (ldrValue > (1023 * 0.9)) { // Lampu mati jika intensitas > 90%
    digitalWrite(RELAY_PIN_LAMP, HIGH); // Lampu mati
  }

  // Alarm dikontrol oleh sensor gas MQ2
  if (mq2Value > 200) { // Nilai threshold sesuai kebutuhan
    digitalWrite(RELAY_PIN_ALARM, LOW); // Alarm menyala
  } else {
    digitalWrite(RELAY_PIN_ALARM, HIGH); // Alarm mati
  }

  // Monitoring values
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  Serial.print("MQ2 Value: ");
  Serial.println(mq2Value);

  // Send data to NodeMCU
  espSerial.print("LDR:");
  espSerial.println(ldrValue);
  espSerial.print("MQ2:");
  espSerial.println(mq2Value);
  espSerial.print("LAMP:");
  espSerial.println(digitalRead(RELAY_PIN_LAMP));

  // Receive commands from NodeMCU
  if (espSerial.available()) {
    String command = espSerial.readStringUntil('\n');
    if (command.startsWith("ROOM_LOCK:")) {
      String state = command.substring(10);
      if (state == "LOCK") {
        digitalWrite(RELAY_PIN_ROOM_LOCK, LOW);
      } else if (state == "UNLOCK") {
        digitalWrite(RELAY_PIN_ROOM_LOCK, HIGH);
      }
    } else if (command.startsWith("MAIN_LOCK:")) {
      String state = command.substring(10);
      if (state == "LOCK") {
        digitalWrite(RELAY_PIN_MAIN_LOCK, LOW);
      } else if (state == "UNLOCK") {
        digitalWrite(RELAY_PIN_MAIN_LOCK, HIGH);
      }
    } else if (command.startsWith("DIMMER:")) {
      int dimmerValue = command.substring(7).toInt();
      analogWrite(DIMMER_PIN, dimmerValue);
    }
  }

  delay(1000);
}
