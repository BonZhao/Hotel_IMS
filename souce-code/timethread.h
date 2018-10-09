#ifndef TIMETHREAD_H
#define TIMETHREAD_H
#include <QThread>
#include <QDateTime>
class timeThread: public QThread
{
    Q_OBJECT
public:
     explicit timeThread(QObject *parent = 0);
     ~timeThread();
     void run();
     bool stop = false;
signals:
   void timeChanged(int);
public slots:
};

class hotelTime: public QDateTime
{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int timeState;
public:

    int getYear(void);
    int getMonth(void);
    int getDay(void);
    int getHour(void);
    int getMinute(void);
    int getTimeState(void);
    hotelTime getHotelTime(void);


    void setYear(int);
    void setMonth(int);  // 1 - 12
    void setDay(int);    // 1 - 31/30/28/29
    void setHour(int);   // 0 - 23
    void setMinute(int); // 0 - 59
    void setTimeState(void);//1/2

    void setHotelTime(int,int,int,int,int);       //设置时间，完整
    void setHotelTime(int,int,int);                   //设置时间，到天

    QDateTime hotelTime_to_QDate();
    QDateTime hotelTime_to_QDate(const hotelTime &other);
    hotelTime QDate_to_hotelTime(const QDateTime &other);
    hotelTime addMin();
    hotelTime addMin(int i);
    void readFileTime();
    void saveFileTime();
};
int period(int y, int m, int d,int h);
#endif // TIMETHREAD_H
