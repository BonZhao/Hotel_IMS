#include "resignin.h"
#include "ui_resignin.h"
#include "hotel.h"
#include "QFile"
#include "QTextStream"
#include "QTextCodec"
#include "QMessageBox"
resignIn::resignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resignIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");

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
          QMessageBox::warning(this,"警告","用户名或密码错误!",QMessageBox::Yes);
          this->ui->txtname->clear();
          this->ui->txtpwd->clear();
          this->ui->txtname->setFocus();
      }


}
