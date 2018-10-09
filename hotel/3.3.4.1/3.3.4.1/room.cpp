#include "room.h"
#include "hotel.h"
#include <QString>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <resignin.h>
room::room()
{

}

room::~room()
{

}

int room::getNum(void)
{
    return num;
}

int room::getMPN(void)
{
    return maxPeopleNum;
}

int room::getPN(void)
{
    return peopleNum;
}

int room::getMoney(void)
{
    return money;
}

int room::getState(void)
{
    return state;
}

int room::getStyle(void)
{
    return roomStyle;
}

void room::changeNum(int n)
{
    num = n;
}

void room::changeState(int sta)
{
    state = sta;
}

void room::changeMPN(int mpn)
{
    maxPeopleNum = mpn;
}

void room::changePN(int pn)
{
    peopleNum = pn;
}


void room::changeStyle(int sty)
{
    roomStyle = sty;
}

void room::changeMoney(int m)
{
    money = m;
}



void establish()                                  //建立必要的文件和文件夹***只做一次
{
    QString day[15];
    QString t = "day";
    QFile fileDay[15];


    QDir *temp = new QDir;
    temp->mkdir("Temp");
    temp->mkdir("Temp/Day1-14");
    temp->mkdir("Temp/client");
    temp->mkdir("Temp/checkIn");
    temp->mkdir("Temp/checkOut");
    temp->mkdir("Temp/reserved");
    temp->mkdir("Temp/Reserved_60");

    for(int i = 1 ; i <= 14;i++)          //Dayi.txt 表示7天之内，两个时段的房间状态
    {
        day[i] = "Temp/Day1-14/" + t + QString::number(i) + ".txt";
        fileDay[i].setFileName(day[i]);
        QTextStream in(&fileDay[i]);
        fileDay[i].open(QIODevice::Text|QIODevice::WriteOnly);
        for(int j = 1 ; j <= ROOMNUM ; j++)
        {
            in << "1"<<endl;
        }
        fileDay[i].close();
    }


    QString hT = "Temp/hotelTime.txt";           //保存时间
    QFile fHotelTime(hT);
    QTextStream in(&fHotelTime);
    if(fHotelTime.open(QIODevice::Text|QIODevice::WriteOnly))
    {
        in << "[Year]2015"<<endl<<"[Month]01"<<endl<<"[Day]01"<<endl;
        in << "[Hour]00" << endl <<"[Minute]00"<<endl<<"[Sec]00"<<endl;
        in <<"***";
    }
    fHotelTime.close();

    QFile HotelInfile("Temp/HotelInfo.txt");
    QTextStream out(&HotelInfile);
    if (HotelInfile.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        out << "[Hotel_Name]:" << "" << endl;
        out << "[Radio]:" << 0 << endl;
        out << "[CheckInRoom]:"<<0 << endl;
        out << "[sumMoney]:" << 0<< endl;
        out << "[ThisMonthMoney]:"<<0 <<endl;
        out << "[NowPeople]:"<<0 <<endl;
        HotelInfile.close();
    }


    extern int reservedState[53][RDAY+1];
    for (int i = 0; i < 53; i++)
    {
        for(int j = 0; j < RDAY+1 ; j++)        //初始化60天预定表
         reservedState[i][j] = 0;

    }
    saveReserved();

    QFile file("Temp/User.txt");
    QTextStream use(&file);
    file.open(QIODevice::Text|QIODevice::WriteOnly);

    QString name = "admin";
    name = getXorEncryptDecrypt(name,11);

    use << name<< endl;
    use << name<< endl;

    use << "***" << endl;
    file.close();
}

void saveRoom()                        //保存七天之内房间信息
{
    QString day[15];
    QString t = "day";
    QFile fileDay[15];
    extern room *roomNum[FLOOR+1][2][11];
    QString state;
    room *roomTemp;
    for(int h = 1 ; h <= 14; h++)
    {
        day[h] = "Temp/Day1-14/" + t + QString::number(h) + ".txt";
        fileDay[h].setFileName(day[h]);
        QTextStream in(&fileDay[h]);
        fileDay[h].open(QIODevice::Text|QIODevice::WriteOnly);

        int ijs[FLOOR+1] = {0,0,0,0,0,0,0};
        int ije[FLOOR+1] = {0,1,1,1,1,1,0};
        int jks[FLOOR+1] = {1,0};
        int ijke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};

        for (int i = 1; i <= FLOOR; i++)
            for (int j = ijs[i]; j <= ije[i]; j++)
                for (int k = jks[j]; k <= ijke[i][j]; k++)
                {
                         roomTemp = roomNum[i][j][k];
                         for (int q = 1; q <= h; q++)
							 roomTemp = roomTemp->right;
						 state = QString::number(roomTemp->getState());
						 in << state << endl;

                 }
        fileDay[h].close();
    }
}




