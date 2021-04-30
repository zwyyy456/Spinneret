// MMAS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "antpath.h"
int main()
{
	//初始化随机种子
	time_t tm;
	time(&tm);
	unsigned int nSeed = (unsigned int)tm;
	srand(nSeed);

	char cTemp = 0;

	//开始搜索
	CTsp tsp;

	while (cTemp != 97)
	{
		commonInit(iHolesNum);

		int nTemp;
		ifstream infile;
		infile.open("data.txt");
		if (!infile.is_open())
			cout << "error!" << endl;
		infile >> nTemp;
		for (int i = 0; i < iHolesNum; ++i)
		{
			infile >> nTemp;
			infile >> x_Ary[i];
			//cout << C[i][0] << " ";
			infile >> y_Ary[i];
			//cout << C[i][1] << endl;
		}
		infile.close();


		tsp.InitData();
		tsp.fnGreedy();
		tsp.Search();

		//输出结果
		printf("\n\n最佳路径如下 :\n");

		char cBuf[128];
		for (int i = 0; i < N_CITY_COUNT; i++)
		{
			sprintf_s(cBuf, "%d ", tsp.m_cGlobalBestAnt.m_nPath[i] + 1);
			printf(cBuf);
		}

		sprintf_s(cBuf, "\n\n本次运行的随机种子是 : %d ", nSeed);
		printf(cBuf);

		printf("\n\n按下回车再次搜索，按下字母'a'然后按回车退出程序!");

		scanf_s("%c", &cTemp);
	}
	//getchar();
	delete_New(iHolesNum);
	return 0;
}

