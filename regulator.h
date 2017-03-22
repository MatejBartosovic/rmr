//
// Created by matejko on 20.2.2017.
//

#ifndef ROBOT_DEMO_REGULATOR_H
#define ROBOT_DEMO_REGULATOR_H

#include "types.h"

class Regulator {
public:
    Regulator(Command &cmd) : goalActive(false),cmd(cmd){}
    virtual void setGoal(Position2d goal){
        this->goal = goal;
        goalActive = true;
    }
    void cancelGoal(){
        cmd.linear = 0;
        cmd.angular = 0;
        cmd.leftVel = 0;
        cmd.rightVel = 0;
        cmd.commandType = Command::Motors;
        goalActive = false;
    }
    virtual bool update(Position2d currentPos) = 0;
protected:
    Position2d goal;
    Command &cmd;
    bool goalActive;
};


#endif //ROBOT_DEMO_REGULATOR_H
