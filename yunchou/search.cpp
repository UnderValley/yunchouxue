//#include "stdafx.h"
#include "myDT.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <Windows.h>


int tw1,tw2;


using namespace std;

int countCustomer;
int tempdemands[MAXCITIES];
int tempdemandsCust[MAXCITIES];

/*void readInput()
{
        FILE *myfile;
        if((myfile=fopen(FileName,"r"))==NULL)
                printf( "File could not be opened\n" );
        else
        {
                //TO DO
                //NUMTRUCKS=8;//count Truck
                fscanf(myfile,"%d",&countCustomer);
                fscanf(myfile,"%d",&cap);
                //coordinates[0].x=coordinates[0].y=0;
                int tmp;
                for(int i=0;i < countCustomer;i++)
                {
                        fscanf(myfile,"%d%lf%lf",&tmp,&coordinates[i].x,&coordinates[i].y);
                }
                //demands[0]=-1;//depot demand
                int j;
                for(int i=0;i<countCustomer;i++)
                {
                        fscanf(myfile,"%d%d",&j,&demands[i]);
                }
        }
        fclose(myfile);
}*/
void readInput()
{
    FILE *myfile; // 定义文件指针

    // 尝试打开文件
    if((myfile = fopen(FileName, "r")) == NULL)
        printf("File could not be opened\n"); // 如果文件无法打开，打印错误信息
    else
    {
        // 读取宿舍楼数量和小车容量
        fscanf(myfile, "%d", &countCustomer);
        fscanf(myfile, "%d", &cap);
        printf("Number of customers: %d\n", countCustomer);
        printf("Capacity of each truck: %d\n", cap);

        // 读取宿舍楼坐标
        int tmp; // 临时变量，用于存储宿舍楼编号
        for(int i = 0; i < countCustomer; i++)
        {
            fscanf(myfile, "%d%lf%lf", &tmp, &coordinates[i].x, &coordinates[i].y); // 读取宿舍楼编号和坐标
            printf("Customer %d: (%lf, %lf)\n", tmp, coordinates[i].x, coordinates[i].y);
        }

        // 读取宿舍楼需求量
        int j; // 临时变量，用于存储宿舍楼编号
        for(int i = 0; i < countCustomer; i++)
        {
            fscanf(myfile, "%d%d", &j, &demands[i]); // 读取宿舍楼编号和需求量
            printf("Customer %d demand: %d\n", j, demands[i]);
        }
    }
    fclose(myfile); // 关闭文件
}

//使用计数排序算法对宿舍楼的需求量进行排序，并将排序后的需求量和相应的宿舍楼编号存储在 tempdemands 和 tempdemandsCust 数组中
void sort() // Counting Sort O(n)
{
    int temp[MAXCAP];
    for(int i = 1; i < cap; i++) temp[i] = 0; // 初始化计数数组
    for(int i = 0; i < countCustomer; i++) temp[demands[i]]++; // 统计每个需求量的出现次数
    for(int i = 2; i < cap; i++) temp[i] += temp[i - 1]; // 累加计数数组
    for(int i = countCustomer - 1; i > 0; i--)
    {
        tempdemands[temp[demands[i]]] = demands[i]; // 填充排序后的需求量
        tempdemandsCust[temp[demands[i]]] = i + 1; // 填充排序后对应的宿舍楼编号
        temp[demands[i]]--;
    }
}

//用于计算两个点之间的欧几里得距离。
double EuclidianDistance(int a,int b)
{
        return (double)(sqrt((coordinates[a].x-coordinates[b].x)*(coordinates[a].x-coordinates[b].x)+(coordinates[a].y-coordinates[b].y)*(coordinates[a].y-coordinates[b].y)));
}

//用于记录每个宿舍楼是否已被分配。数组大小为 MAXCITIES，初始值为 false，表示所有宿舍楼都未被分配。
bool assignCustomer[MAXCITIES]={false};

//用于检查是否还有未被分配的宿舍楼。如果有未被分配的宿舍楼，返回 true；否则返回 false。
bool remaincustomer()
{
        for(int i=0;i<countCustomer;i++)
                if(assignCustomer[i]==false)
                        return true;
        return false;
}

//用于选择下一个宿舍楼，该宿舍楼的需求量不超过小车的剩余容量，并且该宿舍楼尚未被分配。
int nextcustomer(int trkremaincap)//maximum number(demand) little than equal remainCap && corresponding customer didnt assign
{
        for(int i=countCustomer-1;i>=0;i--)
                if(tempdemands[i]<=trkremaincap && assignCustomer[i]==false)
                        return i;
        return -1;
}

