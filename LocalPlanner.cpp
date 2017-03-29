//
// Created by matejko on 18.3.2017.
//
#include "LocalPlanner.h"

LocalPlanner::LocalPlanner(Command cmd, double angularStep, double stepCount, double linearP) : LocalMap(6,6,0.1),
                                                                                                Regulator(cmd),
                                                                                                linearP(linearP),
                                                                                                angularStep(angularStep),
                                                                                                stepCount(stepCount),
                                                                                                simTime(0.1),
                                                                                                flors(5){

}

void LocalPlanner::start() {
    LocalMap::start();
}

bool LocalPlanner::update(Position2d pos) {
    //printf("update local plnner !!!!!!!!!!!!!!!!!!!!!!!!!!\n");
#ifdef MAP
    //printf("updating map\n");
    LocalMap::update(pos);
    //printf("hotovo\n");
#endif
    if(goalActive) {
    }

}

void LocalPlanner::setLinearP(double p) {
    linearP = p;
}

