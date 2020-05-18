#include <iostream>
#include "Timer.hpp"
#include "Course.hpp"
#include "CrossingLight.hpp"
#include "CrossingLightManagement.hpp"
#include "CarFlow.hpp"


int main() {

    // Instanciation et démarrage timer
    MyTimer timer1("Timer Simulation");
    timer1.startTimer(10000);

    // Instanciation carrefour
    Crossroads crossroads;

    // Instanciation parcours
    Course course_1(0, &crossroads); // orientation Nord-Sud
    Course course_2(1, &crossroads); // orientation West-Est

    // Instanciation de feu
    CrossingLight crossingLights[2];

    // Instanciation gestion du feux
    CrossingLightManagement crossingLightManagement(&course_1, &course_2, crossingLights, &crossroads);

    // Instanciation des générateurs de flux de voitures
    CarFlow carFlow_NS(&course_1, 0, &timer1, crossingLights);
    CarFlow carFlow_WE(&course_2, 1, &timer1, crossingLights);

    // Fin
    return EXIT_SUCCESS;
}
