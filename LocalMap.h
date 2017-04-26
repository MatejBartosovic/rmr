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

struct MapPoint{
public:
    int x;
    int y;
    MapPoint(int x,int y) : x(x),y(y){

    }
    MapPoint() : x(0),y(0){

    }
};

class LocalMap : public QThread{
public:
Q_OBJECT
public:
    LocalMap(int sizeX, int sizeY,double resolution,LaserMeasurement &scan);
    void start();
    void update(Position2d pos);
    void update();
    void run();
    void stop();
    QImage getMap();
    void setPathPoint(QPoint point);
    void setPath(std::vector<QPoint> path);
    ~LocalMap();
    double getObstacleDistance(Position2d pos, QImage &otherMap);
    int xSquares;
    int ySquares;
    int xSquares_2;
    int ySquares_2;
    double resolution;
signals:
    void newMap();

private:
    void buildMap();
    void buildGlobalMap(LaserMeasurement otherScan);
    void resetLastMap();
protected:
    std::mutex mapLock;
    std::condition_variable updateCondition;
    Position2d pos;
    QImage map;
    std::vector<QPoint> lastMap;
    std::vector<QPoint> lastPath;
    QTimer *timer;
    LaserMeasurement &scan;
protected slots:
    void timerUpdate();
};



#endif //ROBOT_DEMO_LOCALMAP_H
