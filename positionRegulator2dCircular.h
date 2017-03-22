//
// Created by matejko on 20.2.2017.
//

#ifndef ROBOT_DEMO_POSITIONREGULATOR2DCIRCULAR_H
#define ROBOT_DEMO_POSITIONREGULATOR2DCIRCULAR_H

#include "regulator.h"
#include "types.h"

class PositionRegulator2dCircular : public  Regulator{
public:
    PositionRegulator2dCircular(Command &cmd);
    bool update(Position2d currentPos);

};


#endif //ROBOT_DEMO_POSITIONREGULATOR2D_H
