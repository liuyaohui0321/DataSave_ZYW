/********************************************************************************
** Form generated from reading UI file 'dlgfileorfolder.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGFILEORFOLDER_H
#define UI_DLGFILEORFOLDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgFileOrFolder
{
public:
    QLabel *m_lbTitle;
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *l_name;
    QLineEdit *lineEdit_name;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_address;
    QLineEdit *lineEdit_address;

    void setupUi(QDialog *DlgFileOrFolder)
    {
        if (DlgFileOrFolder->objectName().isEmpty())
            DlgFileOrFolder->setObjectName(QString::fromUtf8("DlgFileOrFolder"));
        DlgFileOrFolder->resize(355, 246);
        m_lbTitle = new QLabel(DlgFileOrFolder);
        m_lbTitle->setObjectName(QString::fromUtf8("m_lbTitle"));
        m_lbTitle->setGeometry(QRect(10, 10, 333, 58));
        QFont font;
        font.setPointSize(14);
        m_lbTitle->setFont(font);
        m_lbTitle->setAlignment(Qt::AlignCenter);
        buttonBox = new QDialogButtonBox(DlgFileOrFolder);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 200, 333, 28));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(DlgFileOrFolder);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(70, 90, 221, 27));
        horizontalLayout_6 = new QHBoxLayout(widget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        l_name = new QLabel(widget);
        l_name->setObjectName(QString::fromUtf8("l_name"));

        horizontalLayout_6->addWidget(l_name);

        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));

        horizontalLayout_6->addWidget(lineEdit_name);

        widget1 = new QWidget(DlgFileOrFolder);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(70, 140, 221, 27));
        horizontalLayout_7 = new QHBoxLayout(widget1);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_address = new QLabel(widget1);
        label_address->setObjectName(QString::fromUtf8("label_address"));

        horizontalLayout_7->addWidget(label_address);

        lineEdit_address = new QLineEdit(widget1);
        lineEdit_address->setObjectName(QString::fromUtf8("lineEdit_address"));

        horizontalLayout_7->addWidget(lineEdit_address);


        retranslateUi(DlgFileOrFolder);

        QMetaObject::connectSlotsByName(DlgFileOrFolder);
    } // setupUi

    void retranslateUi(QDialog *DlgFileOrFolder)
    {
        DlgFileOrFolder->setWindowTitle(QCoreApplication::translate("DlgFileOrFolder", "Dialog", nullptr));
        m_lbTitle->setText(QCoreApplication::translate("DlgFileOrFolder", "\345\210\233\345\273\272\346\226\207\344\273\266", nullptr));
        l_name->setText(QCoreApplication::translate("DlgFileOrFolder", "\345\220\215\347\247\260\357\274\232", nullptr));
        label_address->setText(QCoreApplication::translate("DlgFileOrFolder", "\350\267\257\345\276\204\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgFileOrFolder: public Ui_DlgFileOrFolder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGFILEORFOLDER_H
