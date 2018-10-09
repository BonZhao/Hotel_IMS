#include "hotel.h"
#include "ui_hotel.h"
#include "client.h"
#include "room.h"
#include <QFile>
#include <QString>
#include <QLineEdit>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QTextBrowser>
#include <QTableWidget>
#include <QPushButton>
#include <QList>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include "timethread.h"
#include "resignin.h"
#include <math.h>
#include "hotelinfo.h"
int roomLabeli,roomLabelj,roomLabelk;
extern hotelTime currentTime;
extern client *head;
extern HotelInfo OurHotel;



Hotel::Hotel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hotel)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);


    tThread = new timeThread(this);
    connect(tThread,SIGNAL(timeChanged(int)),this,SLOT(ontimeChanged(int)));

    tThread->start();

    int ijs[FLOOR+1] = {0,0,0,0,0,0,0};
    int ije[FLOOR+1] = {0,1,1,1,1,1,0};
    int jks[FLOOR+1] = {1,0};
    int ijke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};

    for (int i = 1; i <= FLOOR; i++)                 //初始化*roomNum[FLOOR+1][2][11]
    {
        for (int j = ijs[i]; j <= ije[i]; j++)
        {
            for (int k = jks[j]; k <= ijke[i][j]; k++)
             {

                QString t;
                t.setNum(100*i + 10*j + k ,10);
                r[i][j][k] = new QPushButton(t);
                r[i][j][k]->resize(30, 40);
                r[i][j][k]->setMaximumSize(30,40);
                r[i][j][k]->setMinimumSize(30,40);
                r[i][j][k]->setText(t);
                r[i][j][k]->setAutoFillBackground(true);
                r[i][j][k]->setPalette(Qt::yellow);
                r[i][j][k]->setFlat(1);

                connect(r[i][j][k],SIGNAL(clicked()),this,SLOT(on_reserve_clicked()));//预定按钮

                cr[i][j][k] = new QPushButton(t);
                cr[i][j][k]->resize(30, 40);
                cr[i][j][k]->setMaximumSize(30,40);
                cr[i][j][k]->setMinimumSize(30,40);
                cr[i][j][k]->setText(t);
                cr[i][j][k]->setAutoFillBackground(true);
                cr[i][j][k]->setPalette(Qt::cyan);
                cr[i][j][k]->setFlat(1);

                connect(cr[i][j][k],SIGNAL(clicked()),this,SLOT(on_checkIn_clicked()));//入住按钮



            }
        }
    }

/*
                roomLabeli = i;
                roomLabelj = j;
                roomLabelk = k;
*/
}

Hotel::~Hotel()
{
    delete ui;
}

void Hotel::on_checkIn_clicked()
{
    extern room *roomNum[FLOOR+1][2][11];
    extern hotelTime currentTime;
    room * chRoom ; //表示待住房间
    QPushButton * digitalbutton = (QPushButton *) sender();
    QString t = digitalbutton->text();



    ui ->label_28->setText(t);      //放置房间号
    int i = t.mid(0,1).toInt();
    int j = t.mid(1,1).toInt();
    int k = t.mid(2,1).toInt();
    int maxPeopleNum = roomNum[i][j][k]->getMPN();
    ui->spinBox_4->setMaximum(maxPeopleNum);

    ui->lineEdit_12 ->clear();
    ui->lineEdit_10 ->clear();
    ui->lineEdit_11 ->clear();
    ui->lineEdit_13 ->clear();
    ui->lineEdit_14 ->clear();

    ui->label_48->show();ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateTimeEdit_2->setDateTime(currentTime.hotelTime_to_QDate());

    ui->spinBox_4->setValue(1);
    ui->spinBox_4->show();
    ui ->stackedWidget_2->setCurrentIndex(3);

    chRoom = roomNum[i][j][k] -> right;
    int maxCheckTime = 1; //最长入住时长
    /*
    1 - 空；
    2 - 入住；
    3 - 已被预订
    (4 - 脏房...)
    */
    while(chRoom != NULL)
   {
        if(chRoom->getState() == 1)
        maxCheckTime++;
        else
        break;
        chRoom = chRoom ->right;
   }

    ui -> dateTimeEdit_2->setMinimumDateTime(currentTime.hotelTime_to_QDate());
    ui -> dateTimeEdit_2->setMaximumDateTime(currentTime.hotelTime_to_QDate().addDays( maxCheckTime/2));

    ui->dateTimeEdit_2->show();
    ui->label_55->show();
    ui->pushButton_6->show();    //下个月按钮
    ui->pushButton_5->show();    //上个月按钮
}

void Hotel::on_pushButton_5_clicked()            //下个月时间按钮
{
    QDateTime t = ui -> dateTimeEdit_2->dateTime();
    t =  t.addMonths(1);
    t.setDate(QDate(t.date().year(),t.date().month(),1));
    ui->dateTimeEdit_2->setDateTime(t);
}

void Hotel::on_pushButton_6_clicked()           //上个月时间按钮
{
    QDateTime t = ui -> dateTimeEdit_2->dateTime();
    QDateTime p;
    int m = t.date().month();
    int n;
    if(m != 1)
         n = m - 1;
    else n = 12;
    t.setDate(QDate(t.date().year(),n,27));

    while(t.date().month() == n)
    {
        p = t;
        t = t.addDays(1);
    }
    ui->dateTimeEdit_2->setDateTime(p);
}

