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

    void setupUi(QDialog *resignIn)
    {
        if (resignIn->objectName().isEmpty())
            resignIn->setObjectName(QStringLiteral("resignIn"));
        resignIn->resize(455, 264);
        txtname = new QLineEdit(resignIn);
        txtname->setObjectName(QStringLiteral("txtname"));
        txtname->setGeometry(QRect(120, 80, 211, 21));
        label = new QLabel(resignIn);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 80, 47, 20));
        txtpwd = new QLineEdit(resignIn);
        txtpwd->setObjectName(QStringLiteral("txtpwd"));
        txtpwd->setGeometry(QRect(120, 150, 211, 21));
        txtpwd->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(resignIn);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 150, 51, 16));
        pushButton = new QPushButton(resignIn);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(330, 210, 75, 23));

        retranslateUi(resignIn);

        QMetaObject::connectSlotsByName(resignIn);
    } // setupUi

    void retranslateUi(QDialog *resignIn)
    {
        resignIn->setWindowTitle(QApplication::translate("resignIn", "Dialog", 0));
        label->setText(QApplication::translate("resignIn", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        label_2->setText(QApplication::translate("resignIn", "\345\257\206\347\240\201\357\274\232", 0));
        pushButton->setText(QApplication::translate("resignIn", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class resignIn: public Ui_resignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIGNIN_H
