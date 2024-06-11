#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string.h>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <QSettings>
#include <QDebug>
#include <QFileDialog>
using namespace std;
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
// 初始化每一节点信息
void MainWindow::initPos()
{
    sendPosA.init(A);
    sendPosB.init(B);
    sendPosC.init(C);
    recPosD.init(D);
    recPosE.init(E);
    recPosF.init(F);
    recPosG.init(G);
    recPosH.init(H);
    recPosI.init(I);
    updateTasknum();
}
// 按规则生成任务
void MainWindow::generateTask()
{
    sendPosA.regenerate();
    sendPosB.regenerate();
    sendPosC.regenerate();
    updateTasknum();
}
// 加载车辆配置
void MainWindow::loadConfig()
{
    cars.clear();
    sendPosA.resetTask();
    sendPosB.resetTask();
    sendPosC.resetTask();
    carNumA = ui->send1->text().toInt();
    carNumB = ui->send2->text().toInt();
    carNumC = ui->send3->text().toInt();
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
// 进阶算法计算
// 暂时无用
void MainWindow::computeAdvancedAlgoTime()
{
//     ui->output1->setText(QString("%1").arg(i).toLatin1()); output123456 outputtotal
    ;
}
// 原始算法计算时间
void MainWindow::computeOriginAlgoTime()
{
    DES des_first;
    std::vector<Task> tasks_first;  // 第一个任务集
    std::vector<Task> tasks_second; // 第二个任务集

    // 初始化任务数量
    cout << "A:" << sendPosA.taskPool.size() << "   " << sendPosA.taskNum << endl;
    cout << "B:" << sendPosB.taskPool.size() << "   " << sendPosB.taskNum << endl;
    cout << "C:" << sendPosC.taskPool.size() << "   " << sendPosC.taskNum << endl;

    int time_a;
    int time_b;
    int time_c;
    
    // 处理位置A的任务
    while (1)
    {
        vector<int> car_A;
        for(int i=0; i<carNumA; i++) car_A.push_back(i);
        int car_num;
        des_first = sendPosA.find_nearest_neighbour(); // 查找最近邻居
        if (des_first == A)
            break;
        sendPosA.find_task_first(tasks_first, des_first);
        
        switch (des_first)
        {
        case G:
            car_num = min_car(car_A);
            deliver_G(tasks_first, car_num, 0);
            car_num = min_car(car_A);
            deliver_G(tasks_first, car_num, 0);
            while (1)
            {
                car_num = min_car(car_A);
                deliver_G(tasks_first, car_num, 0);
                if (!sendPosA.check_task(G))
                    break;
            }
            break;
        case H:
            car_num = min_car(car_A);
            deliver_H(tasks_first, car_num, 0);
            deliver_H(tasks_first, car_num, 0);
            while (1)
            {
                car_num = min_car(car_A);
                deliver_H(tasks_first, car_num, 0);
                if (!sendPosA.check_task(H))
                    break;
            }
            break;
        case I:
            car_num = min_car(car_A);
            deliver_I(tasks_first, car_num, 0);
            car_num = min_car(car_A);
            deliver_I(tasks_first, car_num, 0);
            while (1)
            {
                car_num = min_car(car_A);
                deliver_I(tasks_first, car_num, 0);
                if (!sendPosA.check_task(I))
                    break;
            }
            break;
        }
    }
    
    // 查找最大时间
    int max = cars[0].time_sum;
    for (int i = 0; i < carNumA; i++)
    {
        cout << "cars[" << i << "].time_sum: " << cars[i].time_sum << endl;
        if (cars[i].time_sum > max) max = cars[i].time_sum;
    }
    ui->output1->setNum(max);
    
    // 处理位置B的任务
    while (1)
    {
        vector<int> car_B;
        for(int i=carNumA; i<carNumA+carNumB; i++) car_B.push_back(i);
        int car_num;
        des_first = sendPosB.find_nearest_neighbour();
        if (des_first == B)
            break;
        sendPosB.find_task_first(tasks_first, des_first);
        
        switch (des_first)
        {
        case D:
            car_num = min_car(car_B);
            deliver_D(tasks_first, car_num, 1);
            car_num = min_car(car_B);
            deliver_D(tasks_first, car_num, 1);
            while (1)
            {
                car_num = min_car(car_B);
                deliver_D(tasks_first, car_num, 1);
                if (!sendPosB.check_task(D))
                    break;
            }
            break;
        case E:
            car_num = min_car(car_B);
            deliver_E(tasks_first, car_num, 1);
            car_num = min_car(car_B);
            deliver_E(tasks_first, car_num, 1);
            while (1)
            {
                car_num = min_car(car_B);
                deliver_E(tasks_first, car_num, 1);
                if (!sendPosB.check_task(E))
                    break;
            }
            break;
        case F:
            car_num = min_car(car_B);
            deliver_F(tasks_first, car_num, 1);
            car_num = min_car(car_B);
            deliver_F(tasks_first, car_num, 1);
            while (1)
            {
                car_num = min_car(car_B);
                deliver_F(tasks_first, car_num, 1);
                if (!sendPosB.check_task(F))
                    break;
            }
            break;
        case G:
            car_num = min_car(car_B);
            deliver_G(tasks_first, car_num, 1);
            car_num = min_car(car_B);
            deliver_G(tasks_first, car_num, 1);
            while (1)
            {
                car_num = min_car(car_B);
                deliver_G(tasks_first, car_num, 1);
                if (!sendPosB.check_task(G))
                    break;
            }
            break;
        case H:
            car_num = min_car(car_B);
            deliver_H(tasks_first, car_num, 1);
            deliver_H(tasks_first, car_num, 1);
            while (1)
            {
                car_num = min_car(car_B);
                deliver_H(tasks_first, car_num, 1);
                if (!sendPosB.check_task(H))
                    break;
            }
            break;
        }
    }
    
    // 查找最大时间
    max = cars[carNumA].time_sum;
    for (int i = carNumA; i < carNumA + carNumB; i++)
    {
        cout << "cars[" << i << "].time_sum: " << cars[i].time_sum << endl;
        if (cars[i].time_sum > max) max = cars[i].time_sum;
    }
    ui->output2->setNum(max);
    
    // 处理位置C的任务
    while (1)
    {
        vector<int> car_C;
        for(int i=carNumA + carNumB; i<carNumA + carNumB + carNumC; i++) car_C.push_back(i);
        int car_num;
        des_first = sendPosC.find_nearest_neighbour();
        if (des_first == C)
            break;
        sendPosC.find_task_first(tasks_first, des_first);
        
        switch (des_first)
        {
        case G:
            car_num = min_car(car_C);
            deliver_G(tasks_first, car_num, 2);
            car_num = min_car(car_C);
            deliver_G(tasks_first, car_num, 2);
            while (1)
            {
                car_num = min_car(car_C);
                deliver_G(tasks_first, car_num, 2);
                if (!sendPosC.check_task(G))
                    break;
            }
            break;
        case H:
            car_num = min_car(car_C);
            deliver_H(tasks_first, car_num, 2);
            deliver_H(tasks_first, car_num, 2);
            while (1)
            {
                car_num = min_car(car_C);
                deliver_H(tasks_first, car_num, 2);
                if (!sendPosC.check_task(H))
                    break;
            }
            break;
        }
    }
    
    // 查找最大时间
    max = cars[carNumA + carNumB].time_sum;
    for (int i = carNumA + carNumB; i < carNumA + carNumB + carNumC; i++)
    {
        cout << "cars[" << i << "].time_sum: " << cars[i].time_sum << endl;
        if (cars[i].time_sum > max) max = cars[i].time_sum;
    }
    ui->output3->setNum(max);
    
    ui->outputtotal->setNum(ui->output3->text().toInt() >
                    (ui->output1->text().toInt() > ui->output2->text().toInt() ? ui->output1->text().toInt() : ui->output2->text().toInt()) ?
                     ui->output3->text().toInt()   :  (ui->output1->text().toInt() > ui->output2->text().toInt() ? ui->output1->text().toInt() : ui->output2->text().toInt()));
        
}
// 保存已生成的任务
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
// 从文件加载任务
void MainWindow::loadTask()
{
    QString key = "";
    QSettings *read_ini = new QSettings(QFileDialog::getOpenFileName(this,"打开文件","../"), QSettings::IniFormat);
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
    updateTasknum(); // 更新任务数量显示
}

// 更新任务数量
void MainWindow::updateTasknum()
{
    ui->recA->setText(QString("%1").arg(sendPosA.taskNum).toLatin1());
    ui->recB->setText(QString("%1").arg(sendPosB.taskNum).toLatin1());
    ui->recC->setText(QString("%1").arg(sendPosC.taskNum).toLatin1());
}

/* functions for algorithm */


// 使用动态规划算法装载小车
void MainWindow::package_load(std::vector<Task> &tasks_first, std::vector<Task> &tasks_second, int carCapacity, int car_num)
{
    int n = tasks_second.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(carCapacity + 1, 0));


    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= carCapacity; ++j)
        {
            if (tasks_second[i - 1].volume <= j)
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - tasks_second[i - 1].volume] + tasks_second[i - 1].volume);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }


    int w = carCapacity;
    for (int i = n; i > 0 && w > 0; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            tasks_second[i - 1].finish();
            for (int count = 0; count < tasks_first.size(); count++)
            {
                if (tasks_first[count].secondDes == tasks_second[i - 1].secondDes && tasks_first[count].volume == tasks_second[i - 1].volume && tasks_first[count].check() == false)
                {
                    tasks_first[count].finish();
                    break;
                }
            }
            cars[car_num].volume -= tasks_second[i - 1].volume;
            w -= tasks_second[i - 1].volume;
        }
    }
    change_taskpool(tasks_second);
    return;
}
// 任务递送函数示例（类似的函数有 deliver_E, deliver_F, 等）
void MainWindow::deliver_D(std::vector<Task> &tasks_first, int car_num, int start_pos)
{
    int building;
    std::vector<Task> tasks_second;
    building = recPosD.find_nearest_son(tasks_first, tasks_second);
    if (building == -1)
        return;
    package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
    cars[car_num].time_sum += (recPosD.neighbs[start_pos].second + recPosD.sonDist[building]) / cars[car_num].speed;
    while (cars[car_num].volume > 3 && building < 6)
    { // ����
        building++;
        if (recPosD.find_task_second(tasks_first, tasks_second, building))
        {
            package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
            cars[car_num].time_sum += (distance_building_D) / cars[car_num].speed;
        }
    }
    // cout << "deliver_D:" << endl;
    // cout << "cars[" << car_num << "]:" << cars[car_num].volume << endl;
    if (building == 6)
        building = 5;
    cars[car_num].time_sum += (recPosD.neighbs[start_pos].second + recPosD.sonDist[building]) / cars[car_num].speed;
    cars[car_num].volume = CAR_VOLUME;
}

void MainWindow::deliver_E(std::vector<Task> &tasks_first, int car_num, int start_pos)
{
    int building;
    std::vector<Task> tasks_second;
    building = recPosE.find_nearest_son(tasks_first, tasks_second);
    if (building == -1)
        return;
    package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
    cars[car_num].time_sum += (recPosE.neighbs[start_pos].second + recPosE.sonDist[building]) / cars[car_num].speed;
    while (cars[car_num].volume > 3 && building < 10)
    { // ����
        building++;
        if (recPosE.find_task_second(tasks_first, tasks_second, building))
        {
            package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
            cars[car_num].time_sum += (distance_building_E) / cars[car_num].speed;
        }
    }
    // cout << "deliver_E:" << endl;
    // cout << "cars[" << car_num << "]:" << cars[car_num].volume << endl;
    if (building == 10)
        building = 9;
    cars[car_num].time_sum += (recPosE.neighbs[start_pos].second + recPosE.sonDist[building]) / cars[car_num].speed;
    cars[car_num].volume = CAR_VOLUME;
}

void MainWindow::deliver_F(std::vector<Task> &tasks_first, int car_num, int start_pos)
{
    int building;
    std::vector<Task> tasks_second;
    building = recPosF.find_nearest_son(tasks_first, tasks_second);
    if (building == -1)
        return;
    package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
    cars[car_num].time_sum += (recPosF.neighbs[start_pos].second + recPosF.sonDist[building]) / cars[car_num].speed;
    while (cars[car_num].volume > 3 && building < 10)
    { // ����
        building++;
        if (recPosF.find_task_second(tasks_first, tasks_second, building))
        {
            package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
            cars[car_num].time_sum += (distance_building_F) / cars[car_num].speed;
        }
    }
    // cout << "deliver_F:" << endl;
    // cout << "cars[" << car_num << "]:" << cars[car_num].volume << endl;
    if (building == 10)
        building = 9;
    cars[car_num].time_sum += (recPosF.neighbs[start_pos].second + recPosF.sonDist[building]) / cars[car_num].speed;
    cars[car_num].volume = CAR_VOLUME;
}