//用于生成初始解，采用贪心算法将宿舍楼分配给小车
bool initialize()
{
 assignCustomer[0] = true; // 仓库已被分配
    sort(); // 对宿舍楼需求量进行排序
    for(int i = 0; i < NUMTRUCKS; i++)
    {
        struct Truck trk;
        trk.remindedCap = cap;
        trk.numMembers = 0;
        trk.totalCost = 0;
        int c = 0, nc = 0;
        for(int j = 0; j < MAXTRUCKCITIES; j++)
            trk.members[j] = 0;
        while((nc = nextcustomer(trk.remindedCap)) != -1)
        {
            trk.remindedCap -= tempdemands[nc];
            if(tempdemandsCust[nc] == 0)
                trk.members[c] = 0; // 第一个宿舍楼是仓库
            else
                trk.members[c] = tempdemandsCust[nc] - 1;
            assignCustomer[nc] = true;
            trk.numMembers++;
            if(c == 0)
                trk.totalCost += EuclidianDistance(trk.members[c], 0); // 从仓库到第一个宿舍楼
            else
                trk.totalCost += EuclidianDistance(trk.members[c], trk.members[c - 1]); // 从上一个宿舍楼到当前宿舍楼
            c++;
        }
        if(c != 0)
            trk.totalCost += EuclidianDistance(trk.members[c - 1], 0); // 返回到仓库
        solution[i] = trk;
    }
    solutionCost = retCost(solution);
    return (!remaincustomer());
}

//用于随机选择下一个宿舍楼，该宿舍楼的需求量不超过小车的剩余容量，并且该宿舍楼尚未被分配。
int nextcustomer2(int trkremaincap)
{
        int r;
        for(int i=countCustomer+1;i>=0;i--)
        {
                r=(int)rand()%countCustomer;
                if(tempdemands[r]<=trkremaincap && assignCustomer[r]==false)
                        return r;
        }
        return -1;
}

//用于生成初始解，采用随机选择宿舍楼的方法将宿舍楼分配给小车。
bool initialize2() // random
{
    sort();
    do {
        for(int j = 0; j < MAXCITIES; j++)
            assignCustomer[j] = false;
        assignCustomer[0] = true; // 仓库已被分配

        struct Truck trk;
        trk.remindedCap = cap;
        trk.numMembers = 0;
        trk.totalCost = 0;
        int c = 0, nc = 0;
        for(int j = 0; j < MAXTRUCKCITIES; j++)
            trk.members[j] = 0;

        // 单辆卡车进行多次配送
        while(remaincustomer()) {
            while((nc = nextcustomer2(trk.remindedCap)) != -1)
            {
                trk.remindedCap -= tempdemands[nc];
                if(tempdemandsCust[nc] == 0)
                    trk.members[c] = 0;
                else
                    trk.members[c] = tempdemandsCust[nc] - 1;
                assignCustomer[nc] = true;
                trk.numMembers++;
                if(c == 0)
                    trk.totalCost += EuclidianDistance(trk.members[c], 0); // 从仓库到第一个客户
                else
                    trk.totalCost += EuclidianDistance(trk.members[c], trk.members[c - 1]); // 从上一个客户到当前客户
                c++;
            }
            if(c != 0)
                trk.totalCost += EuclidianDistance(trk.members[c - 1], 0); // 返回到仓库
            solution[0] = trk; // 只有一辆卡车

            // 重新初始化卡车，进行下一次配送
            trk.remindedCap = cap;
            trk.numMembers = 0;
            c = 0;
        }
        solutionCost = retCost(solution);
    } while(remaincustomer());
    return true;
}

//用于在当前解的基础上生成一个新的解，通过交换同一辆小车内的两个宿舍楼的位置来调整路径。
void tweak1()
{
    tw1++; // 增加 tweak1 的调用计数

    // 复制当前解到 newSolution 中
    for(int ii = 0; ii < NUMTRUCKS; ii++)
    {
        newSolution[ii].clone(solution[ii]);
    }

    int r1 = 0, r2 = 0, t;
    int i; // 选择要调整的小车

    // 随机选择一辆小车 i，并确保该小车有超过一个宿舍楼
    for(int j = 0; j < NUMTRUCKS; j++) {
        i = rand() % NUMTRUCKS;
        if(newSolution[i].numMembers > 1)
            break;
        if(j == NUMTRUCKS - 1)
            return; // 如果所有小车都没有超过一个宿舍楼，则返回
    }

    // 随机选择两个不同的宿舍楼位置 r1 和 r2
    while(r1 == r2) {
        r1 = (int)rand() % (newSolution[i].numMembers);
        r2 = (int)rand() % (newSolution[i].numMembers);
    }

    // 调整路径总成本，去掉交换前的成本
    if(r1 == 0)
        newSolution[i].totalCost -= EuclidianDistance(0, newSolution[i].members[r1]);
    else
        newSolution[i].totalCost -= EuclidianDistance(newSolution[i].members[r1 - 1], newSolution[i].members[r1]);
    if(r1 == newSolution[i].numMembers - 1)
        newSolution[i].totalCost -= EuclidianDistance(newSolution[i].members[r1], 0);
    else
        newSolution[i].totalCost -= EuclidianDistance(newSolution[i].members[r1], newSolution[i].members[r1 + 1]);
    if(r2 == 0)
        newSolution[i].totalCost -= EuclidianDistance(0, newSolution[i].members[r2]);
    else
        newSolution[i].totalCost -= EuclidianDistance(newSolution[i].members[r2 - 1], newSolution[i].members[r2]);
    if(r2 == newSolution[i].numMembers - 1)
        newSolution[i].totalCost -= EuclidianDistance(newSolution[i].members[r2], 0);
    else
        newSolution[i].totalCost -= EuclidianDistance(newSolution[i].members[r2], newSolution[i].members[r2 + 1]);

    // 交换小车 i 中位置 r1 和 r2 的宿舍楼
    t = newSolution[i].members[r1];
    newSolution[i].members[r1] = newSolution[i].members[r2];
    newSolution[i].members[r2] = t;

    // 调整路径总成本，添加交换后的成本
    if(r1 == 0)
        newSolution[i].totalCost += EuclidianDistance(0, newSolution[i].members[r1]);
    else
        newSolution[i].totalCost += EuclidianDistance(newSolution[i].members[r1 - 1], newSolution[i].members[r1]);
    if(r1 == newSolution[i].numMembers - 1)
        newSolution[i].totalCost += EuclidianDistance(newSolution[i].members[r1], 0);
    else
        newSolution[i].totalCost += EuclidianDistance(newSolution[i].members[r1], newSolution[i].members[r1 + 1]);
    if(r2 == 0)
        newSolution[i].totalCost += EuclidianDistance(0, newSolution[i].members[r2]);
    else
        newSolution[i].totalCost += EuclidianDistance(newSolution[i].members[r2 - 1], newSolution[i].members[r2]);
    if(r2 == newSolution[i].numMembers - 1)
        newSolution[i].totalCost += EuclidianDistance(newSolution[i].members[r2], 0);
    else
        newSolution[i].totalCost += EuclidianDistance(newSolution[i].members[r2], newSolution[i].members[r2 + 1]);
}


