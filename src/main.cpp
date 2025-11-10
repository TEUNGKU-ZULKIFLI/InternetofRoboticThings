#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h> // Library Web Server yang lebih canggih
#include <SPIFFS.h>    // Library untuk "hard drive" SPIFFS

// Objek Web Server baru di port 80
WebServer server(80);

// =======================================================
// KONFIGURASI PIN (FOKUS HANYA MOTOR)
// =======================================================
#define ENA 25
#define IN1 26
#define IN2 27
#define ENB 13
#define IN3 14
#define IN4 12
// =======================================================

/**
 * @brief Mengatur kecepatan dan arah kedua sisi motor.
 */
void setMotorSpeed(int speedLeft, int speedRight) {
    // Batasi nilainya agar tidak melebihi 255
    speedLeft = constrain(speedLeft, -255, 255);
    speedRight = constrain(speedRight, -255, 255);

    // --- Logika Motor Kiri ---
    if (speedLeft > 0) { // Maju
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, speedLeft);
    } else if (speedLeft < 0) { // Mundur
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA, -speedLeft);
    } else { // Berhenti
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, 0);
    }

    // --- Logika Motor Kanan ---
    if (speedRight > 0) { // Maju
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, speedRight);
    } else if (speedRight < 0) { // Mundur
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENB, -speedRight);
    } else { // Berhenti
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, 0);
    }
}

// =======================================================
// FUNGSI HANDLER UNTUK WEB SERVER
// =======================================================

// Fungsi ini akan dipanggil jika browser meminta halaman utama ("/")
void handleRoot() {
    File file = SPIFFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
}

// Fungsi ini akan dipanggil jika browser meminta file "/nipple.js"
void handleNippleJS() {
    File file = SPIFFS.open("/nipple.js", "r");
    server.streamFile(file, "text/javascript");
    file.close();
}

// Fungsi ini akan dipanggil jika browser mengirim data ke "/control?x=...&y=..."
void handleControl() {
    int x = 0;
    int y = 0;

    if (server.hasArg("x") && server.hasArg("y")) {
        x = server.arg("x").toInt(); 
        y = server.arg("y").toInt(); 
    }

    int motorSpeed = map(y, -100, 100, -255, 255); // y = throttle
    int turnSpeed = map(x, -100, 100, -255, 255);  // x = steering

    // =======================================================
    //  KOREKSI LOGIKA ADA DI SINI! (TANDA + / - DIBALIK)
    // =======================================================
    int speedLeft = motorSpeed - turnSpeed;
    int speedRight = motorSpeed + turnSpeed;
    // =======================================================

    // Kirim nilai akhir ke fungsi motor
    setMotorSpeed(speedLeft, speedRight);

    server.send(200, "text/plain", "OK");
}

// =======================================================

void setup() {
    Serial.begin(115200);

    pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

    if (!SPIFFS.begin(true)) {
        Serial.println("Gagal me-mount SPIFFS!");
        return; 
    }
    Serial.println("SPIFFS ter-mount dengan sukses.");

    // --- PENGATURAN MODE ACCESS POINT (AP) ---
    const char* ssid = "Mobil_IoRT_GACOR";
    const char* password = "1234567890";

    Serial.print("Membuat Access Point (AP) dengan nama: ");
    Serial.println(ssid);
    
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Alamat IP Robot: ");
    Serial.println(myIP);
    // --- AKHIR PENGATURAN AP ---

    // --- Pengaturan Rute Web Server ---
    server.on("/", HTTP_GET, handleRoot);           
    server.on("/nipple.js", HTTP_GET, handleNippleJS); 
    server.on("/control", HTTP_GET, handleControl);   

    server.begin();
    Serial.println("Web Server aktif!");
}

void loop() {
    server.handleClient(); 
}