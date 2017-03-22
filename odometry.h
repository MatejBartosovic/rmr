//
// Created by matejko on 20.2.2017.
//

#ifndef ROBOT_DEMO_ODOMETRY_H
#define ROBOT_DEMO_ODOMETRY_H

#include <chrono>
#include "types.h"
#include <chrono>
class Odometry {
public:
    Odometry();
    void update(double linear, double angular,double time = 0);
    void reset(Position2d pos);
    double getX();
    double getY();
    double getYaw();
    Position2d getPos();
protected:
    Position2d pos;
    std::chrono::high_resolution_clock::time_point last;
private:
    void integrateRungeKutta2(double linear, double angular);
    void integrateYaw(double angular);
};


#endif //ROBOT_DEMO_ODOMETRY_H