//用于禁忌搜索算法中生成新的解。
void tweak1Tabu()
{
    tw1++; // 增加 tweak1 的计数器
    for(int ii = 0; ii < NUMTRUCKS; ii++)
    {
        newSolution2[ii].clone(solution[ii]); // 将当前解复制到 newSolution2 中
    }

    int r1 = 0, r2 = 0, t;
    int i; // 选择要调整的小车
    for(int j = 0; j < NUMTRUCKS; j++) {
        i = rand() % NUMTRUCKS; // 随机选择一辆小车
        if(newSolution2[i].numMembers > 1) // 确保该小车有超过一个宿舍楼
            break;
        if(j == NUMTRUCKS - 1)
            return; // 如果所有小车都只有一个宿舍楼，则返回
    }

    // 随机选择两个不同的宿舍楼位置 r1 和 r2
    while(r1 == r2) {
        r1 = (int)rand() % (newSolution2[i].numMembers);
        r2 = (int)rand() % (newSolution2[i].numMembers);
    }

    // 计算并调整交换前的路径总成本
    if(r1 == 0)
        newSolution2[i].totalCost -= EuclidianDistance(0, newSolution2[i].members[r1]);
    else
        newSolution2[i].totalCost -= EuclidianDistance(newSolution2[i].members[r1 - 1], newSolution2[i].members[r1]);
    if(r1 == newSolution2[i].numMembers - 1)
        newSolution2[i].totalCost -= EuclidianDistance(newSolution2[i].members[r1], 0);
    else
        newSolution2[i].totalCost -= EuclidianDistance(newSolution2[i].members[r1], newSolution2[i].members[r1 + 1]);
    if(r2 == 0)
        newSolution2[i].totalCost -= EuclidianDistance(0, newSolution2[i].members[r2]);
    else
        newSolution2[i].totalCost -= EuclidianDistance(newSolution2[i].members[r2 - 1], newSolution2[i].members[r2]);
    if(r2 == newSolution2[i].numMembers - 1)
        newSolution2[i].totalCost -= EuclidianDistance(newSolution2[i].members[r2], 0);
    else
        newSolution2[i].totalCost -= EuclidianDistance(newSolution2[i].members[r2], newSolution2[i].members[r2 + 1]);

    // 交换宿舍楼位置
    t = newSolution2[i].members[r1];
    newSolution2[i].members[r1] = newSolution2[i].members[r2];
    newSolution2[i].members[r2] = t;

    // 计算并调整交换后的路径总成本
    if(r1 == 0)
        newSolution2[i].totalCost += EuclidianDistance(0, newSolution2[i].members[r1]);
    else
        newSolution2[i].totalCost += EuclidianDistance(newSolution2[i].members[r1 - 1], newSolution2[i].members[r1]);
    if(r1 == newSolution2[i].numMembers - 1)
        newSolution2[i].totalCost += EuclidianDistance(newSolution2[i].members[r1], 0);
    else
        newSolution2[i].totalCost += EuclidianDistance(newSolution2[i].members[r1], newSolution2[i].members[r1 + 1]);
    if(r2 == 0)
        newSolution2[i].totalCost += EuclidianDistance(0, newSolution2[i].members[r2]);
    else
        newSolution2[i].totalCost += EuclidianDistance(newSolution2[i].members[r2 - 1], newSolution2[i].members[r2]);
    if(r2 == newSolution2[i].numMembers - 1)
        newSolution2[i].totalCost += EuclidianDistance(newSolution2[i].members[r2], 0);
    else
        newSolution2[i].totalCost += EuclidianDistance(newSolution2[i].members[r2], newSolution2[i].members[r2 + 1]);
}


