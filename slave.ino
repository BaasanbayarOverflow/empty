#include <Wire.h>
#include <Stepper.h>


const int steps = 2048;
int cmd = -1;


Stepper stepper_1(steps, 4, 5, 6, 7);
Stepper stepper_2(steps, 8, 9, 10, 12);


void receiveEvent(int bytes) {
  while (Wire.available()) {
    cmd = Wire.read();
  }
}


void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  Serial.println("SLAVE READY");

  stepper_1.setSpeed(10);
  stepper_2.setSpeed(10);
}


void loop() {
  switch (cmd) {
    case 0:
      stepper_1.step(0);
      stepper_2.step(0);
      break;
    case 1:
      stepper_1.step(steps);
      break;
    case 2:
      stepper_1.step(-steps);
      break;
    case 8:
      stepper_2.step(steps);
      break;
    case 9:
      stepper_2.step(-steps);
      break;
    default:
      break;
  }

  cmd = -1;
  delay(100);
}
