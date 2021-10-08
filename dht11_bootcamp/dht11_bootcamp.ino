#define BLYNK_PRINT Serial

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN 14
#define DHTTYPE DHT11

char auth[] = "fszHwRFijui6T_FGuerS3-kHa3Wd4JzM";
char ssid[] = "bdrphone";
char pass[] = "nemo1234";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read temp and humidity");
    return;
  }

  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(900, sendSensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();

}
