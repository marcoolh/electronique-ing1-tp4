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
float ratio = 0;
float angle = 0;
float tension = 0;
String motBinaire = "";

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void loop() {
  reading = analogRead(sensorPin); // Lecture de la valeur analogique du capteur
  
  // Conversion de la valeur en binaire sur 12 bits
  motBinaire = "";
  for (int i = 11; i >= 0; i--) {
    motBinaire += String((reading >> i) & 1);
  }

  ratio = 1 - (reading / 4095.0); // Calcul du ratio en inversant la valeur pour que la jauge se remplisse quand on tourne le potentiomètre dans le sens horaire
  tension = (reading / 4095.0) * 3.3; // Conversion de la valeur lue en tension (0-3.3V)

  display.clearDisplay();
  display.drawRect(SCREEN_WIDTH * .1, SCREEN_HEIGHT * .1, SCREEN_WIDTH * .8, SCREEN_HEIGHT * .3, WHITE); // Contour de la jauge
  display.fillRect(SCREEN_WIDTH * .1 + 2, SCREEN_HEIGHT * .1 + 2, (SCREEN_WIDTH * .8 - 4) * ratio, SCREEN_HEIGHT * .3 - 4, WHITE); // Remplissage de la jauge en fonction du pourcentage

  // Formatage du texte et affichage de la tension et du mot binaire
  display.setTextSize(1); // Taille
  display.setTextColor(WHITE); // Couleur
  display.setCursor(SCREEN_WIDTH * .2, SCREEN_HEIGHT * .5); // Position du texte
  display.println("Tension:" + String(tension, 2) + " V"); // Affichage de la tension avec 2 décimales
  display.setCursor(0, SCREEN_HEIGHT * .75); // Position du second texte
  display.println("Binaire:" + motBinaire); // Affichage du mot binaire
  display.display(); // Mise à jour de l'affichage
  delay(100); // Mise à jour toutes les 0.1 secondes pour voir le remplissage de la jauge en temps réel
}