void establish_2()                      ///*初始化房间信息，存入文件*/ room.txt
{
    QString r = "Temp/Room.txt";
    QFile froom(r);
    froom.open(QIODevice::Text|QIODevice::WriteOnly);
    QTextStream in(&froom);
    /*
     int num;           //编号
    int maxPeopleNum;  //最大入住人数
    int peopleNum;      //当前入住人数
    int money;      //该类型的房间单价
    int roomStyle;

    1. 总统套房  20000         maxPeople          5
    2.豪华标间   500                              2
    3.大床房     800                              2
    4.双人房     1200                             2
    5.套房       3000                             3

    int state;

    1 - 空；
    2 - 入住；
    3 - 已被预订
    (4 - 脏房...)
    */

    for(int i = 1 ; i <= 5 ;i++)                     //1到5层
    {
        for(int j = 1 ; j <= 4 ;j++)
        {
            in << "[RoomNum]:" << QString::number(100*i+j)<<endl;
            in << "[RoomStyle]:" << "4"<<endl;       //双人房
            in << "[Cost]:" << "1200"<<endl;
            in << "[MaxPeople]:" << "2"<< endl;
        }
        for(int j = 5 ; j <= 5 ;j++)
        {
            in << "[RoomNum]:" << QString::number(100*i+j)<<endl;
            in << "[RoomStyle]:" << "2"<<endl;      //豪华标间
            in << "[Cost]:" << "500"<<endl;
            in << "[MaxPeople]:" << "2"<< endl;
        }
        for(int j = 6 ; j <= 7 ;j++)                //套房
        {
            in << "[RoomNum]:" << QString::number(100*i+j)<<endl;
            in << "[RoomStyle]:" << "5"<<endl;
            in << "[Cost]:" << "3000"<<endl;
            in << "[MaxPeople]:" << "3"<< endl;
        }
        for(int j = 8 ; j <= 10 ;j++)              //大床房
        {
            in << "[RoomNum]:" << QString::number(100*i+j)<<endl;
            in << "[RoomStyle]:" << "3"<<endl;
            in << "[Cost]:" << "800"<<endl;
            in << "[MaxPeople]:" << "2"<< endl;
        }
    }
    for(int j = 1 ; j <= 2 ;j++)                    //6层
    {
        in << "[RoomNum]:" << QString::number(100*6+j)<<endl;
        in << "[RoomStyle]:" << "1"<<endl;          //总统套房
        in << "[Cost]:" << "20000"<<endl;
        in << "[MaxPeople]:" << "5"<< endl;
    }
    in <<"***";
    froom.close();
}

void fRoomIn()                                      //从 room.txt 写入房间信息 到roomNum[i][j][k]
{
       extern room *roomNum[FLOOR+1][2][11];
       QFile froom("Temp/Room.txt");
       QTextStream stream(&froom);
       int i, k ,j, rstyle, cost, maxPeople;
       QString fnum,fstyle;
       if (froom.open(QIODevice::Text | QIODevice::ReadOnly))
       {
           fnum = stream.readLine();  //房号
           while (fnum != "***")
            {
                i = fnum.mid(10,1).toInt();
                j = fnum.mid(11,1).toInt();
                k = fnum.mid(12,1).toInt();
                fstyle = stream.readLine().mid(12);
                cost = stream.readLine().mid(7).toInt();
                maxPeople = stream.readLine().mid(12).toInt();
                if(roomNum[i][j][k] == NULL)
                 QMessageBox::warning(NULL,"warning","error",QMessageBox::Cancel);
                else
                {
                    rstyle = fstyle.toInt();
                    roomNum[i][j][k]->changeStyle(rstyle);//写入房间类型
                    roomNum[i][j][k]->changeMoney(cost);  //单价
                    roomNum[i][j][k]->changeMPN(maxPeople);//最大入住人数
                }
				
                fnum = stream.readLine();  //房号
            }

       }
      froom.close();
}