void Hotel::on_pushButton_22_clicked()                  //住房登记表确定住房
{
        extern room *roomNum[FLOOR+1][2][11];


        bool exist;
            client c;
            clientRoomInfo cr;
            c.addNamebirthloc(ui->lineEdit_12->text(), ui->lineEdit_10->text(), ui->lineEdit_11->text());
            c.addcall(ui->lineEdit_14->text());
            c.addiden(ui->lineEdit_13->text());
            int flag = 0, cost = 0;

            QString rnum;
            int num, r1, r2, r3, style;
            rnum = ui->label_28->text();
            num = rnum.toInt();
            r1 = num / 100;
            r2 = (num - r1 * 100) / 10;
            r3 = num - r1 * 100 - r2 * 10;
            style = roomNum[r1][r2][r3] -> getStyle();


            QString file1="Temp/client/"+c.getIDnum()+".txt";
            QFile cfile(file1);

            if(cfile.exists())
                exist=true;
            else
                exist=false;

            if(exist)
            {
                if (cfile.open(QIODevice::Text | QIODevice::ReadOnly))
                {
                    QTextStream stream(&cfile);

                    for (int i = 1; i <= 6; i++)
                        stream.readLine();

                    cr.frequence  = (stream.readLine()).toInt();
                    for (int i = 1; i <= 5; i++)
                    {

                        stream.readLine();
                        cr.roomSt[i] = (stream.readLine()).toInt();
                        cr.time[i]   = (stream.readLine()).toInt();
                        cr.money[i]  = (stream.readLine()).toInt();
                    }
                    stream.readLine();
                    cost = (stream.readLine()).toInt();
                    flag = 1;
                }

                cfile.close();
            }


            if (cfile.open(QIODevice::Text | QIODevice::WriteOnly))
            {
                QTextStream stream(&cfile);

                stream<<ui->lineEdit_12->text()<<endl;//姓名
                stream<<ui->comboBox_2->currentText()<<endl;//性别
                stream<<ui->lineEdit_10->text()<<endl;//生日
                stream<<ui->lineEdit_11->text()<<endl;//地址
                stream<<ui->lineEdit_13->text()<<endl;//身份证号
                stream<<ui->lineEdit_14->text()<<endl;//手机号
                if(exist)
                {
                    stream << cr.frequence + 1 << endl;//入住次数
                    for(int i=1; i<=5; i++)
                    {
                        stream<<"-----类型"<<i<<"-----"<<endl;
                        if(style==i)
                            stream<<cr.roomSt[i]+1<<endl;
                        else
                            stream<<cr.roomSt[i]<<endl;
                        stream<<cr.time[i]<<endl;
                        stream<<cr.money[i]<<endl;
                    }
                    stream<<"---------------"<<endl;
                    stream<<cost;
                }
                else
                {
                    stream<< 1 <<endl;//入住次数
                    for(int i=1; i<=5; i++)
                    {
                        stream<<"-----类型"<< i <<"-----"<< endl;
                        if(style == i)
                            stream<< 1 <<endl;
                        else
                            stream<< 0 <<endl;
                        stream<<0<<endl;
                        stream<<0<<endl;
                    }
                    stream<<"---------------"<<endl;
                    stream<<0;
                }
                flag = 1;

            }
            else
                flag = 0;
            cfile.close();

            if(!exist)
            {
                QFile cfile2("Temp/client/index.txt");
                if (cfile2.open(QIODevice::Text | QIODevice::ReadWrite))
                {
                    QTextStream stream1(&cfile2);
                    stream1.seek(cfile2.size());
                    stream1<<endl<<c.getIDnum();
                    flag=1;
                }
                else
                    flag=0;
            }



            if(ui->spinBox_5->value()==0)
                       {
                           QString rfile="Temp/checkIn/"+ui->label_28->text()+".txt";
                           QFile rcfile(rfile);

                           QDateTime st = ui->dateTimeEdit->dateTime();
                           hotelTime st2 ;
                           st2.QDate_to_hotelTime(st);
                           int sy = st.date().year();
                           int sm = st.date().month();
                           int sd = st.date().day();
                           int sh = st.time().hour();
                           QDateTime et = ui->dateTimeEdit_2->dateTime();
                           hotelTime et2 ;
                           et2.QDate_to_hotelTime(et);
                           int ey = et.date().year();
                           int em = et.date().month();
                           int ed = et.date().day();
                           int eh = et.time().hour();

                           if(rcfile.exists())
                               QMessageBox::information(NULL, "information", "该房间已经有人入住！", QMessageBox::No);
                           else
                           {
                               if (rcfile.open(QIODevice::Text | QIODevice::WriteOnly))
                               {
                                   QTextStream rstream(&rcfile);
                                   rstream<<"[PEOPLENUM]:"<<ui->spinBox_4->value()<<endl;
                                   rstream<<"[STARTTIME]:"<<sy<<"/";
                                   if(sm < 10)
                                    rstream<<  0 << sm <<"/";
                                   else
                                    rstream << sm <<"/";
                                   if(sd < 10)
                                     rstream<<  0 << sd <<"/";
                                   else
                                    rstream << sd <<"/";
                                   if(sh < 10)
                                     rstream<<  0 << sh <<endl;
                                   else
                                    rstream << sh <<endl;


                                   rstream<<"[ENDTIME]:"<<ey<<"/";
                                    if(em < 10)
                                     rstream<<  0 << em <<"/";
                                    else
                                     rstream << em <<"/";
                                    if(ed < 10)
                                      rstream<<  0 << ed <<"/";
                                    else
                                     rstream << ed <<"/";
                                    if(eh < 10)
                                      rstream<<  0 << eh <<endl;
                                    else
                                     rstream << eh <<endl;

                                   rstream<<"[TYPE]:"<<ui->comboBox_3->currentText()<<endl;
                                   rstream<<"[CURRENTMONEY]:0"<<endl;
                                   rstream<<"[ITEM]:1/00;2/00;3/00;4/00;5/00"<<endl;
                                   rstream<<"-----------------------------"<<endl;
                                   rstream<<"[NAME]:"<<ui->lineEdit_12->text()<<endl;
                                   rstream<<"[BIRTHDAY]:"<<ui->lineEdit_10->text()<<endl;
                                   rstream<<"[SEX]:"<<ui->comboBox_2->currentIndex()+1<<endl;
                                   rstream<<"[ID]:"<<ui->lineEdit_13->text()<<endl;
                                   rstream<<"[LOCATION]:"<<ui->lineEdit_11->text()<<endl;
                                   rstream<<"[CELLPHONE]:"<<ui->lineEdit_14->text();
                                   rcfile.close();
                               }
                           }
                       }
                       else
                       {
                           QString rfile="Temp/checkIn/"+ui->label_28->text()+".txt";
                           QFile rcfile(rfile);

                           if (rcfile.open(QIODevice::Text | QIODevice::ReadWrite))
                           {
                               QTextStream rstream(&rcfile);
                               rstream.seek(rcfile.size());
                               rstream<<endl<<"-----------------------------"<<endl;
                               rstream<<"[NAME]:"<<ui->lineEdit_12->text()<<endl;
                               rstream<<"[BIRTHDAY]:"<<ui->lineEdit_10->text()<<endl;
                               rstream<<"[SEX]:"<<ui->comboBox_2->currentIndex()+1<<endl;
                               rstream<<"[ID]:"<<ui->lineEdit_13->text()<<endl;
                               rstream<<"[LOCATION]:"<<ui->lineEdit_11->text()<<endl;
                               rstream<<"[CELLPHONE]:"<<ui->lineEdit_14->text();
                               rcfile.close();
                           }
                       }

                       ui->spinBox_5->setValue(ui->spinBox_5->value()+1);



        ui->lineEdit_12 ->clear();
        ui->lineEdit_10 ->clear();
        ui->lineEdit_11 ->clear();
        ui->lineEdit_13 ->clear();
        ui->lineEdit_14 ->clear();
        ui->comboBox_2->setCurrentIndex(0);
        ui->comboBox_3->setCurrentIndex(0);

        ui->spinBox_4->setValue((ui->spinBox_4->value())-1);
        if(ui->spinBox_4->value() != 0)
        {
            ui->spinBox_4->hide();
            ui->label_48->hide();
            ui->label_30->hide();      //收费类型label hide
            ui->comboBox_3->hide();    //VIP... hide

            ui->label_55->hide();         //时间label
            ui->pushButton_6->hide();    //下个月按钮
            ui->pushButton_5->hide();    //上个月按钮
            ui->dateTimeEdit_2->hide();   //时间编辑

            ui ->stackedWidget_2->setCurrentIndex(3);
        }
        else
        {
            QDateTime t = ui->dateTimeEdit_2->dateTime();
            hotelTime t2 ;
            t2.QDate_to_hotelTime(t);
            int y = t.date().year();
            int m = t.date().month();
            int d = t.date().day();
            int h = t.time().hour();

            int flag = 0;
            int days  = period(y, m, d, h);
            if(transList(0,currentTime.getTimeState(),days,t2.getTimeState(),num,12) == true)
             saveRoom(),flag = 1;
            else if(transList(0,currentTime.getTimeState(),days,t2.getTimeState(),num,32) == true)
                //预定到住人
            {
                flag = 2;
                QString id;
                id = ui -> lineEdit_2->text();
                QString cfilename = "Temp/reserved/" + id  + ".txt";
                QFile file0(cfilename);
                QTextStream in(&file0);
                QString name;
                if (file0.open(QIODevice::Text | QIODevice::ReadOnly))
                {
                      for(int i = 1 ; i <= 7; i++)
                          name = in.readLine();
                      name = name.mid(11);
                }
               file0.close();

               QFile::remove(cfilename);
               QFile::remove(name);
               saveRoom();
               flag = 1;
            }

            if(flag == 1)
            {
                OurHotel.addCheckInRoom_changeRadio(1);
                if(changeReserved(rnum,0,currentTime.getTimeState(),days,t2.getTimeState(),"02")== true)
                saveReserved();

                OurHotel.addPeopleCheckIn_his_mon_now(ui->spinBox_5->value());//增加入住人数
                OurHotel.fileOutHotel();
                QMessageBox::information(NULL, "information", "成功", QMessageBox::Yes);


            }
            else
            {
                if(flag == 2)
                   QMessageBox::warning(NULL, "warning", "未到预定时间，该房有人入住，入住失败", QMessageBox::Cancel);
                else
                QMessageBox::warning(NULL, "warning", "由于外星人进攻地球，入住失败", QMessageBox::Cancel);
            }

            tThread->stop = false;
            ui ->stackedWidget ->setCurrentIndex(0);

        }
}



void Hotel::on_pushButton_clicked()      //已预定房间入住
{
    QString id;
    id = ui -> lineEdit_2->text();
    QString cfilename = "Temp/reserved/" + id  + ".txt";
    QFile file(cfilename);
    QTextStream stream(&file);
    if(file.exists() == true)             //预定信息一致
    {
        if (file.open(QIODevice::Text | QIODevice::ReadOnly))
        {

            ui->lineEdit_12->setText(stream.readLine().mid(7));
            ui->lineEdit_13->setText(stream.readLine().mid(8));          //ID
            ui->lineEdit_14->setText(stream.readLine().mid(13));          //CALLNUMBER
            stream.readLine();
            stream.readLine();
            ui->label_28->setText(stream.readLine().mid(10));            //放置房间号


            ui->label_48->show();
            ui->comboBox_2->setCurrentIndex(0);

            ui->comboBox_3->setCurrentIndex(0);
            ui->dateTimeEdit_2->setDateTime(currentTime.hotelTime_to_QDate());

            ui->spinBox_4->setValue(1);
            ui->spinBox_4->show();
            ui->spinBox_5->hide();
            ui ->stackedWidget_2->setCurrentIndex(3);

            extern room *roomNum[FLOOR+1][2][11];

            QString t = ui->label_28->text();
            int i = t.mid(0,1).toInt();
            int j = t.mid(1,1).toInt();
            int k = t.mid(2,1).toInt();
             room *chRoom = roomNum[i][j][k] -> right;
            int maxCheckTime = 1; //最长入住时长
            /*
            1 - 空；
            2 - 入住；
            3 - 已被预订
            (4 - 脏房...)
            */
            while(chRoom != NULL)
           {
                if(chRoom->getState() == 3)
                maxCheckTime++;
                else
                break;
                chRoom = chRoom ->right;
           }

            ui -> dateTimeEdit_2->setMinimumDateTime(currentTime.hotelTime_to_QDate());
            ui -> dateTimeEdit_2->setMaximumDateTime(currentTime.hotelTime_to_QDate().addDays( maxCheckTime/2));

            ui->dateTimeEdit_2->show();
            ui->label_55->show();
            ui->pushButton_6->show();    //下个月按钮
            ui->pushButton_5->show();    //上个月按钮

            ui ->stackedWidget_2->setCurrentIndex(3);
            file.close();
        }
    }
    else
        QMessageBox::warning(this,"warning","not exist",QMessageBox::Cancel);


}


