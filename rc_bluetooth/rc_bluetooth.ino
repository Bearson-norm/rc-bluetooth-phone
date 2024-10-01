#include <SoftwareSerial.h>

// Pin untuk modul Bluetooth JDY-31
const int BT_RX = D3; // Pin RX Wemos D1 R1, sambungkan ke TX
const int BT_TX = D4; // Pin TX Wemos D1 R1, sambungkan ke RX

// Pin untuk motor driver L298N
const int motorIn1 = D5;
const int motorIn2 = D6;
const int motorIn3 = D7;
const int motorIn4 = D8;

// Membuat objek software serial untuk komunikasi dengan modul Bluetooth
SoftwareSerial bluetoothSerial(BT_RX, BT_TX);

void setup() {
  // Inisialisasi komunikasi serial dengan baud rate 9600
  Serial.begin(9600);
  
  // Inisialisasi komunikasi serial dengan modul Bluetooth dengan baud rate 9600
  bluetoothSerial.begin(9600);
  Serial.println("Bluetooth JDY-31 dengan Wemos D1 R1 siap!");

  // Inisialisasi pin motor sebagai output
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
}

void loop() {
  // Membaca data dari modul Bluetooth dan mengirimkannya ke Serial Monitor
  while (bluetoothSerial.available()) {
    char btData = bluetoothSerial.read();
    Serial.write(btData); // Menggunakan write untuk lebih cepat

    // Kontrol motor berdasarkan data yang diterima
    if (btData == '1') {
      maju();
    } else if (btData == '2') {
      mundur();
    } else if (btData == '3') {
      kanan();
    } else if (btData == '4') {
      kiri();
    } else {
      berhenti();
    }
  }
  
  // Membaca data dari Serial Monitor dan mengirimkannya ke modul Bluetooth
  while (Serial.available()) {
    char serialData = Serial.read();
    bluetoothSerial.write(serialData); // Menggunakan write untuk lebih cepat
  }
}

void maju() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
}

void mundur() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
}

void kanan() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
}

void kiri() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
}

void berhenti() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
}
