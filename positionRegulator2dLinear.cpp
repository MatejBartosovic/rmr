//
// Created by matejko on 26.2.2017.
//

#include "positionRegulator2dLinear.h"
#include <math.h>
#include <stdio.h>

PositionRegulator2dLinear::PositionRegulator2dLinear(Command &cmd) : Regulator(cmd), velCmd(0.025),angularCount(0),linearCount(0),Pa(1.5),Pl(0.5){

}

bool PositionRegulator2dLinear::update(Position2d currentPos) {
    //calculate error
    if(goalActive){
        double Ex = goal.x - currentPos.x;
        double Ey = goal.y - currentPos.y;
        double Elinear  = sqrt (pow(Ex,2) + pow(Ey,2));
        double goalAngular = atan2(Ey,Ex);
        double Eangular = goalAngular - currentPos.yaw;

        /*
         * pi and -pi boarder
         * */
       if(Eangular < -5.5)
            Eangular =  (2*M_PI+Eangular);
        if(Eangular > 5.5)
            Eangular =  -(2*M_PI-Eangular);

        //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        //printf("pos x = %lf, posy = %lf yaw = %lf goal yaw = %lf angular error %lf\n",currentPos.x,currentPos.y,currentPos.yaw,goalAngular,Eangular);
        //stop if near goal position
        if(fabs(Elinear) < 0.05){
            cancelGoal();
            printf("!!!!!!!!!!!! TARGET POSITION REACHED !!!!!!!!!!!!! \n" );
            printf("linear error = %lf \n",Elinear);
            return true;
        }

        //turn in place
        double absEangular = fabs(Eangular);
        if( absEangular > 0.15){
            cmd.linear = 0;
            //cmd.angular = 0.05 * fabs(Eangular)/Eangular;
            cmd.angular = 0.8 * absEangular/Eangular;
            printf("Eangular = %lf\n",Eangular);
            angularCount++;
            cmd.commandType = Command::LinearAngular;
            return true;
        }

        //transform current vel to world frame
        /*double currentVelX = cos(currentPos.yaw) * velCmd;
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

        cmd.commandType = Command::LinearAngular;*/
        cmd.angular = Eangular*Pa;
        cmd.linear = Elinear *Pl;
        cmd.commandType = Command::LinearAngular;

        //printf("linear command = %lf angular command =%lf\n",cmd.linear,cmd.angular);
        if (fabs(cmd.linear) > 0.3)
            cmd.linear = 0.3 * (cmd.linear/fabs(cmd.linear));

        if (fabs(cmd.linear) < 0.1)
            cmd.linear = 0.1 * (cmd.linear/fabs(cmd.linear));
        if(cmd.angular == 0)
            return true;
        if (fabs(cmd.angular) > 0.5)
            cmd.angular = 0.5 * (cmd.angular/fabs(cmd.angular));
        if(fabs(cmd.angular) < 0.15)
            cmd.angular = 0.15 * (cmd.angular/fabs(cmd.angular));
        //printf("linear command = %lf angular command =%lf\n",cmd.linear,cmd.angular);

    }
    return true;
}

void PositionRegulator2dLinear::setAngularP(double p) {
    Pa = p;
}

void PositionRegulator2dLinear::setLinearP(double p) {
    Pl = p;
}

