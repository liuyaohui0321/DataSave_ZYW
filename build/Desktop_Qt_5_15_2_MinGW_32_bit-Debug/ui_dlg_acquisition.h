/********************************************************************************
** Form generated from reading UI file 'dlg_acquisition.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_ACQUISITION_H
#define UI_DLG_ACQUISITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlg_acquisition
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_read;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lbName;
    QLineEdit *m_leName;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *dlg_acquisition)
    {
        if (dlg_acquisition->objectName().isEmpty())
            dlg_acquisition->setObjectName(QString::fromUtf8("dlg_acquisition"));
        dlg_acquisition->resize(556, 212);
        gridLayout = new QGridLayout(dlg_acquisition);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_read = new QGroupBox(dlg_acquisition);
        groupBox_read->setObjectName(QString::fromUtf8("groupBox_read"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_read->sizePolicy().hasHeightForWidth());
        groupBox_read->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_read);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_lbName = new QLabel(groupBox_read);
        m_lbName->setObjectName(QString::fromUtf8("m_lbName"));

        horizontalLayout_2->addWidget(m_lbName);

        m_leName = new QLineEdit(groupBox_read);
        m_leName->setObjectName(QString::fromUtf8("m_leName"));

        horizontalLayout_2->addWidget(m_leName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_2 = new QPushButton(groupBox_read);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(groupBox_read);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addWidget(groupBox_read, 0, 0, 1, 1);


        retranslateUi(dlg_acquisition);

        QMetaObject::connectSlotsByName(dlg_acquisition);
    } // setupUi

    void retranslateUi(QDialog *dlg_acquisition)
    {
        dlg_acquisition->setWindowTitle(QCoreApplication::translate("dlg_acquisition", "dlg_acquisition", nullptr));
        groupBox_read->setTitle(QCoreApplication::translate("dlg_acquisition", "\346\225\260\346\215\256\351\207\207\351\233\206", nullptr));
        m_lbName->setText(QCoreApplication::translate("dlg_acquisition", "\351\207\207\351\233\206\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("dlg_acquisition", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        pushButton->setText(QCoreApplication::translate("dlg_acquisition", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlg_acquisition: public Ui_dlg_acquisition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_ACQUISITION_H