void Hotel::on_reserve_clicked()
{

    QPushButton * digitalbutton = (QPushButton *) sender();
    QString t = digitalbutton->text();

    QString rintime[5], routtime[5];  //1年2月3日4时

    rintime[1] = ui->reserveStartYearLineEdit->text();
    rintime[2] = ui->reserveStartMonthLineEdit->text();
    rintime[3] = ui->reserveStartDayLineEdit->text();
    rintime[4] = ui->reserveStartHourLineEdit->text();

    routtime[1] = ui->reserveEndYearLineEdit->text();
    routtime[2] = ui->reserveEndMonthLineEdit->text();
    routtime[3] = ui->reserveEndDayLineEdit->text();
    routtime[4] = ui->reserveEndHourLineEdit->text();


    ui ->label_17->setText(t);
    ui ->label_22->setText(rintime[1]+ "/" + rintime[2]+ "/"+rintime[3]+"/"+rintime[4]);
    ui ->label_43->setText(routtime[1]+ "/" +routtime[2]+"/"+routtime[3]+"/"+routtime[4]);

    ui ->stackedWidget_2->setCurrentIndex(2);
}

void Hotel::on_pushButton_18_clicked()  //确定预定
{
    QString rnum = ui ->label_17->text();
    hotelTime chaoshi;

    client c;
    c.addName(ui->lineEdit_3->text());
    c.addiden(ui->lineEdit_5->text());
    c.addcall(ui->lineEdit_9->text());

    QString rintime[5], routtime[5];  //1年2月3日4时

    rintime[1] = ui->reserveStartYearLineEdit->text();
    rintime[2] = ui->reserveStartMonthLineEdit->text();
    rintime[3] = ui->reserveStartDayLineEdit->text();
    rintime[4] = ui->reserveStartHourLineEdit->text();

    routtime[1] = ui->reserveEndYearLineEdit->text();
    routtime[2] = ui->reserveEndMonthLineEdit->text();
    routtime[3] = ui->reserveEndDayLineEdit->text();
    routtime[4] = ui->reserveEndHourLineEdit->text();

    int ys = rintime[1].toInt();
    int ms = rintime[2].toInt();
    int ds = rintime[3].toInt();
    int hs = rintime[4].toInt();

    chaoshi.setHotelTime(ys,ms,ds,hs,0);
    chaoshi = chaoshi.addMin(4*60);

    int ye = routtime[1].toInt();
    int me = routtime[2].toInt();
    int de = routtime[3].toInt();
    int he = routtime[4].toInt();

    int s = period(ys, ms, ds, hs);
    int e = period(ye, me, de, he);

    int state1 ,state2;
    if(hs >= 12 && hs < 18) state1 = 1;
    else state1 =2;
    if(he >= 12 && he < 18) state2 = 1;
    else state2 =2;

    changeReserved(rnum,s,state1,e,state2, "01");    //更改预定表数组
    int end;
    if(e >= 6)  end = 6;
    else if(e < 6) end = e;
    if(s <= 6)
    transList(s,state1,end,state2,rnum.toInt(),13);    //更改链表

    saveRoom();            //保存房间信息到七天表之内;
    saveReserved();        //保存房间信息到60天预定表之内；

    QString fileName ="Temp/reserved/" + rnum + '-' + QString::number(chaoshi.date().year())
            +'-'+QString::number(chaoshi.getMonth()) +'-'+QString::number(chaoshi.getDay())+'-'+QString::number(chaoshi.getHour())+".txt";
    QFile fr(fileName);
    QTextStream stream(&fr);
    if (fr.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        stream << c.getIDnum()<<endl;
        stream << "***";
    }
    fr.close();

    saveReserved(c,ui ->label_22->text(),ui->label_43->text(), ui->label_17->text(),fileName);
    //保存客户订单 订单名为 房间号，客户ID;

    QMessageBox::information(NULL,"恭喜","预定成功",QMessageBox::Ok);
    tThread->stop = false;
    ui ->stackedWidget ->setCurrentIndex(0);

}

void Hotel::ontimeChanged(int i)             //时间改变将做的事情
{

    QDateTime p;
    currentTime.readFileTime();
    int s1 = currentTime.getTimeState();
    int m1 = currentTime.getMonth();

    QDate d1 = currentTime.date();
    int ratio = ui->comboBox->currentText().toInt();
    currentTime = currentTime.addMin(ratio);    //1s增加i min;

    int s2 = currentTime.getTimeState();
    int m2 = currentTime.getMonth();

    QDate d2 = currentTime.date();

    if (s1 != s2 )
    {
        timePass();
    }
    if(m1 != m2)
    {
        QMessageBox::information(this,"information","一个月过去了",QMessageBox::Ok);
        OurHotel.clearThisMonthMoney();
    }

        checkInTimeUp();
        reservedTimeUp();
        showRoomState();
        saveRoom();
        saveReserved();
        OurHotel.fileOutHotel();


    p = currentTime.hotelTime_to_QDate();

    currentTime.saveFileTime();
    ui->dateTimeEdit->setDateTime(p);
}

void Hotel::on_frontDeskButton_clicked()  //前台
{
    tThread ->stop = true;
    ui ->stackedWidget ->setCurrentIndex(1);
}

void Hotel::on_backDeskButton_clicked()   //后台
{
    tThread ->stop = true;
    ui->checkInNumLabel->setText(QString::number(OurHotel.getCheckInRoom()));

    int r  = ceil((double)OurHotel.getCheckInRoom()/ROOMNUM * 100);
    QString radiostring = QString::number(r)+"%";
    ui->radioLabel->setText(radiostring);

     ui ->stackedWidget ->setCurrentIndex(2);
}

void Hotel::on_systemButton_clicked()    //系统设置
{
     tThread ->stop = true;
     resignIn r;
     r.setWindowTitle("身份确认");
     if(r.exec ()==QDialog::Accepted)
     ui ->stackedWidget ->setCurrentIndex(3);

}

void Hotel::on_reserveButton_clicked()    //预订
{
     tThread ->stop = true;
     ui->reserveStartYearLineEdit->clear();
     ui->reserveStartMonthLineEdit->clear();
     ui->reserveStartDayLineEdit->clear();
     ui->reserveStartHourLineEdit->clear();
     ui->reserveEndYearLineEdit->clear();
     ui->reserveEndMonthLineEdit->clear();
     ui->reserveEndDayLineEdit->clear();
     ui->reserveEndHourLineEdit->clear();

     ui ->stackedWidget ->setCurrentIndex(1);
     ui ->stackedWidget_2 ->setCurrentIndex(0);
}

void Hotel::on_checkInButton_clicked()   //入住
{
    tThread ->stop = true;
    ui ->stackedWidget ->setCurrentIndex(1);
    ui ->stackedWidget_2 ->setCurrentIndex(6);
    ui->spinBox_5->setValue(0);
    ui->spinBox_5->hide();
    TodayStateEmpty();
}

void Hotel::on_checkOutButton_clicked()
{
        ui ->stackedWidget ->setCurrentIndex(1);
        ui ->stackedWidget_2 ->setCurrentIndex(4);

        ui ->label_4 -> setText("");
        ui -> label_6 -> setText("");
        ui -> label_87 -> setText("");
}





