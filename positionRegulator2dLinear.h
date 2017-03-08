//
// Created by matejko on 26.2.2017.
//

#ifndef ROBOT_DEMO_POSITIONREGULATOR2DLINEAR_H
#define ROBOT_DEMO_POSITIONREGULATOR2DLINEAR_H

#include "regulator.h"
#include "types.h"

class PositionRegulator2dLinear : public Regulator{
public:
    PositionRegulator2dLinear(Command &cmd);
    void update(Position2d currentPos);
    void setAngularP(double p);
    void setLinearP(double p);
protected:
    Command &cmd;
    double velCmd;
    double Pa;
    double Pl;
private:
    int angularCount;
    int linearCount;
};


#endif //ROBOT_DEMO_POSITIONREGULATOR2DLINEAR_H
