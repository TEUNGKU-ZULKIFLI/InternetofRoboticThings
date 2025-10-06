#include <Arduino.h>

// =======================================================
// KONFIGURASI PIN (HARUS SAMA DENGAN WIRING TAHAP 02)
// =======================================================

// Definisikan pin motor sisi KIRI (terhubung ke sisi A di L298N)
#define ENA 25 // Speed Control Kiri (Enable A)
#define IN1 26 // Arah 1 Kiri
#define IN2 27 // Arah 2 Kiri

// Definisikan pin motor sisi KANAN (terhubung ke sisi B di L298N)
#define ENB 13 // Speed Control Kanan (Enable B)
#define IN3 14 // Arah 1 Kanan
#define IN4 12 // Arah 2 Kanan

// =======================================================
// FUNGSI UTAMA
// =======================================================

void setup() {
  // Mulai komunikasi Serial untuk debugging
  Serial.begin(115200);
  Serial.println("Inisialisasi Robot...");

  // Atur semua pin motor sebagai OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set kecepatan awal. Nilai bisa dari 0 (berhenti) hingga 255 (maksimal).
  // Kita mulai dengan 200 agar tidak terlalu kencang.
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  Serial.println("Robot Siap!");
}

// =======================================================
// FUNGSI-FUNGSI GERAKAN
// =======================================================

void maju() {
  Serial.println("Bergerak Maju...");
  // Motor Kiri Maju
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor Kanan Maju
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void mundur() {
  Serial.println("Bergerak Mundur...");
  // Motor Kiri Mundur
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Motor Kanan Mundur
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKanan() {
  Serial.println("Belok Kanan...");
  // Motor Kiri Maju (untuk berputar)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor Kanan Mundur (untuk berputar)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKiri() {
  Serial.println("Belok Kiri...");
  // Motor Kiri Mundur (untuk berputar)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Motor Kanan Maju (untuk berputar)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void berhenti() {
  Serial.println("Berhenti.");
  // Matikan semua motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// =======================================================
// LOOP UTAMA (SEQUENCER UNTUK TESTING)
// =======================================================

void loop() {
  // Ini adalah urutan tes otomatis. Robot akan melakukan ini berulang-ulang.
  
  // Tes maju
  maju();
  delay(2000); // Jalan maju selama 2 detik

  // Tes berhenti
  berhenti();
  delay(1000); // Berhenti selama 1 detik

  // Tes mundur
  mundur();
  delay(2000); // Jalan mundur selama 2 detik

  // Tes berhenti
  berhenti();
  delay(1000);

  // Tes belok kanan
  belokKanan();
  delay(1000); // Berputar ke kanan selama 1 detik

  // Tes berhenti
  berhenti();
  delay(1000);

  // Tes belok kiri
  belokKiri();
  delay(1000); // Berputar ke kiri selama 1 detik
  
  // Tes berhenti
  berhenti();
  delay(3000); // Berhenti selama 3 detik sebelum mengulang seluruh sekuens
}