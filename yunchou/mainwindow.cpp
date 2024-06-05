#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string.h>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <QSettings>
#include <QDebug>
#include <QFileDialog>

const std::string TO_FILE_PATH = "../task.ini";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    time_t t;
    srand((unsigned) time(&t));
    initPos();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPos()
{
    sendPosA.init(A);
    sendPosB.init(B);
    sendPosC.init(C);
    recPosD.init(D);
    recPosE.init(E);
    recPosF.init(F);
    recPosG.init(G);
    recPosI.init(I);
    updateTasknum();
}

void MainWindow::generateTask()
{
    sendPosA.regenerate();
    sendPosB.regenerate();
    sendPosC.regenerate();
    updateTasknum();
}

void MainWindow::loadConfig()
{
    int carNumA = ui->send1->text().toInt();
    int carNumB = ui->send2->text().toInt();
    int carNumC = ui->send3->text().toInt();
    for (int i = 0; i < carNumA; i++) {
        cars.push_back(Car (A));
    }
    for (int i = 0; i < carNumB; i++) {
        cars.push_back(Car (B));
    }
    for (int i = 0; i < carNumC; i++) {
        cars.push_back(Car (C));
    }
    ui->totalNum->setText(QString("%1").arg(cars.size()).toLatin1());
}

void MainWindow::computeAdvancedAlgoTime()
{
    ;
}

void MainWindow::computeOriginAlgoTime()
{
    ;
}

void MainWindow::saveTask()
{
    QSettings *configIniWrite = new QSettings(TO_FILE_PATH.c_str(), QSettings::IniFormat);
    configIniWrite->clear();
    configIniWrite->setValue("tasknum/A", sendPosA.taskNum);
    configIniWrite->setValue("tasknum/B", sendPosB.taskNum);
    configIniWrite->setValue("tasknum/C", sendPosC.taskNum);
    for (int i = 0; i < sendPosA.taskNum; i++) {
        configIniWrite->setValue(QString("A%1/des").arg(i).toLatin1(), sendPosA.taskPool[i].destination);
        configIniWrite->setValue(QString("A%1/secondDes").arg(i).toLatin1(), sendPosA.taskPool[i].secondDes);
        configIniWrite->setValue(QString("A%1/volume").arg(i).toLatin1(), sendPosA.taskPool[i].volume);
    }
    for (int i = 0; i < sendPosB.taskNum; i++) {
        configIniWrite->setValue(QString("B%1/des").arg(i).toLatin1(), sendPosB.taskPool[i].destination);
        configIniWrite->setValue(QString("B%1/secondDes").arg(i).toLatin1(), sendPosB.taskPool[i].secondDes);
        configIniWrite->setValue(QString("B%1/volume").arg(i).toLatin1(), sendPosB.taskPool[i].volume);
    }
    for (int i = 0; i < sendPosC.taskNum; i++) {
        configIniWrite->setValue(QString("C%1/des").arg(i).toLatin1(), sendPosC.taskPool[i].destination);
        configIniWrite->setValue(QString("C%1/secondDes").arg(i).toLatin1(), sendPosC.taskPool[i].secondDes);
        configIniWrite->setValue(QString("C%1/volume").arg(i).toLatin1(), sendPosC.taskPool[i].volume);
    }
    delete configIniWrite;
}

void MainWindow::loadTask()
{
    QString key = "";
    QSettings *read_ini = new QSettings(QFileDialog::getOpenFileName(this,"打开文件","../"), QSettings::IniFormat); // 不打开文件可能存在bug
    sendPosA.taskPool.clear();
    sendPosB.taskPool.clear();
    sendPosC.taskPool.clear();
    Task tmp;
    DES tmpDes, tmpStartDes;
    int tmpVol, tmpSecDes;
    key = QString("tasknum/A");
    sendPosA.taskNum = read_ini->value(key).toInt();
    key = QString("tasknum/B");
    sendPosB.taskNum = read_ini->value(key).toInt();
    key = QString("tasknum/C");
    sendPosC.taskNum = read_ini->value(key).toInt();
    for (int i = 0; i < sendPosA.taskNum; i++) {
        key = QString("A%1/des").arg(i);
        tmpDes = (DES) read_ini->value(key).toInt();
        key = QString("A%1/secondDes").arg(i);
        tmpSecDes = read_ini->value(key).toInt();
        key = QString("A%1/volume").arg(i);
        tmpVol = read_ini->value(key).toInt();
        tmpStartDes = A;
        tmp.setTask(tmpDes, tmpSecDes, tmpVol, tmpStartDes);
        sendPosA.taskPool.push_back(tmp);
    }
    for (int i = 0; i < sendPosB.taskNum; i++) {
        key = QString("B%1/des").arg(i);
        tmpDes = (DES) read_ini->value(key).toInt();
        key = QString("B%1/secondDes").arg(i);
        tmpSecDes = read_ini->value(key).toInt();
        key = QString("B%1/volume").arg(i);
        tmpVol = read_ini->value(key).toInt();
        tmpStartDes = B;
        tmp.setTask(tmpDes, tmpSecDes, tmpVol, tmpStartDes);
        sendPosB.taskPool.push_back(tmp);
    }
    for (int i = 0; i < sendPosC.taskNum; i++) {
        key = QString("C%1/des").arg(i);
        tmpDes = (DES) read_ini->value(key).toInt();
        key = QString("C%1/secondDes").arg(i);
        tmpSecDes = read_ini->value(key).toInt();
        key = QString("C%1/volume").arg(i);
        tmpVol = read_ini->value(key).toInt();
        tmpStartDes = C;
        tmp.setTask(tmpDes, tmpSecDes, tmpVol, tmpStartDes);
        sendPosC.taskPool.push_back(tmp);
    }
    delete read_ini;
    updateTasknum();
}

void MainWindow::updateTasknum()
{
    ui->recA->setText(QString("%1").arg(sendPosA.taskNum).toLatin1());
    ui->recB->setText(QString("%1").arg(sendPosB.taskNum).toLatin1());
    ui->recC->setText(QString("%1").arg(sendPosC.taskNum).toLatin1());
}