//比较两个解决方案的总成本，判断第一个解决方案是否优于第二个解决方案。
bool assessment(Truck solu1[], Truck solu2[])
{
    double cost1 = 0, cost2 = 0;
    for(int i = 0; i < NUMTRUCKS; i++)
    {
        cost1 += solu1[i].totalCost; // 计算第一个解决方案的总成本
        cost2 += solu2[i].totalCost; // 计算第二个解决方案的总成本
    }
    if(cost1 < cost2)
        return true; // 如果第一个解决方案的总成本小于第二个解决方案，返回 true
    return false; // 否则返回 false
}

/*
用于计算一个点所在的区域。
原点    y 轴正方向      第一象限    第四象限     y 轴负方向     第三象限    第二象限
*/
int calcRegion(int point)
{
    if(coordinates[point].x == 0 && coordinates[point].y == 0)
        return 1; // 原点
    if(coordinates[point].x == 0 && coordinates[point].y > 0)
        return 2; // y 轴正方向
    if(coordinates[point].x > 0 && coordinates[point].y >= 0)
        return 3; // 第一象限
    if(coordinates[point].x > 0 && coordinates[point].y < 0)
        return 4; // 第四象限
    if(coordinates[point].x == 0 && coordinates[point].y < 0)
        return 5; // y 轴负方向
    if(coordinates[point].x < 0 && coordinates[point].y < 0)
        return 6; // 第三象限
    if(coordinates[point].x < 0 && coordinates[point].y >= 0)
        return 7; // 第二象限
    cout << "error1\n"; // 如果不在上述区域，打印错误信息
}

//用于比较两个点的角度，用于排序。
bool cmpAngle(int point1, int point2)
{
    int pos1 = calcRegion(point1); // 计算第一个点所在的区域
    int pos2 = calcRegion(point2); // 计算第二个点所在的区域

    if(pos1 < pos2)
        return true; // 如果第一个点的区域小于第二个点的区域，返回 true
    if(pos1 > pos2)
        return false; // 如果第一个点的区域大于第二个点的区域，返回 false

    // 如果两个点在同一个区域，比较它们的角度
    if(pos1 == 1)
        return true; // 原点，返回 true

    if(pos1 == 2)
        return coordinates[pos1].y < coordinates[pos2].y; // y 轴正方向，比较 y 坐标

    if(pos1 == 3)
        return coordinates[pos1].y / coordinates[pos1].x >= coordinates[pos2].y / coordinates[pos2].x; // 第一象限，比较斜率

    if(pos1 == 4)
        return coordinates[pos1].y / coordinates[pos1].x >= coordinates[pos2].y / coordinates[pos2].x; // 第四象限，比较斜率

    if(pos1 == 5)
        return coordinates[pos1].y < coordinates[pos2].y; // y 轴负方向，比较 y 坐标

    if(pos1 == 6)
        return coordinates[pos1].y / coordinates[pos1].x >= coordinates[pos2].y / coordinates[pos2].x; // 第三象限，比较斜率

    if(pos1 == 7)
        return coordinates[pos1].y / coordinates[pos1].x >= coordinates[pos2].y / coordinates[pos2].x; // 第二象限，比较斜率
}

//用于比较两个点的 x 坐标，用于排序
bool cmpX(int point1,int point2){
        return coordinates[point1].x < coordinates[point2].x;
}
//用于比较两个点的 y 坐标，用于排序
bool cmpY(int point1 , int point2){
        return coordinates[point1].y < coordinates[point2].y;
}
//用于对路径中的楼按照角度进行排序，并重新计算路径总成本。
void tweak1AngleSort(Truck * sol,int truckNum){
        sort(sol[truckNum].members,sol[truckNum].members+sol[truckNum].numMembers,cmpAngle);
        sol[truckNum].totalCost=sol[truckNum].calcTotalCost();
}
//用于对路径中的楼按照 x 坐标进行排序，并重新计算路径总成本。
void tweak1xSort(Truck * sol,int truckNum){
        sort(sol[truckNum].members,sol[truckNum].members+sol[truckNum].numMembers,cmpX);
        sol[truckNum].totalCost=sol[truckNum].calcTotalCost();
}
//用于对路径中的楼按照 y 坐标进行排序，并重新计算路径总成本。
void tweak1ySort(Truck * sol,int truckNum){
        sort(sol[truckNum].members,sol[truckNum].members+sol[truckNum].numMembers,cmpY);
        sol[truckNum].totalCost=sol[truckNum].calcTotalCost();
}



