
#include "Common.h"

int iHolesNum;
double PPU_now[3];
double** g_Pheromone; //两两城市间信息素
int* aRoute; //两两城市间信息素
double** g_Distance; //两两城市间距离

double** g_Prob;
double** g_DistanceBeta;

double* x_Ary;
double* y_Ary;

void commonInit(int N) {
    g_Pheromone = new double* [N];
    g_Distance = new double* [N];
    g_Prob = new double* [N];
    g_DistanceBeta = new double* [N];

    x_Ary = new double [N];
    y_Ary = new double[N];
    aRoute = new int [N];

    for (int i = 0; i < N; ++i)
    {
        g_Pheromone[i] = new double[N];
        g_Distance[i] = new double[N];
        g_Prob[i] = new double[N];
        g_DistanceBeta[i] = new double[N];
    }
}

void delete_New(int N) {
    for (int i = 0; i < N; i++)
    {
        delete[] g_Pheromone[i];
        delete[] g_Distance[i];
        delete[] g_Prob[i];
        delete[] g_DistanceBeta[i];
    }
    delete[] x_Ary;
    delete[] y_Ary;
    delete[] aRoute;
    delete[] g_Pheromone;
    delete[] g_Distance;
    delete[] g_Prob;
    delete[] g_DistanceBeta;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  用 途：返回指定范围内的随机整数
//
//  说 明：无
//
//  接 口：int nLow 随机数的下限
//                     int nUpper 随整数的上限
//
//  返 回：int ,范围是[nLow,nUpper)
//
/////////////
int rnd(int nLow, int nUpper)
{

	return nLow + (nUpper - nLow) * rand() / (RAND_MAX + 1);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  用 途：返回指定范围内的随机浮点数
//
//  说 明：无
//
//  接 口：double dbLow 随机数的下限
//                     double dbUpper 随机数的上限
//
//  返 回：double  ,范围是[dbLow,dbUpper)
//
/////////////
double rnd(double dbLow, double dbUpper)
{
	double dbTemp = rand() / ((double)RAND_MAX + 1.0);
	return dbLow + dbTemp * (dbUpper - dbLow);
}

//
double ROUND(double dbA)
{
	return (double)((int)(dbA + 0.5));
}
