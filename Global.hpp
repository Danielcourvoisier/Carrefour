//
// Created by Daniel Courvoisier on 14.05.20.
//

#ifndef CARREFOUR_GLOBAL_HPP
#define CARREFOUR_GLOBAL_HPP

#include <mutex>
#include "TrafficLight.hpp"

// Variables constantes
//TrafficLight feuX[2];  // attention
bool inActivity = true;

// Mutex globaux
std::mutex displayLock;     // recursive mutex???
std::mutex arret_carrefour;
std::mutex verrou_parcours;
std::condition_variable CV[2]; // changer nom

#endif //CARREFOUR_GLOBAL_HPP
