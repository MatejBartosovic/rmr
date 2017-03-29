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
#ifdef LIDAR
    lidar.connect("/dev/laser");
    lidar.enable();
    lidar.start();
#endif
    QThread::start();
}

void LocalMap::run() {
    while(true){
        std::unique_lock<std::mutex> lock(mapLock);

        updateCondition.wait(lock); //vat to new position
        printf("mam noify\n");
        buildMap();
        printf("mapa hotova'\n");
    }
}

void LocalMap::update(Position2d pos){
    {
        //std::lock_guard<std::mutex> lock(mapLock);
        this->pos = pos;
        printf("notify\n");
        updateCondition.notify_all();
        printf("notify hotovo \n");
    } // out of scope will be lock released


}

void LocalMap::stop() {
    lidar.stop();
    QThread::quit();
}

QImage LocalMap::getMap() {
    //std::lock_guard<std::mutex> lock(mapLock);
    return map.copy();
}

LocalMap::~LocalMap() {
    this->stop();
}

void LocalMap::buildMap() {


    resetLastMap();
#ifdef LIDAR
    printf("start\n");
    LaserMeasurement scan = lidar.getMeasurement();
    printf("mam %d bodov\n",scan.numberOfScans);
    if(scan.numberOfScans <0)
        return;
    printf("locking\n");
    mapLock.lock();
    for (int i = 0; i < scan.numberOfScans; i++) {
        int x = (int)(cos(scan.Data[i].scanAngle/180*M_PI)*scan.Data[i].scanDistance/100/resolution) +xSquares_2;
        int y = (int)(sin(scan.Data[i].scanAngle/180*M_PI)*scan.Data[i].scanDistance/100/resolution) +ySquares_2;
        QPoint obstacle(10,10);
        map.setPixel(obstacle,qRgb(0,0,0));
        printf("x= %d y = %d\ndistance + %lf angle = %lf\n",x,y, scan.Data[i].scanDistance,scan.Data[i].scanAngle);
        lastMap.push_back(obstacle);
    }
    printf("unlocking\n");
    mapLock.unlock();
#else
    //fake map building
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
#endif
        //emit new map
    printf("emitting !!!!!!!!!!!!!!!!!!!!!!!!!!\n");
     emit(newMap());
}

void LocalMap::resetLastMap() {
    for (int i = 0; i < lastMap.size(); i++) {
        map.setPixel(lastMap[i],qRgb(255, 255,255));
    }
    lastMap.clear();
}

double LocalMap::getObstacleDistance(Position2d pos, QImage &other_map) {


    int targetOffSet = 1.05/resolution;
    //2m x 2m hladanie robot je v strede (1,1)
    int xObstacle = -1;
    int yObstacle = -1;
    //std::lock_guard<std::mutex> lock(mapLock);
    for(int i = 1;i<=targetOffSet;i++){
        //check fron
        for (int j = 0; j <= i ; j++) {
            //prava strana v predu
            if(other_map.pixel(xSquares_2 +j,ySquares_2-i)==0xff000000) { //0xff000000 je cierna
                //printf("prekazka pred: ");
                //printf(" pred locking for obstacle x = %d, y = %d %x\n", xSquares_2 + j, ySquares_2 - i,other_map.pixel(xSquares_2 + j, ySquares_2 - i));
                xObstacle = xSquares_2 +j;
                yObstacle = ySquares_2-i;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                goto KONEC;
            }
            //lava strana v predu
            if(other_map.pixel(xSquares_2 -j,ySquares_2-i)==0xff000000) {
                //printf("prekazka pred: ");
                //printf(" pred locking for obstacle x = %d, y = %d %x\n", xSquares_2 - j, ySquares_2 - i,other_map.pixel(xSquares_2 + j, ySquares_2 - i));
                xObstacle = xSquares_2 -j;
                yObstacle = ySquares_2-i;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                goto KONEC;
            }
        }
        //check left
        for (int j = ySquares_2; j > xSquares_2 - i ; j--){
            if(other_map.pixel(xSquares_2 -i,j)==0xff000000) {
                //printf("prekazka lava: ");
                //printf("boky lave locking for obstacle x = %d, y = %d %x\n",xSquares_2-i,j,other_map.pixel(xSquares_2-i,j));
                xObstacle = xSquares_2 -i;
                yObstacle = j;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                goto KONEC;
            }
        }
        //check right
        for (int j = ySquares_2; j > xSquares_2 - i ; j--){
            if(other_map.pixel(xSquares_2 -i,j)==0xff000000){
                //printf("prekazka prava: ");
                //printf("boky prave locking for obstacle x = %d, y = %d %x\n",xSquares_2+i,j,other_map.pixel(xSquares_2-i,j));
                xObstacle = xSquares_2 +i;
                yObstacle = j;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                goto KONEC;
            }
        }
    }
    KONEC: if(xObstacle>0){
        //printf("nearest obstacle x= %d y = %d\n",xObstacle,yObstacle);
        double obstacleDistance = sqrt(pow(xSquares_2-xObstacle,2) + pow(ySquares_2-yObstacle,2));
        printf("nearest obstacle distance = %lf\n",obstacleDistance);
        return obstacleDistance;
    }

}