void Hotel:: showRoomState() //实时房态图展示房间状态
{
       extern room *roomNum[FLOOR+1][2][11];
       room *roomTemp;

       int day = 1;
       int duan = 1;
        day = ui ->spinBox->value();
        duan = ui ->spinBox_2->value();
       int  days = 2*(day - 1) + duan;

       QLabel *r[FLOOR+1][2][11][2];
        ui->label_74->setAutoFillBackground(true);     //可以拥有背景色
        ui->label_74->setPalette(Qt::gray);     //全部
        ui->label_74->setAlignment(Qt::AlignCenter);

        ui->label_75->setAutoFillBackground(true);
        ui->label_75->setPalette(Qt::cyan);     //空房
        ui->label_75->setAlignment(Qt::AlignCenter);

        ui->label_76->setAutoFillBackground(true);
        ui->label_76->setPalette(Qt::yellow);     //预订
        ui->label_76->setAlignment(Qt::AlignCenter);

        ui->label_77->setAutoFillBackground(true);
        ui->label_77->setPalette(Qt::red);     //住人
        ui->label_77->setAlignment(Qt::AlignCenter);

        int x[7] ={0} , y[7] ={0};

        int ijs[FLOOR+1] = {0,0,0,0,0,0,0};
        int ije[FLOOR+1] = {0,1,1,1,1,1,0};
        int jks[FLOOR+1] = {1,0};
        int ijke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};

        for (int i = 1; i <= FLOOR; i++)                 //初始化*roomNum[FLOOR+1][2][11]
        {
            for (int j = ijs[i]; j <= ije[i]; j++)
            {
                for (int k = jks[j]; k <= ijke[i][j]; k++)
                 {

                    QString t;
                    t.setNum(100*i + 10*j + k ,10);

                    if(roomNum[i][j][k] == NULL)
                     QMessageBox::warning(NULL,"warning","error",QMessageBox::Cancel);
                    else
                    {
                        roomTemp = roomNum[i][j][k];

                    for(int p = 1 ; p <= days; p++)
                      roomTemp = roomTemp ->right;

                    for(int h = 0 ; h <= 1; h++)
                   {
                        r[i][j][k][h] = new QLabel();

                        r[i][j][k][h]->setMaximumSize(30,40);
                        r[i][j][k][h]->setMinimumSize(30,40);
                        r[i][j][k][h] ->setText(t);
                        r[i][j][k][h]->setAlignment(Qt::AlignCenter);
                        r[i][j][k][h]->setAutoFillBackground(true);
                        if(roomTemp->getState() == 1)
                         r[i][j][k][h]->setPalette(Qt::cyan);     //空房
                        else if(roomTemp->getState() == 2)
                         r[i][j][k][h]->setPalette(Qt::red);      //入住
                        else if(roomTemp->getState() == 3)
                         r[i][j][k][h]->setPalette(Qt::yellow);     //预订
                        else
                         r[i][j][k][h]->setPalette(Qt::gray);     //其他

                    }

                    ui ->gridLayout_2 -> addWidget(r[i][j][k][0],i-1,10*j+k);      //全部房间

                    if (roomNum[i][j][k]->getStyle() == 2)
                    ui ->gridLayout_3 -> addWidget(r[i][j][k][1],x[2],y[2]++);      //豪华标间
                    if(y[2] == 10) x[2]++ , y[2] = 0;

                    if (roomNum[i][j][k]->getStyle() == 3)
                    ui ->gridLayout_4 -> addWidget(r[i][j][k][1],x[3],y[3]++);      //大床房
                    if(y[3] == 10) x[3]++, y[3] = 0;

                    if ( roomNum[i][j][k]->getStyle() == 4)
                    ui ->gridLayout_5 -> addWidget(r[i][j][k][1],x[4],y[4]++);      //双人房
                     if(y[4] == 10) x[4]++, y[4] = 0;

                    if (roomNum[i][j][k]->getStyle() == 5)
                    ui ->gridLayout_6 -> addWidget(r[i][j][k][1],x[5],y[5]++);      //豪华套房
                    if(y[5] == 10) x[5]++ , y[5] = 0;

                    if (roomNum[i][j][k]->getStyle() == 1)
                    ui ->gridLayout_7 -> addWidget(r[i][j][k][1],x[6],y[6]++);        //总统套房
                    if(y[6] == 10) x[6]++ , y[6] = 0;
                    }

                 }
            }
        }

 }

void Hotel::on_pushButton_7_clicked()  //实时房态图
{
    ui->checkInNumLabel->setText(QString::number(OurHotel.getCheckInRoom()));
    int r  = ceil((double)OurHotel.getCheckInRoom()/ROOMNUM * 100);

    QString radiostring = QString::number(r)+"%";
    ui->radioLabel->setText(radiostring);
    ui ->stackedWidget ->setCurrentIndex(2);
    ui ->stackedWidget_3 ->setCurrentIndex(0);
    showRoomState();
}



void Hotel::on_pushButton_9_clicked()        //房间平面图
{
    ui ->stackedWidget ->setCurrentIndex(2);
       ui ->stackedWidget_3 ->setCurrentIndex(2);
}

void Hotel::on_pushButton_11_clicked()     //修改用户名
{
    ui ->stackedWidget ->setCurrentIndex(3);
        ui ->stackedWidget_4 ->setCurrentIndex(0);
}

void Hotel::on_pushButton_12_clicked()   //修改密码
{
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();

    ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    ui->lineEdit_7->setEchoMode(QLineEdit::Password);
    ui->lineEdit_8->setEchoMode(QLineEdit::Password);

    ui ->stackedWidget ->setCurrentIndex(3);
    ui ->stackedWidget_4 ->setCurrentIndex(1);
}

void Hotel::on_pushButton_13_clicked()     //系统参数设置
{
    ui ->stackedWidget ->setCurrentIndex(3);
        ui ->stackedWidget_4 ->setCurrentIndex(2);
}



void Hotel::on_pushButton_20_clicked()         //预订确定2
{
    ui ->stackedWidget ->setCurrentIndex(1);
        ui ->stackedWidget_2 ->setCurrentIndex(3);
}

void Hotel::on_pushButton_34_clicked()         //退房确定1
{
     extern hotelTime currentTime;
    extern room *roomNum[FLOOR+1][2][11];
            QString r;//
            QString roomNumf;//
            QString sum;//
            QString rtype;//
            QString ctype;//
            QString intime;//
            QString Tlength;
            QString cost;//
            QString item[6];
            int u=7;
            int k;
            /*[SUMPEOPLE]:
             [NAME]:dsf
             [BIRTHDAY]:
             [SEX]:1
             [ID]:231154
             [LOCATION]:
             [CELLPHONE]:
             [STARTTIME]:2015/05/12/0
             [TYPE]:
        1. 总统套房  20000
        2.标间       500
        3.大床房     800
        4.双人房     1200
        5.套房       3000

    */
            r = ui -> lineEdit_23 -> text();
            roomNumf = "Temp/checkIn/"+r+".txt";
            QFile fileroom(roomNumf);//QString cfilename = "Temp/reserved/"+cnum+".txt";
            QTextStream stream(&fileroom);
            ui ->stackedWidget ->setCurrentIndex(1);

            if (fileroom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
            ui ->label_4 -> setText(r);
            sum=stream.readLine();
            ui -> label_61-> setText(sum.mid(12));//sum.mid(12)

            int i = r.mid(0,1).toInt();
            int j = r.mid(1,1).toInt();
            int k = r.mid(2,1).toInt();
            int style = roomNum[i][j][k]->getStyle();

            if(style==1)
            ui -> label_6 -> setText("总统套房");

            if(style==2)
            ui -> label_6 -> setText("标间");

            if(style==3)
            ui -> label_6 -> setText("大床");

            if(style==4)
            ui -> label_6 -> setText("双人");

            if(style==5)
            ui -> label_6 -> setText("套房");



            intime=stream.readLine();
            ui -> label_57 -> setText(intime.mid(12));
            ctype=stream.readLine();
            ctype=stream.readLine();
            QString cc=stream.readLine().mid(14);

            QString it=stream.readLine();
            item[1]=it.mid(9,2);
            item[2]=it.mid(14,2);
            item[3]=it.mid(19,2);
            item[4]=it.mid(24,2);
            item[5]=it.mid(29,2);



                ui->label_146->setText(item[1]);
                ui->label_147->setText(item[2]);
                ui->label_148->setText(item[3]);
                ui->label_149->setText(item[4]);
                ui->label_150->setText(item[5]);


            ui -> label_62 -> setText(ctype.mid(7));

            int y=intime.mid(12,4).toInt();
            int m=intime.mid(17,2).toInt();
            int d=intime.mid(20,2).toInt();
            int h=intime.mid(23,2).toInt();
            double t=period (y,m,d,h);
            t=-t+1;

            Tlength=QString::number((int)t, 10);
            ui -> label_87 -> setText(Tlength);

            double c;
            double sumitem=item[1].toInt()*3+item[2].toInt()*10+item[3].toInt()*5+item[4].toInt()*150+item[5].toInt()*220;
            if(style==1)
            c=20000;
            else if(style==2)
            c=500;
            else if(style==3)
            c=80;
            else if(style==4)
            c=1200;
            else
            c=3000;
            if(ctype=="[TYPE]:VIP")
            c=(c/5)*4;

             h=currentTime.getHour();
            if(h>12&&h<=18)
            t=t-0.5;
            c=c*t+cc.toDouble()+sumitem;
            cost=QString::number((int)c, 10);
            ui -> label_63 -> setText(cost);
            ui ->stackedWidget_2 ->setCurrentIndex(5);

            }
            else
           {
            QMessageBox::warning(this,"warning","this room is not ...",QMessageBox::Yes);
            ui ->stackedWidget_2 ->setCurrentIndex(4);
            ui -> lineEdit_23-> setText("");
           }

}



void Hotel::on_pushButton_14_clicked()             //修改用户名
{
    QFile file("Temp/User.txt");
        QString password;
        QTextStream stream(&file);
        if (file.open(QIODevice::ReadWrite))
        {
            stream.readLine();
            password = stream.readLine();
            file.close();
        }

        if (file.open(QIODevice::Text|QIODevice::WriteOnly))
        {
            QString line;
            line =  (ui ->lineEdit ->text());
            line = getXorEncryptDecrypt(line,11);
            stream << line << endl;
            stream << password;

            file.close();
        }
        QMessageBox::information(NULL, "information","修改成功",QMessageBox::Yes);
        ui->lineEdit->clear();

}

