#include "StdAfx.h"
#include"antpath.h"

CTsp::CTsp(void)
{

}

CTsp::~CTsp(void)
{
}


//��ʼ������
void CTsp::InitData()
{
	//�����������м����
	double dbTemp = 0.0;
	for (int i = 0; i < iHolesNum; i++)
	{
		for (int j = 0; j < iHolesNum; j++)
		{
			dbTemp = (x_Ary[i] - x_Ary[j]) * (x_Ary[i] - x_Ary[j]) + (y_Ary[i] - y_Ary[j]) * (y_Ary[i] - y_Ary[j]);
			dbTemp = pow(dbTemp, 0.5);
			g_Distance[i][j] = dbTemp;
			g_DistanceBeta[i][j] = pow(1.0 / g_Distance[i][j], BETA);
		}
	}


	//��ʼ��������Ϣ�أ���ʼʱ���Ȱ���Ϣ�����ó�һ���Ƚϴ��ֵ
	//��һ�ε�����ɺ󣬻���Qmax(1)��Ȼ���Ժ�ͻ�������������Сֵ֮��
	for (int i = 0; i < iHolesNum; i++)
	{
		for (int j = 0; j < iHolesNum; j++)
		{
			g_Pheromone[i][j] = 10000.0;
			g_Prob[i][j] = pow(g_Pheromone[i][j], ALPHA) * g_DistanceBeta[i][j];
		}
	}

	//����������С��Ϣ��֮��ı�ֵ
	double dbN = (double)iHolesNum;
	dbTemp = exp(log(Pbest) / dbN); //��Pbest��N_CITY_COUNT�η�
	m_dbRate = (2.0 / dbTemp - 2.0) / (dbN - 2.0);

	//��Ϊ��һ�ε���ʱ����û��ȫ�����Ž⣬���м��㲻��������Сֵ�������ó�0.0
	Qmax = 0.0;
	Qmin = 0.0;

}


//���»�����Ϣ�أ�ֻ�õ�ǰ�������ȥ����
void CTsp::UpdatePheromone(int nFlag)
{

	if (nFlag == 1) //ʹ��ȫ�����Ž�
	{
		m_cTempAnt = m_cGlobalBestAnt;
	}
	else //ʹ�õ������Ž�
	{
		m_cTempAnt = m_cIterationBestAnt;
	}

	//��ʱ������Ϣ��
	double **dbTempAry;
	dbTempAry = new double* [iHolesNum];
	for (int i = 0; i < iHolesNum; ++i)
	{
		dbTempAry[i] = new double[iHolesNum];
	}


	for (int i = 0; i < iHolesNum; i++)//��ȫ������Ϊ0
		for (int j = 0; j < iHolesNum; j++)
			dbTempAry[i][j] = 0;

	//���������ӵ���Ϣ��,���浽��ʱ������
	int m = 0;
	int n = 0;
	//����Ŀǰ�����������µ���Ϣ��
	double dbTemp = 1.0 / m_cTempAnt.m_dbPathLength;
    for (int j = 1; j < iHolesNum; j++)
	{
		m = m_cTempAnt.m_nPath[j];
		n = m_cTempAnt.m_nPath[j - 1];
		//cout << dbTempAry[n][m];
		dbTempAry[n][m] = dbTempAry[n][m] + dbTemp;
		dbTempAry[m][n] = dbTempAry[n][m];
	}

	//�����кͿ�ʼ����֮�����Ϣ��
	n = m_cTempAnt.m_nPath[0];
	dbTempAry[n][m] = dbTempAry[n][m] + dbTemp;
	dbTempAry[m][n] = dbTempAry[n][m];


	//==================================================================
	//���»�����Ϣ��
    for (int i = 0; i < iHolesNum; i++)
	{
        for (int j = 0; j < iHolesNum; j++)
		{
			g_Pheromone[i][j] = g_Pheromone[i][j] * ROU + dbTempAry[i][j];  //���µĻ�����Ϣ�� = �������Ϣ�� + �����µ���Ϣ��
		}
	}

	//==================================================================
	//��黷����Ϣ�أ��������С�����ֵ�����棬�������µ���
	Qmax = 1.0 / (m_cGlobalBestAnt.m_dbPathLength * (1.0 - ROU));
	Qmin = Qmax * m_dbRate;

    for (int i = 0; i < iHolesNum; i++)
	{
        for (int j = 0; j < iHolesNum; j++)
		{
			if (g_Pheromone[i][j] < Qmin)
			{
				g_Pheromone[i][j] = Qmin;
			}

			if (g_Pheromone[i][j] > Qmax)
			{
				g_Pheromone[i][j] = Qmax;
			}

		}
	}

	//==================================================================
	//�����������м��ѡ�����ֵ
    for (int i = 0; i < iHolesNum; i++)
	{
        for (int j = 0; j < iHolesNum; j++)
		{
			g_Prob[i][j] = pow(g_Pheromone[i][j], ALPHA) * g_DistanceBeta[i][j];
		}
	}
	for (int i = 0; i < iHolesNum; ++i)
	{
		delete[] dbTempAry[i];
	}
	delete[] dbTempAry;
}

