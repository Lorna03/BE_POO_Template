#pragma once
#include <string>
#include <vector>
#include "intervalle.h"

class Plante {
protected:
    std::string nom;
    Intervalle temperature;   // en °C
    Intervalle humidite;      // en %
    Intervalle lumiere;       // en lux

public:
    Plante(const std::string &n, Intervalle t, Intervalle h, Intervalle l)
        : nom(n), temperature(t), humidite(h), lumiere(l) {}
    virtual ~Plante() {}

    const std::string &getNom() const { return nom; }

    // renvoie les noms des paramètres hors de l'intervalle idéal
    std::vector<std::string> verifier(float t, float h, float l) const {
        std::vector<std::string> problemes;

        int pt = temperature.position(t);
        if (pt < 0) problemes.push_back("Trop froid");
        if (pt > 0) problemes.push_back("Trop chaud");

        int ph = humidite.position(h);
        if (ph < 0) problemes.push_back("Air trop sec");
        if (ph > 0) problemes.push_back("Air trop humide");

        int pl = lumiere.position(l);
        if (pl < 0) problemes.push_back("Manque lumiere");
        if (pl > 0) problemes.push_back("Trop de lumiere");

        return problemes;
    }
};

class Cactus : public Plante {
public:
    Cactus() : Plante("Cactus", Intervalle(20, 35), Intervalle(10, 30), Intervalle(2643, 3304.3)) {}
};

class Calathea : public Plante {
public:
    Calathea() : Plante("Calathea", Intervalle(18, 24), Intervalle(40, 80), Intervalle(326, 1322)) {}
};

class Edelweiss : public Plante {
public:
    Edelweiss() : Plante("Edelweiss", Intervalle(0, 15), Intervalle(40, 60), Intervalle(2974, 3304.3)) {}
};

class Dionee : public Plante {
public:
    Dionee() : Plante("Dionee", Intervalle(15, 25), Intervalle(70, 90), Intervalle(2313, 2974)) {}
};

