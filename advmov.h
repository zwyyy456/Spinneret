#ifndef ADVMOV_H
#define ADVMOV_H


class AdvMov
{
public:
    AdvMov();
    U32 u32Ret = 0;
//    void AxInit();
//    void AxMov(int i);
    AdvMot(U32 devSeries);
    void ztest();//调用构造函数时对设备进行初始化

private:
    HAND pDevHandle;
//    HAND pAxisHandle[32];//轴的Handle
//    HAND pGroupHandle;//群组Handle
//    U32 u32DevSerisNum;//设备编号
//    U32 u32AxisCount;//轴数量
//    U32 u32AxVelHigh;
//    U32 u32AxVelLow ; //设置最小运动速度
//    U32 u32AxAcc ;  //设置运动加速度
//    U32 u32AxDec ;  //设置运动减速度
//    I32 i32AxJerk ;  //设置默认运动曲线类型
};

#endif // ADVMOV_H