void MainWindow::deliver_G(std::vector<Task> &tasks_first, int car_num, int start_pos)
{
    int building;
    std::vector<Task> tasks_second;
    building = recPosG.find_nearest_son(tasks_first, tasks_second);
    if (building == -1)
        return;
    package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
    cars[car_num].time_sum += (recPosG.neighbs[start_pos].second + recPosG.sonDist[building]) / cars[car_num].speed;
    while (cars[car_num].volume > 3 && building < 9)
    { // ����
        building++;
        if (recPosG.find_task_second(tasks_first, tasks_second, building))
        {
            package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
            cars[car_num].time_sum += (distance_building_G) / cars[car_num].speed;
        }
    }
    // cout << "deliver_G:" << endl;
    // cout << "cars[" << car_num << "]:" << cars[car_num].volume << endl;
    if (building == 9)
        building = 8;
    cars[car_num].time_sum += (recPosG.neighbs[start_pos].second + recPosG.sonDist[building]) / cars[car_num].speed;
    cars[car_num].volume = CAR_VOLUME;
}

void MainWindow::deliver_H(std::vector<Task> &tasks_first, int car_num, int start_pos)
{
    int building;
    std::vector<Task> tasks_second;
    building = recPosH.find_nearest_son(tasks_first, tasks_second);
    if (building == -1)
        return;
    package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
    cars[car_num].time_sum += (recPosH.neighbs[start_pos].second + recPosH.sonDist[building]) / cars[car_num].speed;
    while (cars[car_num].volume > 3 && building < 7)
    { // ����
        building++;
        if (recPosH.find_task_second(tasks_first, tasks_second, building))
        {
            package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
            cars[car_num].time_sum += (distance_building_H) / cars[car_num].speed;
        }
    }
    // cout << "deliver_H:" << endl;
    // cout << "cars[" << car_num << "]:" << cars[car_num].volume << endl;
    if (building == 7)
        building = 6;
    cars[car_num].time_sum += (recPosH.neighbs[start_pos].second + recPosH.sonDist[building]) / cars[car_num].speed;
    cars[car_num].volume = CAR_VOLUME;
}

