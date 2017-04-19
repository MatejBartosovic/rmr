//
// Created by matejko on 18.3.2017.
//

#ifndef ROBOT_DEMO_LOCALPLANNER_H
#define ROBOT_DEMO_LOCALPLANNER_H

#include "LocalMap.h"
#include "regulator.h"
#include "odometry.h"

struct trajectoryPoint;
struct trajectoryPoint{
public:
    Position2d pos;
    Velocity vel;
    double cost;
    trajectoryPoint* parrent;
    trajectoryPoint(Position2d pos, Velocity vela, trajectoryPoint* parrent) : pos(pos), vel(vela), parrent(parrent) {}
};

class LocalPlanner : public LocalMap, public Regulator{
public:
    //cmd pointer to robot command
    //angularStep step betwen generatd trajectories points
    //stepCount count of angular steps in positive and negative direction
    //note: ((stemCount * angularStep)  / period) is max alloved acceleration
    LocalPlanner(Command &cmd, double angularStep = 0.1, double stepCount = 1, double linearP = 0.5);
    void setLinearP(double p);
    void start();
    bool update(Position2d pos);

private:
    //parameters
    double angularStep;
    double stepCount;
    double simTime;
    int flors;
    double linearP;
    Odometry odometry;

};


#endif //ROBOT_DEMO_LOCALPLANNER_H
