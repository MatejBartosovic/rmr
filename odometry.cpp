//
// Created by matejko on 20.2.2017.
//

#include "odometry.h"
#include <math.h>
#include <stdio.h>

Odometry::Odometry() : pos() {

}

void Odometry::update(double linear, double angular,double time) {
    //printf("odometry update linear = %lf angular = %lf\n",linear,angular);
    if(time){
        std::chrono::high_resolution_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> dif = now-last;
        pos.linearVel = linear/dif.count()*1000;
        pos.angularVel = angular/dif.count()*1000;
        last = now;
    } else{
        printf("odometry update linear = %lf angular = %lf\n",linear,angular);
        pos.linearVel = linear/time;
        pos.angularVel = angular/time;
    }

    if (fabs(angular) < 1e-6)
        integrateRungeKutta2(linear, angular);
    else
    {
        /// Exact integration (should solve problems when angular is zero):
        const double heading_old = pos.yaw;
        const double r = linear/angular;
        integrateYaw(angular);
        pos.x       +=  r * (sin(pos.yaw) - sin(heading_old));
        pos.y       +=  -r * (cos(pos.yaw) - cos(heading_old));
    }
}

void Odometry::integrateRungeKutta2(double linear, double angular)
{
    const double direction = pos.yaw + angular * 0.5;

    /// Runge-Kutta 2nd order integration:
    pos.x       += linear * cos(direction);
    pos.y       += linear * sin(direction);
    integrateYaw(angular);
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

void Odometry::reset(Position2d pos) {
    this->pos = pos;
}

/*
        * pi/2 a -pi/2 boarder function to integrate yaw
        * */
void Odometry::integrateYaw(double angular){
    pos.yaw +=angular;
    if(pos.yaw >M_PI){
        double dif = pos.yaw - M_PI;
        pos.yaw = -M_PI + dif;
    }
    else if (pos.yaw < -M_PI){
        double dif = pos.yaw + M_PI;
        pos.yaw = M_PI  + dif;
    }
}
