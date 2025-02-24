#include <SoftwareSerial.h>
#include <Servo.h>

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11


Servo servo;
SoftwareSerial BTSerial(0, 1); // RX, TX


// MOVEMENT
void forward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("MOVING FORWARD...");  
}

void back(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("MOVING BACK...");  
}

void left(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("MOVING LEFT...");  
}

void right(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("MOVING RIGHT...");  
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

  Serial.println("HALT...");
}

// END MOVEMENT


// LOGIC

int getSpeed(String data) {
  int speed = 0;
  speed += ((data[1] - '0') * 100) + ((data[2] - '0') * 10) + (data[3] - '0');

  return speed;
}

// END LOGIC


void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("HC-08 Bluetooth Communication Started");

  servo.attach(13);
  servo.write(0);
}


void loop() {
  if (BTSerial.available()) {
    String receivedData = BTSerial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(receivedData);
  
    if (receivedData.length() < 4) {
      return;   
    }

    if (receivedData == "STOP") {
      stop();
      return;
    }

    if (receivedData == "PUSHB") {
      servo.write(100);
    } else if (receivedData == "PRS") {
      servo.write(30);
    } else if (receivedData == "SRVRST") {
      servo.write(0);
    }
  
    char signal = receivedData[0];
    int speed = getSpeed(receivedData);
    if (signal == 'F') {
      forward(speed);
      return;
    } else if (signal == 'B') {
      back(speed);
      return;
    } else if (signal == 'L') {
      left(speed);
      return;
    } else if (signal == 'R') {
      right(speed);
      return;
    }
  }
}
