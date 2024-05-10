/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  NOTE: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/
#include <Servo.h>
#include <DHT.h>
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
// Definisikan pin untuk sensor ultrasonik
const int trigPin = D1; // Sesuaikan dengan pin yang digunakan pada ESP8266 (GPIO0 - GPIO15)
const int echoPin = D2; // Sesuaikan dengan pin yang digunakan pada ESP8266 (GPIO0 - GPIO15)

// Variabel untuk menyimpan waktu pulsa ultrasonik
long duration;
// Variabel untuk menyimpan jarak
int distance;
int ddata;

#define DHTPIN D2     // Sesuaikan dengan pin yang digunakan pada ESP8266 (GPIO0 - GPIO15)
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6xMcM8gfe"
#define BLYNK_TEMPLATE_NAME         "NodeMCU"
#define BLYNK_AUTH_TOKEN            "_uSKHcVBTl7LNmQjOj8K92n1nYqlKFE-"

Servo myservo;  // Membuat objek servo untuk mengendalikan servo motor
int pos = 0;    // Variabel untuk menyimpan posisi servo

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Kubs-Tech Bedroom";
char pass[] = "cilojelek230601*";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  myservo.attach(D3);  // Menghubungkan servo motor ke pin D3

  // Inisialisasi pin untuk sensor ultrasonik
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop()
{
  Blynk.run();
  loop1();
}

BLYNK_WRITE(V1) { // Fungsi yang akan dieksekusi ketika widget Slider di Blynk diubah
  int sliderValue = param.asInt(); // Membaca nilai dari widget Slider
  myservo.write(sliderValue); // Menggerakkan servo sesuai dengan nilai Slider
}

void loop1() {
  // Kirimkan sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Baca waktu pulsa ultrasonik
  duration = pulseIn(echoPin, HIGH);
  
  // Hitung jarak dalam centimeter
  distance = duration * 0.034 / 2;
  ddata = duration * 0.034 / 2;
  
  // Tampilkan hasil ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println("cm");

  // Jika jarak terdeteksi 150cm, kirim notifikasi ke Telegram
   if (distance <= 40) {
      Blynk.logEvent("Pets Detected at distance", String(distance) + "cm");
      Serial.print("Pets Detected at distance ");
      Serial.print(distance);
      Serial.println(" cm");
      Blynk.virtualWrite(V3, distance);
  } else {
      Blynk.virtualWrite(V3, distance);  
  }

  delay(1000);
}
