
#include "Common.h"

int iHolesNum;
double PPU_now[3];
double** g_Pheromone; //�������м���Ϣ��
int* aRoute; //�������м���Ϣ��
double** g_Distance; //�������м����

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
//  �� ;������ָ����Χ�ڵ��������
//
//  ˵ ������
//
//  �� �ڣ�int nLow �����������
//                     int nUpper ������������
//
//  �� �أ�int ,��Χ��[nLow,nUpper)
//
/////////////
int rnd(int nLow, int nUpper)
{

	return nLow + (nUpper - nLow) * rand() / (RAND_MAX + 1);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  �� ;������ָ����Χ�ڵ����������
//
//  ˵ ������
//
//  �� �ڣ�double dbLow �����������
//                     double dbUpper �����������
//
//  �� �أ�double  ,��Χ��[dbLow,dbUpper)
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
