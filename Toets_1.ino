#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BME280.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define USE_BMP280
#define DHTTYPE DHT11
#ifdef USE_BMP280
#define DHTPIN 4 
Adafruit_BMP280 sensor;
#else
Adafruit_BME280 sensor;
#endif

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
   dht.begin();
    lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  if (!sensor.begin(0x76)) {
    Serial.println("Sensor niet gevonden!");
    while (1)
      ;
  }

  Serial.println("Sensor gestart");
}

void loop() {
  float T = sensor.readTemperature();
  float A = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Binnen: ");
  lcd.print(T);
  lcd.print(" 'C    ");

  lcd.setCursor(0, 1);
  lcd.print("Buiten: ");
  lcd.print(A);
  lcd.print(" 'C    ");

#ifndef USE_BMP280
#endif
  delay(2000);
}
