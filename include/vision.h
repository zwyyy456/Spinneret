#ifndef VISION_H
#define VISION_H

#include <QMainWindow>
#include "MVGigE.h"
#include "MVImageC.h"
#include "MVCamProptySheet.h"
#include "opencv2/opencv.hpp"

//cam1为全局相机, cam2为微孔相机
class vision
{
private:
    int n_cams;
    bool m_bRun_micro, m_bRun_whole;
    MV_PixelFormatEnums PixelFormat_micro;
    MV_PixelFormatEnums PixelFormat_whole;

public:
    HANDLE m_hCam_micro, m_hCam_whole;
    HANDLE m_hPropDlg_micro, m_hPropDlg_whole;
    HANDLE m_hImg_micro, m_hImg_whole;
    char cam1_IP[20];
    char cam2_IP[20];
    int pix[300][2];
    vision()
    {
        n_cams = 0;
        m_bRun_micro = false;
        m_bRun_whole = false;
        m_hCam_micro = NULL;
        m_hCam_whole = NULL;
        m_hPropDlg_micro = NULL;
        m_hPropDlg_whole = NULL;
        m_hImg_micro= NULL;
        m_hImg_whole= NULL;
        MVInitLib();  // 初始化相机函数库
        strcpy(cam1_IP, "192.168.2.101");
        strcpy(cam2_IP, "169.254.111.121");
    }
    QImage img2QImage(HANDLE hImg); //相机图像转为Qt图像格式
    QString str;
    cv::Mat QImage2cvMat(QImage image); //QImage转为cvMat格式
    int cam_initial();
    int cam1_initial();
    int cam2_initial();
    QImage cam1_qimg, cam2_qimg;
    cv::Mat cam1_mat, cam2_mat;
    int w_micro, h_micro;
    int w_whole, h_whole;
    bool cam1_singlegrab();
    bool cam2_singlegrab();
    void cam1_startgrab();
    void cam2_startgrab();
    void cam1_stopgrab();
    void cam2_stopgrab();
    void whole_findholes();
    void micro_checkhole();
    ~vision()
    {
        //关闭微孔相机及属性页
        if (m_hCam_micro != NULL)
        {
            MVCloseCam(m_hCam_micro);
            m_hCam_micro = NULL;
        }
        if (m_hPropDlg_micro != NULL)
        {
            MVCamProptySheetDestroy(m_hPropDlg_micro);
            m_hPropDlg_micro = NULL;
        }
        //关闭全局相机及属性页
        if (m_hCam_whole != NULL)
        {
            MVCloseCam(m_hCam_whole);
            m_hCam_whole = NULL;
        }
        if (m_hPropDlg_whole != NULL)
        {
            MVCamProptySheetDestroy(m_hPropDlg_whole);
            m_hPropDlg_whole = NULL;
        }
        MVTerminateLib();
    }
};


#endif // VISION_H
