#include <NeuroBoardS3.h>

int sensorPin = 1; // Utilisation du GPIO 1 (ADC)
int reading = 0;
float voltage = 0;


void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  //Leture de la tension analogique
  reading = analogRead(sensorPin);
  // Calcul de la tension (3.3V max et 4096 états)
  voltage = reading * 3.3 / 4096.0;
  // Affichage de la tension avec 2 décimales
  Serial.println("Tension: " + String(voltage, 2));
  delay(800);
}