//用于交换两个卡车路径中的客户段，并调整卡车的剩余容量和成员数量。
bool changePos(Truck* sol, int truckNum1, int s1, int f1, int truckNum2, int s2, int f2) // ta khune ghabl az f1 o f2
{
    int len1 = s1 < f1 ? f1 - s1 : sol[truckNum1].numMembers - s1 + f1; // 计算第一个卡车路径段的长度
    int len2 = s2 < f2 ? f2 - s2 : sol[truckNum2].numMembers - s2 + f2; // 计算第二个卡车路径段的长度

    int cnt1 = s1, cnt2 = s2, tmp;

    if(len1 == len2) { // 如果两个路径段长度相等
        while(cnt2 != f2) {
            tmp = sol[truckNum1].members[cnt1];
            sol[truckNum1].members[cnt1] = sol[truckNum2].members[cnt2];
            sol[truckNum2].members[cnt2] = tmp;
            // 更新剩余容量
            sol[truckNum1].remindedCap += demands[sol[truckNum2].members[cnt2]] - demands[sol[truckNum1].members[cnt1]];
            sol[truckNum2].remindedCap += demands[sol[truckNum1].members[cnt1]] - demands[sol[truckNum2].members[cnt2]];

            cnt1++;
            cnt2++;
            if(cnt1 == sol[truckNum1].numMembers)
                cnt1 = 0;
            if(cnt2 == sol[truckNum2].numMembers)
                cnt2 = 0;
        }
    } else if(len1 > len2) { // 如果第一个路径段长度大于第二个路径段长度
        while(cnt2 != f2) {
            tmp = sol[truckNum1].members[cnt1];
            sol[truckNum1].members[cnt1] = sol[truckNum2].members[cnt2];
            sol[truckNum2].members[cnt2] = tmp;
            // 更新剩余容量
            sol[truckNum1].remindedCap += demands[sol[truckNum2].members[cnt2]] - demands[sol[truckNum1].members[cnt1]];
            sol[truckNum2].remindedCap += demands[sol[truckNum1].members[cnt1]] - demands[sol[truckNum2].members[cnt2]];

            cnt1++;
            cnt2++;
            if(cnt1 == sol[truckNum1].numMembers)
                cnt1 = 0;
            if(cnt2 == sol[truckNum2].numMembers)
                cnt2 = 0;
        }
        cnt2 = sol[truckNum2].numMembers;
        int tmp = cnt1;
        while(cnt1 != f1) {
            sol[truckNum2].members[cnt2++] = sol[truckNum1].members[cnt1++];
            sol[truckNum2].remindedCap -= demands[sol[truckNum1].members[cnt1 - 1]]; // 更新剩余容量
            sol[truckNum1].remindedCap += demands[sol[truckNum1].members[cnt1 - 1]];
            if(cnt1 == sol[truckNum1].numMembers)
                cnt1 = 0;
        }
        sol[truckNum2].numMembers = cnt2;
        if(cnt1 == 0) {
            // do nothing
        } else if(tmp < cnt1) {
            int firstTmp = tmp;
            while(1) {
                sol[truckNum1].members[tmp++] = sol[truckNum1].members[cnt1++];
                if(cnt1 == sol[truckNum1].numMembers)
                    break;
            }
        } else if(tmp > cnt1) {
            for(int i = cnt1; i < tmp; i++) {
                sol[truckNum1].members[i - cnt1] = sol[truckNum1].members[i];
            }
        } else {
            cout << "error2\n";
        }
        sol[truckNum1].numMembers += len2 - len1;
    } else { // 如果第二个路径段长度大于第一个路径段长度
        while(cnt1 != f1) {
            tmp = sol[truckNum1].members[cnt1];
            sol[truckNum1].members[cnt1] = sol[truckNum2].members[cnt2];
            sol[truckNum2].members[cnt2] = tmp;
            // 更新剩余容量
            sol[truckNum1].remindedCap += demands[sol[truckNum2].members[cnt2]] - demands[sol[truckNum1].members[cnt1]];
            sol[truckNum2].remindedCap += demands[sol[truckNum1].members[cnt1]] - demands[sol[truckNum2].members[cnt2]];

            cnt1++;
            cnt2++;
            if(cnt1 == sol[truckNum1].numMembers)
                cnt1 = 0;
            if(cnt2 == sol[truckNum2].numMembers)
                cnt2 = 0;
        }
        cnt1 = sol[truckNum1].numMembers;
        int tmp = cnt2;
        while(cnt2 != f2) {
            sol[truckNum1].members[cnt1++] = sol[truckNum2].members[cnt2++];
            sol[truckNum1].remindedCap -= demands[sol[truckNum2].members[cnt2 - 1]]; // 更新剩余容量
            sol[truckNum2].remindedCap += demands[sol[truckNum2].members[cnt2 - 1]];
            if(cnt2 == sol[truckNum2].numMembers)
                cnt2 = 0;
        }
        sol[truckNum1].numMembers = cnt1;
        if(cnt2 == 0) {
            // do nothing
        } else if(tmp < cnt2) {
            int firstTmp = tmp;
            while(1) {
                sol[truckNum2].members[tmp++] = sol[truckNum2].members[cnt2++];
                if(cnt2 == sol[truckNum2].numMembers)
                    break;
            }
        } else if(tmp > cnt2) {
            for(int i = cnt2; i < tmp; i++) {
                sol[truckNum2].members[i - cnt2] = sol[truckNum2].members[i];
            }
        } else {
            cout << "error3\n";
        }
        sol[truckNum2].numMembers += len1 - len2;
    }
    return true;
}

