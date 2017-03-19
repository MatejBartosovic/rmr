//
// Created by matejko on 20.2.2017.
//

#include "positionRegulator2dCircular.h"
#include <math.h>

PositionRegulator2dCircular::PositionRegulator2dCircular(Command &cmd ) : Regulator(cmd){

}

bool PositionRegulator2dCircular::update(Position2d currentPos) {

    //calculate error
    double Ex = goal.x - currentPos.x;
    double Ey = goal.y - currentPos.y;
    double Elinear  = sqrt (pow(Ex,2) + pow(Ey,2));
    double Eangular = atan2(Ey,Ex);

    //stop if near goal position
    if(fabs(Elinear) < 0.05){
        cmd.leftVel = 0;
        cmd.rightVel = 0;
        cmd.commandType = Command::Motors;
        return true;
    }

    //turn in place
    if(fabs(Eangular) > 0.15){
        cmd.linear = 0;
        cmd.angular = 0.05;
        cmd.commandType = Command::LinearAngular;
        return true;
    }

    //go to target
    cmd.radius = Elinear/(2*sin(Eangular/2));
    cmd.linear = 0.25;
    cmd.commandType = Command::Radius;
    return true;
}