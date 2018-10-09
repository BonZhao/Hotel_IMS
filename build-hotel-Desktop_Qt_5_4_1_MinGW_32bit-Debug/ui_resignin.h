/********************************************************************************
** Form generated from reading UI file 'resignin.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESIGNIN_H
#define UI_RESIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_resignIn
{
public:
    QLineEdit *txtname;
    QLabel *label;
    QLineEdit *txtpwd;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *resignIn)
    {
        if (resignIn->objectName().isEmpty())
            resignIn->setObjectName(QStringLiteral("resignIn"));
        resignIn->resize(460, 260);
        resignIn->setMinimumSize(QSize(460, 258));
        resignIn->setMaximumSize(QSize(460, 260));
        resignIn->setStyleSheet(QStringLiteral("border-image: url(:/background/Images/background/77094b36acaf2edd761be3dd8e1001e939019318.jpg);"));
        txtname = new QLineEdit(resignIn);
        txtname->setObjectName(QStringLiteral("txtname"));
        txtname->setGeometry(QRect(150, 70, 201, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        txtname->setFont(font);
        txtname->setStyleSheet(QString::fromUtf8("border-image: url(:/background/Images/background/tm.png);\n"
"font: 75 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txtname->setCursorPosition(0);
        label = new QLabel(resignIn);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(46, 70, 51, 51));
        label->setStyleSheet(QLatin1String("border-image: url(:/background/Images/background/btn_normal.png);\n"
"image: url(:/symble/Images/symbol/info_normal.png);"));
        txtpwd = new QLineEdit(resignIn);
        txtpwd->setObjectName(QStringLiteral("txtpwd"));
        txtpwd->setGeometry(QRect(150, 150, 201, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        txtpwd->setFont(font1);
        txtpwd->setStyleSheet(QStringLiteral("border-image: url(:/background/Images/background/tm.png);"));
        txtpwd->setEchoMode(QLineEdit::Password);
        txtpwd->setCursorPosition(0);
        label_2 = new QLabel(resignIn);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 150, 51, 51));
        label_2->setStyleSheet(QLatin1String("border-image: url(:/background/Images/background/btn_normal.png);\n"
"image: url(:/symble/Images/symbol/System/LOCK_normal.png);"));
        pushButton = new QPushButton(resignIn);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(310, 210, 41, 41));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/icon/Images/icon/ok_normal.png);"));
        pushButton->setDefault(true);
        pushButton->setFlat(false);
        pushButton_2 = new QPushButton(resignIn);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(380, 210, 41, 41));
        pushButton_2->setStyleSheet(QStringLiteral("border-image: url(:/icon/Images/icon/cancel_normal.png);"));
        pushButton_2->setAutoDefault(false);
        label_3 = new QLabel(resignIn);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 71, 251, 51));
        label_3->setStyleSheet(QStringLiteral("border-image: url(:/background/Images/background/catb_normal.png);"));
        label_4 = new QLabel(resignIn);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(110, 151, 251, 51));
        label_4->setStyleSheet(QStringLiteral("border-image: url(:/background/Images/background/catb_normal.png);"));
        label_4->raise();
        label_3->raise();
        txtname->raise();
        label->raise();
        txtpwd->raise();
        label_2->raise();
        pushButton->raise();
        pushButton_2->raise();

        retranslateUi(resignIn);

        QMetaObject::connectSlotsByName(resignIn);
    } // setupUi

    void retranslateUi(QDialog *resignIn)
    {
        resignIn->setWindowTitle(QApplication::translate("resignIn", "Dialog", 0));
        txtname->setText(QString());
        label->setText(QString());
        txtpwd->setText(QString());
        txtpwd->setPlaceholderText(QString());
        label_2->setText(QString());
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class resignIn: public Ui_resignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIGNIN_H
