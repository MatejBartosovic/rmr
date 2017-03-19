//
// Created by matejko on 18.3.2017.
//

#ifndef ROBOT_DEMO_LOCALPLANNER_H
#define ROBOT_DEMO_LOCALPLANNER_H

#include "LocalMap.h"
#include "regulator.h"

class LocalPlanner : public LocalMap, public Regulator{
public:
    LocalPlanner(Command cmd);
    void start();
    bool update(Position2d currentPos);

};


#endif //ROBOT_DEMO_LOCALPLANNER_H
