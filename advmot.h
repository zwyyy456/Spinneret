#ifndef ADVMOT_H
#define ADVMOT_H

#include "AdvMotApi.h"

class AdvMot
{
public:
    AdvMot();

    U32 u32Ret = 0;
    void AxInit();
    void AxMov(int selectXYZ);
    void AxGo(int selectXYZ);
    void GpGo(int i);
    void GpMov(int i, double *holArray);
    void AxServSeton(int i);
    void AxStateJudge(int selectXYZ);
    void GpStateJudge();
//    void AxMovy(int selectXYZ);
//    void AxGoy(int selectXYZ);
//    void AxMovz(int selectXYZ);
//    void AxGoz(int selectXYZ);


    AdvMot(U32 devSeries);
    ~AdvMot();
    void paraSet(U32 vmax, U32 vmin, U32 acc, U32 dec, I32 axJerk, F64 targetPos, F64 targetDis);


    void ztest();//调用构造函数时对设备进行初始化


    F64 fCmdPosition;//命令位置
    F64 fActPosition;//实际位置
    U16 u16State;//轴状态
    HAND pAxisHandle[3];//轴的Handle
    U16 GpState;

private:
    HAND pDevHandle;
    HAND pGroupHandle;//群组Handle
    U32 u32DevSerisNum;//设备编号
    U32 u32AxisCount;//轴数量
    U32 u32AxVelHigh;
    U32 u32AxVelLow ; //设置最小运动速度
    U32 u32AxAcc ;  //设置运动加速度
    U32 u32AxDec ;  //设置运动减速度
    I32 i32AxJerk ;  //设置默认运动曲线类型
    F64 f64TargetPos;//设置目标位置
    F64 f64TargetDis;//设置目标运动距离




};

#endif // ADVMOT_H