void Hotel::on_pushButton_25_clicked()        //修改密码
{
        ui->lineEdit_6->setEchoMode(QLineEdit::Password);
        ui->lineEdit_7->setEchoMode(QLineEdit::Password);
        ui->lineEdit_8->setEchoMode(QLineEdit::Password);

        QFile file("Temp/User.txt");
        QString password , account;
        QTextStream stream(&file);
        QString oldPassword, newPassword,rePassword;
        if (file.open(QIODevice::Text|QIODevice::ReadWrite))
        {
            account = stream.readLine();
            account = getXorEncryptDecrypt(account,11);
            oldPassword =  stream.readLine();
            oldPassword = getXorEncryptDecrypt(oldPassword,11);
            file.close();
        }
        password = ui ->lineEdit_6->text();
        if(oldPassword != password)
        {
            QMessageBox::warning(NULL,"warning","old password error",
                                 QMessageBox::Cancel,QMessageBox::Cancel );
            ui->lineEdit_6->clear();
            ui->lineEdit_6->setFocus();
        }
        else
        {
            newPassword = ui ->lineEdit_7->text();

            rePassword = ui ->lineEdit_8->text();
            if(newPassword != rePassword)
            {
                QMessageBox::warning(NULL,"warning","There are difference between "
                                                    "your two inputs",
                                     QMessageBox::Cancel,QMessageBox::Cancel );
                ui->lineEdit_7->clear();
                ui->lineEdit_7->setFocus();
                ui->lineEdit_8->clear();
                ui->lineEdit_8->setFocus();
            }
            else
            {
                if (file.open(QIODevice::Text|QIODevice::WriteOnly))
                {
                    account = getXorEncryptDecrypt(account,11);
                    stream << account << endl;

                    newPassword = getXorEncryptDecrypt(newPassword,11);
                    stream  << newPassword;
                    file.close();

                QMessageBox::information(NULL,"information","修改成功",QMessageBox::Yes,
                                         QMessageBox::Yes);

                }
            }

        }
}




void Hotel::on_pushButton_10_clicked()        //转到主界面
{

    tThread ->stop = false;
    ui ->stackedWidget ->setCurrentIndex(0);
}

void Hotel::on_pushButton_8_clicked()      //客户信息管理
{
    QString file0 = "Temp/client/index.txt";
        QFile file(file0);
        QTextStream stream(&file);
        client *current=NULL;
        current = new client[1];
        head = current;
        current->next=NULL;

        int row = 1;
        int column = 0;

        QStringList listHead;
        listHead << "Name" <<"Sex" <<"Birthday" <<"Location"<<"IDNum " <<
              " callNum "<<" Frequency"   <<"Cost" ;
        ui -> tableWidget ->setHorizontalHeaderLabels(listHead);
        ui ->tableWidget ->setColumnCount(8);

         if (file.open(QIODevice::Text | QIODevice::ReadOnly))
           {
             while (stream.atEnd() != 1 )
             {
                 clientRoomInfo cr;
                 QString id;
                 id = stream.readLine();
                 current->next = new client[1];
                 current=current->next;
                 current->next=NULL;
                 current->addiden(id);

                 QString file1 = "Temp/client/"+current->getIDnum()+".txt";
                 QFile cfile(file1);
                 if (cfile.open(QIODevice::Text | QIODevice::ReadOnly))
                 {
                     QTextStream stream1(&cfile);

                     QString name, birthday, loc, sex;
                     name = stream1.readLine();
                     sex = stream1.readLine();
                     birthday = stream1.readLine();
                     loc = stream1.readLine();
                     current->addNamebirthloc(name,birthday,loc);
                     if(sex=="男")
                         current->addsex(1);
                     else if(sex=="女")
                         current->addsex(2);
                     current->addiden(stream1.readLine());
                     current->addcall(stream1.readLine());
                     cr.frequence  = (stream1.readLine()).toInt();
                     for (int i = 1; i <= 5; i++)
                     {
                         stream1.readLine();//------绫诲瀷i------
                         cr.roomSt[i] = (stream1.readLine()).toInt();
                         cr.time[i]   = (stream1.readLine()).toInt();
                         cr.money[i]  = (stream1.readLine()).toInt();
                     }
                     stream1.readLine();//---------------
                     cr.sum = (stream1.readLine()).toInt();
                     current->addinfo(cr);

                     ui ->tableWidget ->setRowCount(row);

                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(name));
                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(sex));
                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(birthday));
                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(loc));
                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(current->getIDnum()));
                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(current->getcall()));
                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(current->getinfo().frequence)));
                     ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(current->getinfo().sum)));
                     row++;
                     column = 0;
                 }
                 cfile.close();
             }

             file.close();
           }

        ui ->stackedWidget ->setCurrentIndex(2);
        ui ->stackedWidget_3 ->setCurrentIndex(1);


}

void Hotel::on_pushButton_26_clicked()          //展示房间状态
{
     showRoomState();
}

void Hotel::on_pushButton_27_clicked()           //tThreadStart
{
    //currentTime
    tThread->start();
}

void Hotel::on_pushButton_36_clicked()              //确定退房
{
    QString roomNum = ui->label_4->text();
    QFile f("Temp/checkIn/" + roomNum +".txt");
    QTextStream stream(&f);
    int flag = 0;
    if (f.open(QIODevice::Text|QIODevice::ReadOnly ))
    {
        int stateEnd,r;
        int e;
        QString endtime;
        r = ui->label_4->text().toInt();
        for (int i=1;i<=3;i++)
        endtime = stream.readLine();

        int y = endtime.mid(10,4).toInt();
        int m = endtime.mid(15,2).toInt();
        int d = endtime.mid(18,2).toInt();
        int h = endtime.mid(21,2).toInt();
        if(h >= 12 && h < 18)stateEnd= 1;
        else stateEnd = 2;

        int t = period(y,m,d,h);

        if(transList(0,currentTime.getTimeState(),t,stateEnd,r,21) == true &&
                changeReserved(roomNum,0,currentTime.getTimeState(),t,stateEnd,"20")== true)
         {
            saveReserved();
            flag = 1;
            saveRoom();
         }

    }
    f.close();

    if(flag == 1)
    {
        f.remove("Temp/checkIn/"+ roomNum +".txt");
        showRoomState();

        OurHotel.cutCheckInRoom_changeRadio(1);
        OurHotel.addSum_thisMon_Money(ui->label_63->text().toInt());

        OurHotel.cutNowPeople(ui->label_61->text().toInt());
        OurHotel.fileOutHotel();
        QMessageBox::information(this,"恭喜","退房成功",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this,"sorry","由于外星人进攻地球，退房失败",QMessageBox::Cancel);
    }

    tThread->stop = false;
    ui ->stackedWidget ->setCurrentIndex(0);
}

void Hotel::on_pushButton_30_clicked()             //pause
{
    tThread ->stop = !(tThread->stop) ;
}


void Hotel::on_pushButton_31_clicked()                //时间参数设置
{
    ui ->stackedWidget ->setCurrentIndex(3);
        ui ->stackedWidget_4 ->setCurrentIndex(2);
}


void Hotel::on_spinBox_3_valueChanged(int arg1)       //房间平面图变换
{
    ui ->stackedWidget ->setCurrentIndex(2);
    ui ->Floor ->setCurrentIndex(arg1-1);
}



void Hotel::on_reserveConfirmButton_clicked()  //输入时间后判断是否能预定
{
    QString rintime[5], routtime[5];  //1年2月3日4时

    rintime[1] = ui->reserveStartYearLineEdit->text();
    rintime[2] = ui->reserveStartMonthLineEdit->text();
    rintime[3] = ui->reserveStartDayLineEdit->text();
    rintime[4] = ui->reserveStartHourLineEdit->text();

    routtime[1] = ui->reserveEndYearLineEdit->text();
    routtime[2] = ui->reserveEndMonthLineEdit->text();
    routtime[3] = ui->reserveEndDayLineEdit->text();
    routtime[4] = ui->reserveEndHourLineEdit->text();


    int ys = rintime[1].toInt();
    int ms = rintime[2].toInt();
    int ds = rintime[3].toInt();
    int hs = rintime[4].toInt();

    int ye = routtime[1].toInt();
    int me = routtime[2].toInt();
    int de = routtime[3].toInt();
    int he = routtime[4].toInt();

    int s = period(ys, ms, ds, hs);
    int e = period(ye, me, de, he);

    int state1 ,state2;
    if(hs >= 12 && hs <= 18) state1 = 1;
    else   state1 = 2;

    if(he >= 12 && he <= 18) state2 = 1;
    else   state2 = 2;

    if(judgeReserved(s,state1,e,state2) == false )
    {
        QMessageBox::warning(NULL,"error","输入的时间有误",QMessageBox::Cancel);
        ui->reserveStartYearLineEdit->clear();
        ui->reserveEndDayLineEdit->clear();
        ui->reserveEndMonthLineEdit->clear();
        ui->reserveEndYearLineEdit->clear();
        ui->reserveEndHourLineEdit->clear();
        ui->reserveStartMonthLineEdit->clear();
        ui->reserveStartDayLineEdit->clear();
        ui->reserveStartHourLineEdit->clear();
    }
    else
    {
        QFile reserfir("Temp/instant.txt");
        reserfir.open(QIODevice::Text | QIODevice::WriteOnly);
        QTextStream in(&reserfir);
        if (ms >= 10 && ds >= 10)
            in << rintime[1] << rintime[2] << rintime[3] << rintime[4] << endl;
        else if (ms >= 10 && ds < 10)
            in << rintime[1] << rintime[2] << '0' << rintime[3] << rintime[4] << endl;
        else if (ms <10 && ds >= 10)
            in << rintime[1] << '0' << rintime[2] << rintime[3] << rintime[4] << endl;
        else
            in << rintime[1] << '0' << rintime[2] << '0' << rintime[3] << rintime[4] << endl;

        if (me >= 10 && de >= 10)
            in << routtime[1] << routtime[2] << routtime[3] << routtime[4] << endl;
        else if (me >= 10 && de<10)
            in << routtime[1] << routtime[2] << '0' << routtime[3] << routtime[4] << endl;
        else if (me < 10 && de >= 10)
            in << routtime[1] << '0' << routtime[2] << routtime[3] << routtime[4] << endl;
        else
            in << routtime[1] << '0' << routtime[2] << '0' << routtime[3] << routtime[4] << endl;

        ui->stackedWidget_2->setCurrentIndex(1);
        reserfir.close();
        RIoptical();
    }


}

