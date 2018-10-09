#include "resignin.h"
#include "ui_resignin.h"
#include "hotel.h"
#include "QFile"
#include "QTextStream"
#include "QTextCodec"
#include "QMessageBox"
#include <QPalette>
#include<QPropertyAnimation>

resignIn::resignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resignIn)
{
    ui->setupUi(this);
    this->setWindowTitle("艾恩葛朗特登入系统(づ￣3￣)づ");
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
     animation->setDuration(1000);
     animation->setStartValue(0);
     animation->setEndValue(1);
     animation->start();

     ui->txtname->setCursorPosition(100);
     ui->txtpwd->setCursorPosition(5);

    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(closeWidget()));
}


resignIn::~resignIn()
{
    ui->txtpwd->setEchoMode(QLineEdit::Password);
    delete ui;


}



QString byteToQString(const QByteArray &byte)

{

  QString result;

  if(byte.size() > 0)
  {
   QTextCodec *codec = QTextCodec::codecForName("utf-8");
   result = codec->toUnicode(byte);

 }

   return result;

}


QByteArray qstringToByte(const QString &strInfo)

{

   QByteArray result;

   if(strInfo.length() > 0)
   {
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    result = codec->fromUnicode(strInfo);

 }

  return result;

}

QString getXorEncryptDecrypt(const QString &str, const char &key)

{

  QString result;
  QByteArray bs = qstringToByte(str);
  for(int i=0; i<bs.size(); i++)
  {
    bs[i] = bs[i] ^ key;
  }

  result = byteToQString(bs);

  return result;

}


void resignIn::on_pushButton_clicked()
{


    QFile file("Temp/User.txt");
    QString password , account;
    QTextStream stream(&file);

    if (file.open(QIODevice::Text|QIODevice::ReadOnly))
    {
        account = stream.readLine();
        password =  stream.readLine();
        account = getXorEncryptDecrypt(account,11);
        password = getXorEncryptDecrypt(password,11);
        file.close();
    }

     if(this->ui->txtname->text()== account &&
         this->ui->txtpwd->text()== password)
      {
          accept();
      }
      else
      {
          QMessageBox::warning(NULL,"警告","用户名或密码错误!",QMessageBox::Yes);
          this->ui->txtname->clear();
          this->ui->txtpwd->clear();
          this->ui->txtname->setFocus();
      }


}

void resignIn::on_pushButton_2_clicked()
{

}

bool resignIn::closeWidget()
{
   //界面动画，改变透明度的方式消失1 - 0渐变
   QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
   animation->setDuration(1000);
   animation->setStartValue(1);
   animation->setEndValue(0);
   animation->start();
   connect(animation, SIGNAL(finished()), this, SLOT(close()));

   return true;
}
void resignIn::closeEvent(QCloseEvent *)
{
    //退出系统
    if(windowTitle() != "身份确认")
        QApplication::quit();


}

void resignIn::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("border-image: url(:/icon/Images/icon/ok_disable.png);");
}

void resignIn::on_pushButton_released()
{
    ui->pushButton->setStyleSheet("border-image: url(:/icon/Images/icon/ok_normal.png);");
}

void resignIn::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet("border-image: url(:/icon/Images/icon/cancel_disable.png);");
}

void resignIn::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet("border-image: url(:/icon/Images/icon/cancel_normal.png);");
}
