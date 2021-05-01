#include "vision.h"
#include "Common.h"

QImage vision::img2QImage(HANDLE hImg) //相机图像转为Qt图像格式
{
    int w = MVImageGetWidth(hImg);
    int h = MVImageGetHeight(hImg);
    int bpp = MVImageGetBPP(hImg);
    int pitch = MVImageGetPitch(hImg);
    unsigned char *pImgData = (unsigned char *)MVImageGetBits(hImg);
    if (bpp == 8)
    {
        uchar *pSrc = pImgData;
        QImage image(pSrc, w,h, pitch, QImage::Format_Indexed8);
        image.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        return image;
    }
    else if (bpp == 24)
    {
        const uchar *pSrc = (const uchar*)pImgData;
        QImage image(pSrc, w,h, pitch, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else
    {
        return QImage();
    }
}

cv::Mat vision::QImage2cvMat(QImage image) //QImage转为cvMat格式
{
    cv::Mat mat;
    //qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

int vision::cam_initial() //将两个相机初始化
{
    MVGetNumOfCameras(&n_cams);  // 获取相机数量
    //无相机
    if (n_cams == 0)
        return 0;
    //打开连接到电脑上的第一个相机
    MVSTATUS_CODES r1 = MVOpenCamByIndex(0, &m_hCam_micro);
    if (m_hCam_micro == NULL)
    {
        if (r1 == MVST_ACCESS_DENIED)
            return 1;
        else
            return 2;
    }
    MVSetTriggerMode(m_hCam_micro, TriggerMode_Off); //设置为连续非触发模式
    //获取相机的宽、高、像素格式
    MVGetWidth(m_hCam_micro, &w_micro);
    MVGetHeight(m_hCam_micro, &h_micro);
    MVGetPixelFormat(m_hCam_micro, &PixelFormat_micro);
    //根据相机的宽、高、像素格式创建图像
    if (PixelFormat_micro == PixelFormat_Mono8)
        m_hImg_micro = MVImageCreate(w_micro, h_micro, 8);
    else
        m_hImg_micro = MVImageCreate(w_micro, h_micro, 24);
    //打开连接到电脑上的第二个相机
    MVSTATUS_CODES r2 = MVOpenCamByIndex(1, &m_hCam_whole);
    if (m_hCam_whole == NULL)
    {
        if (r2 == MVST_ACCESS_DENIED)
            return 3;
        else
            return 4;
    }
    MVSetTriggerMode(m_hCam_whole, TriggerMode_Off);
    MVGetWidth(m_hCam_whole, &w_whole);
    MVGetHeight(m_hCam_whole, &h_whole);
    MVGetPixelFormat(m_hCam_whole, &PixelFormat_whole);
    if (PixelFormat_whole == PixelFormat_Mono8)
        m_hImg_whole = MVImageCreate(w_whole, h_whole, 8);
    else
        m_hImg_whole = MVImageCreate(w_whole, h_whole, 24);
    return 5;
}

int vision::cam1_initial()
{
    MVGetNumOfCameras(&n_cams);  // 获取相机数量
    //无相机
    if (n_cams == 0)
        return 0;
    MVSTATUS_CODES r1 = MVOpenCamByIndex(1, &m_hCam_whole);
    if (m_hCam_whole == NULL)
    {
        if (r1 == MVST_ACCESS_DENIED)
            return 1;
        else
            return 2;
    }
    MVSetTriggerMode(m_hCam_whole, TriggerMode_Off); //设置为连续非触发模式
    //获取相机的宽、高、像素格式
    MVGetWidth(m_hCam_whole, &w_whole);
    MVGetHeight(m_hCam_whole, &h_whole);
    MVGetPixelFormat(m_hCam_whole, &PixelFormat_whole);
    //根据相机的宽、高、像素格式创建图像
    if (PixelFormat_whole == PixelFormat_Mono8)
        m_hImg_whole = MVImageCreate(w_whole, h_whole, 8);
    else
        m_hImg_whole = MVImageCreate(w_whole, h_whole, 24);
    return 3;
}

int vision::cam2_initial()
{
    MVGetNumOfCameras(&n_cams);  // 获取相机数量
    //无相机
    if (n_cams == 0)
        return 0;
    MVSTATUS_CODES r1 = MVOpenCamByIndex(0, &m_hCam_micro);
    if (m_hCam_micro == NULL)
    {
        if (r1 == MVST_ACCESS_DENIED)
            return 1;
        else
            return 2;
    }
    MVSetTriggerMode(m_hCam_micro, TriggerMode_Off); //设置为连续非触发模式
    //获取相机的宽、高、像素格式
    MVGetWidth(m_hCam_micro, &w_micro);
    MVGetHeight(m_hCam_micro, &h_micro);
    MVGetPixelFormat(m_hCam_micro, &PixelFormat_micro);
    //根据相机的宽、高、像素格式创建图像
    if (PixelFormat_micro == PixelFormat_Mono8)
        m_hImg_micro = MVImageCreate(w_micro, h_micro, 8);
    else
        m_hImg_micro = MVImageCreate(w_micro, h_micro, 24);
    return 3;
}

bool vision::cam1_singlegrab()
{
    MVSTATUS_CODES r3 = MVSingleGrab(m_hCam_whole, m_hImg_whole, 150);
    if (r3 == MVST_SUCCESS)
    {
        cam1_qimg = img2QImage(m_hImg_whole);
        return true;
    }
    else
        return false;
}

bool vision::cam2_singlegrab()
{
    MVSTATUS_CODES r4 = MVSingleGrab(m_hCam_micro, m_hImg_micro, 150);
    if (r4 == MVST_SUCCESS)
    {
        cam2_qimg = img2QImage(m_hImg_micro);
        return true;
    }
    else
        return false;
}

void vision::cam1_startgrab()
{
    if (m_bRun_micro)
    {
        MVStopGrab(m_hCam_micro);
        m_bRun_micro = FALSE;
    }
    if (m_hPropDlg_micro != NULL)
    {
        MVCamProptySheetCameraRun(m_hPropDlg_micro, MVCameraRun_OFF);
    }
    m_bRun_whole = TRUE;
    if (m_hPropDlg_whole != NULL)
    {
        MVCamProptySheetCameraRun(m_hPropDlg_whole, MVCameraRun_ON);
    }
}

void vision::cam2_startgrab()
{
    if (m_bRun_whole)
    {
        MVStopGrab(m_hCam_whole);
        m_bRun_whole = FALSE;
    }
    if (m_hPropDlg_whole != NULL)
    {
        MVCamProptySheetCameraRun(m_hPropDlg_whole, MVCameraRun_OFF);
    }
    m_bRun_micro = TRUE;
    if (m_hPropDlg_micro != NULL)
    {
        MVCamProptySheetCameraRun(m_hPropDlg_micro, MVCameraRun_ON);
    }
}

void vision::cam1_stopgrab()
{
    if (m_bRun_whole)
    {
        MVStopGrab(m_hCam_whole);
        m_bRun_whole = FALSE;
    }
    if (m_hPropDlg_whole != NULL)
    {
        MVCamProptySheetCameraRun(m_hPropDlg_whole, MVCameraRun_OFF);
    }
}

void vision::cam2_stopgrab()
{
    if (m_bRun_micro)
    {
        MVStopGrab(m_hCam_micro);
        m_bRun_micro = FALSE;
    }
    if (m_hPropDlg_micro != NULL)
    {
        MVCamProptySheetCameraRun(m_hPropDlg_micro, MVCameraRun_OFF);
    }
}

void vision::whole_findholes()
{
    cam1_mat = QImage2cvMat(cam1_qimg);
    //阈值分割（二值化）
    cv::Mat dstimg = cv::Mat::zeros(cam1_mat.size(),CV_8UC1);
    threshold(cam1_mat, dstimg, 170 , 255, 0);
    //掩膜
    cv::Point2f center[1];
    center[0].x = 1238;
    center[0].y = 1019;
    cv::Mat mask = cv::Mat::zeros(dstimg.size(),CV_8UC1);
    cv::circle(mask,center[0],850,cv::Scalar(255),-1);
    cv::Mat maskimg = cv::Mat::zeros(dstimg.size(),CV_8UC1);
    dstimg.copyTo(maskimg,mask);
    //找出内部孔坐标
    int num=0;
    for(int j=0; j<maskimg.rows; j++)
    {
        uchar* data = maskimg.ptr<uchar>(j);
        for(int i=0; i<maskimg.cols; i++)
        {
            if(data[i]==0)
                continue;
            else
            {
                num++;
                int count = 0;
                int tmp_x=0,tmp_y=0;
                for(int row=j; row<j+15; row++)
                {
                    uchar* tmp = maskimg.ptr<uchar>(row);
                    for(int col=i-10; col<i+11; col++)
                    {
                        if(tmp[col]==255)
                        {
                            tmp[col]=0;
                            count++;
                            tmp_x+=col;
                            tmp_y+=row;
                        }
                    }
                }
                pix[num-1][0]=tmp_x/count;
                pix[num-1][1]=tmp_y/count;
            }
        }
    }
    iHolesNum = num;
    commonInit(iHolesNum);
    cam1_mat = cv::Mat(maskimg.size(),CV_8UC3,cv::Scalar(255,255,255));
    for(int i=0; i<num; i++)
    {
        cv::Point center;
        center.x = pix[i][0];
        center.y = pix[i][1];
        cv::circle(cam1_mat,center,10,cv::Scalar(255,0,0),-1);
        x_Ary[i] = pix[i][0];
        y_Ary[i] = pix[i][1];
    }
    cv::cvtColor(cam1_mat,cam1_mat,cv::COLOR_BGR2RGB);
    cam1_qimg = QImage((const unsigned char*)(cam1_mat.data),cam1_mat.cols,cam1_mat.rows,cam1_mat.cols*cam1_mat.channels(),QImage::Format_RGB888);
}

void vision::micro_checkhole()
{
    cam2_mat = QImage2cvMat(cam2_qimg);
    //感兴趣区域提取
    cv::Mat imgroi = cv::Mat::zeros(cam2_mat.size(),CV_8UC1);
    cam2_mat(cv::Rect(450, 300, 720, 600)).copyTo(imgroi);
    //阈值分割（二值化）
    cv::Mat dstimg = cv::Mat::zeros(imgroi.size(),CV_8UC1);
    threshold(imgroi, dstimg, 100 , 255, 0);
    //缺陷检测
    int pix_num = 0;
    //【1】统计白色像素个数
    cv::Mat_<uchar>::iterator it = dstimg.begin<uchar>();
    cv::Mat_<uchar>::iterator itend = dstimg.end<uchar>();
    for (; it != itend; ++it)
    {
        if ((*it) > 0) pix_num += 1;
    }
    str = "white pix num:";
    str.append(QString::number(pix_num)+"\n");
    double s1 = pix_num;
    //【2】轮廓检测
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(dstimg, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    std::vector<cv::Point2f>center(contours.size());
    std::vector<float>radius(contours.size());
    int cx[1000] = { 0 }, cy[1000] = { 0 };//储存所有轮廓点像素
    int ca = 0;
    for(int i=0;i<contours.size();i++)
    {
        for (int j = 0; j < contours[i].size(); j++)
        {
            cx[ca] = contours[i][j].x;
            cy[ca] = contours[i][j].y;
            ca++;
        }
    }
    //【3】求圆度、堵塞率
    double ex = 0, ey = 0, ex2 = 0, ey2 = 0, exy = 0, ex3 = 0, exy2 = 0, ex2y2 = 0, ey3 = 0, ex2y = 0;//x、y、x^2、y^2、xy、x^3、xy^2、x^2+y^2、y^3、x^2y求和
    double M11 = 0, M12 = 0, M22 = 0, H1 = 0, H2 = 0;
    double x0, y0;//最小二乘圆心坐标和半径
    for (int i = 0; i < ca; i++)
    {
        ex = cx[i] + ex;
        ey = cy[i] + ey;
        ex2 = pow(cx[i], 2) + ex2;
        ey2 = pow(cy[i], 2) + ey2;
        exy = cx[i] * cy[i] + exy;
        ex3 = pow(cx[i], 3) + ex3;
        exy2 = cx[i] * pow(cy[i], 2) + exy2;
        ex2y2 = pow(cx[i], 2) + pow(cy[i], 2) + ex2y2;
        ey3 = pow(cy[i], 3) + ey3;
        ex2y = pow(cx[i], 2) * cy[i] + ex2y;
    }
    M11 = ca* ex2 - ex * ex;
    M12 = ca * exy - ex * ey;
    M22 = ca * ey2 - ey * ey;
    H1 = ca * ex3 + ca * exy2 - ex2y2 * ex;
    H2 = ca* ey3 + ca * ex2y - ex2y2 * ey;
    x0 = -(H2 * M12 - H1 * M22) / (M11 * M22 - M12 * M12) / 2;
    y0 = -(H2 * M11 - H1 * M12) / (M12 * M12 - M11 * M22) / 2;
    str.append("center location:["+QString::number(x0)+","+QString::number(y0)+"]\n");
    //【4】求圆度误差
    double rq = 500, rw = 0;//最大内接圆与最小外接圆半径
    for (int i = 0; i < ca; i++)
    {
        double rs = sqrt(pow((cx[i] - x0), 2) + pow((cy[i] - y0), 2));
        if (rq > rs)
        { rq = rs; }
        if (rw < rs)
        { rw = rs; }
    }
    double yd = rw - rq;
    double s2 = CV_PI * rw * rw ;
    double dsl = 1 - s1 / s2;
    str.append("max inner circle: R = "+QString::number(rq)+"\n");
    str.append("min outter circle: R = "+QString::number(rw)+"\n");
    str.append("block ratio: "+QString::number(dsl*100)+"%\n");
    str.append("circle error: "+QString::number(yd)+"\n");
}

bool vision::micro_focus()
{
    cam2_mat = QImage2cvMat(cam2_qimg);
    cv::Mat sobel;
    cv::Sobel(cam2_mat, sobel, CV_16U, 1, 1);
    double meanValue = mean(sobel)[0];
    if(meanValue <= focusValue)
        return false;
    else
    {
        focusValue = meanValue;
        return true;
    }
}
