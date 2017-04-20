//
// Created by matejko on 22.3.2017.
//
#include "odometry.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    printf("idem\n");
    Odometry a;
    /*a.update(M_PI,M_PI/2);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());
    a.update(M_PI,-M_PI/2);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());
    a.update(2.5,0);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());
    a.update(M_PI,-M_PI/2);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());
    a.update(M_PI,M_PI/2);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());
    a.update(2.5,0);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());*/

    a.update(0.8,0.1);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());

    a.update(0.8,0.1);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());

    a.update(0.8,-0.3);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());

    a.update(3,0);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());

    a.update(2,0.4);
    printf("x= %lf y = %lf yaw = %lf\n",a.getX(),a.getY(),a.getYaw());



    return 0;
}