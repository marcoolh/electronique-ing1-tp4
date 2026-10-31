#include <NeuroBoardS3.h>

int sensorPin = 1; // Utilisation du GPIO 1 (ADC)
int reading = 0;
float voltage = 0;
float ratio = 0;
float angle = 0;


void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  //Leture de la tension analogique
  reading = analogRead(sensorPin);
  // Calcul de la tension (3.3V max et 4096 états)
  voltage = reading * 3.3 / 4096.0;
  ratio = voltage / 3.3; // Ratio entre la puissance actuelle et maximale
  angle = 360 * (1 - ratio); // Angle dans le sens horaire

  Serial.println("Tension: " + String(voltage, 2)); // Affichage de la tension avec 2 décimales
  Serial.println("Angle: " + String(angle, 0) + "°\n");
  delay(800);
}