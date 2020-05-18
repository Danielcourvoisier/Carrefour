//
// Created by Daniel Courvoisier on 14.05.20.
//

#ifndef CARREFOUR_CARFLOW_HPP
#define CARREFOUR_CARFLOW_HPP

#include <thread>
#include "Course.hpp"
#include "CrossingLight.hpp"
#include "Crossroads.hpp"
#include "Car.hpp"
#include "Timer.hpp"


// Variables globales


// Classe CarFlow
class CarFlow {        //modification avec timer
private:
    Course * course;
    int orientation;
    MyTimer* timer;
    CrossingLight* crossingLights;
    thread thd;

public:
    CarFlow(Course *C, int carOrientation, MyTimer* aTimer, CrossingLight* CL);
    ~CarFlow();

    std::vector<std::thread> FLUX;  //typedef std::thread X;
    int co_voitures = 0;
    void createCars();
};


// Constructeur
CarFlow::CarFlow(Course *C, int carOrientation, MyTimer* aTimer, CrossingLight* CL) {
    course = C;
    orientation = carOrientation;
    timer = aTimer;
    crossingLights = CL;
    thd = thread(&CarFlow::createCars, this);
}


// Destructeur
CarFlow::~CarFlow() {
    thd.join();
}


// Créer voiture
void CarFlow::createCars() {
    while (timer->getTimerState() != 4) { //timer à la place d'un nombre connu de voitures
        Car VX("V_" + std::to_string(orientation) + "_" + std::to_string(co_voitures++), orientation, course, &crossingLights[orientation]);
        FLUX.push_back(std::thread(&Car::drive,VX)); //A ne pas mettre la référence mais l'objet lui-même
        int attente = rand()%200;
        std::this_thread::sleep_for(std::chrono::milliseconds(attente));// @suppress("Function cannot be resolved")
    }

    // Using a for loop with iterator
    for(auto it = std::begin(FLUX); it != std::end(FLUX); ++it) {
        (*it).join();
    }
    cout << "toutes les voitures de l'orientation " << orientation << " ont fini leur exécution" << endl;
}

#endif //CARREFOUR_CARFLOW_HPP
