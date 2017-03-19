//
// Created by matejko on 20.2.2017.
//

#ifndef ROBOT_DEMO_ODOMETRY_H
#define ROBOT_DEMO_ODOMETRY_H

#include "types.h"
class Odometry {
public:
    Odometry();
    void update(double linear, double angular);
    double getX();
    double getY();
    double getYaw();
    Position2d getPos();
    Position2d* getPosPointer();
protected:
    Position2d pos;
private:
    void integrateRungeKutta2(double linear, double angular);
    void integrateYaw(double angular);
};


#endif //ROBOT_DEMO_ODOMETRY_H
