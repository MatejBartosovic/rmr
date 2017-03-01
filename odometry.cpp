//
// Created by matejko on 20.2.2017.
//

#include "odometry.h"
#include <math.h>
#include <stdio.h>

Odometry::Odometry() : pos() {

}

void Odometry::update(double linear, double angular) {
    printf("odometry update linear = %lf angular = %lf\n",linear,angular);
    if (fabs(angular) < 1e-6)
        integrateRungeKutta2(linear, angular);
    else
    {
        /// Exact integration (should solve problems when angular is zero):
        const double heading_old = pos.yaw;
        const double r = linear/angular;
        pos.yaw += angular;
        pos.x       +=  r * (sin(pos.yaw) - sin(heading_old));
        pos.y       += -r * (cos(pos.yaw) - cos(heading_old));
    }
}

void Odometry::integrateRungeKutta2(double linear, double angular)
{
    const double direction = pos.yaw + angular * 0.5;

    /// Runge-Kutta 2nd order integration:
    pos.x       += linear * cos(direction);
    pos.y       += linear * sin(direction);
    pos.yaw += angular;
}

double Odometry::getX() {
    return pos.x;
}

double Odometry::getY() {
    return pos.y;
}

double Odometry::getYaw() {
    return pos.yaw;
}

Position2d Odometry::getPos() {
    return pos;
}
