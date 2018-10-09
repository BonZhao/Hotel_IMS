#ifndef CLIENT_H
#define CLIENT_H
#include <QFile>
#include <QString>
#include <QTextStream>
class clientRoomInfo
{
  public:
   int frequence;//入住次数
   int roomSt[6]; //是0的话表示未住过 ， roomSt[i]是1 住过一次，2住过两次,以此类推
    //即表示每类房间的入住次数
   int time[6];   //各类型房间的入住时长;
   int money[6];  //各类型房间的花费；
   int sum;       //该人的总花费；
};
class client
{
private:
 QString name;
 QString old;//
 QString callNumber;
 QString IDNum;
 QString country;//
 QString location;
 QString birthday;
 int sex; // 1 -男  2 - 女
 int type;// 1 - VIP  2 - Normal
 clientRoomInfo info;
public:
    client();
    ~client();
    QString getname();
    QString getbirth();
    QString getold();
    QString getcall();
    QString getIDnum();
    QString getcountry();
    QString getlocation();
        int getsex();
        int gettype();
    clientRoomInfo getinfo();

    void addName(QString n);
    void addNamebirthloc(QString n , QString o ,QString c);
    void addcall(QString);
    void addiden(QString);
    void addinfo(clientRoomInfo);
    void addsex(int n);
    void addtype(int n);

    int csave(client ,QString);      //保存用户信息到第二个参数中
    void cdelete();                  //删除用户信息

    client readclient(QString);      //读取客户信息,并返回客户类
    client *next;
};

void saveReserved(client c ,QString times ,QString timee, QString roomNum, QString fileName); //保存客户预定信息，即订单
#endif // CLIENT_H
