#include <Arduino.h>

void setup() {
  // Memulai komunikasi serial dengan kecepatan 115200 bps
  // Ini adalah kecepatan standar yang umum digunakan
  Serial.begin(115200);
}

void loop() {
  // Mencetak pesan ke port serial
  Serial.println("Halo dari ESP32! Program berjalan...");
  
  // Tunggu 2 detik sebelum mengirim pesan berikutnya
  delay(2000);
}