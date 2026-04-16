#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

Adafruit_BME280 bme;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(6, 6, D9,   
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

int button1 = LOW;
int button2 = LOW;

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(3, OUTPUT);

  bme.begin(0x76);
  float temp = bme.readTemperature();

  matrix.begin();
  matrix.setBrightness(0);
  matrix.show();
}

void loop() {
  button1 = digitalRead(0);
  button2 = digitalRead(1);
  float temp = bme.readTemperature();
  if (button1 == HIGH) {
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(3, LOW);
  }
  else if (button2 == HIGH) {
    if (temp <= 20) {
      matrix.fillScreen(matrix.Color(0, 255, 0));
      matrix.setBrightness(255);
      matrix.show();
      delay(1500);
      matrix.setBrightness(0);
      matrix.show();
    } else {
      matrix.fillScreen(matrix.Color(255, 0, 0));
      matrix.setBrightness(255);
      matrix.show();
      delay(1500);
      matrix.setBrightness(0);
      matrix.show();

    }
  }

}
