/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H
#define PIN_BOUTON D7
#define PIN_CAPTEUR D6

#include <Arduino.h>

class Application {
  public:
    Application();      // Constructeur
    ~Application();     // Destructeur
    
    void init(void);    // Initialisation
    void run(void);     // Boucle principale
};


#endif