#include "hotel.h"
#include "client.h"
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include "room.h"
#include "timethread.h"
#include "resignin.h"
#include "hotelinfo.h"

roomTime DayTime[15];
room *roomNum[FLOOR+1][2][11];            //左侧第一列头链表，
hotelTime currentTime;
int reservedState[53][RDAY+1] = {0};          //记录预约状态
client *head;
HotelInfo OurHotel;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFileInfo t("Temp");

    if(t.exists() == false)
    {
        establish();
        establish_2();
     }
    foundReserved();
    foundlist_0();
    foundList_1();
    OurHotel.fileInHotel();
    Hotel w;
    resignIn r;

    if(r.exec ()==QDialog::Accepted)
    {

        w.show();
        return a.exec();
    }
   else
        return 0;

}
