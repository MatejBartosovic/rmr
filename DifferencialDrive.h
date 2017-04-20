//
// Created by matejko on 20.2.2017.
//

#ifndef ROBOT_DEMO_DIFFERENCIALDRIVE_H
#define ROBOT_DEMO_DIFFERENCIALDRIVE_H


#include "odometry.h"
#include "irobotcreate.h"
#include "LimitInterface.h"

class DifferencialDrive : public Odometry{
public:
    DifferencialDrive(Command &cmd, double ws, double acc);
    void updateCommand();
protected:
    Command &cmd;
    double ws;
    LimitInterface limiter;
private:

};


#endif //ROBOT_DEMO_DIFFERENCIALDRIVE_H
