//
// Created by matejko on 20.2.2017.
//

#ifndef ROBOT_DEMO_DIFFERENCIALDRIVE_H
#define ROBOT_DEMO_DIFFERENCIALDRIVE_H


#include "odometry.h"
#include "irobotcreate.h"


class DifferencialDrive : public Odometry{
public:
    DifferencialDrive(Command &cmd, double ws);
    void updateCommand();
protected:
    Command &cmd;
    double ws;
    double wr;
private:

};


#endif //ROBOT_DEMO_DIFFERENCIALDRIVE_H
