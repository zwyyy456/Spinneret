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
const int N_ANT_COUNT = 50; //��������
const int N_IT_COUNT = 50; //��������

//��Ⱥ�㷨����
const double ALPHA = 2;
const double BETA = 5;
const double ROU = 0.95; //��Ϣ�ز���ϵ����(1-ROU)������Ϣ�صĻӷ��ٶ�
const double Pbest = 0.1; //����һ�������ҵ�����·���ĸ���

const double DB_MAX = 10e9; //һ����־��

extern double** g_Pheromone; //�������м���Ϣ��
extern int* aRoute; //�������м���Ϣ��
extern double** g_Distance; //�������м����

extern double** g_Prob;
extern double** g_DistanceBeta;

extern double* x_Ary;
extern double* y_Ary;

extern int rnd(int nLow, int nUpper); //���������
extern double rnd(double dbLow, double dbUpper);
extern double ROUND(double dbA);

extern void commonInit(int N); //��ʼ����̬����
extern void delete_New(int N); //�ͷ��ڴ�
