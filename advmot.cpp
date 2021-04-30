#include "advmot.h"
#include "QDebug"

AdvMot::AdvMot()
{

}

AdvMot::AdvMot(U32 devSeries)
{
    u32Ret = Acm_DevOpen(devSeries, &pDevHandle);//打开板卡，获取设备Handle
    u32Ret = devSeries;
    u32Ret = Acm_GetU32Property(pDevHandle, FT_DevAxesCount, &u32AxisCount);//获取轴数量

        //根据轴数，将所有轴打开
    for (U32 u32AxisNum=0; u32AxisNum<u32AxisCount; u32AxisNum++)
    {
        u32Ret = Acm_AxOpen(pDevHandle, (USHORT)u32AxisNum, &pAxisHandle[u32AxisNum]);//打开轴，获取每个轴的Handle
        //Acm_AxSetCmdPosition(pAxisHandle[u32AxisNum], 0);//设置轴的命令位置为0
        //Acm_AxSetActualPosition(pAxisHandle[u32AxisNum], 0);//设置轴的实际位置为0
    }
    u32Ret = Acm_GpAddAxis(&pGroupHandle, pAxisHandle[1]);
    u32Ret = Acm_GpAddAxis(&pGroupHandle, pAxisHandle[2]);
    u32Ret = Acm_AxSetSvOn(pAxisHandle[0], 1);//打开0轴伺服
    u32Ret = Acm_AxSetSvOn(pAxisHandle[1], 1);
    u32Ret = Acm_AxSetSvOn(pAxisHandle[2], 1);
    qDebug() << "init successfully";
}

void AdvMot::AxInit()
{
    qDebug() << "init success";
}

void AdvMot::paraSet(U32 vmax, U32 vmin, U32 acc, U32 dec, I32 axJerk, F64 targetPos, F64 targetDis)
{
    u32AxVelHigh = vmax;
    u32AxVelLow = vmin;
    u32AxAcc = acc;
    u32AxDec = dec;
    i32AxJerk = axJerk;
    f64TargetPos = targetPos;
    f64TargetDis = targetDis;
}

void AdvMot::AxGo(int selectXYZ)
{

    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxVelLow, u32AxVelLow);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxVelHigh, u32AxVelHigh);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxAcc, u32AxAcc);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxDec, u32AxDec);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ],PAR_AxJerk, i32AxJerk);

    u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ], f64TargetPos);

    //读取轴的状态和位置
    Acm_AxGetCmdPosition(pAxisHandle[selectXYZ], &fCmdPosition);
    Acm_AxGetActualPosition(pAxisHandle[selectXYZ], &fActPosition);
    Acm_AxGetState(pAxisHandle[selectXYZ], &u16State);
}

void AdvMot::AxMov(int selectXYZ)
{
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxVelLow, u32AxVelLow);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxVelHigh, u32AxVelHigh);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxAcc, u32AxAcc);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ], PAR_AxDec, u32AxDec);
    u32Ret = Acm_SetF64Property(pAxisHandle[selectXYZ],PAR_AxJerk, i32AxJerk);

    u32Ret = Acm_AxMoveRel(pAxisHandle[selectXYZ], f64TargetDis);

    //读取轴的状态和位置
    Acm_AxGetCmdPosition(pAxisHandle[selectXYZ], &fCmdPosition);
    Acm_AxGetActualPosition(pAxisHandle[selectXYZ], &fActPosition);
    Acm_AxGetState(pAxisHandle[selectXYZ], &u16State);
}
void AdvMot::GpGo(int i)
{
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpVelLow, 30000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpVelHigh, 30000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpAcc, 60000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpDec, 60000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpJerk, 0);
    U32 ArrayElementCnt = 2;

    double m_spinneret[3][2] = {{-15521856, 150626}, {-15371856, 150626}, {-15231855, 150626}};
    u32Ret = Acm_GpGetState(pGroupHandle, &GpState);
//    qDebug() << GpState << endl;

    //判断轴状态，不为ready时延时
    do
    {
        u32Ret = Acm_GpGetState(pGroupHandle, &GpState);
        //cout << GpState << endl;
        // 群组状态错误时复位
        if (GpState == 3)
            u32Ret = Acm_GpResetError(pGroupHandle);
    }while(GpState != 1);
    u32Ret = Acm_GpMoveLinearAbs(pGroupHandle, m_spinneret[i], &ArrayElementCnt);

}

void AdvMot::GpMov(int i, double *holeArray)
{
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpVelLow, 30000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpVelHigh, 30000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpAcc, 60000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpDec, 60000);
    u32Ret = Acm_SetF64Property(pGroupHandle, PAR_GpJerk, 0);
    U32 ArrayElementCnt = 2;
    double holeMov[2] = {*holeArray, *(holeArray + 1)};
//    double m_End[2];
//    double m_now[2];
//    m_now[0] = -15521179;
//    m_now[1] = 151168;

    u32Ret = Acm_GpGetState(pGroupHandle, &GpState);
//    qDebug() << GpState << endl;



    //运动到第一个孔的位置
    u32Ret = Acm_GpMoveLinearAbs(pGroupHandle, holeMov, &ArrayElementCnt);

    //判断轴状态，不为ready时延时
    do
    {
        u32Ret = Acm_GpGetState(pGroupHandle, &GpState);
        //cout << GpState << endl;


        // 群组状态错误时复位
        if (GpState == 3)
            u32Ret = Acm_GpResetError(pGroupHandle);
    }while(GpState != 1);
}
void AdvMot::ztest()
{
    qDebug() << "zwy test successfully";
}

AdvMot::~AdvMot()
{
    //操作执行完毕，关闭轴、群组、设备
    Acm_GpClose(&pGroupHandle);//关闭群组

    for (uint u32AxisNum=0; u32AxisNum<u32AxisCount; u32AxisNum++)
    {
        u32Ret = Acm_AxSetSvOn(pAxisHandle[u32AxisNum], 0);
        Acm_AxClose(&pAxisHandle[u32AxisNum]);//关闭每个被打开的轴

    }

    Acm_DevClose(&pDevHandle);
}
