cmake_minimum_required(VERSION 3.16)
project(Carrefour)

set(CMAKE_CXX_STANDARD 20)

add_executable(Carrefour main.cpp Car.hpp Crossroads.hpp Timer.hpp Global.hpp TrafficLight.hpp Course.hpp CrossingLightManagement.hpp CarFlow.hpp)