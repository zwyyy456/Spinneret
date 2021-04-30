#pragma once
#include "Common.h"
#include "Ant.h"

class CTsp
{
public:
	CTsp(void);
	~CTsp(void);

public:

	CAnt m_cAntAry[N_ANT_COUNT];
	CAnt m_cGlobalBestAnt; //����ȫ�����Ž��
	CAnt m_cIterationBestAnt; //����������Ž��
	CAnt m_cTempAnt; //��ʱ

	double m_dbRate; //�����Ϣ�غ���С��Ϣ�صı�ֵ

	double Qmax; //��Ϣ������
	double Qmin;  //��Ϣ������


public:

	//��ʼ������
	void InitData();

	//��ʼ����
	void Search();

	//���»�����Ϣ��
	void UpdatePheromone(int nFlag);

	void fnGreedy();//�ֲ�̰���㷨
};