//用于在两个卡车之间交换路径段，通过调整路径来生成新的解
bool tweak2(Truck *sol, int truckNum1, int truckNum2) // return: javab peida karde ya na
{
    tw2++; // 增加 tweak2 的计数器
    int startPoint1;
    int startPoint2;
    int sum1;
    int sum2;
    int cnt1, cnt2;

    bool find = false;

    // 尝试多次交换路径段
    for(int i = 0; i < (sol[truckNum1].numMembers * sol[truckNum2].numMembers) / 4 || i < sol[truckNum1].numMembers + sol[truckNum2].numMembers; i++) //@@@@ tedade dafaate tekarar
    {
        startPoint1 = rand() % sol[truckNum1].numMembers; // 随机选择第一个卡车的起始点
        startPoint2 = rand() % sol[truckNum2].numMembers; // 随机选择第二个卡车的起始点
        cnt1 = startPoint1 + 1;
        cnt2 = startPoint2 + 1;
        cnt1 %= sol[truckNum1].numMembers;
        cnt2 %= sol[truckNum2].numMembers;
        sum1 = demands[sol[truckNum1].members[startPoint1]]; // 初始化第一个路径段的需求量
        sum2 = demands[sol[truckNum2].members[startPoint2]]; // 初始化第二个路径段的需求量

        bool valid = true;
        // 检查路径段是否有效
        while(sum2 + sol[truckNum2].remindedCap < sum1 || sum1 + sol[truckNum1].remindedCap < sum2)
        {
            if(sum1 + sol[truckNum1].remindedCap < sum2)
            {
                if(cnt1 == startPoint1)
                {
                    valid = false;
                    break;
                }
                sum1 += demands[sol[truckNum1].members[cnt1++]];
                cnt1 %= sol[truckNum1].numMembers;
            }
            else
            {
                if(cnt2 == startPoint2)
                {
                    valid = false;
                    break;
                }
                sum2 += demands[sol[truckNum2].members[cnt2++]];
                cnt2 %= sol[truckNum2].numMembers;
            }
        }

        // 如果路径段有效，进行交换
        if(valid)
        {
            if(cnt1 != startPoint1 && cnt2 != startPoint2) //@@  2ta dor kamel ba ham avaz nemishan
            {
                changePos(sol, truckNum1, startPoint1, cnt1, truckNum2, startPoint2, cnt2);
                sol[truckNum1].totalCost = sol[truckNum1].calcTotalCost(); // 重新计算第一个卡车的总成本
                sol[truckNum2].totalCost = sol[truckNum2].calcTotalCost(); // 重新计算第二个卡车的总成本
                return true;
            }
        }
    }
    return false;
}



//用于打印每辆卡车的路径信息，包括客户数量、剩余容量、总成本和路径。
void show(Truck * sol)
{
        cout<<"\n==================Best Solution====================\n";
        for(int i=0;i<NUMTRUCKS;i++)
        {
                printf("number of cust:%d\n",sol[i].numMembers);
                printf("remain Cap:%d\n",sol[i].remindedCap);
                printf("total cost:%lf\n",sol[i].totalCost);
                printf("Path:");
                for(int j=0;j<sol[i].numMembers;j++)
                        printf("%d,",sol[i].members[j]);
                printf("\n\n");
        }
        cout<<"result cost: "<<retCost(sol)<<endl;
        cout<<"tw1: "<<tw1<<"    tw2:"<<tw2<<endl;
}

//用于在当前解的基础上生成一个新的解，通过不同的调整方法（tweak1、tweak2 或排序）来生成新解。
bool tweak(int current,int end)
{
        double level = (double)current/end; //@@
        double wTweak3=4+0.5*level;
        double wTweak2=5+1.5*level;
        double wTweak1=3+3*level;
        double wSort=0.5+2*level;

        double sum=wTweak1+wTweak2+wTweak3+wSort;
        double rnd=rand()%(int)(sum*1000);
        rnd/=1000;

        if(rnd<=wTweak3){
                //tweak3();
                for(int i=0;i<NUMTRUCKS;i++)
                        newSolution[i].clone(solution[i]);
                int r1=rand()%NUMTRUCKS;
                int r2=rand()%NUMTRUCKS;
                if(NUMTRUCKS<2)//@@
                        return false;
                while(r1==r2)
                        r2=rand()%NUMTRUCKS;
                tweak2(newSolution,r1,r2);
        }
        else if(rnd<=wTweak3+wTweak2){
                for(int i=0;i<NUMTRUCKS;i++)
                        newSolution[i].clone(solution[i]);
                int r1=rand()%NUMTRUCKS;
                int r2=rand()%NUMTRUCKS;
                while(r1==r2)
                        r2=rand()%NUMTRUCKS;
                tweak2(newSolution,r1,r2);
        }
        else if(rnd<=wTweak3+wTweak2+wTweak1){
                tweak1();
        }
        else{
                //tweakSort();
                /*for(int i=0;i<NUMTRUCKS;i++)
                        newSolution[i].clone(solution[i]);
                tweak1AngleSort(newSolution,rand()%NUMTRUCKS);*/
        }

        return true;
}



