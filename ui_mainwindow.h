/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *spin_boxes;
    QLabel *label_3;
    QLabel *label_2;
    QDoubleSpinBox *XSpinBox;
    QLabel *label;
    QDoubleSpinBox *YSpinBox;
    QLabel *label_5;
    QDoubleSpinBox *linearPSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *angularPSpinBox;
    QVBoxLayout *buttons;
    QPushButton *pushButton;
    QPushButton *setNewGoalButton;
    QPushButton *cancelGoalButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QDoubleSpinBox *linearSpinBox;
    QLabel *label_7;
    QDoubleSpinBox *angularSpinBox;
    QLabel *local_map;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 321);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        spin_boxes = new QVBoxLayout();
        spin_boxes->setSpacing(6);
        spin_boxes->setObjectName(QString::fromUtf8("spin_boxes"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        spin_boxes->addWidget(label_3);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        spin_boxes->addWidget(label_2);

        XSpinBox = new QDoubleSpinBox(centralWidget);
        XSpinBox->setObjectName(QString::fromUtf8("XSpinBox"));

        spin_boxes->addWidget(XSpinBox);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        spin_boxes->addWidget(label);

        YSpinBox = new QDoubleSpinBox(centralWidget);
        YSpinBox->setObjectName(QString::fromUtf8("YSpinBox"));

        spin_boxes->addWidget(YSpinBox);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        spin_boxes->addWidget(label_5);

        linearPSpinBox = new QDoubleSpinBox(centralWidget);
        linearPSpinBox->setObjectName(QString::fromUtf8("linearPSpinBox"));

        spin_boxes->addWidget(linearPSpinBox);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        spin_boxes->addWidget(label_4);

        angularPSpinBox = new QDoubleSpinBox(centralWidget);
        angularPSpinBox->setObjectName(QString::fromUtf8("angularPSpinBox"));

        spin_boxes->addWidget(angularPSpinBox);


        horizontalLayout_4->addLayout(spin_boxes);

        buttons = new QVBoxLayout();
        buttons->setSpacing(6);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        buttons->addWidget(pushButton);

        setNewGoalButton = new QPushButton(centralWidget);
        setNewGoalButton->setObjectName(QString::fromUtf8("setNewGoalButton"));

        buttons->addWidget(setNewGoalButton);

        cancelGoalButton = new QPushButton(centralWidget);
        cancelGoalButton->setObjectName(QString::fromUtf8("cancelGoalButton"));

        buttons->addWidget(cancelGoalButton);


        horizontalLayout_4->addLayout(buttons);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        linearSpinBox = new QDoubleSpinBox(centralWidget);
        linearSpinBox->setObjectName(QString::fromUtf8("linearSpinBox"));

        verticalLayout_2->addWidget(linearSpinBox);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_2->addWidget(label_7);

        angularSpinBox = new QDoubleSpinBox(centralWidget);
        angularSpinBox->setObjectName(QString::fromUtf8("angularSpinBox"));

        verticalLayout_2->addWidget(angularSpinBox);


        horizontalLayout_4->addLayout(verticalLayout_2);

        local_map = new QLabel(centralWidget);
        local_map->setObjectName(QString::fromUtf8("local_map"));

        horizontalLayout_4->addWidget(local_map);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "angular P", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "linear P", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        setNewGoalButton->setText(QApplication::translate("MainWindow", "Set goal", 0, QApplication::UnicodeUTF8));
        cancelGoalButton->setText(QApplication::translate("MainWindow", "Cancel goal", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Linear speed", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Angular speed", 0, QApplication::UnicodeUTF8));
        local_map->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