void foundlist_0()
{
    QString day[15];
    QString t = "day";
    QFile fileDay[15];
    extern roomTime DayTime[15];
    extern room *roomNum[FLOOR+1][2][11];
    room * temporary;
    room * last[151];
    room * temporaryLast;
    extern hotelTime currentTime;
    int temporaryState;
    int p = 1;
    int ijs[FLOOR+1] = {0,0,0,0,0,0,0};
    int ije[FLOOR+1] = {0,1,1,1,1,1,0};
    int jks[FLOOR+1] = {1,0};
    int ijke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};
    for (int i = 1; i <= FLOOR; i++)                 //初始化*roomNum[FLOOR+1][2][11]
        for (int j = ijs[i]; j <= ije[i]; j++)
            for (int k = jks[j]; k <= ijke[i][j]; k++)
             {

					 roomNum[i][j][k] = new room;
					 roomNum[i][j][k]->right = roomNum[i][j][k]->down =
						 roomNum[i][j][k]->next = roomNum[i][j][k]->last = NULL;
					 last[p++] = roomNum[i][j][k];

				 
             }
    fRoomIn();
    if(currentTime.getTimeState() == 1)
    DayTime[0].timeType = 2;
    else
    DayTime[0].timeType = 1;

    for(int i = 1 ; i <= 14;i++)              //打开文件，并建立竖向链表
    {
        day[i] = "Temp/Day1-14/" + t + QString::number(i) + ".txt";
        fileDay[i].setFileName(day[i]);
        QTextStream in(&fileDay[i]);
        if(fileDay[i].open(QIODevice::Text|QIODevice::ReadOnly))
        {
            temporaryState = (in.readLine()).toInt();          //先读一行
            temporary = new room;
            temporary->changeState(temporaryState);
            temporary->right = NULL;

            DayTime[i].down = temporary;

            if(DayTime[i-1].timeType == 1)
            DayTime[i].timeType = 2;
            else
            DayTime[i].timeType = 1;

            temporaryLast = temporary;                     //上一个变化

			
            last[1] ->right = temporary;                    //横向
			temporary->changeStyle(last[1]->getStyle());
            last[1] = temporary;
            for(int j = 2 ; j < p ; j++)
            {
                temporaryState = (in.readLine()).toInt();
                temporary = new room;                              //申请一个节点
                temporary->changeState(temporaryState);
				temporary->right = NULL;

                temporaryLast ->down = temporary;             //竖向链表链接
                temporaryLast = temporary;

                last[j]->right = temporary;               //横向链表链接
                temporary ->changeStyle(last[j]->getStyle());
                last[j] = temporary;
            }
			temporary->down = NULL;
			
            fileDay[i].close();
        }

    }

}

void foundList_1(void)                                 //建立空、满、预订链表
{
    class room *currentR = NULL, *lE[6], *lR[6], *lF[6];
    extern roomTime DayTime[15];
    int i, j;

    for (i = 0; i <= 14; i++)                 //初始化链表头
        for (j = 0; j <= 5; j++)
        {
            DayTime[i].empty[j] = new class room[1];
            DayTime[i].reserved[j] = new class room[1];
            DayTime[i].full[j] = new class room[1];

            DayTime[i].empty[j]->last = NULL;
            DayTime[i].reserved[j]->last = NULL;
            DayTime[i].full[j]->last = NULL;
            DayTime[i].empty[j]->next = NULL;
            DayTime[i].reserved[j]->next = NULL;
            DayTime[i].full[j]->next = NULL;
        }
    for (j = 0; j <= 5; j++)
    {
        lE[j] = NULL;
        lR[j] = NULL;
        lF[j] = NULL;
    }

    for (i = 1; i <= 14; i++)  //建立房间状态链表
    {
        currentR = DayTime[i].down;
        while (currentR != NULL)
        {

            if (currentR->getState() == 1)  //状态为空
            {

                if (DayTime[i].empty[currentR->getStyle()]->next == NULL)
                {

                    DayTime[i].empty[currentR->getStyle()]->next = currentR;
                    currentR->last = DayTime[i].empty[currentR->getStyle()];
                    currentR->next = NULL;

                }
                else
                {
                    currentR->next = NULL;
                    currentR->last = lE[currentR->getStyle()];
                    lE[currentR->getStyle()]->next = currentR;
                }
                lE[currentR->getStyle()] = currentR;
            }
            else if (currentR->getState() == 2)  //满
            {
                if (DayTime[i].full[currentR->getStyle()]->next == NULL)
                {
                    DayTime[i].full[currentR->getStyle()]->next = currentR;
                    currentR->last = DayTime[i].full[currentR->getStyle()];
                    currentR->next = NULL;
                }
                else
                {
                    currentR->next = NULL;
                    currentR->last = lF[currentR->getStyle()];
                    lF[currentR->getStyle()]->next = currentR;
                }

                lF[currentR->getStyle()] = currentR;
            }
            else if (currentR->getState() == 3)  //预订
            {

                if (DayTime[i].reserved[currentR->getStyle()]->next == NULL)
                {
                    DayTime[i].reserved[currentR->getStyle()]->next = currentR;
                    currentR->last = DayTime[i].reserved[currentR->getStyle()];
                    currentR->next = NULL;
                }
                else
                {
                    currentR->next = NULL;
                    currentR->last = lR[currentR->getStyle()];
                    lR[currentR->getStyle()]->next = currentR;
                }
                lR[currentR->getStyle()] = currentR;
            }

            currentR = currentR->down;
        }//while

        for (j = 0; j <= 5; j++)//初始化
        {
            lE[j] = NULL;
            lR[j] = NULL;
            lF[j] = NULL;
        }

    }//for

}

