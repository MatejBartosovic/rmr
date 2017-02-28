//
// Created by matejko on 26.2.2017.
//

#include "positionRegulator2dLinear.h"
#include <math.h>
#include <stdio.h>

PositionRegulator2dLinear::PositionRegulator2dLinear(Command &cmd) : cmd(cmd), velCmd(0.025),angularCount(0),linearCount(0){

}

void PositionRegulator2dLinear::update(Position2d currentPos) {
    //calculate error
    if(goalActive){
        double Ex = goal.x - currentPos.x;
        double Ey = goal.y - currentPos.y;
        double Elinear  = sqrt (pow(Ex,2) + pow(Ey,2));
        double goalAngular = atan2(Ey,Ex);
        double Eangular = goalAngular - currentPos.yaw;
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("pos x = %lf, posy = %lf yaw = %lf goal yaw = %lf angular error %lf\n",currentPos.x,currentPos.y,currentPos.yaw,goalAngular,Eangular);
        //stop if near goal position
        if(fabs(Elinear) < 0.05){
            cmd.leftVel = 0;
            cmd.rightVel = 0;
            cmd.linear = 0;
            cmd.angular = 0;
            cmd.commandType = Command::Motors;
            printf("!!!!!!!!!!!! TARGET POSITION REACHED !!!!!!!!!!!!! \n" );
            printf("linear error = %lf \n",Elinear);
            printf("angular count = %d linear count =%d\n",angularCount,linearCount);
            goalActive = false;
            return;
        }

        //turn in place
        if(fabs(Eangular) > 0.15){
            cmd.linear = 0;
            cmd.angular = 0.05 * fabs(Eangular)/Eangular;
            printf("Eangular = %lf\n",Eangular);
            angularCount++;
            cmd.commandType = Command::LinearAngular;
            return;
        }

        //transform current vel to world frame
        double currentVelX = cos(currentPos.yaw) * velCmd;
        double currentVelY = sin(currentPos.yaw) * velCmd;

        //calculate goal velocity in each axis
        double velP = 5;
        double goalVelX = Ex * velP;
        double goalVelY = Ey * velP;

        double eVelX = goalVelX - currentVelX;
        double eVelY = goalVelY - currentVelY;

        double angularP = 0.2;
        cmd.angular = ( eVelY/eVelX -1) * angularP;
        cmd.linear = velCmd;
        linearCount++;
        cmd.commandType = Command::LinearAngular;
    }

}