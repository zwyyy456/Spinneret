#include "StdAfx.h"
#include"antpath.h"

CTsp::CTsp(void)
{

}

CTsp::~CTsp(void)
{
}


//初始化数据
void CTsp::InitData()
{
	//计算两两城市间距离
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


	//初始化环境信息素，开始时，先把信息素设置成一个比较大的值
	//第一次迭代完成后，会变成Qmax(1)，然后以后就会限制在最大和最小值之间
	for (int i = 0; i < iHolesNum; i++)
	{
		for (int j = 0; j < iHolesNum; j++)
		{
			g_Pheromone[i][j] = 10000.0;
			g_Prob[i][j] = pow(g_Pheromone[i][j], ALPHA) * g_DistanceBeta[i][j];
		}
	}

	//计算最大和最小信息素之间的比值
	double dbN = (double)iHolesNum;
	dbTemp = exp(log(Pbest) / dbN); //对Pbest开N_CITY_COUNT次方
	m_dbRate = (2.0 / dbTemp - 2.0) / (dbN - 2.0);

	//因为第一次迭代时，还没有全局最优解，所有计算不出最大和最小值，先设置成0.0
	Qmax = 0.0;
	Qmin = 0.0;

}


//更新环境信息素，只用当前最好蚂蚁去更新
void CTsp::UpdatePheromone(int nFlag)
{

	if (nFlag == 1) //使用全局最优解
	{
		m_cTempAnt = m_cGlobalBestAnt;
	}
	else //使用迭代最优解
	{
		m_cTempAnt = m_cIterationBestAnt;
	}

	//临时保存信息素
	double **dbTempAry;
	dbTempAry = new double* [iHolesNum];
	for (int i = 0; i < iHolesNum; ++i)
	{
		dbTempAry[i] = new double[iHolesNum];
	}


	for (int i = 0; i < iHolesNum; i++)//先全部设置为0
		for (int j = 0; j < iHolesNum; j++)
			dbTempAry[i][j] = 0;

	//计算新增加的信息素,保存到临时数组里
	int m = 0;
	int n = 0;
	//计算目前最优蚂蚁留下的信息素
	double dbTemp = 1.0 / m_cTempAnt.m_dbPathLength;
    for (int j = 1; j < iHolesNum; j++)
	{
		m = m_cTempAnt.m_nPath[j];
		n = m_cTempAnt.m_nPath[j - 1];
		//cout << dbTempAry[n][m];
		dbTempAry[n][m] = dbTempAry[n][m] + dbTemp;
		dbTempAry[m][n] = dbTempAry[n][m];
	}

	//最后城市和开始城市之间的信息素
	n = m_cTempAnt.m_nPath[0];
	dbTempAry[n][m] = dbTempAry[n][m] + dbTemp;
	dbTempAry[m][n] = dbTempAry[n][m];


	//==================================================================
	//更新环境信息素
    for (int i = 0; i < iHolesNum; i++)
	{
        for (int j = 0; j < iHolesNum; j++)
		{
			g_Pheromone[i][j] = g_Pheromone[i][j] * ROU + dbTempAry[i][j];  //最新的环境信息素 = 留存的信息素 + 新留下的信息素
		}
	}

	//==================================================================
	//检查环境信息素，如果在最小和最大值的外面，则将其重新调整
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
	//计算两两城市间的选择概率值
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
		//每只蚂蚁搜索一遍
		for (int j = 0; j < N_ANT_COUNT; j++)
		{ 
			m_cAntAry[j].Search();
		}


		//保存最佳结果
		for (int j = 0; j < N_ANT_COUNT; j++)
		{
			//保存搜索最优解
			if (m_cAntAry[j].m_dbPathLength < m_cGlobalBestAnt.m_dbPathLength)
			{
				m_cGlobalBestAnt = m_cAntAry[j];
				if (i == 0) {
					for (int k = 0; k < iHolesNum; k++)
						m_cGlobalBestAnt.m_nPath[k] = aRoute[k];
					m_cGlobalBestAnt.CalPathLength();
				}
			}

			//保存迭代最优解
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
		// 更新环境信息素，使用全局最优和迭代最优交替更新的策略
		// 每过5次迭代使用一次全局最优蚂蚁更新信息素
		// 这样可以扩大搜索范围
		if ((i + 1) % 5 == 0)
		{
			UpdatePheromone(1);
		}
		else
		{
			UpdatePheromone(0);
		}

		//输出本次迭代的结果

		cout<<"["<<i<<"]:"<< m_cGlobalBestAnt.m_dbPathLength<<endl;
	}

}

//贪婪算法
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
	cout << "贪婪算法结束" << endl;
	delete[] bIfChoosen;
}