//用于在禁忌搜索算法中生成一个新的解，通过不同的调整方法（tweak1Tabu、tweak2）来生成新解。
bool tweakTabu(int current, int end)
{
    double level = (double)current / end; // 计算当前进度
    double wTweak3 = 4 + 0.5 * level;
    double wTweak2 = 5 + 1.5 * level;
    double wTweak1 = 3 + 3 * level;
    double wSort = 0.5 + 2 * level;

    double sum = wTweak1 + wTweak2 + wTweak3; // + wSort;
    double rnd = rand() % (int)(sum * 1000);
    rnd /= 1000;

    if(rnd <= wTweak3) {
        // 调用 tweak3（注释掉的代码）
        for(int i = 0; i < NUMTRUCKS; i++)
            newSolution2[i].clone(solution[i]);
        int r1 = rand() % NUMTRUCKS;
        int r2 = rand() % NUMTRUCKS;
        if(NUMTRUCKS < 2)
            return false;
        while(r1 == r2)
            r2 = rand() % NUMTRUCKS;
        tweak2(newSolution2, r1, r2);
    }
    else if(rnd <= wTweak3 + wTweak2) {
        for(int i = 0; i < NUMTRUCKS; i++)
            newSolution2[i].clone(solution[i]);
        int r1 = rand() % NUMTRUCKS;
        int r2 = rand() % NUMTRUCKS;
        while(r1 == r2)
            r2 = rand() % NUMTRUCKS;
        tweak2(newSolution2, r1, r2);
    }
    else if(rnd <= wTweak3 + wTweak2 + wTweak1) {
        tweak1Tabu();
    }
    else {
        // 调用排序调整方法（注释掉的代码）
        /*for(int i = 0; i < NUMTRUCKS; i++)
            newSolution2[i].clone(solution[i]);
        tweak1AngleSort(newSolution2, rand() % NUMTRUCKS);*/
    }

    return true;
}


//用于计算一个解决方案的总成本
double retCost(Truck sol[])
{
        double totalcost=0;
        for(int i=0;i<NUMTRUCKS;i++)
                totalcost+=sol[i].totalCost;
        return totalcost;
}

//用于检查一个解决方案是否有效，即所有客户是否都被分配且仅被分配一次。
bool checkValid(Truck * sol){
        int bood[10000+1]={};
        for(int i=0;i<NUMTRUCKS;i++){
                for(int j=0;j<sol[i].numMembers;j++)
                        bood[sol[i].members[j]]++;
        }

        for(int i=1;i<countCustomer;i++){
                if(bood[i]!=1)
                        return false;
        }
        return true;

}

//用于实现迭代爬山算法，通过多次重新生成初始解，每次从新的初始解开始进行爬山搜索，找到局部最优解。
bool iterHill(int numStart)
{
    // 初始化解
    initialize2();
    int iter = 0, countStart = 0;
    for(int i = 0; i < NUMTRUCKS; i++) {
        best[i].clone(solution[i]);
        bestCost = solutionCost;
    }
    do {
        countStart++;
        iter = 0;
        do {
            iter++;
            tweak(iter, MAXITERATION / numStart); // 调整解，生成新解

            if(retCost(newSolution) < solutionCost) {
                for(int i = 0; i < NUMTRUCKS; i++)
                    solution[i].clone(newSolution[i]);
                solutionCost = retCost(newSolution);
            }
        } while(solutionCost > OPTIMALVALUE && iter < MAXITERATION / numStart);
        if(solutionCost < bestCost) {
            for(int i = 0; i < NUMTRUCKS; i++)
                best[i].clone(solution[i]);
            bestCost = retCost(solution);
        }
        initialize2(); // 重新初始化解
    } while(countStart < numStart && bestCost > OPTIMALVALUE);

    show(best); // 显示最终解
    return true;
}

//实现随机爬山算法，通过不断调整解来寻找最优解
bool stcHill()
{
    initialize2(); // 初始化解

    int newCost;
    int iter = 0;

    // 将当前解复制到最佳解中
    for(int i = 0; i < NUMTRUCKS; i++)
        best[i].clone(solution[i]);
    bestCost = solutionCost;

    do {
        iter++;

        // 调整解，生成新解
        tweak(iter, MAXITERATION);

        // 计算新解的总成本
        newCost = retCost(newSolution);

        // 计算接受较差解的概率
        double prb = 1 / (1 + exp((solutionCost - newCost) / TSHL));

        // 生成随机数
        double rnd = rand() % 10000;
        rnd /= 10000;

        // 根据概率决定是否接受新解
        if(prb <= rnd) {
            for(int i = 0; i < NUMTRUCKS; i++)
                solution[i].clone(newSolution[i]);
            solutionCost = retCost(newSolution);

            // 更新最佳解
            if(solutionCost < bestCost) {
                for(int i = 0; i < NUMTRUCKS; i++)
                    best[i].clone(solution[i]);
                bestCost = solutionCost;
            }
        }

    } while(iter < MAXITERATION && bestCost > OPTIMALVALUE);

    show(best); // 显示最终解
    return true;
}

