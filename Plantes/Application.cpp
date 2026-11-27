/*********************************************************************
 * @file  Apllication.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include <Wire.h>
#include <Adafruit_SHT31.h>

Adafruit_SHT31 capteur;

Application::Application()
{
  // Constructeur
}
  
Application::~Application()
{
  // Destructeur
}  

void Application::init(void)
{
  // Initialise la LED intégrée
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // LOW = allumée sur ESP8266
  pinMode(PIN_BOUTON, INPUT);
  Wire.begin();                 // SDA = D2, SCL = D1

  if (!capteur.begin(0x44)) {   // adresse I2C du SHT31
    Serial.println("SHT31 non trouve");
  }
  
}

void Application::run(void)
{
  /*bool appuye = digitalRead(PIN_BOUTON);
  int lumiere = analogRead(A0);
  

  // LED intégrée inversée : LOW = allumée
  digitalWrite(LED_BUILTIN, appuye ? LOW : HIGH);
  digitalWrite(LED_BUILTIN, lumiere <300 ? LOW : HIGH);
  digitalWrite(LED_BUILTIN, lumiere <300 ? LOW : HIGH);
  
  float temperature = capteur.readTemperature();
  float humidite = capteur.readHumidity();

  if (isnan(temperature) || isnan(humidite)) {
    Serial.println("Erreur de lecture");
  } else {
    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.print(" C   Humidite : ");
    Serial.print(humidite);
    Serial.println(" %");
  }*/
  delay(2000);
}