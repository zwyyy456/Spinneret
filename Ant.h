#pragma once
#include"Common.h"

class CAnt
{
public:
	CAnt(void);
	~CAnt(void);

public:


	double m_dbPathLength; //�����߹���·������
    vector<int> m_nPath;//�����䳤����
    vector<int> m_nAllowedCity;//�����䳤����
//    QVector<int> m_nPath;
//    QVector<int> m_nAllowedCity;
    //vector<vector<int> > a(row,vector<int>(column));
    //int* m_nPath; //�����ߵ�·��
    //int* m_nAllowedCity; //ûȥ���ĳ���

	int m_nCurCityNo; //��ǰ���ڳ��б��
	int m_nMovedCityCount; //�Ѿ�ȥ���ĳ�������

	bool m_blGreedSearch; //�Ƿ�ʹ��̰��ԭ��ѡ����һ����
public:

	int ChooseNextCity(); //ѡ����һ������

	void Init(); //��ʼ��
	void Move(); //�����ڳ��м��ƶ�
	void Search(); //����·��
	void CalPathLength(); //���������߹���·������

};

