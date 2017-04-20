//
// Created by matejko on 15.3.2017.
//

#ifndef ROBOT_DEMO_LOCALMAP_H
#define ROBOT_DEMO_LOCALMAP_H

#include "rplidar.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <math.h>
#include "types.h"
#include <QThread>
#include <QLabel>
#include <QTimer>
class LocalMap : public QThread{
public:
Q_OBJECT
public:
    LocalMap(int sizeX, int sizeY,double resolution,LaserMeasurement &scan);
    void start();
    void update(Position2d pos);
    void update();
    void run();
    void globalMapRun();
    void stop();
    QImage getMap();
    ~LocalMap();
    double getObstacleDistance(Position2d pos, QImage &otherMap);
signals:
    void newMap();

private:
    void buildMap();
    void buildGlobalMap(LaserMeasurement otherScan);
    void resetLastMap();
protected:
    std::mutex mapLock;
    std::condition_variable updateCondition;
    std::mutex globalMapLock;
    std::condition_variable globalUpdateCondition;
    int xSquares;
    int ySquares;
    int xSquares_2;
    int ySquares_2;
    double resolution;
    Position2d pos;
    QImage map;
    std::vector<QPoint> lastMap;
    QTimer *timer;
    LaserMeasurement &scan;
protected slots:
    void timerUpdate();
};



#endif //ROBOT_DEMO_LOCALMAP_H
