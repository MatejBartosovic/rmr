//
// Created by matejko on 18.3.2017.
//

#include "LocalMap.h"

LocalMap::LocalMap(int sizeX, int sizeY, double resolution) :
        resolution(resolution), xSquares(sizeX/resolution), ySquares(sizeY/resolution),
        xSquares_2(xSquares>>1), ySquares_2(ySquares>>1),map(xSquares,ySquares,QImage::Format_RGB32) {
    for (int i = 0; i < map.width(); i++)
        for (int j = 0; j < map.height(); j++)
            map.setPixel(i,j,qRgb(255, 255, 255));
}

void LocalMap::start() {
    if(REAL_ROBOT)
        lidar.start();
    QThread::start();
}

void LocalMap::run() {
    while(true){
        buildMap();
        if(!REAL_ROBOT)
            usleep(100000);
    }
}

void LocalMap::update(Position2d pos){
    this->pos = pos;
}

void LocalMap::stop() {
    lidar.stop();
    QThread::quit();
}

QImage LocalMap::getMap() {
    //std::lock_guard<std::mutex> lock(mapLock);
    return map;
}

LocalMap::~LocalMap() {
    this->stop();
}

void LocalMap::buildMap() {


    resetLastMap();

    if( REAL_ROBOT){
        LaserMeasurement scan = lidar.getMeasurement();
        for (int i = 0; i < scan.numberOfScans; i++) {
            int x = (int)cos(scan.Data->scanAngle)*scan.Data->scanDistance/resolution +xSquares_2;
            int y = (int)sin(scan.Data->scanAngle)*scan.Data->scanDistance/resolution +ySquares_2;
            QPoint obstacle(y,x);
            map.setPixel(obstacle,qRgb(0,0,0));
            lastMap.push_back(obstacle);
        }
    }
    else{
        //fake map building
        //mapLock.lock();
        for(int i=0;i<=10;i++){
            //line simulator
            double x = 2 - pos.x;
            double y = ((-0.5+0.1*i) +pos.y);
            QPoint obstacle(xSquares_2 + (sin(pos.yaw)*x + cos(pos.yaw)*y)/resolution,ySquares_2-(cos(pos.yaw)*x -sin(pos.yaw)*y)/resolution);
            lastMap.push_back(obstacle);
            map.setPixel(obstacle,qRgb(0,0,0));
        }
        QPoint robot(0+xSquares_2,0+ySquares_2);
        map.setPixel(robot,qRgb(255, 0,0));
        //mapLock.unlock();

        emit(newMap()); //print new map
    }
}

void LocalMap::resetLastMap() {
    for (int i = 0; i < lastMap.size(); i++) {
        map.setPixel(lastMap[i],qRgb(255, 255,255));
    }
    lastMap.clear();
}
