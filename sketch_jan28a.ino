#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>


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

  Wire.beginTransmission(4);
  Wire.write(0);             
  Wire.endTransmission();

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
  Wire.begin();
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("MASTER READY");

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
    } else if (receivedData == "PRSS") {
      servo.write(30);
    } else if (receivedData == "SRVRST") {
      servo.write(0);
    }

    if (receivedData == "Z010") { // FIRST STEPPER RIGHT
      Serial.println("FSR");
      Wire.beginTransmission(4);
      Wire.write(1);             
      Wire.endTransmission(); 
      return;
    } else if (receivedData == "X010") { // FIRST STEPPER LEFT
      Serial.println("FSL");
      Wire.beginTransmission(4);
      Wire.write(2);             
      Wire.endTransmission(); 
      return;
    } else if (receivedData == "C010") { // SECOND STEPPER RIGHT
      Serial.println("SSR");
      Wire.beginTransmission(4);
      Wire.write(8);             
      Wire.endTransmission(); 
      return;
    } else if (receivedData == "V010") { // SECOND STEPPER LEFT
      Serial.println("SSL");
      Wire.beginTransmission(4);
      Wire.write(9);             
      Wire.endTransmission(); 
      return;
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
