//
// Created by matejko on 18.3.2017.
//
#include "LocalPlanner.h"

LocalPlanner::LocalPlanner(Command &cmd, double angularStep, double stepCount, double linearP) : localMap(4,4,0.05,scan),
                                                                                                 globalMap(6,6,0.1,scan),
                                                                                                Regulator(cmd),
                                                                                                linearP(linearP),
                                                                                                angularStep(angularStep),
                                                                                                stepCount(stepCount),
                                                                                                simTime(0.3),
                                                                                                flors(4){

}

void LocalPlanner::start() {
#ifdef LIDAR
    lidar.connect("/dev/laser");
    lidar.enable();
    lidar.start();
#endif
    localMap.start();
    globalMap.start();
}

bool LocalPlanner::update(Position2d pos) {
    //printf("update local plnner !!!!!!!!!!!!!!!!!!!!!!!!!!\n");
#ifdef MAP
    #ifdef LIDAR
    scan = lidar.getMeasurement();
    localMap.update();
    globalMap.update(pos);
    #else
    localMap.update(pos);
    #endif
#endif
    if(goalActive) {
        double vel = getLinearVel(pos);
        if (vel==0){
            printf("~~~~~~~~~TARGET POSITION REACHED~~~~~~~~~~~~~~\n");
            Regulator::cancelGoal();
            return false;
        }
        //generate trajectories tree
        double distance = simTime * vel;
        std::vector<std::vector<trajectoryPoint>> trajectoryFlors(flors);
        trajectoryFlors.clear();

        std::vector<trajectoryPoint> currentTrajectoryPositions;
        currentTrajectoryPositions.push_back(trajectoryPoint(Position2d(),pos.vel,NULL));

        trajectoryFlors.push_back(currentTrajectoryPositions);
        currentTrajectoryPositions.clear();

        for (int i = 0; i < flors; i++) {
            for (int j = 0; j < trajectoryFlors[i].size(); j++) {
                for (int k = -stepCount; k <= stepCount; k++) {
                    odometry.reset(trajectoryFlors[i][j].pos);
                    double angularVel = (trajectoryFlors[i][j].vel.angular +  (k * angularStep));
                    double linearVel = getLinearVel(trajectoryFlors[i][j].pos);
                    //printf("sucasna rychlost %lf %lf k = %d\n",linearVel,angularVel,k);
                    odometry.update(linearVel*simTime, angularVel*simTime);
                    currentTrajectoryPositions.push_back(trajectoryPoint(odometry.getPos(), Velocity(vel,angularVel),&trajectoryFlors[i][j]));
                }
            }
            trajectoryFlors.push_back(currentTrajectoryPositions);
            currentTrajectoryPositions.clear();
        }

        //get map
        QImage otherMap = localMap.getMap();
        if(localMap.getObstacleDistance(Position2d(),otherMap)<0.2){
            printf("hmm skoro som nabural\n");
            Regulator::cancelGoal();
            return false;
        }
        //calculate distance and cost for each trajectory point
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        for (int i = 1; i < trajectoryFlors.size(); i++) {
            for (int j = 0; j < trajectoryFlors[i].size() ; j++) {
                trajectoryFlors[i][j].cost = 0;
                double obstacleDistance = localMap.getObstacleDistance(trajectoryFlors[i][j].pos,otherMap);
                double td = sqrt(pow(goal.x - (trajectoryFlors[i][j].pos.x*cos(trajectoryFlors[i][j].pos.yaw) + pos.x),2)+ pow(goal.y - (trajectoryFlors[i][j].pos.y*sin(trajectoryFlors[i][j].pos.yaw)+pos.y),2));
                //printf("robot pos %lf %lf ",pos.x,pos.y);
                //printf("pint pos %lf %lf %lf ",trajectoryFlors[i][j].pos.x,trajectoryFlors[i][j].pos.y,trajectoryFlors[i][j].pos.yaw);

                if(obstacleDistance > 2){
                    //printf("td = %lf\n",td);
                    if(i==trajectoryFlors.size()-1){
                        //trajectoryFlors[i][j].tdCost = 25*exp(td);
                        trajectoryFlors[i][j].tdCost = td;
                        trajectoryFlors[i][j].cost += trajectoryFlors[i][j].tdCost;
                    }
                    //printf("priamo %lf\n",td);
                }
                /*else if(obstacleDistance < 0.3){
                    trajectoryFlors[i][j].obstacleCost = 10000000;
                    trajectoryFlors[i][j].cost += trajectoryFlors[i][j].obstacleCost;
                }*/
                else {
                    //printf("obstace\n");
                    trajectoryFlors[i][j].obstacleCost = exp(0.5 / obstacleDistance);
                    trajectoryFlors[i][j].cost +=  trajectoryFlors[i][j].obstacleCost;
                    trajectoryFlors[i][j].tdCost = td;
                    trajectoryFlors[i][j].cost +=trajectoryFlors[i][j].tdCost;
                    //printf("blizko prekazky td = %lf exp = %lf\n",td,exp(0.3 / obstacleDistance)/10);
                }
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
            printf("%lf ",cost);
            costs.push_back(cost);
        }
        printf("\n");
        //chose the best trajectory
        std::vector<double>::iterator minElement = std::min_element(costs.begin(),costs.end());
        std::vector<trajectoryPoint*> trajectory(flors+1);
        trajectory.clear();

        trajectoryPoint* point = &trajectoryFlors.back()[std::distance(costs.begin(), minElement)];
        printf("trajectory:\n");
        while(point){
            trajectory.push_back(point);
            localMap.setPathPoint(QPoint(trajectory.back()->pos.x/localMap.resolution,trajectory.back()->pos.y/localMap.resolution));
            //printf("x = %lf y = %lf\n",point->pos.x,point->pos.y);
            point = point->parrent;
        }
        cmd.linear = trajectory[trajectory.size()- 2]->vel.linear;
        cmd.angular = trajectory[trajectory.size()- 2]->vel.angular;
        cmd.commandType = Command::Motors;
        printf("trajectory linear = %lf angular = %lf cost = %lf obstacle cost %lf distance cost =%lf\n",cmd.linear,cmd.angular,*minElement,trajectory[trajectory.size()- 2]->obstacleCost,trajectory[trajectory.size()- 2]->tdCost);
    }
}

void LocalPlanner::setLinearP(double p) {
    linearP = p;
}

double LocalPlanner::getLinearVel(Position2d p) {
    double Ex = goal.x - p.x;
    double Ey = goal.y - p.y;
    double Elinear = sqrt(pow(Ex, 2) + pow(Ey, 2));
    if(Elinear < 0.05){
        printf("~~~~~~~~~TARGET POSITION REACHED~~~~~~~~~~~~~~\n");
        printf("linear error = %lf\n",Elinear);
        return  0;
    }
    double vel = 0.5 * Elinear;
    if (vel > 0.3)
        vel = 0.3;
    if (vel < -0.3)
        vel = -0.3;
    return  vel;
}