void CTsp::Search()
{
//	char cBuf[256];

	m_cGlobalBestAnt.m_dbPathLength = DB_MAX;

//	double dbMinLen = DB_MAX;

	for (int i = 0; i < N_IT_COUNT; i++)
	{
		m_cIterationBestAnt.m_dbPathLength = DB_MAX;
		//ÿֻ��������һ��
		for (int j = 0; j < N_ANT_COUNT; j++)
		{ 
			m_cAntAry[j].Search();
		}


		//������ѽ��
		for (int j = 0; j < N_ANT_COUNT; j++)
		{
			//�����������Ž�
			if (m_cAntAry[j].m_dbPathLength < m_cGlobalBestAnt.m_dbPathLength)
			{
				m_cGlobalBestAnt = m_cAntAry[j];
				if (i == 0) {
					for (int k = 0; k < iHolesNum; k++)
						m_cGlobalBestAnt.m_nPath[k] = aRoute[k];
					m_cGlobalBestAnt.CalPathLength();
				}
			}

			//����������Ž�
			if (m_cAntAry[j].m_dbPathLength < m_cIterationBestAnt.m_dbPathLength)
			{
				m_cIterationBestAnt = m_cAntAry[j];
				if (i == 0) {
					for (int k = 0; k < iHolesNum; k++)
						m_cIterationBestAnt.m_nPath[k] = aRoute[k];
					m_cIterationBestAnt.CalPathLength();
				}
				//cout<<m_cIterationBestAnt.m_dbPathLength<<endl;
			}

		}
		// ���»�����Ϣ�أ�ʹ��ȫ�����ź͵������Ž�����µĲ���
		// ÿ��5�ε���ʹ��һ��ȫ���������ϸ�����Ϣ��
		// ������������������Χ
		if ((i + 1) % 5 == 0)
		{
			UpdatePheromone(1);
		}
		else
		{
			UpdatePheromone(0);
		}

		//������ε����Ľ��

		cout<<"["<<i<<"]:"<< m_cGlobalBestAnt.m_dbPathLength<<endl;
	}

}

//̰���㷨
void CTsp::fnGreedy() {
	bool* bIfChoosen = new bool[iHolesNum];
	aRoute[0] = 0;
	bIfChoosen[0] = true;
	for (int i = 1; i < iHolesNum; ++i)
	{
		bIfChoosen[i] = false;
	}
	int tMinNum, tMinDistance;
	double tmpDistance;
	for (int n = 0; n < iHolesNum - 1; ++n)
	{
		tMinDistance = 999999;
		tMinNum = 0;
		for (int i = 1; i < iHolesNum; ++i)
		{
			if (bIfChoosen[i] == false)
			{
				tmpDistance = g_Distance[(aRoute[n])][i];
				if (tmpDistance < tMinDistance)
				{
					tMinDistance = tmpDistance;
					tMinNum = i;
				}
			}
		}
		//cout << endl;
		//cout << tMinNum<<" "<<endl;
		aRoute[n + 1] = tMinNum;
		bIfChoosen[tMinNum] = true;
	}
	cout << "̰���㷨����" << endl;
	delete[] bIfChoosen;
}
