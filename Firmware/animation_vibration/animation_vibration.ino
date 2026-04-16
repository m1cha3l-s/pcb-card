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
bool bmeAvailable = false;

int button1 = LOW;
int button2 = LOW;
int previousButton2 = LOW;

const uint8_t TEMPERATURE_DISPLAY_BRIGHTNESS = 60;
const uint16_t TEMPERATURE_FRAME_DELAY_MS = 80;
bool temperatureAnimationActive = false;
char temperatureText[16];
uint16_t temperatureTextWidth = 0;
int temperatureScrollX = 0;
unsigned long lastTemperatureFrameMs = 0;

void startTemperatureAnimation() {
  if (!bmeAvailable) {
    return;
  }
  float temperatureC = bme.readTemperature();
  if (isnan(temperatureC)) {
    return;
  }
  snprintf(temperatureText, sizeof(temperatureText), "%.1fC", temperatureC);
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color(175, 10, 180));
  int16_t x1, y1;
  uint16_t w, h;
  matrix.getTextBounds(temperatureText, 0, 0, &x1, &y1, &w, &h);
  temperatureTextWidth = w;
  temperatureScrollX = matrix.width();
  lastTemperatureFrameMs = 0;
  temperatureAnimationActive = true;
  matrix.setBrightness(TEMPERATURE_DISPLAY_BRIGHTNESS);
}

void updateTemperatureAnimation() {
  if (!temperatureAnimationActive) {
    return;
  }
  unsigned long now = millis();
  if (lastTemperatureFrameMs != 0 && (now - lastTemperatureFrameMs) < TEMPERATURE_FRAME_DELAY_MS) {
    return;
  }
  lastTemperatureFrameMs = now;
  matrix.fillScreen(0);
  matrix.setCursor(temperatureScrollX, 0);
  matrix.print(temperatureText);
  matrix.show();
  temperatureScrollX--;
  if (temperatureScrollX < -static_cast<int>(temperatureTextWidth)) {
    matrix.fillScreen(0);
    matrix.setBrightness(0);
    matrix.show();
    temperatureAnimationActive = false;
  }
}

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(3, OUTPUT);

  Wire.begin();
  bmeAvailable = bme.begin(0x76);
  if (!bmeAvailable) {
    bmeAvailable = bme.begin(0x77);
  }

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
  if (button2 == HIGH && previousButton2 == LOW) {
    startTemperatureAnimation();
  }
  previousButton2 = button2;
  updateTemperatureAnimation();

}
