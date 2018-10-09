#ifndef RESIGNIN_H
#define RESIGNIN_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class resignIn;
}

class resignIn : public QDialog
{
    Q_OBJECT

public:
    explicit resignIn(QWidget *parent = 0);
    ~resignIn();

private slots:


    void on_pushButton_clicked();

private:
    Ui::resignIn *ui;
};

QString getXorEncryptDecrypt(const QString &, const char &);

QString byteToQString(const QByteArray &byte);

QByteArray qstringToByte(const QString &strInfo);


#endif // RESIGNIN_H
