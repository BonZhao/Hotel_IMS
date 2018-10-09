#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QLabel>
#define FLOOR 6         //层数
#define ROOMNUM 52      //房间数
#define RDAY 120        //预定天数

class room
{
public:
    room();
    ~room();
        void changeMoney(int m);        //改变房间单价
        void changeState(int sta);        //改变房间状态
        void changeNum(int n);
        void changeMPN(int mpn);
        void changePN(int pn);
        void changeStyle(int sty);
        //class room *next;
        int getNum(void);
        int getState(void);
        int getMoney(void);
        int getMPN(void);
        int getPN(void);
        int getStyle(void);

        class room *last;
        class room *next;
        class room *right;
        class room *down;
        int days;

private:
    int num;
    int maxPeopleNum;  //最大入住人数
    int peopleNum;      //当前入住人数
    int money;      //该类型的房间单价
    int roomStyle;
    /*
    1. 总统套房  20000
    2.豪华标间       500
    3.大床房     800
    4.双人房     1200
    5.套房       3000
    */
    int state;
    /*
    1 - 空；
    2 - 入住；
    3 - 已被预订
    (4 - 脏房...)
    */

};



struct roomTime
{
    int timeType;//1 12:00 - 18:00  2 18:00 -nextday 12:00
    room *down;
    room *empty[6];
    room *reserved[6];
    room *full[6];

};
void establish();      //建立必要的文件和文件夹***只做一次 Dayi.txt,hotelTime.txt,60天预定表
void establish_2();                  ///*初始化房间信息，存入文件*/ room.txt

void saveRoom();                        //保存七天之内房间信息,Dayi.txt
bool saveReserved(void);                //保存60天预定表到文件，以房间号为单位 Temp\Reserved_60


void fRoomIn();                         //从 room.txt 写入房间信息 到roomNum[i][j][k]
bool foundReserved(void);               //从roomReserved_60写入可预订信息

void foundlist_0();                      //建立十字链表
void foundList_1() ;                     //建立空、满、预订链表

bool transList(int day1, int tPart1, int day2, int tPart2, int num, int s);
bool timePass(void);                //时间流逝
void reservedTimeUp(void);
void checkInTimeUp(void);


bool judgeReserved(int day1, int tPart1, int day2, int tPart2);
//判断预定时间是否合法，把能预定的房间放入文件roomCanReserved

bool changeReserved(QString rNum, int day1, int tPart1, int day2, int tPart2, QString trans);
#endif // ROOM_H
