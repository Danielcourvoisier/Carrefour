//
// Created by Daniel Courvoisier on 14.05.20.
//

#ifndef CARREFOUR_CROSSINGLIGHTMANAGEMENT_HPP
#define CARREFOUR_CROSSINGLIGHTMANAGEMENT_HPP

#include <mutex>
#include <thread>
#include <string>
#include <iostream>
#include "Global.hpp"
#include "Course.hpp"
#include "CrossingLight.hpp"
#include "Crossroads.hpp"

// Variables globales
extern std::mutex displayLock;


// Classe CrossingLightManagement
class CrossingLightManagement {
private:
    Course *course1;
    Course *course2;
    CrossingLight *crossingLight;
    Crossroads *crossroads;
    int state;
    thread thd;

public:
    CrossingLightManagement(Course* C1, Course* C2, CrossingLight* CL, Crossroads* CR);
    ~CrossingLightManagement();

    [[noreturn]] void detecter();
};


// Constructeur
CrossingLightManagement::CrossingLightManagement(Course *C1, Course *C2, CrossingLight *CL, Crossroads *CR) {
    course1 = C1;
    course2 = C2;
    crossingLight = CL,
    crossroads = CR;
    state = 0;
    thd = thread(&CrossingLightManagement::detecter, this);
}


// Destructeur
CrossingLightManagement::~CrossingLightManagement() {
    thd.join();
}


[[noreturn]] // Detecter
void CrossingLightManagement::detecter() {
    bool aFirst = true;
    bool bFirst = false;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        if ((state == 0) && (aFirst) && (course1->getDetect() > 0)) {
            displayLock.lock();
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 0 : FLUX A détecté -> FEU B imposé à ROUGE \n"  << endl;
            crossingLight[1].update("R");
            state = 1;
            displayLock.unlock();
        } else

        if ((state == 0) && (aFirst) && ((!course1->getDetect()) > 0)) {
            displayLock.lock();
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 0 : FLUX A pas détecté -> On bascule \n"  << endl;
            crossingLight[1].update("R");
            aFirst = false;
            bFirst = true;
            displayLock.unlock();
        } else

        if ((state == 0) && (bFirst) && ((!course2->getDetect()) > 0)) {
            displayLock.lock();
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 0 : FLUX B pas détecté -> On bascule \n"  << endl;
            crossingLight[1].update("R");
            aFirst = true;
            bFirst = false;
            displayLock.unlock();
        } else

        if ((state == 1) && (!crossroads->get_occupation())) {
            displayLock.lock();
            crossingLight[0].update("V");
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 1:  FLUX B bloqué et on libère FLUX A ->  FEU A imposé à VERT \n"  << endl;
            state = 2;
            CV[0].notify_all();
            displayLock.unlock();
        } else

        if ((state == 2) && (!crossroads->get_occupation()) && (!course1->getDetect())) {
            displayLock.lock();
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 2: FLUX A tari -> on revient à l'état d'attente\n" << endl;
            state=0;
            aFirst = false;
            bFirst=true;
            displayLock.unlock();
        } else

        if ((state == 0) && (bFirst) && (course2->getDetect() > 0)) {
            displayLock.lock();
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 0: FLUX B détecté -> FEU A imposé à ROUGE \n"  << endl;
            crossingLight[0].update("R");
            state = 3;
            displayLock.unlock();
        } else

        if ((state == 3) && (!crossroads->get_occupation())) {
            displayLock.lock();
            crossingLight[1].update("V");
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 3: FLUX A bloqué et on libère FLUX B -> FEU B imposé à VERT \n"  << endl;
            state=4;
            CV[1].notify_all();
            displayLock.unlock();
        } else

        if ((state == 4) && (!crossroads->get_occupation()) && (!course2->getDetect())) {
            displayLock.lock();
            cout <<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> état 4: FLUX B tari -> on revient à l'état d'attente\n" << endl;
            state=0;
            aFirst = true;
            bFirst = false;
            displayLock.unlock();
        }
    }
}


#endif //CARREFOUR_CROSSINGLIGHTMANAGEMENT_HPP
