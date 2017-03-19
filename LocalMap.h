//
// Created by matejko on 15.3.2017.
//

#ifndef ROBOT_DEMO_LOCALMAP_H
#define ROBOT_DEMO_LOCALMAP_H

#include "rplidar.h"
#include <thread>
#include <vector>
#include <mutex>
#include <math.h>
#include "types.h"
#include <QThread>
#include <QLabel>
#include <QObject>

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
signals:
    void newMap();

private:
    void buildMap();

    void resetLastMap();
    rplidar lidar;
protected:
    std::mutex mapLock;
    int xSquares;
    int ySquares;
    int xSquares_2;
    int ySquares_2;
    double resolution;
    Position2d pos;
    QImage map;
    std::vector<QPoint> lastMap;

};



#endif //ROBOT_DEMO_LOCALMAP_H