void Hotel::RIoptical()            //将可预订房间pushButton添加
{
  extern room *roomNum[FLOOR+1][2][11];
  QFile file("Temp/roomCanReserve.txt");
  QTextStream stream(&file);

   int a, b, c, d;
  // QPushButton  *r[FLOOR+1][2][11];

  int x[7] ={0} , y[7] ={0};

  if (file.open(QIODevice::Text | QIODevice::ReadOnly))
  {
      QString roomNumber ;
      roomNumber = stream.readLine();
      while (roomNumber != "***")
      {
          a = roomNumber.toInt();
          b = a / 100;
          c = a / 10 % 10;
          d = a % 10;
          if (roomNum[b][c][d]->getStyle() == 2 )
          ui ->reserveLayout_2 -> addWidget(r[b][c][d],x[2],y[2]++);      //豪华标间
          if(y[2] == 10) x[2]++ , y[2] = 0;

          if (roomNum[b][c][d]->getStyle() == 3)
          ui ->reserveLayout_3 -> addWidget(r[b][c][d],x[3],y[3]++);      //大床房
          if(y[3] == 10) x[3]++, y[3] = 0;

          if ( roomNum[b][c][d]->getStyle() == 4)
          ui ->reserveLayout_4 ->addWidget(r[b][c][d],x[4],y[4]++);      //双人房
           if(y[4] == 10) x[4]++, y[4] = 0;

          if (roomNum[b][c][d]->getStyle() == 5)
          ui ->reserveLayout_5 ->addWidget(r[b][c][d],x[5],y[5]++);      //豪华套房
          if(y[5] == 10) x[5]++ , y[5] = 0;

          if (roomNum[b][c][d]->getStyle() == 1)
          ui ->reserveLayout_1-> addWidget(r[b][c][d],x[1],y[1]++);        //总统套房
          if(y[6] == 10) x[1]++ , y[1] = 0;
         roomNumber = stream.readLine();

       }

  }
  file.close();

}
void Hotel ::TodayStateEmpty()              //今日空闲房间
{
    extern room *roomNum[FLOOR+1][2][11];
    room *roomTemp;

    int x[7] ={0} , y[7] ={0};

    int ijs[FLOOR+1] = {0,0,0,0,0,0,0};
    int ije[FLOOR+1] = {0,1,1,1,1,1,0};
    int jks[FLOOR+1] = {1,0};
    int ijke[FLOOR+1][2]={0,0,9,0,9,0,9,0,9,0,9,0,2,0};

    for (int i = 1; i <= FLOOR; i++)                 //初始化*roomNum[FLOOR+1][2][11]
    {
        for (int j = ijs[i]; j <= ije[i]; j++)
        {
            for (int k = jks[j]; k <= ijke[i][j]; k++)
             {

                QString t;
                t.setNum(100*i + 10*j + k ,10);

                if(roomNum[i][j][k] == NULL)
                 QMessageBox::warning(NULL,"warning","error",QMessageBox::Cancel);
                else
                {
                    roomTemp = roomNum[i][j][k];
                    roomTemp = roomTemp ->right;
              if(roomTemp->getState() == 1) //The room is empty
              {

                  if (roomNum[i][j][k]->getStyle() == 2)
                  ui ->reserveLayout_11 -> addWidget(cr[i][j][k],x[2],y[2]++);      //豪华标间
                  if(y[2] == 10) x[2]++ , y[2] = 0;

                  if (roomNum[i][j][k]->getStyle() == 3)
                  ui ->reserveLayout_12 -> addWidget(cr[i][j][k],x[3],y[3]++);      //大床房
                  if(y[3] == 10) x[3]++, y[3] = 0;

                  if ( roomNum[i][j][k]->getStyle() == 4)
                  ui ->reserveLayout_13 ->addWidget(cr[i][j][k],x[4],y[4]++);      //双人房
                   if(y[4] == 10) x[4]++, y[4] = 0;

                  if (roomNum[i][j][k]->getStyle() == 5)
                  ui ->reserveLayout_14 ->addWidget(cr[i][j][k],x[5],y[5]++);      //豪华套房
                  if(y[5] == 10) x[5]++ , y[5] = 0;

                  if (roomNum[i][j][k]->getStyle() == 1)
                  ui ->reserveLayout_15-> addWidget(cr[i][j][k],x[1],y[1]++);        //总统套房
                  if(y[6] == 10) x[1]++ , y[1] = 0;
               }

               else if(roomTemp->getState() == 3) //The room is reserved
              {
                  ui->gridLayout->addWidget(cr[i][j][k]);
               }

             }
           }
         }
      }
}



void Hotel::on_pushButton_4_clicked(bool checked)      //按某种方式查找客户信息
{
        int n, row=1, column=0;
        QString s, sex;
        client *c;
        QStringList listHead;
        listHead << "Name" <<"Sex" <<"Birthday" <<"Location"<<"IDNum " <<
              " callNum "<<" Frequency"   <<"Cost" ;
        ui -> tableWidget ->setHorizontalHeaderLabels(listHead);
        ui ->tableWidget ->setColumnCount(8);

        n = ui->comboBox_5->currentIndex();
        s = ui->lineEdit_15->text();
        c = head->next;

        ui->tableWidget->clear();

        while(c != NULL)
        {
            if(c->getsex()==1)
                sex="男";
            else if(c->getsex()==2)
                sex="女";
            if(n==0)
            {
                if(s==c->getname() || ui->lineEdit_15->text().isEmpty())
                {
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getname()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(sex));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getbirth()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getlocation()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getIDnum()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getcall()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(c->getinfo().frequence)));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(c->getinfo().sum)));
                    row++;
                    column = 0;
                }
            }
            else if(n==1)
            {
                if(s==c->getIDnum() || ui->lineEdit_15->text().isEmpty())
                {
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getname()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(sex));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getbirth()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getlocation()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getIDnum()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getcall()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(c->getinfo().frequence)));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(c->getinfo().sum)));
                    row++;
                    column = 0;
                }
            }
            else if(n==2)
            {
                if(s==c->getcall() || ui->lineEdit_15->text().isEmpty())
                {
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getname()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(sex));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getbirth()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getlocation()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getIDnum()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(c->getcall()));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(c->getinfo().frequence)));
                    ui ->tableWidget ->setItem(row-1 , column++ ,new QTableWidgetItem(QString::number(c->getinfo().sum)));
                    row++;
                    column = 0;
                }
            }

            c=c->next;
        }
}



void Hotel::on_pushButton_37_clicked()         //退房返回主界面
{
    tThread->stop = false;
    ui ->stackedWidget ->setCurrentIndex(0);

}

void Hotel::on_pushButton_3_clicked() //按房号查找正在入住 客户信息
{
    QString file0="Temp/checkIn/"+ui->lineEdit_4->text()+".txt";
    QFile file(file0);

    if(file.exists())
    {
        if (file.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            ui->textBrowser->setText(stream.readAll());
        }
        else
            ui->textBrowser->setText("未找到房间信息T_T");
    }
    else
    {
        ui->textBrowser->setText("未找到房间信息T_T");
    }

}

void Hotel::on_pushButton_16_clicked()        //恢复设置
{
   QMessageBox::StandardButton rb =
           QMessageBox::warning(this,"warning", "您确定要恢复设置吗？"
            "（恢复后您现有保存的所有数据将消失）",QMessageBox::Ok|QMessageBox::Cancel ,
                                QMessageBox::Cancel);

   if(rb == QMessageBox::Cancel)
   {
        QMessageBox::information(this,"information","已取消",QMessageBox::Ok);

        QMessageBox message(QMessageBox::NoIcon, "information", "已取消");

        message.setIconPixmap(QPixmap("icon.png"));
        message.exec();

   }
   else
   {

    QDir d("Temp");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);

    d.setPath("Temp/client");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);

    d.setPath("Temp/checkIn");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);

    d.setPath("Temp/checkOut");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);

    d.setPath("Temp/reserved");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);

    d.setPath("Temp/reserved/id-order");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);


    d.setPath("Temp/Reserved_60");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);

    d.setPath("Temp/Day1-14");
    d.setFilter(QDir::Files);
    for (int i=0; i < (int)d.count(); i++)
        d.remove(d[i]);

    OurHotel.clear();

    OurHotel.fileOutHotel();
    establish();
    establish_2();

    fRoomIn();                         //从 room.txt 写入房间信息 到roomNum[i][j][k]
    foundReserved();               //从roomReserved_60写入可预订信息

    foundlist_0();                      //建立十字链表
    foundList_1() ;                     //建立空、满、预订链表

    showRoomState();
    QMessageBox::information(this,"恭喜","恢复成功",QMessageBox::Ok);
   }
}

