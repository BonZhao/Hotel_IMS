#ifndef HOTEL_H
#define HOTEL_H

#include <QMainWindow>
#include <QPushButton>
#include "timethread.h"
#include "room.h"
namespace Ui {
class Hotel;
}



class Hotel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hotel(QWidget *parent = 0);
    timeThread *tThread;
    ~Hotel();
    QPushButton  *r[FLOOR+1][2][11];       //预定按钮
    QPushButton  *cr[FLOOR+1][2][11];      //入住按钮




    void showRoomState();           //展示房态


public slots:
    void ontimeChanged(int);                       //时间改变将做的事情
private slots:

    /*************主界面按钮******************/
     void on_reserve_clicked();                    //预定
     void on_frontDeskButton_clicked();            //前台
     void on_backDeskButton_clicked();            //后台
     void on_systemButton_clicked();              //系统设置
     void on_pushButton_17_clicked();            //版权声明

    /**************前台管理******************/
     void on_reserveButton_clicked();          //点击预定
     void on_checkInButton_clicked();          //点击住房
     void on_checkOutButton_clicked();         //点击退房

     //预定
     void RIoptical();                    //将可预订房间pushButton添加界面
     void on_pushButton_18_clicked();         //确定预定
     void on_pushButton_20_clicked();            //预订确定2
     void on_reserveConfirmButton_clicked();          //输入时间后判断是否能预定
     //入住
     void TodayStateEmpty();             //今日空闲房间加入界面
     void on_checkIn_clicked();
     void on_pushButton_clicked();        //已预定房间入住
     void on_pushButton_22_clicked();      //住房登记表确定住房
     void on_pushButton_5_clicked();       //下个月时间按钮
     void on_pushButton_6_clicked();       //上个月时间按钮
     //退房
     void on_pushButton_34_clicked();            //退房确定1
     void on_pushButton_36_clicked();             //确定退房
     void on_pushButton_37_clicked();     //退房返回主界面
     //换房
     void on_pushButton_33_clicked();       //换房输入房间号确定
     void on_pushButton_32_clicked();        //换房取消
     void on_pushButton_42_clicked();       //换房显示房间信息确定
     void on_pushButton_39_clicked();         //换房显示房间信息取消
     void on_pushButton_28_clicked();        //显示换房页面
     //续住
      void on_pushButton_40_clicked();

     /**********后台管理**************/
     void on_pushButton_7_clicked();             //实时房态图
     void on_pushButton_8_clicked();            //客户信息管理
     void on_pushButton_9_clicked();              //房间平面图

     //房态
     void on_pushButton_26_clicked();             //展示房间状态
     //客户信息
     void on_pushButton_4_clicked(bool checked); //按某种方式查找客户信息
     void on_pushButton_3_clicked();            //按房号查找正在入住 客户信息
     //房间平面图
     void on_spinBox_3_valueChanged(int arg1);        //房间平面图变换

     /**************系统设置******************/
     void on_pushButton_11_clicked();            //修改用户名
     void on_pushButton_14_clicked();             //修改用户名

     void on_pushButton_12_clicked();            //修改密码
     void on_pushButton_25_clicked();           //修改密码

     void on_pushButton_13_clicked();           //系统参数设置
     void on_pushButton_31_clicked();             //时间参数设置

     void on_pushButton_16_clicked();     //恢复设置

     /***************其他*******************/

    void on_pushButton_10_clicked();            //转到主界面
    void on_pushButton_27_clicked();            //tThreadStart
    void on_pushButton_30_clicked();            //pause

    void on_pushButton_43_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_29_clicked();

    void on_frontDeskButton_pressed();

    void on_backDeskButton_pressed();

    void on_systemButton_pressed();

    void on_pushButton_17_pressed();

    void on_pushButton_4_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_53_clicked();

private:
    Ui::Hotel *ui;
};
#endif // HOTEL_H


