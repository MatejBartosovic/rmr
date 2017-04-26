//
// Created by matejko on 18.3.2017.
//

#ifndef ROBOT_DEMO_LOCALPLANNER_H
#define ROBOT_DEMO_LOCALPLANNER_H

#include "LocalMap.h"
#include "GlobalMap.h"
#include "regulator.h"
#include "odometry.h"

struct trajectoryPoint;
struct trajectoryPoint{
public:
    Position2d pos;
    Velocity vel;
    double cost;
    double tdCost;
    double obstacleCost;
    trajectoryPoint* parrent;
    trajectoryPoint(Position2d pos, Velocity vela, trajectoryPoint* parrent) : pos(pos), vel(vela), parrent(parrent) {}
};

class LocalPlanner : public Regulator{
public:
    //cmd pointer to robot command
    //angularStep step betwen generatd trajectories points
    //stepCount count of angular steps in positive and negative direction
    //note: ((stemCount * angularStep)  / period) is max alloved acceleration
    LocalPlanner(Command &cmd, double angularStep = 0.1, double stepCount = 3, double linearP = 0.5);
    void setLinearP(double p);
    void start();
    bool update(Position2d pos);
    GlobalMap globalMap;
    LocalMap localMap;

private:
    double getLinearVel(Position2d p);
    //parameters
    double angularStep;
    double stepCount;
    double simTime;
    int flors;
    double linearP;
    Odometry odometry;
    LaserMeasurement scan;
    rplidar lidar;
};


#endif //ROBOT_DEMO_LOCALPLANNER_H
