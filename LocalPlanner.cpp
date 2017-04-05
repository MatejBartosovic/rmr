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
    LocalMap::update(pos);
#endif
    /*if(goalActive) {
        double Ex = goal.x - pos.x;
        double Ey = goal.y - pos.y;
        double Elinear = sqrt(pow(Ex, 2) + pow(Ey, 2));

        /

	//if(Elinear < 0.05){
           // printf("~~~~~~~~~TARGET POSITION REACHED~~~~~~~~~~~~~~\n");
           // printf("linear error = %lf\n",Elinear);
           // cancelGoal();
         //   return  true;
       // }
        double vel = 0.5 * Elinear;
        if (vel > 0.3)
            vel = 0.3;
        if (vel < -0.3)
            vel = -0.3;

        //generate trajectories tree
        double distance = simTime * vel;
        std::vector<std::vector<trajectoryPoint>> trajectoryFlors(flors);
        trajectoryFlors.clear();

        std::vector<trajectoryPoint> currentTrajectoryPositions;
        currentTrajectoryPositions.push_back(trajectoryPoint(pos,NULL));

        trajectoryFlors.push_back(currentTrajectoryPositions);
        currentTrajectoryPositions.clear();

        for (int i = 0; i < flors; i++) {

            for (int j = 0; j < trajectoryFlors[i - 1].size(); j++) {
                for (int k = -stepCount; k <= stepCount; k++) {
                    odometry.reset(trajectoryFlors[i][j].pos);
                    double angle = simTime * k * angularStep;
                    odometry.update(distance, angle, simTime);
                    currentTrajectoryPositions.push_back(trajectoryPoint(odometry.getPos(), &trajectoryFlors[i - 1][j]));
                }
            }
            trajectoryFlors.push_back(currentTrajectoryPositions);
            currentTrajectoryPositions.clear();
        }

        //get map
        QImage map = LocalMap::getMap();

        //calculate distance and cost for each trajectory point
        for (int i = 0; i < trajectoryFlors.size(); i++) {
            for (int j = 0; j < trajectoryFlors[i].size() ; j++) {
                double obstacleDistance = getObstacleDistance(trajectoryFlors[i][j].pos,map);
                //todo zefektivnit vypocet ak je bod nevhodny

                // * cost function here
                
                 
                //trajectoryFlors[i][j].
            }
        }
        int lastRow = trajectoryFlors.size()-1;
        std::vector<double> costs(trajectoryFlors[lastRow].size());
        costs.clear();

        //sum cost to each trajectory
        for (int i = 0; i < trajectoryFlors[lastRow].size(); i++) {
            double cost = 0;
            trajectoryPoint* currentTrajectoryPoint = &trajectoryFlors[lastRow][i];
            while(currentTrajectoryPoint){
                cost +=currentTrajectoryPoint->cost;
                currentTrajectoryPoint = currentTrajectoryPoint->parrent;
            }
            costs.push_back(cost);
        }
        //chose the best trajectory
        std::vector<double>::iterator minElement = std::min_element(costs.begin(),costs.end());
        printf("minimum %lf\n",*minElement);
    }*/

}

void LocalPlanner::setLinearP(double p) {
    linearP = p;
}

