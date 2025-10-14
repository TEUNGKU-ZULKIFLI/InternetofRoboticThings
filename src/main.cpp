#include <Arduino.h>

// Pustaka (library) untuk fungsionalitas Bluetooth Serial
#include "BluetoothSerial.h"

// Cek konfigurasi Bluetooth (baris ini wajib ada)
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

// Membuat objek untuk komunikasi Bluetooth, kita beri nama 'SerialBT'
BluetoothSerial SerialBT;

#define ENA 25
#define IN1 26
#define IN2 27
#define ENB 13
#define IN3 14
#define IN4 12

void maju()
{
  Serial.println("Maju");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void mundur()
{
  Serial.println("Mundur");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void belokKanan()
{
  Serial.println("Kanan");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void belokKiri()
{
  Serial.println("Kiri");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void berhenti()
{
  Serial.println("Berhenti");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
// =======================================================

void setup()
{
  Serial.begin(115200);

  // Memulai Bluetooth dan memberikan nama pada perangkat kita
  // Nama ini akan muncul saat Anda mencari perangkat Bluetooth di HP
  SerialBT.begin("Mobil_IoRT_GACOR");
  Serial.println("Robot siap dikontrol via Bluetooth!");
  Serial.println("Silakan pairing dengan 'Mobil_IoRT_GACOR'");

  // Setup pin motor sebagai OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set kecepatan motor
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  // Pastikan robot berhenti saat pertama kali dinyalakan
  berhenti();
}

void loop()
{
  // Cek apakah ada data/perintah yang masuk dari smartphone
  if (SerialBT.available())
  {
    // Baca satu karakter perintah yang masuk
    char command = SerialBT.read();

    // Tampilkan perintah yang diterima ke Serial Monitor (untuk debugging)
    Serial.print("Perintah diterima: ");
    Serial.println(command);

    // Logika untuk menjalankan fungsi berdasarkan perintah
    switch (command)
    {
    case 'F': // Jika karakter 'F' (Forward) diterima
      maju();
      break;
    case 'B': // Jika karakter 'B' (Backward) diterima
      mundur();
      break;

    case 'L': // Jika karakter 'L' (Left) diterima
      belokKiri();
      break;

    case 'R': // Jika karakter 'R' (Right) diterima
      belokKanan();
      break;

    default: // Jika karakter lain yang diterima (misal: 'S' atau apa pun)
      berhenti();
      break;
    }
  }
}