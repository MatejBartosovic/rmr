//
// Created by matejko on 20.4.2017.
//

#include "GlobalMap.h"
GlobalMap::GlobalMap(int sizeX, int sizeY, double resolution,LaserMeasurement &scan) :
        resolution(resolution), xSquares(sizeX/resolution), ySquares(sizeY/resolution),
        xSquares_2(xSquares>>1), ySquares_2(ySquares>>1),map(xSquares,ySquares,QImage::Format_RGB32),scan(scan) {
    for (int i = 0; i < map.width(); i++)
        for (int j = 0; j < map.height(); j++)
            map.setPixel(i,j,qRgb(255, 255, 255));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

void GlobalMap::start() {
    QThread::start();
    timer->start(5000);
}

void GlobalMap::timerUpdate(){
    emit(newMap());
}

void GlobalMap::run() {
    while(1){
        std::unique_lock<std::mutex> lock(mapLock);
        updateCondition.wait(lock);
        data = scan; //data zo skenera
        lock.unlock();
        buildMap();
    }
}

void GlobalMap::update(Position2d pos){
    this->pos = pos;
    updateCondition.notify_all();
}

void GlobalMap::buildMap(){
    if(data.numberOfScans <0)
        return;
    for (int i = 0; i < data.numberOfScans; i++) {
        if(data.Data[i].scanDistance <5)
            continue;
        int x = (int)(cos(data.Data[i].scanAngle/180*M_PI + pos.yaw)*data.Data[i].scanDistance/100/resolution*1.45) +pos.x/resolution;
        int y = (int)(sin(data.Data[i].scanAngle/180*M_PI + pos.yaw)*data.Data[i].scanDistance/100/resolution*1.45) +pos.y/resolution;
        if(x>xSquares || y > ySquares)
            continue;
        QPoint obstacle(y,x);
        map.setPixel(obstacle,qRgb(0,0,0));
    }

}

QImage GlobalMap::getMap(){
    std::lock_guard<std::mutex> lock(mapLock);
    return map;
}
