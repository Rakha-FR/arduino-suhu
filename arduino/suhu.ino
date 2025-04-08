#include "Adafruit_Sensor.h"

#include <WiFi.h>

#include <HTTPClient.h>
#include "DHT.h"
#include "DHT_U.h"

#include "config.h"

#define DPIN 4   // Ubah sesuai dengan pin yang digunakan
#define DTYPE DHT11  // Bisa DHT11 atau DHT22
#define LED_BUILTIN 2

// Inisialisasi sensor DHT
DHT dht(DPIN, DTYPE);

void setup() {
    Serial.begin(115200);
    
    Serial.print("Menghubungkan ke WiFi: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nTerhubung ke WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    dht.begin();
}

void loop() {
  delay(2000); // Delay agar pembacaan stabil

    float suhu = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(suhu) || isnan(hum)) {
        Serial.println("Gagal membaca dari sensor DHT!");
        return;
    }

    Serial.print("Mengirim data ke API: ");
    Serial.print(suhu);
    Serial.print(" C, ");
    Serial.print(hum);
    Serial.println(" %");

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(SERVER_API);
        http.addHeader("Content-Type", "application/json");

        // Buat data dalam format JSON
        String jsonData = "{\"temperature\": " + String(suhu) + ", \"humidity\": " + String(hum) + "}";
        int httpResponseCode = http.POST(jsonData);

        if (httpResponseCode > 0) {
            Serial.print("Response: ");
            Serial.println(httpResponseCode);
        } else {
            Serial.print("Error: ");
            Serial.println(http.errorToString(httpResponseCode).c_str());
        }
        http.end();
    } else {
        Serial.println("WiFi tidak terhubung.");
    }

    delay(5000); // Kirim data setiap 5 detik
}