#include <Arduino.h>
#include <WiFi.h> // Pustaka yang kita gunakan untuk semua fungsi WiFi

// =======================================================
//          !!! GANTI DENGAN KREDENSIAL WIFI ANDA !!!
// =======================================================
const char *ssid = "Mobil_IoRT_GACOR";
const char *password = "1234567890";
// =======================================================

// Membuat objek server yang akan berjalan di port 80 (port standar untuk web)
WiFiServer server(80);

// =======================================================
// KONFIGURASI PIN DAN FUNGSI GERAKAN (TIDAK BERUBAH)
// =======================================================
#define ENA 25
#define IN1 26
#define IN2 27
#define ENB 13
#define IN3 14
#define IN4 12

// Kita tambahkan Serial.println di setiap fungsi agar bisa dipantau di Serial Monitor
void maju()
{
  Serial.println("Request diterima: MAJU");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void mundur()
{
  Serial.println("Request diterima: MUNDUR");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void belokKanan()
{
  Serial.println("Request diterima: KANAN");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void belokKiri()
{
  Serial.println("Request diterima: KIRI");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void berhenti()
{
  Serial.println("Request diterima: STOP");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
// =======================================================

void setup()
{
  Serial.begin(115200);

  // Setup pin motor (sama seperti sebelumnya)
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  berhenti();

  // Memulai koneksi ke WiFi
  Serial.println();
  Serial.print("Menghubungkan ke jaringan WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Menunggu hingga koneksi berhasil, dengan indikator titik-titik
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Memberi tahu kita jika koneksi berhasil dan menampilkan alamat IP robot
  Serial.println("\nWiFi terhubung!");
  Serial.print("Alamat IP Robot: ");
  Serial.println(WiFi.localIP()); // INI ADALAH ALAMAT WEB SERVER ANDA!

  // Memulai server
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); // Cek apakah ada browser yang connect
  if (!client)
  {
    return; // Jika tidak ada, ulangi loop
  }

  // Tunggu hingga client mengirim data (request HTTP)
  while (!client.available())
  {
    delay(1);
  }

  // Baca baris pertama dari request (misal: "GET /maju HTTP/1.1")
  String request = client.readStringUntil('\r');
  client.flush(); // Bersihkan sisa data dari client

  // Cek request URL untuk menentukan gerakan
  if (request.indexOf("/maju") != -1)
  {
    maju();
  }
  else if (request.indexOf("/mundur") != -1)
  {
    mundur();
  }
  else if (request.indexOf("/kiri") != -1)
  {
    belokKiri();
  }
  else if (request.indexOf("/kanan") != -1)
  {
    belokKanan();
  }
  else if (request.indexOf("/stop") != -1)
  {
    berhenti();
  }

  // Kirim Halaman Web (HTML) sebagai respons ke browser
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close"); // Tutup koneksi setelah respons selesai
  client.println();                    // Baris kosong wajib setelah header
  client.println("<!DOCTYPE HTML>");
  client.println("<html><head><title>Kontrol Mobil IoRT</title><meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'></head>");
  client.println("<body style='font-family: Arial; text-align: center; background-color: #282c34; color: white;'>");
  client.println("<h1>Kontrol Mobil IoRT via WiFi</h1>");
  client.println("<p><a href='/maju'><button style='font-size: 24px; padding: 20px 40px; margin: 5px; width: 200px; background-color: #61afef;'>MAJU</button></a></p>");
  client.println("<p>");
  client.println("<a href='/kiri'><button style='font-size: 24px; padding: 20px 40px; margin: 5px; width: 200px; background-color: #c678dd;'>KIRI</button></a>");
  client.println("<a href='/stop'><button style='font-size: 24px; padding: 20px 40px; margin: 5px; width: 200px; background-color: #e06c75;'>STOP</button></a>");
  client.println("<a href='/kanan'><button style='font-size: 24px; padding: 20px 40px; margin: 5px; width: 200px; background-color: #c678dd;'>KANAN</button></a>");
  client.println("</p>");
  client.println("<p><a href='/mundur'><button style='font-size: 24px; padding: 20px 40px; margin: 5px; width: 200px; background-color: #98c379;'>MUNDUR</button></a></p>");
  client.println("</body></html>");

  delay(1);
}