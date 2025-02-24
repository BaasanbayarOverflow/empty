#include <Wire.h>
#include <SoftwareSerial.h>


SoftwareSerial BTSerial(0, 1); // RX, TX


void setup() {
  Wire.begin();
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("MASTER READY");

}

void loop() {
  if (BTSerial.available()) {
    String receivedData = BTSerial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(receivedData);

    if (receivedData == "STRT") {
      Serial.println("SLAVE LED ON");
      Wire.beginTransmission(4);
      Wire.write(1);             
      Wire.endTransmission(); 
      return;
    }

    if (receivedData == "RST") {
      Serial.println("SLAVE LED OFF");
      Wire.beginTransmission(4);
      Wire.write(0);             
      Wire.endTransmission();
      return;
    }
  }
}
