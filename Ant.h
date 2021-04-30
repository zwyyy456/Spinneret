#pragma once
#include"Common.h"

class CAnt
{
public:
	CAnt(void);
	~CAnt(void);

public:


	double m_dbPathLength; //蚂蚁走过的路径长度
    vector<int> m_nPath;//声明变长数组
    vector<int> m_nAllowedCity;//声明变长数组
//    QVector<int> m_nPath;
//    QVector<int> m_nAllowedCity;
    //vector<vector<int> > a(row,vector<int>(column));
    //int* m_nPath; //蚂蚁走的路径
    //int* m_nAllowedCity; //没去过的城市

	int m_nCurCityNo; //当前所在城市编号
	int m_nMovedCityCount; //已经去过的城市数量

	bool m_blGreedSearch; //是否使用贪心原则选择下一城市
public:

	int ChooseNextCity(); //选择下一个城市

	void Init(); //初始化
	void Move(); //蚂蚁在城市间移动
	void Search(); //搜索路径
	void CalPathLength(); //计算蚂蚁走过的路径长度

};

