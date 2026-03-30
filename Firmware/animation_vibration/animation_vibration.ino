#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

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

  matrix.begin();
  matrix.setTextColor(matrix.Color(175, 10, 180));
  matrix.print("m1cha3l");
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
    matrix.setBrightness(100);
    delay(500);
    matrix.setBrightness(0);
  }

}
