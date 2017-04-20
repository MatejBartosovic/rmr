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


}

QImage GlobalMap::getMap(){
    std::lock_guard<std::mutex> lock(mapLock);
    return map;
}