bool transList(int day1, int tPart1, int day2, int tPart2, int num, int s)
{

    extern room *roomNum[FLOOR+1][2][11];
    extern roomTime DayTime[15];
    extern hotelTime currentTime;
    extern int reservedState[53][RDAY+1];
    int r1, r2, r3, i1, i2, i, j;
    class room *current;

    r1 = num / 100;
    r2 = (num - r1 * 100) / 10;
    r3 = num - r1 * 100 - r2 * 10;

    if(day1 < 0 || day1 > 6) return false;
    if(day2 < 0 || day2 > 6) return false;

    int h = currentTime.getHour();
    int state;
    if(h >= 12 && h < 18) state = 1;
    else  state = 2;



       i1 = day1 * 2 + tPart1 - state + 1;    //起始时间
       i2 = day2 * 2 + tPart2 - state + 1;    //结束时间

      if (i1 < 0 || i1 > 14 || i2 < 0 || i2 > 14 || i1 > i2)
        return false;


  /*  if (DayTime[1].timeType == 1)            //现在的时间段
    {
        i1 = day1 * 2 + tPart1;
        i2 = day2 * 2 + tPart2;
    }
    else if (DayTime[1].timeType == 2)
    {
        i1 = day1 * 2 + tPart1 - 1;
        i2 = day2 * 2 + tPart2 - 1;
    }
    else
        return false;    */


    if(roomNum[r1][r2][r3] == NULL)
     QMessageBox::warning(NULL,"warning","The room is not exist",QMessageBox::Cancel);
    else
    {
        for (i = i1; i <= i2; i++)
            {
                current = roomNum[r1][r2][r3]->right;
                for (j = 1; j < i; j++)
                    current = current->right;

                if (s == 13)//空-》预定
                {
                    if (current->getState() != 1)
                        return false;
                    else
                    {
                        current->changeState(3);
                        current->last->next = current->next;
                        if (current->next != NULL)
                            current->next->last = current->last;

                        current->next = DayTime[i].reserved[current->getStyle()]->next;
                        current->last = DayTime[i].reserved[current->getStyle()];
                        if (DayTime[i].reserved[current->getStyle()]->next != NULL)
                            DayTime[i].reserved[current->getStyle()]->next->last = current;
                        DayTime[i].reserved[current->getStyle()]->next = current;
                    }
                }
                else if (s == 31)//预定-》空
                {
                    if (current->getState() != 3)
                        return false;
                    else
                    {
                        current->changeState(1);
                        current->last->next = current->next;
                        if (current->next != NULL)
                            current->next->last = current->last;
                        current->next = DayTime[i].empty[current->getStyle()]->next;
                        current->last = DayTime[i].empty[current->getStyle()];
                        if (DayTime[i].empty[current->getStyle()]->next != NULL)
                            DayTime[i].empty[current->getStyle()]->next->last = current;
                        DayTime[i].empty[current->getStyle()]->next = current;
                    }
                }
                else if (s == 12)//空-》满
                {
                    if (current->getState() != 1)
                        return false;
                    else
                    {
                        current->changeState(2);
                        current->last->next = current->next;  //删链表节点
                        if (current->next != NULL)
                            current->next->last = current->last;

                        current->next = DayTime[i].full[current->getStyle()]->next;
                        current->last = DayTime[i].full[current->getStyle()];
                        //链接到满链表上
                        if (DayTime[i].full[current->getStyle()]->next != NULL)
                            DayTime[i].full[current->getStyle()]->next->last = current;

                        DayTime[i].full[current->getStyle()]->next = current;
                    }
                }
                else if (s == 21)//满-》空
                {
                    if (current->getState() != 2)
                        return false;
                    else
                    {
                        current->changeState(1);
                        current->last->next = current->next;
                        if (current->next != NULL)
                            current->next->last = current->last;
                        current->next = DayTime[i].empty[current->getStyle()]->next;
                        current->last = DayTime[i].empty[current->getStyle()];
                        if (DayTime[i].empty[current->getStyle()]->next != NULL)
                            DayTime[i].empty[current->getStyle()]->next->last = current;
                        DayTime[i].empty[current->getStyle()]->next = current;
                    }
                }
                else if (s == 32)//预定-》满
                {
                    if (current->getState() != 3)
                        return false;
                    else
                    {
                        current->changeState(2);
                        current->last->next = current->next;
                        if (current->next != NULL)
                            current->next->last = current->last;
                        current->next = DayTime[i].full[current->getStyle()]->next;
                        current->last = DayTime[i].full[current->getStyle()];
                        if (DayTime[i].full[current->getStyle()]->next != NULL)
                            DayTime[i].full[current->getStyle()]->next->last = current;
                        DayTime[i].full[current->getStyle()]->next = current;
                    }
                }
                else if (s == 23)//满-》预定
                {
                    if (current->getState() != 2)
                        return false;
                    else
                    {
                        current->changeState(3);
                        current->last->next = current->next;
                        if (current->next != NULL)
                            current->next->last = current->last;
                        current->next = DayTime[i].reserved[current->getStyle()]->next;
                        current->last = DayTime[i].reserved[current->getStyle()];
                        if (DayTime[i].reserved[current->getStyle()]->next != NULL)
                            DayTime[i].reserved[current->getStyle()]->next->last = current;
                        DayTime[i].reserved[current->getStyle()]->next = current;
                    }
                }
                else
                    return false;

            }
            return true;
    }


}



