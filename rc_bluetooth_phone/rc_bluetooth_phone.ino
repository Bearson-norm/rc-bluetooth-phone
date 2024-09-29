#include <SoftwareSerial.h>

#define in1 D5  // Pin Input 1 Motor A pada Motor Driver L298N
#define in2 D8  // Pin Input 2 Motor A pada Motor Driver L298N

#define in3 D10 // Pin Input 3 Motor B pada Motor Driver L298N
#define in4 D11 // Pin Input 4 Motor B pada Motor Driver L298N

SoftwareSerial bluetooth(D6, D7); // RX, TX
unsigned long lastReceivedTime = 0; // Waktu terakhir menerima input Bluetooth
const unsigned long timeout = 2000; // Waktu timeout dalam milidetik (2 detik)

void setup() {
  Serial.begin(9600); // Serial monitor baud rate
  bluetooth.begin(9600); // Bluetooth baud rate
  Serial.println("Bluetooth JDY-31 test");
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  stopMotors();
}

void loop() {
  if (bluetooth.available()) {
    char c = bluetooth.read(); // 1 = up, 2 = down, 3 = right, 4 = left
    Serial.write(c); // Display data from Bluetooth in Serial Monitor
    lastReceivedTime = millis(); // Update waktu terakhir menerima input

    if (c == '1') {
      moveForward();
      Serial.println("Maju");
    } else if (c == '2') {
      moveBackward();
      Serial.println("Mundur");
    } else if (c == '3') {
      moveRight();
      Serial.println("Kanan");
    } else if (c == '4') {
      moveLeft();
      Serial.println("Kiri");
    } else {
      stopMotors();
    }
  } else if (millis() - lastReceivedTime >= timeout) {
    stopMotors();
    Serial.println("Stop");

  }

  if (Serial.available()) {
    char c = Serial.read();
    bluetooth.write(c); // Send data from Serial Monitor to Bluetooth
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
