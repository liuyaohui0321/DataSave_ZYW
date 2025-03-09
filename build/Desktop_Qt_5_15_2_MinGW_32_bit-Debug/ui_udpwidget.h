/********************************************************************************
** Form generated from reading UI file 'udpwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPWIDGET_H
#define UI_UDPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_udpWidget
{
public:
    QLabel *l_ip;
    QLabel *l_port;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    QPushButton *pbtn_connect;

    void setupUi(QDialog *udpWidget)
    {
        if (udpWidget->objectName().isEmpty())
            udpWidget->setObjectName(QString::fromUtf8("udpWidget"));
        udpWidget->resize(459, 224);
        l_ip = new QLabel(udpWidget);
        l_ip->setObjectName(QString::fromUtf8("l_ip"));
        l_ip->setGeometry(QRect(20, 10, 111, 41));
        QFont font;
        font.setPointSize(12);
        l_ip->setFont(font);
        l_port = new QLabel(udpWidget);
        l_port->setObjectName(QString::fromUtf8("l_port"));
        l_port->setGeometry(QRect(20, 80, 121, 41));
        l_port->setFont(font);
        lineEdit_ip = new QLineEdit(udpWidget);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(140, 10, 281, 51));
        lineEdit_ip->setFont(font);
        lineEdit_port = new QLineEdit(udpWidget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(140, 90, 281, 51));
        lineEdit_port->setFont(font);
        pbtn_connect = new QPushButton(udpWidget);
        pbtn_connect->setObjectName(QString::fromUtf8("pbtn_connect"));
        pbtn_connect->setGeometry(QRect(150, 160, 141, 41));
        pbtn_connect->setFont(font);

        retranslateUi(udpWidget);

        QMetaObject::connectSlotsByName(udpWidget);
    } // setupUi

    void retranslateUi(QDialog *udpWidget)
    {
        udpWidget->setWindowTitle(QCoreApplication::translate("udpWidget", "Dialog", nullptr));
        l_ip->setText(QCoreApplication::translate("udpWidget", "IP:", nullptr));
        l_port->setText(QCoreApplication::translate("udpWidget", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        pbtn_connect->setText(QCoreApplication::translate("udpWidget", "\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class udpWidget: public Ui_udpWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPWIDGET_H
