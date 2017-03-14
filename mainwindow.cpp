#include <math.h>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "positionRegulator2dCircular.h"
#include "positionRegulator2dLinear.h"

/*
 * Ta staticka funkcia bol genialny napad ...
 * treba prerobit na boost::bind
 * */
iRobotCreate robot;
Command cmd;
DifferencialDrive difDrive(cmd,0.275,0.1);
PositionRegulator2dLinear regulator2d(cmd);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
 //
    ui->setupUi(this);

    ui->linearSpinBox->setSingleStep(0.05);
    ui->linearSpinBox->setRange(-0.5,0.5);
    ui->angularSpinBox->setSingleStep(0.05);
    ui->angularSpinBox->setRange(-0.5,0.5);

    connect(ui->linearSpinBox,SIGNAL(valueChanged(double)),this,SLOT(linearSpinBoxChange(double)));
    connect(ui->angularSpinBox,SIGNAL(valueChanged(double)),this,SLOT(angularSpinBoxChange(double)));
    connect(ui->startTestPushButton,SIGNAL(clicked()),this,SLOT(startTestButtonCallback()));

    connect(ui->angularPSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setAngularP(double)));
    connect(ui->linearPSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setLinearP(double)));

    connect(ui->setNewGoalButton,SIGNAL(clicked()),this,SLOT(setNewGoal()));
    connect(ui->cancelGoalButton,SIGNAL(clicked()),this,SLOT(cancelGoal()));

    //connect(ui->linearPSpinBox,SIGNAL(valueChanged(double)),&regulator2d,SLOT(setLinearP(double)));
    //regulator2d.setGoal(Position2d(1,1,0));
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

    difDrive.update((double)inputData.Distance/1000.0,-(double)inputData.Angle/180.0*M_PI);

    regulator2d.update(difDrive.getPos());
    //update command
    difDrive.updateCommand();

    //set speed to robot
    robot.moveMotors((int)(cmd.rightVel*1000),(int)(cmd.leftVel*1000));

}
void MainWindow::on_pushButton_clicked()
{
    if(robot.ConnectToPort("/dev/robot",this)){
        connect( this, SIGNAL( showMB() ), this, SLOT( showMessageBox() ), Qt::BlockingQueuedConnection );
        robot.dataProcess(this,&demoCallback);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    robot.moveMotors(-35,35);
    //robot.moveRobot(linear,angular);
    usleep(1000*1000);
    robot.moveMotors(0,0);
}

void MainWindow::linearSpinBoxChange(double val){
    cmd.linear = val;
}

void MainWindow::angularSpinBoxChange(double val){
    cmd.angular = val;
}
void MainWindow::startTestButtonCallback() {
    printf("spavning\n");
    testThread = std::thread(&MainWindow::runTest,this);
}

void MainWindow::runTest(){
    while(true){
        difDrive.update(cmd.linear,cmd.angular);
        regulator2d.update(difDrive.getPos());
        difDrive.updateCommand();
        //printf("linear = %lf, angular = %lf \n",cmd.linear,cmd.angular);
        printf("left vel = %lf, right vel = %lf \n",cmd.leftVel*1000,cmd.rightVel*1000);
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
    regulator2d.setGoal(Position2d(ui->XSpinBox->value(),ui->YSpinBox->value(),0));
}

void MainWindow::cancelGoal(){
    regulator2d.cancelGoal();
}