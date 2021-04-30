#include <iostream>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;
#pragma once
extern int iHolesNum ;
extern double PPU_now[3] ;
const int N_ANT_COUNT = 50; //蚂蚁数量
const int N_IT_COUNT = 50; //迭代次数

//蚁群算法参数
const double ALPHA = 2;
const double BETA = 5;
const double ROU = 0.95; //信息素残留系数，(1-ROU)就是信息素的挥发速度
const double Pbest = 0.1; //蚂蚁一次搜索找到最优路径的概率

const double DB_MAX = 10e9; //一个标志数

extern double** g_Pheromone; //两两城市间信息素
extern int* aRoute; //两两城市间信息素
extern double** g_Distance; //两两城市间距离

extern double** g_Prob;
extern double** g_DistanceBeta;

extern double* x_Ary;
extern double* y_Ary;

extern int rnd(int nLow, int nUpper); //返回随机数
extern double rnd(double dbLow, double dbUpper);
extern double ROUND(double dbA);

extern void commonInit(int N); //初始化动态数组
extern void delete_New(int N); //释放内存
