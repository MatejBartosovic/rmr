//
// Created by matejko on 18.3.2017.
//

#include "LocalPlanner.h"

LocalPlanner::LocalPlanner(Command cmd) : LocalMap(6,6,0.1), Regulator(cmd){

}

void LocalPlanner::start() {
    LocalMap::start();
}

bool LocalPlanner::update(Position2d currentPos) {
    LocalMap::update(currentPos);
}