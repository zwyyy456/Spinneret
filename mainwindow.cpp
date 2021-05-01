#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vision.h"
#include <QMessageBox>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <QDebug>
#include <QFile>
#include <QTableView>
#include <QStandardItem>
#include <QSqlQueryModel>
#include "advmot.h"
#include <QFileDialog>
#include <QTimer>
#include "secondwidget.h"

#include "stdafx.h"
#include "antpath.h"
vision camera;
AdvMot mAdv(0x66000000);
bool running = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    //导航栏
    ui->navibut1->setStyleSheet(style_navibut1);
    ui->navibut2->setStyleSheet(style_navibut2);
    ui->navibut3->setStyleSheet(style_navibut3);
    ui->navibut4->setStyleSheet(style_navibut4);
    ui->navibut5->setStyleSheet(style_navibut5);
    //菜单栏
    ui->menubut1->setStyleSheet(style_menubut);
    ui->menubut2->setStyleSheet(style_menubut);
    ui->menubut3->setStyleSheet(style_menubut);
    ui->menubut4->setStyleSheet(style_menubut);
    //检测主页
    ui->main_init->setStyleSheet(style_pushbut1);
    ui->main_link->setStyleSheet(style_pushbut1);
    ui->main_method->setStyleSheet(style_combobox);
    ui->main_position->setStyleSheet(style_combobox);
    ui->main_type->setStyleSheet(style_combobox);
    ui->main_go->setStyleSheet(style_pushbut1);
    ui->main_cam1->setStyleSheet(style_labelcam);
    ui->main_cam2->setStyleSheet(style_labelcam);
    ui->main_start->setStyleSheet(style_pushbut2);
    ui->main_pause->setStyleSheet(style_pushbut2);
    ui->main_stop->setStyleSheet(style_pushbut2);
    ui->main_restart->setStyleSheet(style_pushbut2);
    ui->main_lightpc->setStyleSheet(style_light0);
    ui->main_lightx->setStyleSheet(style_light0);
    ui->main_lighty->setStyleSheet(style_light0);
    ui->main_lightz->setStyleSheet(style_light0);
    ui->main_lightcam1->setStyleSheet(style_light0);
    ui->main_lightcam2->setStyleSheet(style_light0);
    ui->main_moveup->setStyleSheet(style_pushbut1);
    ui->main_movedown->setStyleSheet(style_pushbut1);
    ui->main_movefront->setStyleSheet(style_pushbut1);
    ui->main_moveback->setStyleSheet(style_pushbut1);
    ui->main_moveleft->setStyleSheet(style_pushbut1);
    ui->main_moveright->setStyleSheet(style_pushbut1);
    ui->main_save->setStyleSheet(style_pushbut1);
    //设备调试
    ui->equipx_method->setStyleSheet(style_combobox);
    ui->equipy_method->setStyleSheet(style_combobox);
    ui->equipz_method->setStyleSheet(style_combobox);
    ui->equipx_debug->setStyleSheet(style_pushbut1);
    ui->equipy_debug->setStyleSheet(style_pushbut1);
    ui->equipz_debug->setStyleSheet(style_pushbut1);
    ui->equipx_go->setStyleSheet(style_pushbut1);
    ui->equipy_go->setStyleSheet(style_pushbut1);
    ui->equipz_go->setStyleSheet(style_pushbut1);
    ui->equipx_goleft->setStyleSheet(style_pushbut1);
    ui->equipx_goright->setStyleSheet(style_pushbut1);
    ui->equipy_goback->setStyleSheet(style_pushbut1);
    ui->equipy_gofront->setStyleSheet(style_pushbut1);
    ui->equipz_goup->setStyleSheet(style_pushbut1);
    ui->equipz_godown->setStyleSheet(style_pushbut1);
    ui->equip_linkcam1->setStyleSheet(style_pushbut1);
    ui->equip_linkcam2->setStyleSheet(style_pushbut1);
    ui->equip_IPcam1->setStyleSheet(style_pushbut1);
    ui->equip_IPcam2->setStyleSheet(style_pushbut1);
    ui->equip_procam1->setStyleSheet(style_pushbut1);
    ui->equip_procam2->setStyleSheet(style_pushbut1);
    ui->equip_singlegrabcam1->setStyleSheet(style_pushbut1);
    ui->equip_singlegrabcam2->setStyleSheet(style_pushbut1);
    ui->equip_grabcam1->setStyleSheet(style_pushbut1);
    ui->equip_grabcam2->setStyleSheet(style_pushbut1);
    ui->equip_stopcam1->setStyleSheet(style_pushbut1);
    ui->equip_stopcam2->setStyleSheet(style_pushbut1);
    ui->equip_savecam1->setStyleSheet(style_pushbut1);
    ui->equip_savecam2->setStyleSheet(style_pushbut1);
    ui->equip_cam1->setStyleSheet(style_labelcam);
    ui->equip_cam2->setStyleSheet(style_labelcam);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Delay_MSec(unsigned int msec)//延时函数
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}

