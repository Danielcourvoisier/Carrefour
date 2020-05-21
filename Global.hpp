//
// Created by Daniel Courvoisier on 14.05.20.
//

#ifndef CARREFOUR_GLOBAL_HPP
#define CARREFOUR_GLOBAL_HPP

#include <mutex>
#include "TrafficLight.hpp"

// Variables constantes
//bool inActivity = true;

// Mutex globaux
recursive_mutex displayLock;
std::mutex arret_carrefour;
std::mutex verrou_parcours;
std::condition_variable CV[2]; // changer nom lors de l'implémentation

#endif //CARREFOUR_GLOBAL_HPP
