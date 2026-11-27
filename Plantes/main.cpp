#include <Arduino.h>
#include <Wire.h>
#include <rgb_lcd.h>
#include <Adafruit_SHT31.h>
#include <string>
#include <vector>
#include "plante.h"


rgb_lcd lcd;
Adafruit_SHT31 sht31;
const int PIN_BOUTON = D5;

std::vector<Plante*> plantes;       // la liste des plantes
size_t courante = 0;                // indice de la plante choisie

float temperature = 0;
float humidite = 0;
float lumiere = 0;
unsigned long dernierMesure = 0;

bool boutonAppuye() {
    static bool ancien = false;
    static unsigned long dernierChgt = 0;

    bool actuel = digitalRead(PIN_BOUTON) == HIGH;
    bool appui = false;

    if (actuel && !ancien && millis() - dernierChgt > 200) {
        appui = true;
        dernierChgt = millis();
    }
    ancien = actuel;
    return appui;
}

float lireLux() {
    long somme = 0;
    for (int i = 0; i < 10; i++) {
        somme += analogRead(A0);
        delay(2);
    }
    int brut = somme / 10;
    if (brut < 1) brut = 1;
    float r = (1023.0f - brut) * 10.0f / brut;
    if (r < 0.1f) r = 0.1f;
    return 255.84f * pow(r, -10.0f / 9.0f);
}

void lireCapteurs(){
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    if (!isnan(t)) temperature = t;          // on ignore une lecture ratée (si ce n'est pas un nombre)
    if (!isnan(h)) humidite = h;
    lumiere = lireLux(); 
}    


void afficher(const std::vector<std::string> &pb) {
    static size_t indexPb = 0;
    static unsigned long dernierPb = 0;

    // ligne 1 : plante + température
    lcd.setCursor(0, 0);
    lcd.print(plantes[courante]->getNom().c_str());
    lcd.print(" ");
    lcd.print(temperature, 1);
    lcd.print("C    ");

    // ligne 2 : diagnostic
    lcd.setCursor(0, 1);
    if (pb.empty()) {
        lcd.setRGB(0, 255, 0);
        lcd.print("Tout va bien    ");
        indexPb = 0;
    } else {
        lcd.setRGB(255, 80, 0);
        if (millis() - dernierPb > 2000) {
            dernierPb = millis();
            indexPb = (indexPb + 1) % pb.size();
        }
        if (indexPb >= pb.size()) indexPb = 0;
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(pb[indexPb].c_str());
    }
}

void setup() {

    Serial.begin(74880);
    delay(1000);
    pinMode(PIN_BOUTON, INPUT);
    plantes.push_back(new Cactus());
    plantes.push_back(new Calathea());
    plantes.push_back(new Edelweiss());
    plantes.push_back(new Dionee());

    
    lcd.begin(16, 2);
    if (!sht31.begin(0x44)) {                // essaie 0x45 si "absent"
        lcd.print("SHT31 absent");
        while (true) delay(1000);
    }
}

void loop() {
    if (boutonAppuye()) {
        courante = (courante + 1) % plantes.size();   // revient à 0 après la dernière
        lcd.clear();                                  // efface l'ancien nom
    }

    if (millis() - dernierMesure > 1000) {
        dernierMesure = millis();
        lireCapteurs();
    }


    Serial.print("T=");  Serial.print(temperature);
    Serial.print(" H="); Serial.print(humidite);
    Serial.print(" L="); Serial.println(lumiere);

    afficher(plantes[courante]->verifier(temperature, humidite, lumiere));
    delay(50);
}