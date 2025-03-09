/********************************************************************************
** Form generated from reading UI file 'dlgplaybackdata.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPLAYBACKDATA_H
#define UI_DLGPLAYBACKDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgPlayBackData
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_read;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_read_name;
    QLineEdit *tb_read_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *m_comGth;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_write_pattern;
    QComboBox *comboBox_write_parrent;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_xunhuan_cnt;
    QLineEdit *lineEdit_xuhuan_cnt;
    QPushButton *pbtn_read;
    QPushButton *pushButton;

    void setupUi(QDialog *DlgPlayBackData)
    {
        if (DlgPlayBackData->objectName().isEmpty())
            DlgPlayBackData->setObjectName(QString::fromUtf8("DlgPlayBackData"));
        DlgPlayBackData->resize(558, 236);
        verticalLayout = new QVBoxLayout(DlgPlayBackData);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_read = new QGroupBox(DlgPlayBackData);
        groupBox_read->setObjectName(QString::fromUtf8("groupBox_read"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_read->sizePolicy().hasHeightForWidth());
        groupBox_read->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_read);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_read_name = new QLabel(groupBox_read);
        label_read_name->setObjectName(QString::fromUtf8("label_read_name"));

        horizontalLayout->addWidget(label_read_name);

        tb_read_name = new QLineEdit(groupBox_read);
        tb_read_name->setObjectName(QString::fromUtf8("tb_read_name"));

        horizontalLayout->addWidget(tb_read_name);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox_read);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        m_comGth = new QComboBox(groupBox_read);
        m_comGth->setObjectName(QString::fromUtf8("m_comGth"));

        horizontalLayout_2->addWidget(m_comGth);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_write_pattern = new QLabel(groupBox_read);
        label_write_pattern->setObjectName(QString::fromUtf8("label_write_pattern"));

        horizontalLayout_3->addWidget(label_write_pattern);

        comboBox_write_parrent = new QComboBox(groupBox_read);
        comboBox_write_parrent->setObjectName(QString::fromUtf8("comboBox_write_parrent"));

        horizontalLayout_3->addWidget(comboBox_write_parrent);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_xunhuan_cnt = new QLabel(groupBox_read);
        label_xunhuan_cnt->setObjectName(QString::fromUtf8("label_xunhuan_cnt"));

        horizontalLayout_4->addWidget(label_xunhuan_cnt);

        lineEdit_xuhuan_cnt = new QLineEdit(groupBox_read);
        lineEdit_xuhuan_cnt->setObjectName(QString::fromUtf8("lineEdit_xuhuan_cnt"));

        horizontalLayout_4->addWidget(lineEdit_xuhuan_cnt);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 2);

        pbtn_read = new QPushButton(groupBox_read);
        pbtn_read->setObjectName(QString::fromUtf8("pbtn_read"));

        gridLayout->addWidget(pbtn_read, 4, 0, 1, 1);

        pushButton = new QPushButton(groupBox_read);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 4, 1, 1, 1);


        verticalLayout->addWidget(groupBox_read);


        retranslateUi(DlgPlayBackData);

        QMetaObject::connectSlotsByName(DlgPlayBackData);
    } // setupUi

    void retranslateUi(QDialog *DlgPlayBackData)
    {
        DlgPlayBackData->setWindowTitle(QCoreApplication::translate("DlgPlayBackData", "Dialog", nullptr));
        groupBox_read->setTitle(QCoreApplication::translate("DlgPlayBackData", "\350\257\273\345\217\226\346\226\207\344\273\266", nullptr));
        label_read_name->setText(QCoreApplication::translate("DlgPlayBackData", "\346\226\207\344\273\266\345\220\215\347\247\260\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("DlgPlayBackData", "\345\233\236\346\224\276\351\200\232\351\201\223", nullptr));
        label_write_pattern->setText(QCoreApplication::translate("DlgPlayBackData", "\350\257\273\345\217\226\346\250\241\345\274\217\357\274\232", nullptr));
        label_xunhuan_cnt->setText(QCoreApplication::translate("DlgPlayBackData", "\345\276\252\347\216\257\345\233\236\350\257\273\346\254\241\346\225\260\357\274\232", nullptr));
        pbtn_read->setText(QCoreApplication::translate("DlgPlayBackData", "\345\274\200\345\247\213\345\233\236\346\224\276", nullptr));
        pushButton->setText(QCoreApplication::translate("DlgPlayBackData", "\345\201\234\346\255\242\345\233\236\346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgPlayBackData: public Ui_DlgPlayBackData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPLAYBACKDATA_H
