//
// Created by matejko on 18.3.2017.
//
#include "LocalPlanner.h"

LocalPlanner::LocalPlanner(Command &cmd, double angularStep, double stepCount, double linearP) : LocalMap(6,6,0.1),
                                                                                                Regulator(cmd),
                                                                                                linearP(linearP),
                                                                                                angularStep(angularStep),
                                                                                                stepCount(stepCount),
                                                                                                simTime(1),
                                                                                                flors(3){

}

void LocalPlanner::start() {
    LocalMap::start();
}

bool LocalPlanner::update(Position2d pos) {
    //printf("update local plnner !!!!!!!!!!!!!!!!!!!!!!!!!!\n");
#ifdef MAP
    #ifdef LIDAR
    LocalMap::update();
    #else
    LocalMap::update(pos);
    #endif
#endif
    if(goalActive) {
        double Ex = goal.x - pos.x;
        double Ey = goal.y - pos.y;
        double Elinear = sqrt(pow(Ex, 2) + pow(Ey, 2));

        if(Elinear < 0.05){
            printf("~~~~~~~~~TARGET POSITION REACHED~~~~~~~~~~~~~~\n");
            printf("linear error = %lf\n",Elinear);
            cancelGoal();
            return  true;
        }
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
        printf("robot ide %lf %lf\n",pos.vel.linear,pos.vel.angular);
        currentTrajectoryPositions.push_back(trajectoryPoint(Position2d(),pos.vel,NULL));

        trajectoryFlors.push_back(currentTrajectoryPositions);
        currentTrajectoryPositions.clear();

        for (int i = 0; i < flors; i++) {
            for (int j = 0; j < trajectoryFlors[i].size(); j++) {
                for (int k = -stepCount; k <= stepCount; k++) {
                    odometry.reset(trajectoryFlors[i][j].pos);
                    double angularVel = (trajectoryFlors[i][j].vel.angular +  k * angularStep);
                    printf("sucasna rychlost %lf %lf",trajectoryFlors[i][j].vel.linear,trajectoryFlors[i][j].vel.angular);
                    odometry.update(distance, angularVel*simTime);
                    printf("trajectory generation vel = %lf %lf\n",vel,angularVel);
                    currentTrajectoryPositions.push_back(trajectoryPoint(odometry.getPos(), Velocity(vel,angularVel),&trajectoryFlors[i][j]));
                }
            }
            trajectoryFlors.push_back(currentTrajectoryPositions);
            currentTrajectoryPositions.clear();
        }

        //get map
        QImage otherMap = LocalMap::getMap();

        //calculate distance and cost for each trajectory point
        for (int i = 1; i < trajectoryFlors.size(); i++) {
            for (int j = 0; j < trajectoryFlors[i].size() ; j++) {
                double obstacleDistance = getObstacleDistance(trajectoryFlors[i][j].pos,otherMap);
                double td = sqrt(pow(goal.x -trajectoryFlors[i][j].pos.x,2)+pow(goal.y - trajectoryFlors[i][j].pos.y,2));
                if(obstacleDistance > 2)
                    trajectoryFlors[i][j].cost = td;
                else if(obstacleDistance < 0.2){
                    cancelGoal();
                    printf("hmm skoro som nabural\n goal cancelled\n");
                }
                else
                    trajectoryFlors[i][j].cost = exp(0.3/obstacleDistance) + td ;
                //printf("odstacle distance = %lf target distance = %lf\n",obstacleDistance,d);
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
        std::vector<trajectoryPoint*> trajectory(flors+1);

        trajectoryPoint* point = &trajectoryFlors.back()[std::distance(costs.begin(), minElement)];
        while(point){
            trajectory.push_back(point);
            point = point->parrent;
        }

        cmd.linear = trajectory[trajectory.size()- 2]->vel.linear;
        cmd.angular = trajectory[trajectory.size()- 2]->vel.angular;
        cmd.commandType = Command::Motors;
        printf("minimum %lf vel = %lf %lf\n",*minElement,cmd.linear,cmd.angular);
    }
}

void LocalPlanner::setLinearP(double p) {
    linearP = p;
}

