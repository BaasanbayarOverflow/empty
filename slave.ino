#include <Wire.h>


const int LED = 13;
int cmd = 0;


void receiveEvent(int bytes) {
  cmd = Wire.read();
}


void setup() {
  pinMode(LED, OUTPUT);

  Wire.begin(4);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  Serial.println("SLAVE READY");
}


void loop() {
  if (cmd == 0) {
    digitalWrite(LED, LOW);
    return;
  }

  if (cmd == 1) {
    digitalWrite(LED, HIGH);
    return;
  }
}
