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
	CAnt m_cGlobalBestAnt; //保存全局最优结果
	CAnt m_cIterationBestAnt; //保存迭代最优结果
	CAnt m_cTempAnt; //临时

	double m_dbRate; //最大信息素和最小信息素的比值

	double Qmax; //信息素上限
	double Qmin;  //信息素下限


public:

	//初始化数据
	void InitData();

	//开始搜索
	void Search();

	//更新环境信息素
	void UpdatePheromone(int nFlag);

	void fnGreedy();//局部贪婪算法
};
