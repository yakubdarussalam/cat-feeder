#include <Servo.h>
#include <DHT.h>
#define BLYNK_PRINT Serial

const int trigPin = D1;
const int echoPin = D2;

long duration;
int distance;

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_TEMPLATE_ID "TMPL6xMcM8gfe"
#define BLYNK_TEMPLATE_NAME "NodeMCU"
#define BLYNK_AUTH_TOKEN "V0z6Yz7K6JUTnbLXrRDP22FpKJjdJSNQ"
const char* blynkServer = "prakitblog.com";
const int blynkPort = 8181;

Servo myservo;
int pos = 0;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>

char ssid[] = "Kubs-Tech Bedroom";
char pass[] = "cilojelek230601*";

void setup() {
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, blynkServer, blynkPort);
  myservo.attach(D3);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  dht.begin();
}

void loop() {
  Blynk.run();
  loop1();
}

BLYNK_WRITE(V1) {
  int sliderValue = param.asInt();
  myservo.write(sliderValue);
}

void loop1() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Debug statement tambahan
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 25) {
    Serial.println("Condition met: distance < 150");
    Blynk.notify("Pets Detected");
    Serial.print("Pets Detected at distance ");
    Serial.print(distance);
    Serial.println(" cm");
    Blynk.virtualWrite(V3, distance);
  } else {
    Serial.println("Condition not met: distance >= 150");
    Blynk.virtualWrite(V3, distance);
  }

  delay(1000);
}
