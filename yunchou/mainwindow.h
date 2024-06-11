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
    int carNumA = 0;
    int carNumB = 0;
    int carNumC = 0;
    std::vector<Car> cars;
    void initPos();
    void package_load(std::vector<Task>& tasks_first,std::vector<Task>& tasks_second, int carCapacity, int car_num);
    void deliver_D(std::vector<Task>& tasks_first,int car_num,int start_pos);
    void deliver_E(std::vector<Task>& tasks_first,int car_num,int start_pos);
    void deliver_F(std::vector<Task>& tasks_first,int car_num,int start_pos);
    void deliver_G(std::vector<Task>& tasks_first,int car_num,int start_pos);
    void deliver_H(std::vector<Task>& tasks_first,int car_num,int start_pos);
    void deliver_I(std::vector<Task>& tasks_first,int car_num,int start_pos);
    int min_car(std::vector<int> car_num);
    void change_taskpool(std::vector<Task> &tasks_first);


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

void package_load(std::vector<Task>& tasks, int carCapacity);
void deliver_F(std::vector<Task>& tasks_first,int car_num,int start_pos);

#endif // MAINWINDOW_H