void MainWindow::on_navibut1_pressed()
{
     ui->stackedWidget->setCurrentWidget(ui->page);
}
void MainWindow::on_navibut2_pressed()
{
     ui->stackedWidget->setCurrentWidget(ui->page_2);
}
void MainWindow::on_navibut3_pressed()
{
     ui->stackedWidget->setCurrentWidget(ui->page_3);
}
void MainWindow::on_navibut4_pressed()
{
     ui->stackedWidget->setCurrentWidget(ui->page_4);
}
void MainWindow::on_navibut5_pressed()
{
     ui->stackedWidget->setCurrentWidget(ui->page_5);
}



int __stdcall StreamCB_whole(MV_IMAGE_INFO* pInfo, ULONG_PTR nUserVal)
{
    MainWindow* pWd = (MainWindow*)nUserVal;
    return (pWd->showStreamOnLabel_whole(pInfo));
}
int MainWindow::showStreamOnLabel_whole(MV_IMAGE_INFO* pInfo)
{
    MVInfo2Image(camera.m_hCam_whole,pInfo,(MVImage*)camera.m_hImg_whole);
    camera.cam1_qimg = camera.img2QImage(camera.m_hImg_whole);
    QPixmap pixmap1,pixmap2;
    pixmap1 = pixmap1.fromImage(camera.cam1_qimg);
    pixmap1 = pixmap1.scaled(ui->main_cam1->width(), ui->main_cam1->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->main_cam1->setPixmap(pixmap1);
    pixmap2 = pixmap2.fromImage(camera.cam1_qimg);
    pixmap2 = pixmap2.scaled(ui->equip_cam1->width(), ui->equip_cam1->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->equip_cam1->setPixmap(pixmap2);
    return 0;
}
int __stdcall StreamCB_micro(MV_IMAGE_INFO* pInfo, ULONG_PTR nUserVal)
{
    MainWindow* pWd = (MainWindow*)nUserVal;
    return (pWd->showStreamOnLabel_micro(pInfo));
}
int MainWindow::showStreamOnLabel_micro(MV_IMAGE_INFO* pInfo)
{
    MVInfo2Image(camera.m_hCam_micro,pInfo,(MVImage*)camera.m_hImg_micro);
    camera.cam2_qimg = camera.img2QImage(camera.m_hImg_micro);
    QPixmap pixmap1,pixmap2;
    pixmap1 = pixmap1.fromImage(camera.cam2_qimg);
    pixmap1 = pixmap1.scaled(ui->main_cam2->width(), ui->main_cam2->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->main_cam2->setPixmap(pixmap1);
    pixmap2 = pixmap2.fromImage(camera.cam2_qimg);
    pixmap2 = pixmap2.scaled(ui->equip_cam2->width(), ui->equip_cam2->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->equip_cam2->setPixmap(pixmap2);
    return 0;
}

void MainWindow::on_main_init_clicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    int error = camera.cam_initial();
    if(error == 5)
    {
        ui->main_link->setEnabled(true);
        QApplication::restoreOverrideCursor();
        ui->equip_linkcam1->setEnabled(false);
        ui->equip_linkcam2->setEnabled(false);
    }
    else if(error == 0)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","没有找到相机, 请检查相机的IP地址以及相机接线!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else if(error == 1)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接微孔相机，请关闭可能在控制相机的程序!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else if(error == 2)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接微孔相机!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else if(error == 3)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接全局相机，请关闭可能在控制相机的程序!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接全局相机!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    mAdv.AxInit();
    for (int z = 0; z < 3; z++)
        mAdv.AxServSeton(z);
}

void MainWindow::on_main_link_clicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    bool error = camera.cam2_singlegrab();
    if(error == true)
    {
        QApplication::restoreOverrideCursor();
        QPixmap pixmap;
        pixmap = pixmap.fromImage(camera.cam2_qimg);
        pixmap = pixmap.scaled(ui->main_cam2->width(), ui->main_cam2->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->main_cam2->setPixmap(pixmap);
    }
    else
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","微孔相机无法单帧拍摄!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    MVSTATUS_CODES r5 = MVStartGrab(camera.m_hCam_whole, StreamCB_whole, (ULONG_PTR)this);
    if(r5 == MVST_SUCCESS)
    {
        camera.cam1_startgrab();
        ui->main_go->setEnabled(true);
    }
    else
    {
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","全局相机无法连续拍摄!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
}

void MainWindow::on_main_go_clicked()
{
    int i = ui->main_position->currentIndex();
    qDebug() << "the" << i << "spinrete";
    mAdv.GpGo(i);
    mAdv.paraSet(8000, 2000, 20000, 20000, 0, -7518800, 200);
    mAdv.AxGo(0);
    mAdv.AxStateJudge(0);
    ui->main_start->setEnabled(true);
}

void MainWindow::on_main_start_clicked()
{
    ui->main_start->setEnabled(false);
    ui->main_restart->setEnabled(false);
    //若不是处于暂停，则从头开始检测
    if(running == false)
    {
        //----------------------停止全局相机，孔群图像处理----------------------------//
        camera.cam1_stopgrab();
        camera.whole_findholes();
        //显示孔群
        QPixmap pixmap;
        pixmap = pixmap.fromImage(camera.cam1_qimg);
        pixmap = pixmap.scaled(ui->main_cam1->width(), ui->main_cam1->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->main_cam1->setPixmap(pixmap);
        Delay_MSec(100);//无延时图像无法正常显示
        //获取当前轴位置
        Acm_AxGetActualPosition(mAdv.pAxisHandle[1], &PPU_now[1]);
        Acm_AxGetActualPosition(mAdv.pAxisHandle[2], &PPU_now[2]);
        //将孔群像素位置转化为PPU位置
        for(int i = 0; i < iHolesNum; i++)
        {
            x_Ary[i] = PPU_now[1] + (x_Ary[i]-1226.6)*49.087 - 127570;
            y_Ary[i] = PPU_now[2] - (y_Ary[i]-1030)*48.9 + 470;
        }
        //-------------------------------轨迹规划-------------------------------------//
        //初始化随机种子
        time_t tm;
        time(&tm);
        unsigned int nSeed = (unsigned int)tm;
        srand(nSeed);
        //开始搜索
        CTsp tsp;
//            commonInit(iHolesNum);
        tsp.InitData();
        qDebug()<<iHolesNum;
        tsp.fnGreedy();
        tsp.Search();

//        //输出结果
//        printf("\n\n最佳路径如下 :\n");
//        for (int i = 0; i < iHolesNum; i++)
//        {
//             cout<<tsp.m_cGlobalBestAnt.m_nPath[i]<<" ";
//        }
//        cout<<endl;
//        cout<<nSeed;
        double rePath[300][2];
        cv::Point p1, p2;
        for(int i=0;i<iHolesNum;i++)
        {
            rePath[i][0] = x_Ary[tsp.m_cGlobalBestAnt.m_nPath[i]];
            rePath[i][1] = y_Ary[tsp.m_cGlobalBestAnt.m_nPath[i]];
          if(i<iHolesNum-1)
          {
            p1.x = camera.pix[tsp.m_cGlobalBestAnt.m_nPath[i]][0];  p1.y =camera.pix[tsp.m_cGlobalBestAnt.m_nPath[i]][1];
            p2.x = camera.pix[tsp.m_cGlobalBestAnt.m_nPath[i+1]][0];  p2.y =camera.pix[tsp.m_cGlobalBestAnt.m_nPath[i+1]][1];
            cv::line(camera.cam1_mat, p1, p2, cv::Scalar(0, 0, 255), 2);
          }
        }
        //显示轨迹规划路径---------------------------------------------------------------------------------------------------------
        pixmap = pixmap.fromImage(camera.cam1_qimg);
        pixmap = pixmap.scaled(ui->main_cam1->width(), ui->main_cam1->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->main_cam1->setPixmap(pixmap);
        Delay_MSec(50);
        //将检测状态设为正在运行
        running = true;
        ui->main_pause->setEnabled(true);
        ui->main_stop->setEnabled(true);
        //-----------------------运动到第一个微孔---------------------------//
        mAdv.GpMov(0, rePath[0]);
//        zhizhen= new second;
//        zhizhen->show();
//        mWidget = new secondWidget(this);//this是否需要暂定
//        QLabel *zLbl = new QLabel(mWidget);
//        zLbl->setNum(10);
//        mWidget->show();
        //----------------------------对焦--------------------------------//
        camera.focusValue = 0;
        mAdv.paraSet(2000, 2000, 10000, 10000, 0, 0, -50);
        do
        {
            mAdv.AxMov(0);
            mAdv.AxStateJudge(0);
            Delay_MSec(50);
            camera.cam2_singlegrab();
            pixmap = pixmap.fromImage(camera.cam2_qimg);
            pixmap = pixmap.scaled(ui->main_cam2->width(), ui->main_cam2->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->main_cam2->setPixmap(pixmap);
            QPixmap pixmap2 = pixmap2.fromImage(camera.cam2_qimg);
            Delay_MSec(50);
        }while(camera.micro_focus());
        //------------------------第一个孔的检测结果----------------------------//
        camera.micro_checkhole();
        ui->mainlabel7->setText(camera.str);
        //------------------------剩余孔的检测结果----------------------------//
        for (int i = 1; i < iHolesNum; i++)
        {
            mAdv.GpMov(i, rePath[i]); //执行直线插补运动
            mAdv.GpStateJudge();
            if (running == false)
                break;
            Delay_MSec(100);
            MVSingleGrab(camera.m_hCam_micro,camera.m_hImg_micro, 150);
            camera.micro_checkhole();
            ui->mainlabel7->setText(camera.str);
            pixmap = pixmap.fromImage(camera.cam2_qimg);
            pixmap = pixmap.scaled(ui->main_cam2->width(), ui->main_cam2->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->main_cam2->setPixmap(pixmap);
            Delay_MSec(50);
        }
    }
    //如果是暂停继续剩余所有孔运动+检测
    //-------------------------孔群检测结束----------------------------//
    running = false;
    ui->main_start->setEnabled(true);
    ui->main_restart->setEnabled(true);
    ui->main_pause->setEnabled(false);
    ui->main_stop->setEnabled(false);
    delete_New(iHolesNum);
}

void MainWindow::on_main_stop_clicked()
{
    running = false;
    ui->main_stop->setEnabled(false);
    ui->main_start->setEnabled(true);
    ui->main_restart->setEnabled(true);
    ui->main_pause->setEnabled(false);
}

void MainWindow::on_main_restart_clicked()
{
//    on_main_start_clicked();
//    ui->main_start->setEnabled(false);
//    ui->main_restart->setEnabled(false);
//    ui->main_pause->setEnabled(true);
//    ui->main_stop->setEnabled(true);
}

void MainWindow::on_m_ShowBtn_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    //建立并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." ;
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }
    QSqlQuery sql_query;
    model->setQuery("select bIfAdmin,cName,cPassword from user");
    model->setHeaderData(0,Qt::Horizontal,tr("是否为管理员"));
    model->setHeaderData(1,Qt::Horizontal,tr("user"));
    model->setHeaderData(2,Qt::Horizontal,tr("pass"));
    qDebug() << "show" ;
    ui->m_TableView->setModel(model);
    ui->m_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    database.close();
}

void MainWindow::on_m_DeleteAllBtn_2_clicked()
{
    QString cUserName=ui->m_NameInputLineEdit->text();
    QString cPassword=ui->m_PwdInputLineEdit->text();
    bool bIfAdmin=ui->m_RadioButton->isChecked();
    bool bIfRepeat=false;

    //建立并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." ;
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }
    QSqlQuery sql_query;

    //查询数据
    sql_query.exec("select * from user");
    if(!sql_query.exec())
    {
        qDebug()<<"false";
    }
    else
    {
        qDebug()<<"sussess";
        while(sql_query.next())
        {
            if(cUserName==nullptr||cPassword==nullptr)
            {
                QMessageBox::information(this,"警告","用户名或密码不能为空!",QMessageBox::Ok);
                bIfRepeat=true;
                break;
            }

            if(cUserName==sql_query.value(1).toString())
            {
                QMessageBox::information(this,"警告","用户名已存在!",QMessageBox::Ok);
                bIfRepeat=true;
                break;
            }
            qDebug()<<"name"<<sql_query.value(1).toString();
            qDebug()<<"password"<<sql_query.value(2).toString();
        }
        sql_query.exec();
    }

    if(bIfRepeat==false)
    {
        //插入数据
        qDebug()<<"inserting";
        qDebug()<<cUserName<<"    "<<cPassword;

        sql_query.prepare("insert into user(bIFAdmin,cName,cPassword) VALUES(?,?,?)");
        sql_query.addBindValue(bIfAdmin);//
        sql_query.addBindValue(cUserName);//
        sql_query.addBindValue(cPassword);//
        if(sql_query.exec())
        {
            qDebug()<<"插入成功";
        }
        QMessageBox::information(this,"提醒","注册成功!",QMessageBox::Ok);
    }
    database.close();
}

void MainWindow::on_m_ChangeBtn_clicked()
{
    QString cUserName=ui->m_ChangeNameLineEdit->text();
    QString cNewPassword=ui->m_ChangePasswordLineEdit->text();
    bool bIfExist=false;

    //建立并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." ;
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }
    QSqlQuery sql_query;

    //查询数据
    sql_query.exec("select * from user");
    if(!sql_query.exec())
    {
        qDebug()<<"false";
    }
    else
    {
        qDebug()<<"suesss";
        while(sql_query.next())
        {
            qDebug()<<"name"<<sql_query.value(1).toString();
            qDebug()<<"pwd"<<sql_query.value(2).toString();
            if(cUserName==sql_query.value(1).toString())
            {
                sql_query.prepare("update user set cPassword=? where cName= ?");
                sql_query.addBindValue(cNewPassword);
                sql_query.addBindValue(cUserName);
                sql_query.exec();
                bIfExist=true;
                break;
            }
        }
    }
    if(bIfExist==false)
    {
        QMessageBox::information(this,"警告","用户名不存在!",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this,"提示","密码修改成功!",QMessageBox::Ok);
    }

    database.close();
}

void MainWindow::on_m_DeleteBtn_clicked()
{
    QString cUserName=ui->m_DeleteNameLineEdit->text();
    bool bIfExist=false;

    //建立并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." ;
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }
    QSqlQuery sql_query;

    //查询数据
    sql_query.exec("select * from user");
    if(!sql_query.exec())
    {
        qDebug()<<"false";
    }
    else
    {
        qDebug()<<"sussess";
        while(sql_query.next())
        {
            qDebug()<<"name"<<sql_query.value(1).toString();
            qDebug()<<"pwd"<<sql_query.value(2).toString();
            if(cUserName==sql_query.value(1).toString())
            {
                sql_query.prepare("delete from user where cName= ?");
                sql_query.addBindValue(cUserName);
                sql_query.exec();
                bIfExist=true;
                break;
            }
        }
    }
    if(bIfExist==false)
    {
        QMessageBox::information(this,"警告","用户名不存在!",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this,"提示","用户信息删除成功!",QMessageBox::Ok);
    }
    database.close();

}

void MainWindow::on_m_DeleteAllBtn_clicked()
{
    //建立并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." ;
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }
    QSqlQuery sql_query;

    //查询数据
    sql_query.exec("select * from user");
    if(!sql_query.exec())
    {
        qDebug()<<"false";
    }
    else
    {
        qDebug()<<"success";
        while(sql_query.next())
        {
            QString cNameToDelete=sql_query.value(1).toString();
            sql_query.exec("delete from user where cName = cNameToDelete ");
        }
    }

    database.close();

}

void MainWindow::on_equipx_go_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipx_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipx_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipx_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipx_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipx_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetPos = ui->equipx_pto->text().toDouble();//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxGo(1);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipx_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipx_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipx_goright_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipx_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipx_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipx_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipx_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipx_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetDis = ui->equipx_prela->text().toDouble();//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxMov(1);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipx_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipx_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipx_goleft_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipx_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipx_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipx_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipx_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipx_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetDis =-(ui->equipx_prela->text().toDouble());//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxMov(1);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipx_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipx_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipy_go_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipy_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipy_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipy_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipy_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipy_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetPos = ui->equipy_pto->text().toDouble();//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxGo(2);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipy_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipy_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipy_gofront_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipy_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipy_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipy_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipy_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipy_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetDis = ui->equipy_prela->text().toDouble();//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxMov(2);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipy_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipy_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipy_goback_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipy_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipy_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipy_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipy_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipy_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetDis = - (ui->equipy_prela->text().toDouble());//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxMov(2);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipy_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipy_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipz_go_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipz_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipz_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipz_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipz_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipz_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetPos = ui->equipz_pto->text().toDouble();//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxGo(0);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipy_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipy_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipz_goup_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipz_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipz_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipz_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipz_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipz_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetDis = ui->equipz_prela->text().toDouble();//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxGo(0);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipy_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipy_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equipz_godown_clicked()
{
    U32 Vmax, Vmin, Acc, Dec;
    I32 AxJerk;
    F64 TargetPos = 0;
    F64 TargetDis = 0;

    Vmax = ui->equipz_vmax->text().toULong(); //读取输入的最大速度
    Vmin = ui -> equipz_vmin -> text().toULong(); //读取输入的最小速度
    Acc = ui -> equipz_amax -> text().toULong(); //读取输入的加速度
    Dec = ui -> equipz_amin -> text().toULong(); //读取输入的减速度
    AxJerk = ui ->equipz_method -> currentIndex(); //根据索引值确定输入的曲线类型
    TargetDis = - (ui->equipz_prela->text().toDouble());//读取输入的目标位置

    mAdv.paraSet(Vmax, Vmin, Acc, Dec, AxJerk, TargetPos, TargetDis);

    mAdv.AxGo(0);
 //   u32Ret = Acm_AxMoveAbs(pAxisHandle[selectXYZ],ui->);
    ui -> equipy_pnow -> setNum(mAdv.fActPosition);
    //ui -> label_AxCmdPos -> setNum(fCmdPosition);
    ui -> equipy_state -> setNum(mAdv.u16State);
}

void MainWindow::on_equip_linkcam1_clicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    int error = camera.cam1_initial();
    if(error == 3)
    {
        ui->equip_linkcam1->setEnabled(false);
        ui->equip_procam1->setEnabled(true);
        ui->equip_grabcam1->setEnabled(true);
        ui->equip_singlegrabcam1->setEnabled(true);
        ui->main_init->setEnabled(false);
        QApplication::restoreOverrideCursor();
    }
    else if(error == 0)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","没有找到相机, 请检查相机的IP地址以及相机接线!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else if(error == 1)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接相机，请关闭可能在控制相机的程序!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else if(error == 2)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接相机!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
}
void MainWindow::on_equip_linkcam2_clicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    int error = camera.cam2_initial();
    if(error == 3)
    {
        ui->equip_linkcam2->setEnabled(false);
        ui->equip_procam2->setEnabled(true);
        ui->equip_grabcam2->setEnabled(true);
        ui->equip_singlegrabcam2->setEnabled(true);
        ui->main_init->setEnabled(false);
        QApplication::restoreOverrideCursor();
    }
    else if(error == 0)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","没有找到相机, 请检查相机的IP地址以及相机接线!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else if(error == 1)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接相机，请关闭可能在控制相机的程序!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
    else if(error == 2)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法连接相机!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
}