//用于更新模拟退火算法中的温度参数
int updateT(int iter,int t)
{
        return (TSAMIN + (iter/MAXITERATION )*(iter/MAXITERATION)*(TSAMAX-TSAMIN));
}

//实现模拟退火算法，通过逐渐降低温度来减少接受较差解的概率，从而寻找最优解
bool simulatedAnnealing(int numChangeT)
{
    int totalIt = 0;
    if(!initialize())
        initialize2();
    int iter = 0, countChange = 0;
    double t = TSAMIN, newCost;

    // 将当前解复制到最佳解中
    for(int i = 0; i < NUMTRUCKS; i++) {
        best[i].clone(solution[i]);
        bestCost = solutionCost;
    }

    do {
        countChange++;
        iter = 0;
        do {
            iter++;
            totalIt++;
            tweak(totalIt, MAXITERATION); // 调整解，生成新解
            newCost = retCost(newSolution);

            // 如果新解优于当前解，接受新解
            if(newCost < solutionCost) {
                for(int i = 0; i < NUMTRUCKS; i++)
                    solution[i].clone(newSolution[i]);
                solutionCost = newCost;
                if(solutionCost < bestCost) {
                    for(int i = 0; i < NUMTRUCKS; i++)
                        best[i].clone(solution[i]);
                    bestCost = solutionCost;
                }
            }
            // 根据概率决定是否接受较差解
            else {
                double prb = exp((newCost - solutionCost) / t);
                double rnd = rand() % 10000;
                rnd /= 10000;
                if(prb <= rnd) {
                    for(int i = 0; i < NUMTRUCKS; i++)
                        solution[i].clone(newSolution[i]);
                    solutionCost = newCost;
                }
            }

        } while(solutionCost > OPTIMALVALUE && iter < MAXITERATION / numChangeT);

        // 更新温度
        t = updateT(totalIt, t);

    } while(totalIt < MAXITERATION && bestCost > OPTIMALVALUE);

    show(best); // 显示最终解
    return true;
}

double goal;

//实现禁忌搜索算法，通过在解空间中搜索并避免循环，寻找最优解。
bool tabuSearch(int numHillit) // n
{
    int totalIt = 0;
    // 初始化解
    initialize2();

    int iter = 0, countHill = 0;
    double newCost, new2Cost;

    // 将当前解复制到最佳解中
    for(int i = 0; i < NUMTRUCKS; i++) {
        best[i].clone(solution[i]);
        bestCost = solutionCost;
    }

    // 将最佳解插入禁忌列表
    tl.insert(best);

    do {
        iter++;
        // 调整解，生成新解
        tweak(iter, MAXITERATION);
        newCost = retCost(newSolution);

        // 检查新解是否在禁忌列表中
        bool newsToList = tl.search(newSolution);
        countHill = 0;
        do {
            countHill++;
            // 调整解，生成新的候选解
            tweakTabu(iter, MAXITERATION);
            new2Cost = retCost(newSolution2);

            // 如果候选解不在禁忌列表中，且优于当前解或当前解在禁忌列表中，接受候选解
            if((tl.search(newSolution2) == false) && (new2Cost < newCost || newsToList)) {
                newsToList = false;
                for(int i = 0; i < NUMTRUCKS; i++) {
                    newSolution[i].clone(newSolution2[i]);
                }
                newCost = new2Cost;
            }

        } while(newCost > OPTIMALVALUE && countHill < numHillit);

        // 如果新解不在禁忌列表中，且优于当前解，接受新解并更新当前解
        if(newsToList == false && newCost < solutionCost) {
            for(int i = 0; i < NUMTRUCKS; i++) {
                solution[i].clone(newSolution[i]);
            }
            solutionCost = newCost;
            tl.insert(newSolution);
            goal = (double)iter / MAXITERATION;
        }

    } while(iter < MAXITERATION && bestCost > OPTIMALVALUE);

    show(solution); // 显示最终解
    cout << "sol cost: " << solutionCost << endl; // 打印最终解的总成本
    cout << "goal: " << goal << endl; // 打印目标值
    return true;
}


int main()
{
    // 读取输入数据，包括宿舍楼数量、小车容量、宿舍楼坐标和需求
    readInput();

    // 定义用于计算时间的变量
    LARGE_INTEGER frequency;
    LARGE_INTEGER t1, t2;
    double elapsedTime;

    // 获取高精度计时器的频率
    QueryPerformanceFrequency(&frequency);
    // 获取当前时间
    QueryPerformanceCounter(&t1);

    // 初始化随机数生成器
    srand(time(NULL));

    // 选择解决问题的方法
    //tabuSearch(300); // 使用禁忌搜索算法
    //simulatedAnnealing(20); // 使用模拟退火算法
     stcHill(); // 使用随机爬山算法
    //iterHill(100); // 使用迭代爬山算法

    // 获取当前时间
    QueryPerformanceCounter(&t2);
    // 计算算法执行时间
    elapsedTime = (t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
    // 输出执行时间
    cout << "time: " << elapsedTime << endl;

    // 等待用户输入以结束程序
    getchar();
    return 0;
}

