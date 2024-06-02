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
    recPosA.init(A);
    recPosB.init(B);
    recPosC.init(C);
    recPosD.init(D);
    sendPosE.init(E);
    sendPosF.init(F);
    sendPosG.init(G);
    updateTasknum();
}

void MainWindow::generateTask()
{
    recPosA.regenerate();
    recPosB.regenerate();
    recPosC.regenerate();
    recPosD.regenerate();
    updateTasknum();
}

void MainWindow::loadConfig()
{
    int carNumE = ui->send1->text().toInt();
    int carNumF = ui->send2->text().toInt();
    int carNumG = ui->send3->text().toInt();
    for (int i = 0; i < carNumE; i++) {
        cars.push_back(Car (E));
    }
    for (int i = 0; i < carNumF; i++) {
        cars.push_back(Car (F));
    }
    for (int i = 0; i < carNumG; i++) {
        cars.push_back(Car (G));
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
    ui->recA->setText(QString("%1").arg(recPosA.taskNum).toLatin1());
    ui->recB->setText(QString("%1").arg(recPosB.taskNum).toLatin1());
    ui->recC->setText(QString("%1").arg(recPosC.taskNum).toLatin1());
    ui->recD->setText(QString("%1").arg(recPosD.taskNum).toLatin1());
}
