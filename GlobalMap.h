//
// Created by matejko on 20.4.2017.
//

#ifndef ROBOT_DEMO_GLOBALMAP_H
#define ROBOT_DEMO_GLOBALMAP_H

#include <QThread>
#include <QImage>
#include <QTimer>
#include "rplidar.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "types.h"
class GlobalMap : public QThread{
public:
Q_OBJECT
public:
    GlobalMap(int sizeX, int sizeY,double resolution,LaserMeasurement &scan);
    int xSquares;
    int ySquares;
    int xSquares_2;
    int ySquares_2;
    double resolution;
    LaserMeasurement &scan;
    LaserMeasurement data;
    QImage map;
    QTimer *timer;
    void run();
    void start();
    void update(Position2d pos);
    QImage getMap();
signals:
    void newMap();
private:
    void buildMap();
    std::mutex mapLock;
    std::condition_variable updateCondition;
    Position2d pos;
protected slots:
    void timerUpdate();

};


#endif //ROBOT_DEMO_GLOBALMAP_H
