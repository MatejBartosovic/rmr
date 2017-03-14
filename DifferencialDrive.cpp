//
// Created by matejko on 20.2.2017.
//

#include "DifferencialDrive.h"

DifferencialDrive::DifferencialDrive(Command &cmd, double ws,double acc) : cmd(cmd), ws(ws),limiter(cmd,acc){

}

void DifferencialDrive::updateCommand() {
    //if(cmd.commandType == Command::LinearAngular){
        cmd.leftVel  = (cmd.linear - cmd.angular * ws / 2.0);
        cmd.rightVel = (cmd.linear + cmd.angular * ws / 2.0);
        cmd.radius = cmd.linear / cmd.angular;
    //}
    limiter.enforce();
}