void Hotel::on_pushButton_17_clicked()               //版权声明
{

    QMessageBox::about(this,tr("作者信息以及版权声明"),
     tr("<h2>酒店管理系统 3.3.4.2</h2>""<p>Copyright © 2015 梁杰，李正清，赵泊宁"
        "All rights reserved.""<p>酒店管理系统由2504工作室独立开发完成，"
        "对于其它用户在未经作者允许的情况下不得作为商业用途。"
        "<p><h3>软件作者: 梁杰，李正清，赵泊宁<br>邮箱:944033912@qq.com</h3><p>"
        " <p><h6>   梁杰 李正清，赵泊宁 2015年6月"));


}

void Hotel::on_pushButton_33_clicked()            //换房输入房间号确定
{
        extern hotelTime currentTime;
        extern room *roomNum[FLOOR+1][2][11];
        QString rf;
        QString rnb;//
        QString rnaf;
        QString rtype;
        QString psum;
        QString ctype;
        QString intimebe;
        QString intimeaf;
        QString costnow;
        QString endtime;
        QString cost;
        QString it;

        double c;
        double cn;

        rnb = ui -> lineEdit_24 -> text();
        rnaf = ui -> lineEdit_25 -> text();
        rf="Temp/checkIn/"+rnb+".txt";
        QFile fileroom(rf);
        QTextStream stream(&fileroom);
        if (fileroom.open(QIODevice::ReadOnly | QIODevice::Text))
       {
        psum=stream.readLine();
        intimebe=stream.readLine();
        endtime=stream.readLine();
        ctype=stream.readLine();
        costnow=stream.readLine();
        it=stream.readLine();

        ui ->label_95 -> setText(rnb);
        ui ->label_102 -> setText(rnaf);
        ui ->label_99 -> setText(psum.mid(12));
        ui ->label_104 -> setText(psum.mid(12));
        ui ->label_105 -> setText(ctype.mid(7));
        ui ->label_108 -> setText(ctype.mid(7));
        ui ->label_101 -> setText(intimebe.mid(12));
        ui ->label_107 -> setText(endtime.mid(10));
        ui->label_151->setText(it);
        cost=costnow.mid(14);
        cn=cost.toInt();
        int i = rnb.mid(0,1).toInt();
        int j = rnb.mid(1,1).toInt();
        int k = rnb.mid(2,1).toInt();
        int style = roomNum[i][j][k]->getStyle();

        if(style==1)
        ui -> label_98 -> setText("总统套房");

        if(style==2)
        ui -> label_98-> setText("标间");

        if(style==3)
        ui -> label_98-> setText("大床");

        if(style==4)
        ui -> label_98-> setText("双人");

        if(style==5)
        ui -> label_98-> setText("套房");

        int x = rnaf.mid(0,1).toInt();
        int o = rnaf.mid(1,1).toInt();
        int z = rnaf.mid(2,1).toInt();
        int stylen = roomNum[x][o][z]->getStyle();

         if(stylen==1)
         ui -> label_103 -> setText("总统套房");

         if(stylen==2)
         ui -> label_103 -> setText("标间");

         if(stylen==3)
         ui -> label_103-> setText("大床");

         if(stylen==4)
         ui -> label_103 -> setText("双人");

         if(stylen==5)
         ui -> label_103-> setText("套房");

         int y=intimebe.mid(12,4).toInt();
         int m=intimebe.mid(17,2).toInt();
         int d=intimebe.mid(20,2).toInt();
         int h=intimebe.mid(23,2).toInt();
         double t=period (y,m,d,h);
         t=-t;
         if(style==1)
         c=20000;
         else if(style==2)
         c=500;
         else if(style==3)
         c=800;
         else if(style==4)
         c=1200;
         else
         c=3000;
         if(ctype=="[TYPE]:VIP")
         c=(c/5)*4;

         h=currentTime.getHour();

             if(h>=12&&h<18)
                 t=t+0.5;
             else
                 t=t+1;


         c=c*t+cn;
         cost=QString::number((int)c, 10);
         ui ->label_100 -> setText(cost);
         y=currentTime.getYear();
         d=currentTime.getMonth();
         m=currentTime.getDay();

         QString year=QString::number(y,10);
         QString month;
         QString day;
         QString hour;
         if(m<10)
         month="0"+QString::number(m,10);
         else
         month=QString::number(m,10);
         if(d<10)
         day="0"+QString::number(d,10);
         else
         day=QString::number(d,10);
         if(h<10)
         hour="0"+QString::number(h,10);
         else
         hour=QString::number(h,10);
         intimeaf=year+"/"+month+"/"+day+"/"+hour;
         ui ->label_106 -> setText(intimeaf);
          ui ->stackedWidget_2 ->setCurrentIndex(9);
        }
        else
        {
         QMessageBox::warning(this,"warning","this room is not avaliable",QMessageBox::Yes);
         ui ->stackedWidget_2 ->setCurrentIndex(8);
         ui -> lineEdit_24-> setText("");
         ui -> lineEdit_25-> setText("");
        }
}

void Hotel::on_pushButton_32_clicked()       //换房取消
{
    tThread->stop = false;
    ui ->stackedWidget ->setCurrentIndex(0);
    ui ->lineEdit_24 -> setText("");
    ui ->lineEdit_25 -> setText("");
}

void Hotel::on_pushButton_42_clicked()       //换房显示房间信息确定
{
    QString rnb = ui->label_95->text();
        QString rnaf = ui->label_102->text();
        QString copy;
        QFile fb("Temp/checkIn/" + rnb +".txt");
        QFile faf("Temp/checkIn/" + rnaf +".txt");
        QTextStream streamb(&fb);
        QTextStream streamaf(&faf);
        if (fb.open(QIODevice::Text|QIODevice::ReadOnly ))
        {
            for (int i=1;i<=6;i++)
            streamb.readLine();
            if (faf.open(QIODevice::Text|QIODevice::WriteOnly ))
            {
                streamaf<<"[PEOPLENUM]:"<<ui->label_104->text()<<endl;
                streamaf<<"[STARTTIME]:"<<ui->label_106->text()<<endl;
                streamaf<<"[ENDTIME]:"<<ui->label_107->text()<<endl;
                streamaf<<"[TYPE]:"<<ui->label_105->text()<<endl;
                streamaf<<"[CURRENTCOST]:"<<ui->label_100->text()<<endl;
                streamaf<<ui->label_151->text()<<endl;
                int stateEnd,r;
                int e;
                QString endtime;
                int rafn = ui->label_102->text().toInt();
                int rbn = ui->label_95->text().toInt();
                endtime =ui->label_107->text();

                int y = endtime.mid(0,4).toInt();
                int m = endtime.mid(5,2).toInt();
                int d = endtime.mid(8,2).toInt();
                int h = endtime.mid(11,2).toInt();
                if(h >= 12 && h < 18)stateEnd= 1;
                else stateEnd = 2;
                int t = period(y,m,d,h);
                transList(0,currentTime.getTimeState(),t,stateEnd,rafn,12);
                transList(0,currentTime.getTimeState(),t,stateEnd,rbn,21);
                saveRoom();

                if(changeReserved(rnb,0,currentTime.getTimeState(),t,stateEnd,"20")== true)
                {
                    if(changeReserved(rnaf,0,currentTime.getTimeState(),t,stateEnd,"02")== true)
                        saveReserved();
                }

            }
            while(!streamb.atEnd())
            {
            copy=streamb.readLine();
            streamaf<<copy<<endl;
            }
        }
        fb.close();
        faf.close();
        fb.remove("Temp/checkIn/"+ rnb +".txt");
        showRoomState();
        QMessageBox::information(this,"恭喜","换房成功",QMessageBox::Ok);
        tThread->stop = false;
        ui ->stackedWidget ->setCurrentIndex(0);
}

void Hotel::on_pushButton_39_clicked()  //换房显示房间信息取消
{
    tThread->stop = false;
    ui ->stackedWidget ->setCurrentIndex(0);
}



void Hotel::on_pushButton_28_clicked()    //显示换房页面
{
    tThread->stop = true;
    ui ->lineEdit_24 -> setText("");
    ui ->lineEdit_25 -> setText("");

    ui ->stackedWidget ->setCurrentIndex(1);
    ui ->stackedWidget_2 ->setCurrentIndex(8);

}

