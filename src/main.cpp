#include <NeuroBoardS3.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largeur de l'écran OLED, en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED, en pixels

// Déclaration de l'écran connecté en I2C (pins SDA et SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int sensorPin = 1; // Utilisation du GPIO 1 (ADC)
int reading = 0;
float voltage = 0;
float ratio = 0;
float angle = 0;


void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void loop() {
  //Leture de la tension analogique
  reading = analogRead(sensorPin);
  // Calcul de la tension (3.3V max et 4096 états)
  voltage = reading * 3.3 / 4096.0;

  display.clearDisplay();
  display.setTextSize(5);
  display.setCursor(0, 0);
  display.println(String(voltage, 0) + "V");
  display.display();
  delay(800);
}