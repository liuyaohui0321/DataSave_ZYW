/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *label_name;
    QLabel *label_password;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_password;
    QLabel *label;
    QPushButton *pbtn_login;
    QPushButton *pbtn_logout;
    QLabel *label_error;
    QPushButton *pbtn_show;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(440, 302);
        label_name = new QLabel(Login);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(90, 70, 101, 41));
        label_password = new QLabel(Login);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(90, 140, 101, 41));
        lineEdit_name = new QLineEdit(Login);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(170, 80, 151, 27));
        lineEdit_password = new QLineEdit(Login);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(170, 140, 151, 27));
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 30, 131, 20));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        pbtn_login = new QPushButton(Login);
        pbtn_login->setObjectName(QString::fromUtf8("pbtn_login"));
        pbtn_login->setGeometry(QRect(110, 230, 93, 29));
        pbtn_logout = new QPushButton(Login);
        pbtn_logout->setObjectName(QString::fromUtf8("pbtn_logout"));
        pbtn_logout->setGeometry(QRect(240, 230, 93, 29));
        label_error = new QLabel(Login);
        label_error->setObjectName(QString::fromUtf8("label_error"));
        label_error->setGeometry(QRect(90, 190, 241, 20));
        pbtn_show = new QPushButton(Login);
        pbtn_show->setObjectName(QString::fromUtf8("pbtn_show"));
        pbtn_show->setGeometry(QRect(320, 140, 41, 29));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        label_name->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_password->setText(QCoreApplication::translate("Login", "\345\257\206\347\240\201:", nullptr));
        label->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        pbtn_login->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        pbtn_logout->setText(QCoreApplication::translate("Login", "\351\200\200\345\207\272", nullptr));
        label_error->setText(QString());
        pbtn_show->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