void MainWindow::on_equip_IPcam1_clicked()
{

}
void MainWindow::on_equip_IPcam2_clicked()
{

}

void MainWindow::on_equip_procam1_clicked()
{
    //设置相机属性页
    if (camera.m_hPropDlg_whole == NULL)
    {
        //创建及初始化属性页对话框
        const char t_Title[] = "camera attribute" ;
        LPCTSTR strCaption = (LPCTSTR)t_Title;
        MVCamProptySheetCreateEx(&camera.m_hPropDlg_whole, camera.m_hCam_whole,0,strCaption,0xffff);
        if (camera.m_hPropDlg_whole == NULL)
        {
            QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法创建全局相机属性页面!",QMessageBox::Yes);
            if(t_Re == QMessageBox::Yes)
                return;
        }
    }
    if (camera.m_hPropDlg_whole != NULL)
        MVCamProptySheetShow(camera.m_hPropDlg_whole, SW_SHOW);
}
void MainWindow::on_equip_procam2_clicked()
{
    //设置相机属性页
    if (camera.m_hPropDlg_micro == NULL)
    {
        //创建及初始化属性页对话框
        const char t_Title[] = "camera attribute" ;
        LPCTSTR strCaption = (LPCTSTR)t_Title;
        MVCamProptySheetCreateEx(&camera.m_hPropDlg_micro, camera.m_hCam_micro,0,strCaption,0xffff);
        if (camera.m_hPropDlg_micro == NULL)
        {
            QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","无法创建微孔相机属性页面!",QMessageBox::Yes);
            if(t_Re == QMessageBox::Yes)
                return;
        }
    }
    if (camera.m_hPropDlg_micro != NULL)
    {
        MVCamProptySheetShow(camera.m_hPropDlg_micro, SW_SHOW);
    }
}

