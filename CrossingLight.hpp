//
// Created by Daniel Courvoisier on 14.05.20.
//

#ifndef CARREFOUR_CROSSINGLIGHT_HPP
#define CARREFOUR_CROSSINGLIGHT_HPP

#include <string>
#include <iostream>
#include "Global.hpp"


// Namespace 
using namespace std;

// Variables globales
extern std::mutex displayLock;


// Classe CrossingLight
class CrossingLight {
private:
    string color;

public:
    CrossingLight();
    void update(string new_color);
    string getCouleur();
};


// Constructeur
CrossingLight::CrossingLight() {
    color = "R";
}


// Mise à jour état feu
void CrossingLight::update(string new_color){
    displayLock.lock();
    cout << "Mise à jour de l'état du feu : "<< new_color << endl;
    displayLock.unlock();
    color = new_color;
}


// Retourne état feu
string CrossingLight::getCouleur() {
    return color;
}

#endif //CARREFOUR_CROSSINGLIGHT_HPP