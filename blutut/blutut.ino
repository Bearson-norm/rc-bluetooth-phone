#include <SoftwareSerial.h>

// Pin untuk modul Bluetooth JDY-31
const int BT_RX = D3; // Pin RX Wemos D1 R1, sambungkan ke TX
const int BT_TX = D4; // Pin TX Wemos D1 R1, sambungkan ke RX

// Membuat objek software serial untuk komunikasi dengan modul Bluetooth
SoftwareSerial bluetoothSerial(BT_RX, BT_TX);

void setup() {
  // Inisialisasi komunikasi serial dengan baud rate 9600
  Serial.begin(9600);
  
  // Inisialisasi komunikasi serial dengan modul Bluetooth dengan baud rate 9600
  bluetoothSerial.begin(9600);
  Serial.println("Bluetooth JDY-31 dengan Wemos D1 R1 siap!");
}

void loop() {
  // Membaca data dari modul Bluetooth dan mengirimkannya ke Serial Monitor
  while (bluetoothSerial.available()) {
    char btData = bluetoothSerial.read();
    Serial.write(btData); // Menggunakan write untuk lebih cepat
  }
  
  // Membaca data dari Serial Monitor dan mengirimkannya ke modul Bluetooth
  while (Serial.available()) {
    char serialData = Serial.read();
    bluetoothSerial.write(serialData); // Menggunakan write untuk lebih cepat
  }
}
