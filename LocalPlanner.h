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
    double cost;
    trajectoryPoint* parrent;
    trajectoryPoint(Position2d pos,trajectoryPoint* parrent) : pos(pos), parrent(parrent) {}
};

class LocalPlanner : public LocalMap, public Regulator{
public:
    LocalPlanner(Command cmd, double maxAngularChange = 0.6, double stepCount = 3, double linearP = 0.5);
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