bool timePass(void)
{
    extern room *roomNum[FLOOR+1][2][11];
    extern int reservedState[53][RDAY+1];
    extern roomTime DayTime[15];
    extern hotelTime currentTime;
    int i=1, j=0, k=1;
    class room *current1, *current2, *current3;


   /*  QString rNum[100];
     QString rFile[100];
      QString fileName = '-'+rintime[3]+'-'+rintime[4]+".txt";
      QString date = '-' + QString::number(currentTime.getYear());
      date = '-'+ QString::number(currentTime.getMonth());
      date = '-'+ QString::number(currentTime.getDay());
      date = '-'+ QString::number(currentTime.getHour()) +".txt";

    for (int p = 1; p <= FLOOR; p++)    //储存文件地址
        for (int j = 0; j <= pj[p]; j++)
            for (int k = kjs[j]; k <= pjke[p][j]; k++)
            {

                rFile[i] = "Temp/reserved/id-order/"+ QString::number(p) +  QString::number(j) +  QString::number(k)+date;
                i++;
            }

    for (i = 0; i < 52; i++)
        {
            if(reservedState[i][0] == 1)
            {

            }

        }
   */
    for (i = 0; i <= 13; i++)
     DayTime[i] = DayTime[i + 1];


    DayTime[14] = DayTime[0];
    current1 = DayTime[14].down;
    current2 = DayTime[13].down;
    current3 = DayTime[1].down;
	i = 1, j = 0, k = 1;
    int num = 0;
    while (current1 != NULL)          //把预定表加到前几天链表里
    {
        if (reservedState[i][14] == 0)       //后面没有预定
        current1->changeState(1);

        current1->changePN(0);         //调整房间最后一列

        if (num < 52 &&reservedState[num][14] == 0)       //后面没有预定
            current1->changeState(1);
         else if (num < 52 && reservedState[num][14] == 1)  //后面有预定
           current1->changeState(3);


        current2->right = current1;
        current1->right = NULL;
        roomNum[i][j][k]->right = current3;   //调整房号数组
        k++;
        if (k == 10)
        {
            k = 0;
            j = 1;
        }
        if (k == 1 && j == 1)
        {
            j = 0;
            i++;
        }

		current1 = current1->down;
		current2 = current2->down;
		current3 = current3->down;
        num++;
    }

    if (DayTime[14].timeType == 2)
        DayTime[14].timeType = 1;
    else if (DayTime[14].timeType == 1)
        DayTime[14].timeType = 2;
    else
        return false;

    DayTime[0].down = NULL;                  //还原DayTime【0】
    for (i = 1; i <= 5; i++)
    {
        DayTime[0].empty[i] = NULL;
        DayTime[0].full[i] = NULL;
        DayTime[0].reserved[i] = NULL;
        DayTime[0].timeType = 0;
    }

    for (i = 0; i < 52; i++)                  //修改预约数组
        {
            for (j = 0; j < RDAY - 1; j++)
                reservedState[i][j] = reservedState[i][j + 1];
            reservedState[i][RDAY - 1] = 0;
        }

    saveReserved();
    return true;
}


