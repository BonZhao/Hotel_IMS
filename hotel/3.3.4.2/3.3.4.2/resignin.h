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

    void on_pushButton_2_clicked();
    bool closeWidget();

    void closeEvent(QCloseEvent *);

    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_2_pressed();

    void on_pushButton_2_released();

private:
    Ui::resignIn *ui;
};

QString getXorEncryptDecrypt(const QString &, const char &);

QString byteToQString(const QByteArray &byte);

QByteArray qstringToByte(const QString &strInfo);


#endif // RESIGNIN_H
