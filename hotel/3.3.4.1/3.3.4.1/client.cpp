#include "client.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
client::client()
{

    this -> name = "";
    this -> old = "0";
    this ->country = "NULL";
    this -> callNumber = "NULL";
    this->IDNum = "IDNum";
    this->location="NULL";
    this->birthday="NULL";

    for(int i = 0; i < 6 ; i++)
    {
        this ->info.roomSt[i] = 0;
        this ->info.time[i] = 0;
        this ->info.money[i] = 0;
    }
    this ->info.sum = 0;
    this ->info.frequence = 0;
}

client::~client()
{

}

QString client:: getname()
{
    return name;
}

QString client:: getbirth()
{
    return birthday;
}

QString client:: getcall()
{
    return callNumber;
}

QString client:: getIDnum()
{
    return IDNum;
}

QString client:: getlocation()
{
    return location;
}

clientRoomInfo client:: getinfo()
{

    return info;
}

int client:: getsex()
{
    return sex;
}

int client:: gettype()
{
    return type;
}

void client::addName(QString n )    //添加姓名和电话号码
{
        this -> name = n;

}

void client::addNamebirthloc(QString n , QString o ,QString c)    //添加姓名和电话号码
{
        this -> name = n;
        this -> birthday = o;
        this ->location = c;
}

void client::addcall(QString phoneNum)              //添加电话号码
{
    this -> callNumber = phoneNum;
}

void client:: addiden(QString IDNum)             //添加身份证号
{
    this->IDNum = IDNum;
}

void client:: addsex(int n)             //添加性别
{
    this->sex = n;
}

void client:: addtype(int n)             //添加会员类型
{
    this->type = n;
}

void client::addinfo(clientRoomInfo a)              //录入住房信息
{
    this ->info.frequence = a.frequence;
    for(int i = 0; i < 6 ; i++)
    {
        this ->info.roomSt[i] = a.roomSt[i];
        this ->info.time[i] = a.time[i];
        this ->info.money[i] = a.money[i];
    }
    this ->info.sum = a.sum;

}

int client::csave(client c ,QString file0)           //保存用户信息
{
    QFile file(file0);
    QTextStream stream(&file);
    if (file.open(QIODevice::Text | QIODevice::Append))
    {
        stream << c.name << endl << c.old << endl << c.IDNum << endl << c.country << endl;
        stream << c.callNumber << endl << c.info.frequence<<endl;
        for (int i = 1; i <= 5; i++)
        {
            stream << c.info.roomSt[i] << endl;
            stream << c.info.time[i] << endl;
            stream << c.info.money[i] << endl;
        }
        stream << c.info.sum << endl;
        file.close();
        return 1;
    }
    else
        return 0;
}

client client::readclient(QString file0)               //读取客户信息,并返回客户类
{
    client c;
    clientRoomInfo cr;
    QFile file(file0);
    QTextStream stream(&file);
     if (file.open(QIODevice::Text | QIODevice::ReadOnly))
       {


         c.addNamebirthloc(stream.readLine(),stream.readLine(),stream.readLine());
         c.addiden(stream.readLine());
         c.addcall(stream.readLine());
         cr.frequence  = (stream.readLine()).toInt();

         for (int i = 1; i <= 5; i++)
         {
             cr.roomSt[i] = (stream.readLine()).toInt();
             cr.time[i]   = (stream.readLine()).toInt();
             cr.money[i]  = (stream.readLine()).toInt();
         }
         cr.sum = (stream.readLine()).toInt();
         c.addinfo(cr);
       }
    return c;
}

void saveReserved(client c ,QString times ,QString timee ,QString roomNum,QString fileName)        //保存客户预定信息，即订单
{
    QString cnum = c.getIDnum();
    QString cfilename = "Temp/reserved/"  + cnum + ".txt";
    QFile file(cfilename);
    QTextStream stream(&file);
    if (file.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        stream <<"[NAME]:"<< c.getname() <<endl;
        stream <<"[IDNUM]:" << c.getIDnum() << endl;
        stream <<"[CALLNUMBER]:"<< c.getcall() << endl;
        stream <<"[TIMESTART]:"<< times << endl;
        stream <<"[TIMEEND]:"<< timee << endl;
        stream <<"[RoomNum]:"<<roomNum << endl;
        stream <<"[FileName]:"<<fileName<< endl;
        file.close();
    }

}
