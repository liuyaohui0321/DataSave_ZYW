/********************************************************************************
** Form generated from reading UI file 'dlgwritedata.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGWRITEDATA_H
#define UI_DLGWRITEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgWriteData
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_write;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_write_name;
    QLineEdit *tb_write_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_write_address;
    QLineEdit *tb_write_address;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_data;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pbtn_chooseDataPath;
    QPushButton *pbtn_write;

    void setupUi(QDialog *DlgWriteData)
    {
        if (DlgWriteData->objectName().isEmpty())
            DlgWriteData->setObjectName(QString::fromUtf8("DlgWriteData"));
        DlgWriteData->resize(439, 356);
        verticalLayout_2 = new QVBoxLayout(DlgWriteData);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_write = new QGroupBox(DlgWriteData);
        groupBox_write->setObjectName(QString::fromUtf8("groupBox_write"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_write->sizePolicy().hasHeightForWidth());
        groupBox_write->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_write);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_write_name = new QLabel(groupBox_write);
        label_write_name->setObjectName(QString::fromUtf8("label_write_name"));

        horizontalLayout->addWidget(label_write_name);

        tb_write_name = new QLineEdit(groupBox_write);
        tb_write_name->setObjectName(QString::fromUtf8("tb_write_name"));

        horizontalLayout->addWidget(tb_write_name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_write_address = new QLabel(groupBox_write);
        label_write_address->setObjectName(QString::fromUtf8("label_write_address"));

        horizontalLayout_2->addWidget(label_write_address);

        tb_write_address = new QLineEdit(groupBox_write);
        tb_write_address->setObjectName(QString::fromUtf8("tb_write_address"));

        horizontalLayout_2->addWidget(tb_write_address);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_data = new QLabel(groupBox_write);
        label_data->setObjectName(QString::fromUtf8("label_data"));

        horizontalLayout_3->addWidget(label_data);

        lineEdit_3 = new QLineEdit(groupBox_write);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_3->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pbtn_chooseDataPath = new QPushButton(groupBox_write);
        pbtn_chooseDataPath->setObjectName(QString::fromUtf8("pbtn_chooseDataPath"));

        horizontalLayout_4->addWidget(pbtn_chooseDataPath);

        pbtn_write = new QPushButton(groupBox_write);
        pbtn_write->setObjectName(QString::fromUtf8("pbtn_write"));

        horizontalLayout_4->addWidget(pbtn_write);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox_write);


        retranslateUi(DlgWriteData);

        QMetaObject::connectSlotsByName(DlgWriteData);
    } // setupUi

    void retranslateUi(QDialog *DlgWriteData)
    {
        DlgWriteData->setWindowTitle(QCoreApplication::translate("DlgWriteData", "Dialog", nullptr));
        groupBox_write->setTitle(QCoreApplication::translate("DlgWriteData", "\345\206\231\345\205\245\346\226\207\344\273\266", nullptr));
        label_write_name->setText(QCoreApplication::translate("DlgWriteData", "\346\226\207\344\273\266\345\220\215\347\247\260\357\274\232", nullptr));
        label_write_address->setText(QCoreApplication::translate("DlgWriteData", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        label_data->setText(QCoreApplication::translate("DlgWriteData", "\346\225\260\346\215\256\350\267\257\345\276\204\357\274\232", nullptr));
        pbtn_chooseDataPath->setText(QCoreApplication::translate("DlgWriteData", "\351\200\211\346\213\251\346\225\260\346\215\256", nullptr));
        pbtn_write->setText(QCoreApplication::translate("DlgWriteData", "\345\274\200\345\247\213\345\206\231\345\205\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgWriteData: public Ui_DlgWriteData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGWRITEDATA_H