bool foundReserved(void)
{

    int pj[FLOOR + 1] = { 0, 1, 1, 1, 1, 1, 0 };        //截止量
    int kjs[2] = { 1, 0 };
    int pjke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};
    int i = 0;
    extern int reservedState[53][RDAY+1];
    QString rNum[100];

    for (int p = 1; p <= FLOOR; p++)    //储存文件地址
        for (int j = 0; j <= pj[p]; j++)
            for (int k = kjs[j]; k <= pjke[p][j]; k++)
            {

                rNum[i] = "Temp/Reserved_60/" +  QString::number(p) +  QString::number(j) +  QString::number(k) + ".txt";
                i++;
            }

    for (i = 0; i < 52; i++)   //读入
    {
        QFile fr(rNum[i]);
        QTextStream stream(&fr);
        if (fr.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            int j;
            QString fstate;
            for (j = 1; j <= RDAY; j++)
            {
                fstate = stream.readLine();
                if (fstate == "***")
                    return false;
                reservedState[i][j] = fstate.toInt();
            }
        }
        else
            return false;

        if (stream.readLine() != "***")
            return false;
        fr.close();
    }

    return true;
}

bool saveReserved(void)         //保存60天预定表到文件，以房间号为单位
{
    int pj[FLOOR + 1] = { 0, 1, 1, 1, 1, 1, 0 };        //截止量
    int kjs[2] = { 1, 0 };
    int pjke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};
    int i = 0;
    extern int reservedState[53][RDAY+1];
    QString rNum[100];

    for (int p = 1; p <= FLOOR; p++)    //储存文件地址
        for (int j = 0; j <= pj[p]; j++)
            for (int k = kjs[j]; k <= pjke[p][j]; k++)
            {
                rNum[i] = "Temp/Reserved_60/" +  QString::number(p) +  QString::number(j) +  QString::number(k) + ".txt";
                i++;
            }

    for (i = 0; i < 52; i++)   //写入预定表
    {
        QFile fr(rNum[i]);
        QTextStream stream(&fr);
        if (fr.open(QIODevice::Text | QIODevice::WriteOnly))
        {
            int j;
            QString fstate;
            for (j = 0; j < RDAY; j++)
            {
                fstate = QString::number(reservedState[i][j]);
                stream << fstate << "\n";
            }
            stream << "***";
        }
        else
            return false;
        fr.close();
    }

    return true;
}

bool judgeReserved(int day1, int tPart1, int day2, int tPart2) //判断预定时间是否合法，把能预定的房间放入文件roomCanReserved
{
    int t1, t2;
    extern hotelTime currentTime;
    extern int reservedState[53][RDAY+1];

    int h = currentTime.getHour();
    int state;
    if(h >= 12 && h <= 18) state = 1;
    else if(h < 12 ) state = 0;
    else  if(h > 18) state = 2;
    else return false;

    if(day1 < 0 || day2 < 0 || day2 < day1)
        return false;

            t1 = day1 * 2 + tPart1 - state;    //起始时间
            t2 = day2 * 2 + tPart2 - state;    //结束时间

       if(t1 < 0 || t2 < 0)
       return false;
       if (t1 < 0 || t1 > 51 || t2 < 0 || t2 > 51 || t1 > t2)
        return false;

    QFile fr("Temp\\roomCanReserve.txt");
    QFile ft("Temp/roomNoCanReserve.txt");
    QTextStream stream(&fr);
    QTextStream stream2(&ft);
    ft.open(QIODevice::Text | QIODevice::WriteOnly);
    if (fr.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        int pj[FLOOR + 1] = { 0, 1, 1, 1, 1, 1, 0 };        //截止量
        int kjs[2] = { 1, 0 };
        int pjke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};
        int i = 0, j = 0, count = 0;

        QString rNum[100];

        for (int p = 1; p <= FLOOR; p++)    //创建房间编号
            for (int j = 0; j <= pj[p]; j++)
                for (int k = kjs[j]; k <= pjke[p][j]; k++)
                {
                    rNum[i] =  QString::number(p) +  QString::number(j) +  QString::number(k);
                    i++;
                }

        for (i = 0; i < 52; i++)         //各个房间进行遍历
        {
            for (j = t1; j <= t2; j++)          //每天进行遍历
            {
                if (reservedState[i][j] == 1)
                {
                    count = 1;
                    stream2 << rNum[i] << endl;
                    break;
                }
            }
            if (count == 0)
                stream << rNum[i] << endl;
            else
                count = 0;

        }
    }
    else
        return false;

    stream << "***" << endl;
    stream2 << "***" << endl;
    fr.close();
    ft.close();
    return true;

}

