#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "task.h"
#include "vector"
#include "sendpos.h"
#include "worldModule.h"
#include "car.h"
#include "pos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    sendPos sendPosA;
    sendPos sendPosB;
    sendPos sendPosC;
    class pos recPosD;
    class pos recPosE;
    class pos recPosF;
    class pos recPosG;
    class pos recPosH;
    class pos recPosI;
    std::vector<Car> cars;
    void initPos();

private:
    Ui::MainWindow *ui;
    void updateTasknum();

public  slots:
    void generateTask();
    void loadConfig();
    void computeOriginAlgoTime();
    void computeAdvancedAlgoTime();
    void saveTask();
    void loadTask();
};
#endif // MAINWINDOW_H
