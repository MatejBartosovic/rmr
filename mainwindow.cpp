#include <math.h>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "positionRegulator2dCircular.h"
#include "positionRegulator2dLinear.h"
#include "LocalMap.h"
#include "LocalPlanner.h"

/*
 * Ta staticka funkcia bol genialny napad ...
 * treba prerobit na boost::bind
 * */
iRobotCreate robot;
Command cmd;
DifferencialDrive difDrive(cmd,0.275,0.1);
PositionRegulator2dLinear regulator2d(cmd);
LocalPlanner localPlaner(cmd);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
 //
    ui->setupUi(this);

    ui->currentX->setText("sss");
    ui->linearSpinBox->setSingleStep(0.05);
    ui->linearSpinBox->setRange(-0.5,0.5);
    ui->angularSpinBox->setSingleStep(0.05);
    ui->angularSpinBox->setRange(-0.5,0.5);
    ui->XSpinBox->setRange(-10,10);
    ui->YSpinBox->setRange(-10,10);
    ui->local_map->resize(QSize(400,400));

    connect(ui->linearSpinBox,SIGNAL(valueChanged(double)),this,SLOT(linearSpinBoxChange(double)));
    connect(ui->angularSpinBox,SIGNAL(valueChanged(double)),this,SLOT(angularSpinBoxChange(double)));

    connect(ui->angularPSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setAngularP(double)));
    connect(ui->linearPSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setLinearP(double)));

    connect(ui->setNewGoalButton,SIGNAL(clicked()),this,SLOT(setNewGoal()));
    connect(ui->cancelGoalButton,SIGNAL(clicked()),this,SLOT(cancelGoal()));
    connect(&localPlaner.localMap,SIGNAL(newMap()),this,SLOT(drawMap()));
    connect(&localPlaner.globalMap,SIGNAL(newMap()),this,SLOT(drawGlobalMap()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::demoCallback(CreateSensors inputData,void *ioPointer)
{
    MainWindow *currentWindow=(MainWindow*)ioPointer;
    QString vystup = "Neplatny udaj.";
    vystup = QString::number(inputData.Voltage);

    currentWindow->ui->label->setText(vystup);

    //calculate odometry

    difDrive.update((double)inputData.Distance/1000.0,(double)inputData.Angle/180.0*M_PI);

    currentWindow->ui->currentX->setText(QString(std::to_string(difDrive.getX()).c_str()));
    currentWindow->ui->currentY->setText(QString(std::to_string(difDrive.getY()).c_str()));
    currentWindow->ui->currentYaw->setText(QString(std::to_string(difDrive.getYaw()).c_str()));


    regulator2d.update(difDrive.getPos());
    localPlaner.update(difDrive.getPos());

    //update command
    difDrive.updateCommand();

    //set speed to robot
    robot.moveMotors((int)(cmd.rightVel*1000),(int)(cmd.leftVel*1000));

}
void MainWindow::on_pushButton_clicked()
{
#ifdef REAL_ROBOT
    if(robot.ConnectToPort("/dev/robot",this)){
        connect( this, SIGNAL( showMB() ), this, SLOT( showMessageBox() ), Qt::BlockingQueuedConnection );
        robot.dataProcess(this,&demoCallback);
        localPlaner.start();
    }
#else
        testThread = std::thread(&MainWindow::runTest,this);
        localPlaner.start();
#endif
}

void MainWindow::linearSpinBoxChange(double val){
    cmd.linear = val;
}

void MainWindow::angularSpinBoxChange(double val){
    cmd.angular = val;
}

void MainWindow::runTest(){
    printf("running test\n");
    while(true){
        difDrive.updateSim(cmd.linear/10,cmd.angular/10,cmd.linear,cmd.angular);

        ui->currentX->setText(QString(std::to_string(difDrive.getX()).c_str()));
        ui->currentY->setText(QString(std::to_string(difDrive.getY()).c_str()));
        ui->currentYaw->setText(QString(std::to_string(difDrive.getYaw()).c_str()));

        localPlaner.update(difDrive.getPos());
        //regulator2d.update(difDrive.getPos());
        difDrive.updateCommand();
        //printf("linear = %lf, angular = %lf \n",cmd.linear,cmd.angular);
        //printf("left vel = %lf, right vel = %lf \n",cmd.leftVel*1000,cmd.rightVel*1000);

        usleep(100000);
    }
}

void MainWindow::setAngularP(double p){
    regulator2d.setAngularP(p);
}

void MainWindow::setLinearP(double p){
    regulator2d.setLinearP(p);
}

void MainWindow::setNewGoal(){
    //regulator2d.setGoal(Position2d(ui->XSpinBox->value(),ui->YSpinBox->value(),0));
    //usleep(100000);
    localPlaner.setGoal(Position2d(ui->XSpinBox->value(),ui->YSpinBox->value(),0));
}

void MainWindow::cancelGoal(){
    regulator2d.cancelGoal();
    //localPlaner.cancelGoal();
}

void MainWindow::drawMap(){
    ui->local_map->setPixmap(QPixmap::fromImage(localPlaner.localMap.getMap().scaled(400,400,Qt::KeepAspectRatio)));
}

void MainWindow::drawGlobalMap(){
    ui->globalMap->setPixmap(QPixmap::fromImage(localPlaner.globalMap.getMap().scaled(400,400,Qt::KeepAspectRatio)));
}