bool changeReserved(QString rNum, int day1, int tPart1, int day2, int tPart2, QString trans)
{
    int t1, t2;
    extern int reservedState[53][RDAY+1];
    extern hotelTime currentTime;

    int h = currentTime.getHour();
    int state;
    if(h >= 12 && h < 18) state = 1;
    else if(h < 12 ) state = 2;
    else  if(h >= 18) state = 2;
    else return false;


            t1 = day1 * 2 + tPart1 - state;    //起始时间
            t2 = day2 * 2 + tPart2 - state;    //结束时间

       if(t1 < 0 || t2 < 0)
       return false;
       if (t1 < 0 || t1 > 51 || t2 < 0 || t2 > 51 || t1 > t2)
        return false;

    int num, i, j;
    num = rNum.toInt();
    i = (num / 100 - 1) * 10 + num % 100 - 1;

    if (trans == "01")           //从0到1
    {
        for (j = t1; j <= t2; j++)
        {
            /*if (reservedState[i][j] != 0)
                return false;
            else*/
                reservedState[i][j] = 1;
        }
    }
    else if (trans == "10")    //从1到0
    {
        for (j = t1; j <= t2; j++)
        {
            /*if (reservedState[i][j] != 1)
                return false;
            else*/
                reservedState[i][j] = 0;
        }
    }
    else if(trans == "02")
    {
        for (j = t1; j <= t2; j++)
        {
            /*if (reservedState[i][j] != 0)
                return false;
            else*/
                reservedState[i][j] = 2;
        }
    }
    else if(trans == "20")
    {
        for (j = t1; j <= t2; j++)
        {
            /*if (reservedState[i][j] != 1)
                return false;
            else*/
                reservedState[i][j] = 0;
        }
    }
    else
        return false;

    return true;


}

void checkInTimeUp(void)
{
    extern hotelTime currentTime;

    int pj[FLOOR + 1] = { 0, 1, 1, 1, 1, 1, 0 };        //截止量
    int kjs[2] = { 1, 0 };
    int pjke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};
    int i=0;

    QString rNum[100];

    for (int p = 1; p <= FLOOR; p++)    //创建房间编号
        for (int j = 0; j <= pj[p]; j++)
            for (int k = kjs[j]; k <= pjke[p][j]; k++)
            {
                rNum[i] =  QString::number(p) +  QString::number(j) +  QString::number(k);
                i++;
            }

    for(int i = 0; i < 52; i++)
    {
        QString file0="Temp/checkIn/"+rNum[i]+".txt";
        QFile file(file0);

        if(file.exists())
        {
            if (file.open(QIODevice::Text | QIODevice::ReadOnly))
            {
                QString cyear, cmonth, cday, chour, allInfo;
                int y, m, d, h;
                QTextStream stream(&file);
                stream.readLine();
                stream.readLine();
                allInfo = stream.readLine();//找到离开时间
                cyear = allInfo.mid(10,4);
                cmonth = allInfo.section("/",1,1);
                cday = allInfo.section("/",2,2);
                chour = allInfo.section("/",3,3);

                int month_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

                if (currentTime.getYear() % 4 == 0 && currentTime.getYear() % 100 != 0 || currentTime.getYear() % 400 == 0)
                    month_day[1]=29;

                y=cyear.toInt()+(cmonth.toInt()+(cday.toInt()+(chour.toInt()+4)/24)/month_day[cmonth.toInt()])/12;
                m=(cmonth.toInt()+(cday.toInt()+(chour.toInt()+4)/24)/month_day[cmonth.toInt()])%12;
                d=(cday.toInt()+(chour.toInt()+4)/24)%month_day[cmonth.toInt()];
                h=(chour.toInt()+4)%24;

                if(currentTime.getYear()>y
                  ||currentTime.getYear()==y&&currentTime.getMonth()>m
                  ||currentTime.getYear()==y&&currentTime.getMonth()==m&&currentTime.getDay()>d
                  ||currentTime.getYear()==y&&currentTime.getMonth()==m&&currentTime.getDay()==d&&currentTime.getHour()>=h)
                    //该房间已超时
                {
                    file.remove();
                    QMessageBox::information(NULL,rNum[i]+"房间","已超出退房时间，强制退房！",QMessageBox::Yes,
                                             QMessageBox::Yes);
                }
            }
        }
    }

}

