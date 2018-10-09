#include <hotel.h>
#include "room.h"

#ifndef HOTELINFO_H
#define HOTELINFO_H



class HotelInfo
{

private:
    QString name;
    int sumMoney = 0;
    int thisMonthMoney = 0;
    int roomNum = ROOMNUM;
    int checkInRoom = 0;
    double radio;        //入住率

    //int historyPeopleSum;
    //int thisMonthPeople;
    int nowPeople;

public:
    HotelInfo();
    ~HotelInfo();

    int getsumMoney();                   //得到总收入
    void addSumMoney(int fare);          //增加总收入
     int getThisMonthMoney();             //得到本月收入
    void addThisMonthMoney(int fare);     //增加本月收入
    void clearThisMonthMoney();           //清空本月收入



    void addSum_thisMon_Money(int fare);    //同时增加本月和本年收入

    void addCheckInRoom_changeRadio(int num);    //增加入住房间数，改变入住率
    void cutCheckInRoom_changeRadio(int num);    //减少入住房间数，改变入住率
    double getRadio();                             //得到入住率



    bool fileInHotel();                        //从HotelInfo.txt读入各种信息
    bool fileOutHotel();                       //向HotelInfo.txt读入各种信息

    /*  void getPeopleSum();                     //得到总人数
    void getThisMonthPeopleSum();            //得到本月入住人数

    void clearThisMonthPeopleSum(int num);    //清空本月入住人数*/

    int getnowPeople();              //得到当前人数
    void addPeopleCheckIn_his_mon_now(int num);          //增加入住人数 （历史加本月加当前）
    void cutNowPeople(int num);              //减少当前人数

    int getCheckInRoom();
    void clear();
};

#endif // HOTELINFO_H
