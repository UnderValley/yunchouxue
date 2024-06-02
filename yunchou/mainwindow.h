#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "task.h"
#include "vector"
#include "recpos.h"
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
    RecPos recPosA;
    RecPos recPosB;
    RecPos recPosC;
    RecPos recPosD;
    class pos sendPosE;
    class pos sendPosF;
    class pos sendPosG;
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
};
#endif // MAINWINDOW_H
