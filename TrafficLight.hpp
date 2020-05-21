//
// Created by Daniel Courvoisier on 14.05.20.
//

#ifndef CARREFOUR_TRAFFICLIGHT_HPP
#define CARREFOUR_TRAFFICLIGHT_HPP

#include <string>
#include <iostream>
#include "Global.hpp"


// Namespace 
using namespace std;

// Variables globales
extern std::mutex displayLock;


// Classe TrafficLight
class TrafficLight {
private:
    string color;

public:
    TrafficLight();
    void update(string new_color);
    string getCouleur();
};


// Constructeur
TrafficLight::TrafficLight() {
    color = "R";
}


// Mise à jour état feu
void TrafficLight::update(string new_color){
    displayLock.lock();
    cout << "Mise à jour de l'état du feu : "<< new_color << endl;
    displayLock.unlock();
    color = new_color;
}


// Retourne état feu
string TrafficLight::getCouleur() {
    return color;
}

#endif //CARREFOUR_TRAFFICLIGHT_HPP