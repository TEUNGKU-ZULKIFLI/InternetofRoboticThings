# 📐 Diagram Pin I/O — Power 5v ke L298N

Document ini memetakan bagian power dengan jelas supaya tidak ribet di masa mendatang.

---

## 🔌 Tabel Koneksi Pin

| Pin pada L298N     | Pin pada ESP32 | Fungsi                                 |
|--------------------|----------------|----------------------------------------|
| **12V**            | **➕**    | Mengambil daya dc serta Mengatur bagian positif/volt          |
| **GND**            | **GND**    | Mengambil daya dc serta Membagikan ke board ESP32               |
| **5V**            | **5V**    | Membagikan power ke board supaya board bisa hidup               |
### [`Soft`](assets/WiredDiagram01.png) [`Hard`](assets/WiredDiagram02.png)

---

> [!WARNING]
> Pastikan semua koneksi stabil dan tidak terbalik. Gunakan jumper kabel berkualitas dan periksa polaritas baterai sebelum menyalakan sistem.

---

>[!CAUTION]
> Sebelum mengupload program pastikan kabel power yang `in`/`out` <=> `LN298N` dicabut

---

## 🧠 Konfigurasi Nama Bluetooth dalam Kode

```cpp
void setup()
{
  Serial.begin(115200);

  // Memulai Bluetooth dan memberikan nama pada perangkat kita
  // Nama ini akan muncul saat Anda mencari perangkat Bluetooth di HP
  SerialBT.begin("Mobil_IoRT_GACOR");
  Serial.println("Robot siap dikontrol via Bluetooth!");
  Serial.println("Silakan pairing dengan 'Mobil_IoRT_GACOR'");
```

`.begin` menginitial dengan nama `Mobil_IoRT_GACOR`
`.println` memberitahukan lewat terminal bahwa `Robot siap dikontrol via Bluetooth!` dan `Silakan pairing dengan Mobil_IoRT_GACOR`
