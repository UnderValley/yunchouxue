#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::updateTasknum()
{
    ui->recA->setText(QString("%1").arg(sendPosA.taskNum).toLatin1());
    ui->recB->setText(QString("%1").arg(sendPosB.taskNum).toLatin1());
    ui->recC->setText(QString("%1").arg(sendPosC.taskNum).toLatin1());
}
