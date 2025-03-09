/********************************************************************************
** Form generated from reading UI file 'diskconfirm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKCONFIRM_H
#define UI_DISKCONFIRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiskConfirm
{
public:
    QLabel *label;
    QPushButton *pbtn_ok;
    QPushButton *pbtn_no;

    void setupUi(QWidget *DiskConfirm)
    {
        if (DiskConfirm->objectName().isEmpty())
            DiskConfirm->setObjectName(QString::fromUtf8("DiskConfirm"));
        DiskConfirm->resize(400, 213);
        label = new QLabel(DiskConfirm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 40, 181, 51));
        pbtn_ok = new QPushButton(DiskConfirm);
        pbtn_ok->setObjectName(QString::fromUtf8("pbtn_ok"));
        pbtn_ok->setGeometry(QRect(70, 130, 93, 29));
        pbtn_no = new QPushButton(DiskConfirm);
        pbtn_no->setObjectName(QString::fromUtf8("pbtn_no"));
        pbtn_no->setGeometry(QRect(220, 130, 93, 29));

        retranslateUi(DiskConfirm);

        QMetaObject::connectSlotsByName(DiskConfirm);
    } // setupUi

    void retranslateUi(QWidget *DiskConfirm)
    {
        DiskConfirm->setWindowTitle(QCoreApplication::translate("DiskConfirm", "Form", nullptr));
        label->setText(QString());
        pbtn_ok->setText(QCoreApplication::translate("DiskConfirm", "\347\241\256\350\256\244", nullptr));
        pbtn_no->setText(QCoreApplication::translate("DiskConfirm", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiskConfirm: public Ui_DiskConfirm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKCONFIRM_H