void MainWindow::on_equip_singlegrabcam1_clicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    bool error = camera.cam1_singlegrab();
    if(error == true)
    {
        QApplication::restoreOverrideCursor();
        QPixmap pixmap;
        pixmap = pixmap.fromImage(camera.cam1_qimg);
        pixmap = pixmap.scaled(ui->equip_cam1->width(), ui->equip_cam1->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->equip_cam1->setPixmap(pixmap);
        ui->equip_savecam1->setEnabled(true);
    }
    else
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","全局相机无法单帧拍摄!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
}
void MainWindow::on_equip_singlegrabcam2_clicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    bool error = camera.cam2_singlegrab();
    if(error == true)
    {
        QApplication::restoreOverrideCursor();
        QPixmap pixmap;
        pixmap = pixmap.fromImage(camera.cam2_qimg);
        pixmap = pixmap.scaled(ui->equip_cam2->width(), ui->equip_cam2->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->equip_cam2->setPixmap(pixmap);
        ui->equip_savecam2->setEnabled(true);
    }
    else
    {
        QApplication::restoreOverrideCursor();
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","微孔相机无法单帧拍摄!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
}

void MainWindow::on_equip_grabcam1_clicked()
{
    MVSTATUS_CODES r6 = MVStartGrab(camera.m_hCam_whole, StreamCB_whole, (ULONG_PTR)this);
    if(r6 == MVST_SUCCESS)
    {
        camera.cam1_startgrab();
        ui->equip_stopcam1->setEnabled(true);
        ui->equip_grabcam1->setEnabled(false);
        ui->equip_singlegrabcam1->setEnabled(false);
        ui->equip_savecam1->setEnabled(true);
    }
    else
    {
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","全局相机无法连续拍摄!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
}
void MainWindow::on_equip_grabcam2_clicked()
{
    MVSTATUS_CODES r7 = MVStartGrab(camera.m_hCam_micro, StreamCB_micro, (ULONG_PTR)this);
    if(r7 == MVST_SUCCESS)
    {
        camera.cam2_startgrab();
        ui->equip_stopcam2->setEnabled(true);
        ui->equip_grabcam2->setEnabled(false);
        ui->equip_singlegrabcam2->setEnabled(false);
        ui->equip_savecam2->setEnabled(true);
    }
    else
    {
        QMessageBox::StandardButton t_Re = QMessageBox::warning(this,"失败","微孔相机无法连续拍摄!",QMessageBox::Yes);
        if(t_Re == QMessageBox::Yes)
            return;
    }
}

void MainWindow::on_equip_stopcam1_clicked()
{
    camera.cam1_stopgrab();
    ui->equip_stopcam1->setEnabled(false);
    ui->equip_grabcam1->setEnabled(true);
    ui->equip_singlegrabcam1->setEnabled(true);
}
void MainWindow::on_equip_stopcam2_clicked()
{
    camera.cam2_stopgrab();
    ui->equip_stopcam2->setEnabled(false);
    ui->equip_grabcam2->setEnabled(true);
    ui->equip_singlegrabcam2->setEnabled(true);
}

void MainWindow::on_equip_savecam1_clicked()
{
    camera.cam1_stopgrab();
    QString t_FileName = QFileDialog::getSaveFileName(this, tr("保存图像"),"untitled.bmp",
                               tr("Images (*.png *.xpm *.jpg *.bmp *.tif)"));
    char t_File[100];
    sprintf(t_File,"%s",t_FileName.toStdString().c_str());
    if (!t_FileName.isEmpty())
    {
        MVImageSave(camera.m_hImg_whole,t_File);
    }
    MVStartGrab(camera.m_hCam_whole, StreamCB_whole, (ULONG_PTR)this);
    camera.cam1_startgrab();
}
void MainWindow::on_equip_savecam2_clicked()
{
    camera.cam2_stopgrab();
    QString t_FileName = QFileDialog::getSaveFileName(this, tr("保存图像"),"untitled.bmp",
                               tr("Images (*.png *.xpm *.jpg *.bmp *.tif)"));
    char t_File[100];
    sprintf(t_File,"%s",t_FileName.toStdString().c_str());
    if (!t_FileName.isEmpty())
    {
        MVImageSave(camera.m_hImg_micro,t_File);
    }
    MVStartGrab(camera.m_hCam_micro, StreamCB_micro, (ULONG_PTR)this);
    camera.cam2_startgrab();
}

void MainWindow::on_main_movex_clicked()
{
    mAdv.AxServSeton(1);
}

void MainWindow::on_main_movey_clicked()
{
    mAdv.AxServSeton(2);
}

void MainWindow::on_main_movez_clicked()
{
    mAdv.AxServSeton(0);
}

void MainWindow::on_main_moveup_clicked()
{
    //默认一次移动50PPU
    F64 TargetDis = 50;
    TargetDis = -(ui->DisLineEdit->text().toDouble());
    mAdv.paraSet(5000, 2000, 20000, 20000, 0, 0, TargetDis);
    mAdv.AxMov(0);
}


void MainWindow::on_main_movedown_clicked()
{
    //默认一次移动50PPU
    F64 TargetDis = 50;
    TargetDis = ui->DisLineEdit->text().toDouble();
    mAdv.paraSet(5000, 2000, 20000, 20000, 0, 0, TargetDis);
    mAdv.AxMov(0);
}

void MainWindow::on_main_moveright_clicked()
{
    F64 TargetDis = 5000;
    TargetDis = ui->DisLineEdit->text().toDouble();
    mAdv.paraSet(5000, 2000, 20000, 20000, 0, 0, TargetDis);
    mAdv.AxMov(1);
}

void MainWindow::on_main_moveleft_clicked()
{
    F64 TargetDis = 5000;
    TargetDis = -(ui->DisLineEdit->text().toDouble());
    mAdv.paraSet(5000, 2000, 20000, 20000, 0, 0, TargetDis);
    mAdv.AxMov(1);
}

void MainWindow::on_main_movefront_clicked()
{
    F64 TargetDis = 5000;
    TargetDis = ui->DisLineEdit->text().toDouble();
    mAdv.paraSet(5000, 2000, 20000, 20000, 0, 0, TargetDis);
    mAdv.AxMov(2);
}

void MainWindow::on_main_moveback_clicked()
{
    F64 TargetDis = 5000;
    TargetDis = -(ui->DisLineEdit->text().toDouble());
    mAdv.paraSet(5000, 2000, 20000, 20000, 0, 0, TargetDis);
    mAdv.AxMov(2);
}

void MainWindow::on_navibut3_clicked()
{
    mAdv.AxInit();
    for (int i = 0; i < 3; i++)
        mAdv.AxServSeton(i);
}
