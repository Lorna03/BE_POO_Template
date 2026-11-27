#pragma once

class Intervalle {
private:
    float mini, maxi;
public:
    Intervalle(float a, float b) : mini(a), maxi(b) {}
    bool contient(float v) const { return v >= mini && v <= maxi; }
    float getMin() const { return mini; }
    float getMax() const { return maxi; }

    // -1 = trop bas, 0 = dans l'intervalle, +1 = trop haut
    int position(float v) const {
        if (v < mini) return -1;
        if (v > maxi) return 1;
        return 0;
    }
};