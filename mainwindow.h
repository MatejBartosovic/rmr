#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "irobotcreate.h"
#include "DifferencialDrive.h"
#include <thread>
#include <condition_variable>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void showMB();
public slots:
    void linearSpinBoxChange(double val);
    void angularSpinBoxChange(double val);
    void startTestButtonCallback();
public:

    void forMsgBox(){emit showMB();}

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static int demoCallback(CreateSensors inputData,void *ioPointer);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void showMessageBox()
            {
                QMessageBox Msgbox;
                Msgbox.setText("Save work and change Battery!");
                Msgbox.setIcon(QMessageBox::Critical);
                Msgbox.exec();
                exit(-1);
            }

private:
    void runTest();
    Ui::MainWindow *ui;
    std::thread testThread;
};

#endif // MAINWINDOW_H
