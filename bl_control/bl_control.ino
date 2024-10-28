#include <SoftwareSerial.h>

// Pin untuk modul Bluetooth JDY-31
const int BT_RX = D3; // Pin RX Wemos D1 R1, sambungkan ke TX
const int BT_TX = D4; // Pin TX Wemos D1 R1, sambungkan ke RX

// Pin untuk LED
const int ledPin = D5; // Sesuaikan pin LED sesuai dengan kebutuhan Anda
bool ledState = false; // Menyimpan status LED (nyala/mati)

// Membuat objek software serial untuk komunikasi dengan modul Bluetooth
SoftwareSerial bluetoothSerial(BT_RX, BT_TX);

void setup() {
  // Inisialisasi komunikasi serial dengan baud rate 9600
  Serial.begin(9600);
  
  // Inisialisasi komunikasi serial dengan modul Bluetooth dengan baud rate 9600
  bluetoothSerial.begin(9600);
  Serial.println("Bluetooth JDY-31 dengan Wemos D1 R1 siap!");

  // Inisialisasi pin LED sebagai output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Memastikan LED mati saat awal
}

void loop() {
  // Membaca data dari modul Bluetooth dan mengirimkannya ke Serial Monitor
  while (bluetoothSerial.available()) {
    String btData = bluetoothSerial.readString(); // Membaca data sebagai string
    Serial.println(btData); // Menampilkan data di Serial Monitor
    
    // Jika data yang diterima adalah "lampu", toggle state LED
    if (btData == "lampu") {
      ledState = !ledState; // Toggle state LED
      digitalWrite(ledPin, ledState ? HIGH : LOW); // Atur LED berdasarkan state
      Serial.println(ledState ? "LED Menyala" : "LED Mati"); // Tampilkan status LED
    }
  }
}
