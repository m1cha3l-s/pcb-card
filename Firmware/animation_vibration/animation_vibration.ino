#include <Adafruit_GFX.h>
#include <Adafruit_BME280.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(6, 6, D9,   
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
Adafruit_BME280 bme;

int button1 = LOW;
int button2 = LOW;
void showTemperatureAnimation() {
  float temperatureC = bme.readTemperature();
  char temperatureText[16];
  snprintf(temperatureText, sizeof(temperatureText), "%.1fC", temperatureC);

  matrix.setBrightness(60);
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color(175, 10, 180));

  int16_t x1, y1;
  uint16_t w, h;
  matrix.getTextBounds(temperatureText, 0, 0, &x1, &y1, &w, &h);

  for (int x = matrix.width(); x >= -w; x--) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(temperatureText);
    matrix.show();
    delay(80);
  }

  matrix.fillScreen(0);
  matrix.setBrightness(0);
  matrix.show();
}

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(3, OUTPUT);

  Wire.begin();
  bme.begin(0x76);

  matrix.begin();
  matrix.setBrightness(0);
  matrix.show();
}

void loop() {
  button1 = digitalRead(0);
  button2 = digitalRead(1);
  if (button1 == HIGH) {
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(3, LOW);
  }
  else if (button2 == HIGH) {
    showTemperatureAnimation();
  }

}