void Hotel::on_pushButton_40_clicked()   //续住输入房间号点击确定
{
        extern hotelTime currentTime;
        extern room *roomNum[FLOOR+1][2][11];
        QString rNum=ui -> lineEdit_26->text();
        QString rf= "Temp/checkIn/"+rNum+".txt";
        QString intime;
        QString endtime;
        QString rtype;
        QString ctype;
        QString sum;
        QString costnow;
        QString it;
        QFile fileroom(rf);
        QTextStream stream(&fileroom);
        ui ->stackedWidget ->setCurrentIndex(1);
        if (fileroom.open(QIODevice::ReadOnly | QIODevice::Text))
        {
             sum=stream.readLine();
             intime=stream.readLine();
             endtime=stream.readLine();
             ctype=stream.readLine();
             costnow=stream.readLine();
             it=stream.readLine();
             ui->label_151->setText(it);
            ui ->label_132 -> setText(rNum);    //房间号
            ui->label_138->setText(endtime.mid(10)); //原截止时间
            int i = rNum.mid(0,1).toInt();
            int j = rNum.mid(1,1).toInt();
            int k = rNum.mid(2,1).toInt();
            int style = roomNum[i][j][k]->getStyle();
            room *proroom=roomNum[i][j][k]->right;

            if(style==1)
            ui -> label_133 -> setText("总统套房");
            if(style==2)
            ui -> label_133-> setText("标间");
            if(style==3)
            ui -> label_133-> setText("大床");
            if(style==4)
            ui -> label_133 -> setText("双人");
            if(style==5)
            ui -> label_133-> setText("套房");

            ui ->label_134 -> setText(sum.mid(12));       //入住人数
            ui ->label_136 -> setText(intime.mid(12));    //入住时间
            ui ->label_137 -> setText(ctype.mid(7));      //收费类型

            int y=intime.mid(12,4).toInt();
            int m=intime.mid(17,2).toInt();
            int d=intime.mid(20,2).toInt();
            int h=intime.mid(23,2).toInt();
            double t=period (y,m,d,h);
             t=-t;
             QString cost=costnow.mid(14);
             double cn=cost.toInt();
             double c;
             if(style==1)
             c=20000;
             else if(style==2)
             c=500;
             else if(style==3)
             c=800;
             else if(style==4)
             c=1200;
             else
             c=3000;
             if(ctype=="[TYPE]:VIP")
             c=(c/5)*4;

             int hj=currentTime.getHour();
             if(hj>=12&&hj<18)//判断时段
                 t=t+0.5;//时段1的收费
             else
                 t=t+1;//时段二的收费
             c=c*t+cn;

             cost=QString::number((int)c, 10);
             ui ->label_135 -> setText(cost);      //已消费
             QString END=endtime.mid(10)+" 00:00";
             ui->dateTimeEdit_3->setDateTime(QDateTime::fromString(END, "yyyy/MM/dd/hh mm:ss"));


             int max = 0;
             while(proroom != NULL)
            {
             if(proroom->getState() == 1)
             max++;
             proroom = proroom ->right;
            }
             ui->dateTimeEdit_3->setMinimumDateTime(QDateTime::fromString(END, "yyyy/MM/dd/hh mm:ss"));
             ui->dateTimeEdit_3->setMaximumDateTime(QDateTime::fromString(END, "yyyy/MM/dd/hh mm:ss").addDays(max/2));
             ui ->stackedWidget_2 ->setCurrentIndex(11);
        }
        else
        {
         ui -> lineEdit_26-> setText("");         //续住房间号
         QMessageBox::warning(this,"warning","this room is not avaliable",QMessageBox::Yes);
         ui ->stackedWidget_2 ->setCurrentIndex(10);
        }
}


void Hotel::on_pushButton_38_clicked()
{

}

void Hotel::on_pushButton_43_clicked()          //酒店情况
{
    int r  = ceil((double)OurHotel.getCheckInRoom()/ROOMNUM * 100);
    QString radiostring = QString::number(r)+"%";

    ui->label_116->setText(radiostring);         //入住率
    ui->label_117->setText(QString::number(OurHotel.getThisMonthMoney()));         //本月收入
    ui->label_118->setText(QString::number(OurHotel.getsumMoney()));         //历史总收入
    ui->label_119->setText(QString::number(OurHotel.getnowPeople()));         //当前入住人数
    ui->label_121->setText(QString::number(OurHotel.getCheckInRoom()));           //已入住房间数
    ui->label_123->setText(QString::number(ROOMNUM-OurHotel.getCheckInRoom()));           //未入住房间数

    ui->stackedWidget_3->setCurrentIndex(3);
}

void Hotel::on_pushButton_46_clicked()
{
        QString rNum=ui -> lineEdit_26->text();
        int num= rNum.toInt();
        QString rf= "Temp/checkIn/"+rNum+".txt";
        QFile f(rf);
        QFile ft("Temp/checkIn/"+rNum+"x"+".txt");
        QTextStream stream(&f);
        QTextStream streamt(&ft);
        QString intime=ui ->label_136 ->text();     //入住时间
        QString ctype=ui ->label_137 ->text();      //收费类型
        QString sum=ui ->label_134 ->text();        //入住人数
        QString costnow="0";
        QString endtimeb=ui ->label_138 ->text();   //原截止时间
        QString it=ui->label_151->text();
        int ey,em,ed,eh,t;
        /*if (f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        if(ft.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            for(int u=1;u<=2;u++)
            {
            endtimeb=stream.readLine();
            streamt<<endtimeb<<endl;
            }
            endtimeb=stream.readLine();
        }
        }
        f.close();
        ft.close();*/
        QDateTime et = ui->dateTimeEdit_3->dateTime();
        hotelTime et3 ;
        et3.QDate_to_hotelTime(et);
        int y = et.date().year();
        int m = et.date().month();
        int d = et.date().day();
        int h = et.time().hour();
        int x=period(y,m,d,h);
        if(h>=12&&h<18)
            h=1;
        else
            h=2;
        QString year=QString::number(y,10);
        QString month;
        QString day;
        QString hour;
        if(m<10)
        month="0"+QString::number(m,10);
        else
        month=QString::number(m,10);
        if(d<10)
        day="0"+QString::number(d,10);
        else
        day=QString::number(d,10);
        if(h<10)
        hour="0"+QString::number(h,10);
        QString endtime=year+"/"+month+"/"+day+"/"+hour;
        ey = endtimeb.mid(0,4).toInt();
        em = endtimeb.mid(5,2).toInt();
        ed = endtimeb.mid(8,2).toInt();
        eh = endtimeb.mid(11,2).toInt();
        t=period(ey,em,ed,eh);
          if(eh>=12&&eh<18)
              eh=1;
          else
              eh=2;

          if(eh==2)
          t++;
          eh=3-eh;
          if(transList(t,eh,x,h,num,12) == true)
          {

              showRoomState();
              QMessageBox::information(this,"恭喜","改住成功",QMessageBox::Ok);
              tThread->stop = false;
          }
          else
              QMessageBox::warning(this,"sorry","由于外星人进攻地球，改住失败",QMessageBox::Cancel);

         if (f.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             if(ft.open(QIODevice::WriteOnly | QIODevice::Text))
              {
              int o=1;
              QString copy;
              while(!stream.atEnd())
              {
                  copy=stream.readLine();
                  if(o!=3)
                  streamt<<copy<<endl;
                  else
                  {
                   streamt<<"[ENDTIME]:"<<endtime<<endl;
                  }
                  o++;
               }
             }
         }
        f.close();
        f.remove("Temp/checkIn/"+ rNum +".txt");
        ft.close();
        if (f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            if(ft.open(QIODevice::ReadOnly | QIODevice::Text))
             {
             QString copy;
             while(!streamt.atEnd())
             {
                 copy=streamt.readLine();
                 stream<<copy<<endl;
             }
            }
        }
        f.close();
        ft.close();
        ft.remove("Temp/checkIn/"+ rNum+"x" +".txt");
        ui ->stackedWidget ->setCurrentIndex(0);
}

void Hotel::on_pushButton_47_clicked()    //续住取消2
{
    tThread->stop = false;
        ui ->stackedWidget ->setCurrentIndex(0);
        ui -> lineEdit_26-> setText("");
}

void Hotel::on_pushButton_41_clicked()       //续住取消1
{
    tThread->stop = false;
      ui ->stackedWidget ->setCurrentIndex(0);
      ui->lineEdit_26-> setText("");
}

void Hotel::on_pushButton_45_clicked()     //续住上个月
{
    QDateTime t = ui -> dateTimeEdit_2->dateTime();
            QDateTime p;
            int m = t.date().month();
            int n;
            if(m != 1)
                 n = m - 1;
            else n = 12;
            t.setDate(QDate(t.date().year(),n,27));

            while(t.date().month() == n)
            {
                p = t;
                t = t.addDays(1);
            }
            ui->dateTimeEdit_2->setDateTime(p);
}

void Hotel::on_pushButton_44_clicked()           //续住下个月按钮
{
    QDateTime t = ui -> dateTimeEdit_2->dateTime();
           t =  t.addMonths(1);
           t.setDate(QDate(t.date().year(),t.date().month(),1));
           ui->dateTimeEdit_2->setDateTime(t);
}

void Hotel::on_pushButton_29_clicked()      //续住按钮
{
    tThread ->stop = true;
    ui ->stackedWidget ->setCurrentIndex(1);
    ui ->stackedWidget_2 ->setCurrentIndex(10);
}
