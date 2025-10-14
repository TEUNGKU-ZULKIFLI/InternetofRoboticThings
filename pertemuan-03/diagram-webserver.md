# 📐 Diagram Pin I/O — Web Server ESP32

Dokumen ini menjelaskan koneksi power dan pin motor untuk kontrol via Web Server.

## 🔌 Tabel Koneksi Pin

| Pin pada L298N     | Pin pada ESP32 | Fungsi                                 |
|--------------------|----------------|----------------------------------------|
| ENA                | 25             | Enable motor A                         |
| IN1                | 26             | Motor A maju                           |
| IN2                | 27             | Motor A mundur                         |
| ENB                | 13             | Enable motor B                         |
| IN3                | 14             | Motor B maju                           |
| IN4                | 12             | Motor B mundur                         |

> [!NOTE]
> Gunakan kabel jumper berkualitas dan pastikan koneksi power stabil.

## 🌐 Koneksi WiFi

```cpp
const char* ssid = "NAMA_WIFI_ANDA";
const char* password = "PASSWORD_WIFI_ANDA";
