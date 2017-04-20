//
// Created by matejko on 14.3.2017.
//

#ifndef ROBOT_DEMO_LIMITINTERFACE_H
#define ROBOT_DEMO_LIMITINTERFACE_H

#include "types.h"

class LimitInterface {
public:
    LimitInterface(Command &cmd, double acc);
    void enforce();

private:
    double acc;
    int lastLeftVel;
    int lastRightVel;
    Command cmd;
};

#endif //ROBOT_DEMO_LIMITINTERFACE_H
