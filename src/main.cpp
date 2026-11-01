#include <Arduino.h>
#include <DHT.h>
#include <HX711.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>

#define DHT_PIN  15
#define DHT_TYPE DHT22
#define DOUT_PIN 4
#define SCK_PIN  5

DHT dht(DHT_PIN, DHT_TYPE);
HX711 scale;
Adafruit_BMP280 bmp;
bool bmpFound = false;

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("DHT22 ready");

  scale.begin(DOUT_PIN, SCK_PIN);
  if (scale.wait_ready_timeout(3000)) {
    scale.set_scale();
    scale.tare();
  } else {
    Serial.println("HX711 NOT found — check wiring!");
  }

  Wire.begin(21, 22);
  if (bmp.begin(0x76) || bmp.begin(0x77)) {
    bmpFound = true;
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);
  } else {
    Serial.println("BMP280 NOT found — check SDA->GPIO21, SCL->GPIO22");
  }
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  // more
}