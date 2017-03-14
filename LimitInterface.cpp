//
// Created by matejko on 14.3.2017.
//

#include "LimitInterface.h"
LimitInterface::LimitInterface(Command &cmd, double acc) :cmd(cmd), acc(acc), lastLeftVel(0), lastRightVel(0){
}
void LimitInterface::enforce() {
    int dif = cmd.leftVel - lastLeftVel;
    if(dif > acc)
        cmd.leftVel = lastLeftVel + acc;
    if(dif < -acc)
        cmd.leftVel = lastLeftVel - acc;

    dif = cmd.rightVel - lastRightVel;
    if(dif > acc)
        cmd.rightVel = lastRightVel + acc;
    if(dif < -acc)
        cmd.rightVel = lastRightVel - acc;
}

