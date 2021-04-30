#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GigECamera_Types.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int showStreamOnLabel_whole(MV_IMAGE_INFO* pInfo);
    int showStreamOnLabel_micro(MV_IMAGE_INFO* pInfo);
    void Delay_MSec(unsigned int msec);

private slots:
    void on_navibut1_pressed();
    void on_navibut2_pressed();
    void on_navibut3_pressed();
    void on_navibut4_pressed();
    void on_navibut5_pressed();

    void on_main_init_clicked();
    void on_main_link_clicked();

    void on_main_start_clicked();

    void on_m_ShowBtn_clicked();

    void on_m_DeleteAllBtn_2_clicked();

    void on_m_ChangeBtn_clicked();

    void on_m_DeleteBtn_clicked();

    void on_m_DeleteAllBtn_clicked();

    void on_equipx_go_clicked();

    void on_equipx_goright_clicked();

    void on_equipx_goleft_clicked();

    void on_equipy_go_clicked();

    void on_equipy_gofront_clicked();

    void on_equipy_goback_clicked();

    void on_equipz_go_clicked();

    void on_equipz_goup_clicked();

    void on_equipz_godown_clicked();

    void on_equip_linkcam1_clicked();
    void on_equip_linkcam2_clicked();
    void on_equip_IPcam1_clicked();
    void on_equip_IPcam2_clicked();
    void on_equip_procam1_clicked();
    void on_equip_procam2_clicked();
    void on_equip_singlegrabcam1_clicked();
    void on_equip_singlegrabcam2_clicked();
    void on_equip_grabcam1_clicked();
    void on_equip_grabcam2_clicked();
    void on_equip_stopcam1_clicked();
    void on_equip_stopcam2_clicked();
    void on_equip_savecam1_clicked();
    void on_equip_savecam2_clicked();

    void on_main_go_clicked();

private:
    Ui::MainWindow *ui;
    QString style_navibut1 = "QPushButton{background-color:rgb(46,49,49); background-repeat:no-repeat; background-origin:content;\
                                          background-image:url(:/hsq/icon/navibut1.png); background-position:top; padding:20px;\
                                          text-align:bottom; color:rgb(238,238,238); border-radius:10px;}"
                             "QPushButton:hover{background-color:rgb(56,59,59)}"
                             "QPushButton:checked{background-color:rgb(30,32,32)}";
    QString style_navibut2 = "QPushButton{background-color:rgb(46,49,49); background-repeat:no-repeat; background-origin:content;\
                                          background-image:url(:/hsq/icon/navibut2.png); background-position:top; padding:20px;\
                                          text-align:bottom; color:rgb(238,238,238); border-radius:10px;}"
                             "QPushButton:hover{background-color:rgb(56,59,59)}"
                             "QPushButton:checked{background-color:rgb(30,32,32)}";
    QString style_navibut3 = "QPushButton{background-color:rgb(46,49,49); background-repeat:no-repeat; background-origin:content;\
                                          background-image:url(:/hsq/icon/navibut3.png); background-position:top; padding:20px;\
                                          text-align:bottom; color:rgb(238,238,238); border-radius:10px;}"
                             "QPushButton:hover{background-color:rgb(56,59,59)}"
                             "QPushButton:checked{background-color:rgb(30,32,32)}";
    QString style_navibut4 = "QPushButton{background-color:rgb(46,49,49); background-repeat:no-repeat; background-origin:content;\
                                          background-image:url(:/hsq/icon/navibut4.png); background-position:top; padding:20px;\
                                          text-align:bottom; color:rgb(238,238,238); border-radius:10px;}"
                             "QPushButton:hover{background-color:rgb(56,59,59)}"
                             "QPushButton:checked{background-color:rgb(30,32,32)}";
    QString style_navibut5 = "QPushButton{background-color:rgb(46,49,49); background-repeat:no-repeat; background-origin:content;\
                                          background-image:url(:/hsq/icon/navibut5.png); background-position:top; padding:20px;\
                                          text-align:bottom; color:rgb(238,238,238); border-radius:10px;}"
                             "QPushButton:hover{background-color:rgb(56,59,59)}"
                             "QPushButton:checked{background-color:rgb(30,32,32)}";
    QString style_menubut = "QPushButton{background-color:rgb(46,49,49); border-radius:15px;}"
                            "QPushButton:hover{background-color:rgb(56,59,59)}"
                            "QPushButton:checked{background-color:rgb(30,32,32)}";
    QString style_pushbut1 = "QPushButton{background-color:rgb(120,122,122); color:rgb(238, 238, 238); border-radius:5px;}"
                             "QPushButton:hover{background-color:rgb(56,59,59)}"
                             "QPushButton:pressed{background-color:rgb(30,32,32)}";
    QString style_pushbut2 = "QPushButton{background-color:rgb(120,122,122); color:rgb(238, 238, 238); border-radius:30px;}"
                             "QPushButton:hover{background-color:rgb(56,59,59)}"
                             "QPushButton:pressed{background-color:rgb(30,32,32)}";
    QString style_combobox = "QComboBox{background-color:rgb(120,122,122); color:rgb(238,238,238); border-radius:5px;}";
    QString style_labelcam = "QLabel{background-color:rgb(120,122,122); border-radius:5px;}";
    QString style_light0 = "QPushButton{background-color:rgba(0,0,0,0); background-repeat:no-repeat; background-origin:content;\
                                        background-image:url(:/hsq/icon/main_light0.png); background-position:center;}";
    QString style_light1 = "QPushButton{background-color:rgba(0,0,0,0); background-repeat:no-repeat; background-origin:content;\
                                        background-image:url(:/hsq/icon/main_light1.png); background-position:center;}";
    QString style_light2 = "QPushButton{background-color:rgba(0,0,0,0); background-repeat:no-repeat; background-origin:content;\
                                        background-image:url(:/hsq/icon/main_light2.png); background-position:center;}";
};
#endif // MAINWINDOW_H
