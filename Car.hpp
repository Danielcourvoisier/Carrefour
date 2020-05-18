//
// Created by Daniel Courvoisier on 14.05.20.
//

#ifndef CARREFOUR_CAR_HPP
#define CARREFOUR_CAR_HPP

#include <string>
#include <thread>
#include "Global.hpp"
#include "Course.hpp"
#include "CrossingLight.hpp"

// Variables globales
extern std::mutex displayLock;


// Classe Car
class Car {
private:
    string name;
    int orientation;
    Course* course;
    int position;
    CrossingLight *crossingLight;

public:
    Car(string nom, int carOrientation, Course * CX, CrossingLight *CL);
    void drive();
};


// Constructeur
Car::Car(string nom, int carOrientation, Course * CX, CrossingLight *CL) {
    name = nom;
    orientation = carOrientation;
    course = CX;
    crossingLight = CL;
    position = 0;

    displayLock.lock();
    cout <<"============================================================================> " << name <<" est créée"  << endl;
    displayLock.unlock();
};


// Rouler
void Car::drive(){
    verrou_parcours.lock();
    position=course->reactualiser(name, position);
    verrou_parcours.unlock();

    while (position < 100){
        if (position == 6){
            std::unique_lock<std::mutex> monlock(arret_carrefour);
            while ((crossingLight->getCouleur() == "R")){
                //std::unique_lock<std::mutex> monlock(arret_carrefour);
                displayLock.lock();
                cout << "---------- " << name << " est bloquée devant le carrefour car le feu est rouge" << endl;
                displayLock.unlock();
                CV[orientation].wait(monlock);
                displayLock.lock();
                cout << "-------------------- " << name << " est libérée et va rentrer dans le carrefour" << endl;
                //_maPosition=_monParcours->reactualiser(_nom,_maPosition);
                displayLock.unlock();
            }
            int attente = rand()%30; //simule un temps de réaction long pour entrer dans le carrefour
            std::this_thread::sleep_for(std::chrono::milliseconds(attente));

        }

        int attente = rand()%200;
        std::this_thread::sleep_for(std::chrono::milliseconds(attente));
        verrou_parcours.lock();
        position=course->reactualiser(name, position);
        verrou_parcours.unlock();
    }
}

#endif //CARREFOUR_CAR_HPP