void MainWindow::deliver_I(std::vector<Task> &tasks_first, int car_num, int start_pos)
{
    int building;
    std::vector<Task> tasks_second;
    building = recPosI.find_nearest_son(tasks_first, tasks_second);
    if (building == -1)
        return;
    package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
    cars[car_num].time_sum += (recPosI.neighbs[start_pos].second + recPosI.sonDist[building]) / cars[car_num].speed;
    while (cars[car_num].volume > 3 && building < 8)
    {
        building++;
        if (recPosI.find_task_second(tasks_first, tasks_second, building))
        {
            package_load(tasks_first, tasks_second, cars[car_num].volume, car_num);
            cars[car_num].time_sum += (distance_building_I) / cars[car_num].speed;
        }
    }
    // cout << "deliver_I:" << endl;
    // cout << "cars[" << car_num << "]:" << cars[car_num].volume << endl;
    if (building == 8) building = 7;
    cars[car_num].time_sum += (recPosI.neighbs[start_pos].second + recPosI.sonDist[building]) / cars[car_num].speed;
    cars[car_num].volume = CAR_VOLUME;
}
// 查找最小时间的车辆编号
int MainWindow::min_car(vector<int> car_num)
{
    int min = car_num[0];
    for (int i = 0; i < car_num.size(); i++)
    {
        if (cars[car_num[i]].time_sum < cars[min].time_sum)
        {
            min = car_num[i];
        }
    }
    return min;
}

void MainWindow::change_taskpool(std::vector<Task> &tasks){
    switch (tasks[0].startPos)
    {
    case A:
        for(int i=0;i<tasks.size();i++){
            if(tasks[i].check()){
                for(int j=0;j<sendPosA.taskPool.size();j++){
                    if(sendPosA.taskPool[j].secondDes==tasks[i].secondDes && sendPosA.taskPool[j].volume==tasks[i].volume
                    && sendPosA.taskPool[j].destination==tasks[i].destination && sendPosA.taskPool[j].check()==false){
                        sendPosA.taskPool[j].finish();
                    }
                }
            }
            
        }
        break;
    case B:
        for(int i=0;i<tasks.size();i++){
            if(tasks[i].check()){
                for(int j=0;j<sendPosB.taskPool.size();j++){
                    if(sendPosB.taskPool[j].secondDes==tasks[i].secondDes && sendPosB.taskPool[j].volume==tasks[i].volume
                    && sendPosB.taskPool[j].destination==tasks[i].destination && sendPosB.taskPool[j].check()==false){
                        sendPosB.taskPool[j].finish();
                    }
                }
            }
        }
        break;
    case C:
        for(int i=0;i<tasks.size();i++){
            if(tasks[i].check()){
                for(int j=0;j<sendPosC.taskPool.size();j++){
                    if(sendPosC.taskPool[j].secondDes==tasks[i].secondDes && sendPosC.taskPool[j].volume==tasks[i].volume
                    && sendPosC.taskPool[j].destination==tasks[i].destination && sendPosC.taskPool[j].check()==false){
                        sendPosC.taskPool[j].finish();
                    }
                }
            }
        }
        break;
    }
}