void reservedTimeUp(void)
{
    extern hotelTime currentTime;

    int pj[FLOOR + 1] = { 0, 1, 1, 1, 1, 1, 0 };        //截止量
    int kjs[2] = { 1, 0 };
    int pjke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};
    int i=0;

    QString rNum[100];

    for (int p = 1; p <= FLOOR; p++)    //创建房间编号
        for (int j = 0; j <= pj[p]; j++)
            for (int k = kjs[j]; k <= pjke[p][j]; k++)
            {
                rNum[i] =  QString::number(p) +  QString::number(j) +  QString::number(k);
                i++;
            }

    for(int i = 0; i < 52; i++)
    {
        QString cyear, cmonth, cday, chour, id;
        cyear.setNum(currentTime.getYear());
        cmonth.setNum(currentTime.getMonth());
        cday.setNum(currentTime.getDay());
        chour.setNum(currentTime.getHour());
        QString file0="Temp/reserved/"+rNum[i]+"-"+cyear+"-"+cmonth+"-"+cday+"-"+chour+".txt";
        QFile file(file0);

        if(file.exists())
        {
            if (file.open(QIODevice::Text | QIODevice::ReadOnly))
            {
                QTextStream stream(&file);
                id = stream.readLine();

                QString file1="Temp/reserved/"+id+".txt";
                QFile file2(file1);
                if(file2.exists())
                {
                    if (file2.open(QIODevice::Text | QIODevice::ReadOnly))
                    {
                        QString allInfo;
                        int year, month, day, hour, tday, tpart, t;
                        QTextStream stream1(&file2);
                        stream1.readLine();
                        stream1.readLine();
                        stream1.readLine();
                        stream1.readLine();
                        allInfo = stream1.readLine();//找到离开时间
                        cyear = allInfo.mid(10,4);
                        cmonth = allInfo.section("/",1,1);
                        cday = allInfo.section("/",2,2);
                        chour = allInfo.section("/",3,3);
                        year=cyear.toInt();
                        month=cmonth.toInt();
                        day=cday.toInt();
                        hour=chour.toInt();

                        t=period(year,month,day,hour);
                        if(currentTime.getHour()<12)//计算要更改的状态数
                        {
                            if(hour<12)
                            {
                                tday=t;
                                tpart=2;
                            }
                            else if(hour>=18)
                            {
                                tday=t+1;
                                tpart=2;
                            }
                            else
                            {
                                tday=t+1;
                                tpart=1;
                            }
                        }
                        else if(currentTime.getHour()>=18)
                        {
                            if(hour<12)
                            {
                                tday=t-1;
                                tpart=2;
                            }
                            else if(hour>=18)
                            {
                                tday=t;
                                tpart=2;
                            }
                            else
                            {
                                tday=t;
                                tpart=1;
                            }
                        }
                        else
                        {
                            if(hour<12)
                            {
                                tday=t-1;
                                tpart=2;
                            }
                            else if(hour>=18)
                            {
                                tday=t;
                                tpart=2;
                            }
                            else
                            {
                                tday=t;
                                tpart=1;
                            }
                        }

                        transList(0,currentTime.getTimeState(),tday,tpart,rNum[i].toInt(),31);//预定-》空
                        changeReserved(rNum[i],0,currentTime.getTimeState(),tday,tpart,"10");

                    }
                    file2.remove();
                    QMessageBox::information(NULL,rNum[i]+"房间","已超出预定时间，强制取消预订！",QMessageBox::Yes,
                                                            QMessageBox::Yes);
                }

            }
        }
        file.remove();

    }

}
