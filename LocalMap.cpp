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
    timer = new QTimer(this);
 connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

void LocalMap::start() {
#ifdef LIDAR
    lidar.connect("/dev/laser");
    lidar.enable();
    lidar.start();
#endif
    QThread::start();
    timer->start(1000);
}

void LocalMap::run() {
    while(true){
        std::unique_lock<std::mutex> lock(mapLock);
        updateCondition.wait(lock); //vat to new position
        buildMap();
    }
}

void LocalMap::update(Position2d pos){
    {
        std::lock_guard<std::mutex> lock(mapLock);
        this->pos = pos;
        updateCondition.notify_all();
    } // out of scope will be lock released
}

void LocalMap::update(){
        //std::lock_guard<std::mutex> lock(mapLock);
        updateCondition.notify_all();
}

void LocalMap::stop() {
    lidar.stop();
    QThread::quit();
}

QImage LocalMap::getMap() {
    std::lock_guard<std::mutex> lock(mapLock);
    return map;
}

LocalMap::~LocalMap() {
    this->stop();
}

void LocalMap::buildMap() {


    //resetLastMap();
#ifdef LIDAR
    LaserMeasurement scan = lidar.getMeasurement();
struct timeval tp;
gettimeofday(&tp, NULL);

    printf("mam %d bodov sec = %d usec = %d\n",scan.numberOfScans,tp.tv_sec,tp.tv_usec);
if(scan.numberOfScans <0)
        return;
    resetLastMap();
    for (int i = 0; i < scan.numberOfScans; i++) {
	if(scan.Data[i].scanDistance <10)
		continue;
        int x = (int)(cos(scan.Data[i].scanAngle/180*M_PI)*scan.Data[i].scanDistance/100/resolution*1.45) +xSquares_2;
        int y = (int)(sin(scan.Data[i].scanAngle/180*M_PI)*scan.Data[i].scanDistance/100/resolution*1.45) +ySquares_2;
        if(x>xSquares || y > ySquares)
		continue;
	QPoint obstacle(y,x);
        map.setPixel(obstacle,qRgb(0,0,0));
        //printf("x= %d y = %d\ndistance %lf angle = %lf\n",x,y, scan.Data[i].scanDistance,scan.Data[i].scanAngle);
        lastMap.push_back(obstacle);
    }
#else
    //fake map building
    resetLastMap();
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
    //printf("emitting !!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    emit(newMap());
}

void LocalMap::resetLastMap() {
    for (int i = 0; i < lastMap.size(); i++) {
        map.setPixel(lastMap[i],qRgb(255, 255,255));
    }
    lastMap.clear();
}

double LocalMap::getObstacleDistance(Position2d otherPos, QImage &otherMap) {


    int targetOffSet = 1.05/resolution;

    //2m x 2m hladanie robot je v strede (1,1)
    int xObstacle = -1;
    int yObstacle = -1;

    int robotPosX = xSquares_2 -otherPos.y/resolution;
    int robotPosY = ySquares_2 -otherPos.x/resolution;
    //printf("future robot position x = %d y = %d real x = %lf y =%lf \n",robotPosX,robotPosY,otherPos.x,otherPos.y);
    for(int i = 1;i<=targetOffSet;i++){
        //check fron
        for (int j = 0; j <= i ; j++) {
            //prava strana v predu
            if(otherMap.pixel(robotPosX +j,robotPosY-i)==0xff000000) { //0xff000000 je cierna
                //printf("prekazka pred: ");
                //printf(" pred locking for obstacle x = %d, y = %d %x\n", robotPosX + j, robotPosY - i,map.pixel(robotPosX + j, robotPosY - i));
                xObstacle = robotPosX +j;
                yObstacle = robotPosY-i;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                return sqrt(pow((robotPosX-xObstacle),2) + pow(robotPosY-yObstacle,2))*resolution;
            }
            //lava strana v predu
            if(otherMap.pixel(robotPosX -j,robotPosY-i)==0xff000000) {
                //printf("prekazka pred: ");
                //printf(" pred locking for obstacle x = %d, y = %d %x\n", robotPosX - j, robotPosY - i,map.pixel(robotPosX + j, robotPosY - i));
                xObstacle = robotPosX -j;
                yObstacle = robotPosY-i;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                return sqrt(pow((robotPosX-xObstacle),2) + pow(robotPosY-yObstacle,2))*resolution;
            }
        }
        //check left
        for (int j = robotPosY; j > robotPosX - i ; j--){
            if(otherMap.pixel(robotPosX -i,robotPosY -j)==0xff000000) {
                //printf("prekazka lava: ");
                //printf("boky lave locking for obstacle x = %d, y = %d %x\n",robotPosX-i,j,map.pixel(robotPosX-i,j));
                xObstacle = robotPosX -i;
                yObstacle = robotPosY -j;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                return sqrt(pow((robotPosX-xObstacle),2) + pow(robotPosY-yObstacle,2))*resolution;
            }
        }
        //check right
        for (int j = robotPosY; j > robotPosX - i ; j--){
            if(otherMap.pixel(robotPosX -i,j)==0xff000000){
                //printf("prekazka prava: ");
                //printf("boky prave locking for obstacle x = %d, y = %d %x\n",robotPosX+i,j,map.pixel(robotPosX-i,j));
                xObstacle = robotPosX +i;
                yObstacle = j;
                //printf("obstacle fount x = %d y= %d\n",xObstacle,yObstacle);
                return sqrt(pow((robotPosX-xObstacle),2) + pow(robotPosY-yObstacle,2))*resolution;
            }
        }
    }
    return 10; //no obstacle found so return large number
}

void LocalMap::timerUpdate(){
    emit(newMap());
}
