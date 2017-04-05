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
    LocalMap(int sizeX, int sizeY,double resolution);
    void start();
    void update(Position2d pos);
    void run();
    void stop();
    QImage getMap();
    ~LocalMap();
    double getObstacleDistance(Position2d pos, QImage &map);
signals:
    void newMap();

private:
    void buildMap();
    void resetLastMap();
    rplidar lidar;
protected:
    std::mutex mapLock;
    std::condition_variable updateCondition;
    int xSquares;
    int ySquares;
    int xSquares_2;
    int ySquares_2;
    double resolution;
    Position2d pos;
    QImage map;
    std::vector<QPoint> lastMap;
    QTimer *timer;
protected slots:
    void timerUpdate();
};



#endif //ROBOT_DEMO_LOCALMAP_H
