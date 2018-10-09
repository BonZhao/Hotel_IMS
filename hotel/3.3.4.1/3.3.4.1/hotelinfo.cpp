#include "hotelinfo.h"
#include "QFile"
#include <QTextStream>
HotelInfo::HotelInfo()
{

}

HotelInfo::~HotelInfo()
{

}


int HotelInfo::  getsumMoney()                  //得到总收入
{
   return sumMoney;
}
void HotelInfo:: addSumMoney(int fare)           //增加收入
{
   sumMoney = sumMoney + fare;
}
/*
01234567890123456
[Hotel_Name]:
[Radio]:
[CheckInRoom]:
[sumMoney]:
[ThisMonthMoney]:
[NowPeople]:

 */
bool HotelInfo:: fileInHotel()               //从HotelInfo.txt读入各种信息
{
    QFile file("Temp/Hotel.txt");
    QTextStream in(&file);
    if (file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
       this->name = in.readLine().mid(13);
       this->radio = in.readLine().mid(9).toDouble();
       this->checkInRoom = in.readLine().mid(14).toInt();
       this->sumMoney = in.readLine().mid(11).toInt();
       this->thisMonthMoney = in.readLine().mid(17).toInt();
       this->nowPeople = in.readLine().mid(12).toInt();

       radio = (double)checkInRoom/ROOMNUM;
       file.close();

       return true;
     }
    return false;
}

bool HotelInfo::fileOutHotel()                       //向HotelInfo.txt写入各种信息
{
    QFile file("Temp/Hotel.txt");
    QTextStream out(&file);
    if (file.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        out << "[Hotel_Name]:" << this->name << endl;
        radio = (double)checkInRoom/ROOMNUM;
        out << "[Radio]:" << this->radio << endl;
        out << "[CheckInRoom]:"<<this->checkInRoom << endl;
        out << "[sumMoney]:" << this ->sumMoney << endl;
        out << "[ThisMonthMoney]:"<<this->thisMonthMoney <<endl;
        out << "[NowPeople]:"<<this->nowPeople <<endl;
        file.close();
       return true;
    }
    return false;
}


int HotelInfo::  getThisMonthMoney()            //得到本月收入
{
    return thisMonthMoney;
}

void HotelInfo::  addThisMonthMoney(int fare)             //增加本月收入
{
    thisMonthMoney = thisMonthMoney + fare;
}

void HotelInfo::  clearThisMonthMoney()           //清空本月收入
{
    thisMonthMoney = 0;
}



void HotelInfo:: addSum_thisMon_Money(int fare)    //同时增加本月和本年收入
{
    addThisMonthMoney(fare);
    addSumMoney(fare);
}

void HotelInfo::  addCheckInRoom_changeRadio(int num)    //增加入住房间数，改变入住率
{
   this->checkInRoom = checkInRoom + num;
   this -> radio = checkInRoom/ROOMNUM;
}

void HotelInfo::  cutCheckInRoom_changeRadio(int num)    //减少入住房间数，改变入住率
{
    this->checkInRoom = checkInRoom - num;
    this -> radio = checkInRoom/ROOMNUM;
}

double HotelInfo::  getRadio()                            //得到入住率
{
  return radio;
}

int HotelInfo:: getnowPeople()
{
    return nowPeople;
}

void HotelInfo:: addPeopleCheckIn_his_mon_now(int num)          //增加入住人数 （历史加本月加当前）
{
    nowPeople = nowPeople + num;
}

void HotelInfo::cutNowPeople(int num)             //减少当前人数
{
    nowPeople = nowPeople - num;
}


int HotelInfo:: getCheckInRoom()
{
    return this->checkInRoom;
}

void HotelInfo::clear()
{
    this->checkInRoom = 0;
    this->nowPeople = 0;
    this->sumMoney = 0;
    this->thisMonthMoney = 0;
}
