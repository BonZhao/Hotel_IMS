#include "timethread.h"
#include <QThread>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QString>
#include <QTextStream>

int month1[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int month2[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
timeThread::timeThread(QObject *parent):
    QThread(parent)
{

}



timeThread::~timeThread()
{

}





int hotelTime::getYear(void)
{
    return this->year;
}

int hotelTime::getMonth(void)
{
    return this->month;
}

int hotelTime::getDay(void)
{
    return this->day;
}

int hotelTime::getHour(void)
{
    return this->hour;
}

int hotelTime::getMinute(void)
{
    return this->minute;
}

int hotelTime::getTimeState(void)
{
    if(this->time().hour() >= 12 && this->time().hour() < 18)
     this->timeState = 1;
    else
     this->timeState = 2;
    return this->timeState;
}

hotelTime hotelTime ::getHotelTime(void)
{
    hotelTime t;
    t.setHotelTime(this->year,this->month,this->day,this->hour,this->minute);
    return t;
}

void  hotelTime:: setYear(int yearSet)
{
    this->year = yearSet;
    this->setDate(QDate(yearSet,month,day));
}

void  hotelTime:: setMonth(int monthSet)
{
    this->month = monthSet;
    this->setDate(QDate(year,monthSet,day));
 }

void hotelTime:: setDay(int daySet)    // 1 - 31/30/28/29
{
    this->day = daySet;
    this->setDate(QDate(year,month,daySet));
 }

void hotelTime::setHour(int hourSet)
{
    this->hour = hourSet;
    this->setTime(QTime(hourSet,minute,0,0));
    this->setTimeState();
}

void hotelTime:: setMinute(int minuteSet)
{
    this->minute = minuteSet;
    this->setTime(QTime(hour,minuteSet,0,0));
 }

void hotelTime:: setTimeState(void)
{
    if(this->hour >= 12 && this->hour < 18 )
    this->timeState = 1;
    else
    this ->timeState = 2;
}

void hotelTime::setHotelTime(int yearSet,int monthSet,int daySet)                   //设置时间，到天
{
    this->setYear(yearSet);
    this->setMonth(monthSet);
    this->setDay(daySet);
    this->setDate(QDate(yearSet,monthSet,daySet));
    
}

void hotelTime::setHotelTime(int yearSet,int monthSet,int daySet , int hourSet , int minuteSet)                   //设置时间，完整
{
    this->setYear(yearSet);
    this->setMonth(monthSet);
    this->setDay(daySet);
    this->setHour(hourSet);
    this->setMinute(minuteSet);
    this->setTimeState();
    this->setDate(QDate(yearSet,monthSet,daySet));
    this->setTime(QTime(hourSet,minuteSet,0,0));
}

QDateTime hotelTime::hotelTime_to_QDate()
{
    QDateTime t;
    t.setDate(QDate(year,month,day));
    t.setTime(QTime(hour,minute,0,0));
    return t;
}

QDateTime hotelTime::hotelTime_to_QDate(const hotelTime &other)
{
    QDateTime t;
    t.setDate(QDate(other.year,other.month,other.day));
    t.setTime(QTime(other.hour,other.minute,0,0));
    return t;
}

hotelTime hotelTime::QDate_to_hotelTime(const QDateTime &other)
{
    hotelTime t;
    year = other.date().year();
    month = other.date().month();
    day = other.date().day();
    hour = other.time().hour();
    minute = other.time().minute();

    t.setHotelTime(year,month,day,hour,minute);
    return t;
}

hotelTime hotelTime::addMin(int i)
{
    QDateTime p;
    hotelTime t;
    p = this->hotelTime_to_QDate();
    p = p.addSecs(60 * i);
    t = t.QDate_to_hotelTime(p);
    return t;
}

hotelTime hotelTime::addMin()
{
    hotelTime t;
    t.setHotelTime(year,month,day,hour,minute);
    int flag = ((year % 400 == 0) || (year %4 ==0 && year %100 != 0) );
    // 1 - 闰    0 -平


    if(minute != 59)
    t.setMinute(minute + 1);
    else
    {
        t.setMinute(0);
        if(hour != 23) t.setHour(hour+1);
        else
        {
            t.setHour(0);
            if(flag == 1)
            {
                if(day == month1[month])
                {
                    if(month == 12) t.setYear(year+1),t.setMonth(1),t.setDay(1);
                    else t.setMonth(month+1),t.setDay(1);
                }
                else t.setDay(day+1);
            }
            else if(flag == 0)
            {
                if(day == month2[month])
                {
                    if(month == 12) t.setYear(year+1),t.setMonth(1),t.setDay(1);
                    else t.setMonth(month+1),t.setDay(1);
                }
                else t.setDay(day+1);
            }
        }
    }
    return t;
}

void hotelTime::readFileTime()                  //读取时间到系统中
{
    QString hT = "Temp/hotelTime.txt";
    QFile fHotelTime(hT);
    QTextStream in(&fHotelTime);
    int year , month ,day,hour,minute,sec;
    if(fHotelTime.open(QIODevice::Text|QIODevice::ReadOnly))
    {
        year = in.readLine().mid(6).toInt();
        month = in.readLine().mid(7).toInt();
        day = in.readLine().mid(5).toInt();
        hour = in.readLine().mid(6).toInt();
        minute=in.readLine().mid(8).toInt();
        sec = in.readLine().mid(5).toInt();
        this->setHotelTime(year,month,day,hour,minute);
    }
    fHotelTime.close();
}

void hotelTime::saveFileTime()                    //保存系统时间
{
    QString hT = "Temp/hotelTime.txt";
    QFile fHotelTime(hT);
    QTextStream in(&fHotelTime);
    QString year , month ,day,hour,minute,sec;

    year = QString::number(this->getYear());
    month = QString::number(this->getMonth());
    day = QString::number(this->getDay());
    hour = QString::number(this->getHour());
    minute =QString::number(this->getMinute());
    if(fHotelTime.open(QIODevice::Text|QIODevice::WriteOnly))
    {
        in << "[Year]"<<year <<endl<<"[Month]"<<month <<endl<<"[Day]"<<day<<endl;
        in << "[Hour]"<<hour << endl <<"[Minute]"<< minute<<endl<<"[Sec]00"<<endl;
        in <<"***";
    }
    fHotelTime.close();
}

void timeThread::run()
{

    for(int i = 0 ; i < 10000; i++)
    {
        QMutex mutex;
       // mutex.lock();

        //mutex.unlock();
       if(!(this ->stop))
        emit timeChanged(i);
        this->msleep(1000);
    }
}

int period(int y, int m, int d,int h)          //算输入时间和系统时间时间差
{
    extern hotelTime currentTime;
    int now[5];
    now[1]=currentTime.getYear();
    now[2] = currentTime.getMonth();
    now[3] = currentTime.getDay();
    now[4] = currentTime.getHour();
    if (now[4] < 12)
        now[3]--;
    if (h <= 12)
        d--;
    int i,u,p;
    int month_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int year[3],days[3];
    year[1] = y - 1;
    year[2] = now[1]-1;

    days[1] = y * 365 + y / 4 - y / 100 + y / 400;
    days[2] = now[1] * 365 + now[1] / 4 - now[1]/ 100 + now[1] / 400;

    if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
        month_day[1]=29;

    for (i = 0; i< m - 1; i++)
        days[1] += month_day[i];

    if (now[1] % 4 == 0 && now[1] % 100 != 0 || now[1] % 400 == 0)
        month_day[1] = 29;
    else
        month_day[1] = 28;

    for (u = 0; u < now[2]- 1;u++)
        days[2] += month_day[u];

    days[1] += d - 1;
    days[2] += now[3] - 1;
    p = days[1] - days[2];
    return p;
}
