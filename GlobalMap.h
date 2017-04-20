//
// Created by matejko on 20.4.2017.
//

#ifndef ROBOT_DEMO_GLOBALMAP_H
#define ROBOT_DEMO_GLOBALMAP_H

#include <QThread>
#include <QImage>
#include <QTimer>
#include "rplidar.h"
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
    QImage map;
    QTimer *timer;
    void run();
    void start();
protected slots:
    void timerUpdate();
};


#endif //ROBOT_DEMO_GLOBALMAP_H
