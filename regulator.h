//
// Created by matejko on 20.2.2017.
//

#ifndef ROBOT_DEMO_REGULATOR_H
#define ROBOT_DEMO_REGULATOR_H

#include "types.h"

class Regulator {
public:
    Regulator() : goalActive(false){};
    virtual void setGoal(Position2d goal){
        this->goal = goal;
        goalActive = true;
    }
    virtual void update(Position2d currentPos) = 0;
protected:
    Position2d goal;
    bool goalActive;
};


#endif //ROBOT_DEMO_REGULATOR_H
