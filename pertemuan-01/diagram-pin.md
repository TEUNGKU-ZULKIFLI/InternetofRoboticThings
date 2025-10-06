# 📐 Diagram Pin I/O — ESP32 ke L298N

Dokumen ini menjelaskan konfigurasi pin antara ESP32 dan driver motor L298N yang digunakan untuk mengendalikan 4 motor DC pada mobil prototype.

---

## 🔌 Tabel Koneksi Pin

| Pin pada L298N     | Pin pada ESP32 | Fungsi                                 |
|--------------------|----------------|----------------------------------------|
| **ENA**            | **GPIO 25**    | Mengatur Kecepatan Motor Kiri          |
| **IN1**            | **GPIO 26**    | Mengatur Arah Motor Kiri               |
| **IN2**            | **GPIO 27**    | Mengatur Arah Motor Kiri               |
| **IN3**            | **GPIO 14**    | Mengatur Arah Motor Kanan              |
| **IN4**            | **GPIO 12**    | Mengatur Arah Motor Kanan              |
| **ENB**            | **GPIO 13**    | Mengatur Kecepatan Motor Kanan         |
| **GND** (di L298N) | **GND**        | **SANGAT PENTING!** Titik Referensi Ground |

> Pastikan semua koneksi stabil dan tidak terbalik. Gunakan jumper kabel berkualitas dan periksa polaritas baterai sebelum menyalakan sistem.

---

## 🧠 Konfigurasi Pin dalam Kode

```cpp
// Motor Kiri (Sisi A)
#define ENA 25
#define IN1 26
#define IN2 27

// Motor Kanan (Sisi B)
#define ENB 13
#define IN3 14
#define IN4 12
