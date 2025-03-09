/********************************************************************************
** Form generated from reading UI file 'dlgexportdata.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEXPORTDATA_H
#define UI_DLGEXPORTDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgExportData
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_read;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_lbName;
    QLineEdit *m_leName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lbLocalPath;
    QLineEdit *m_leLocalPath;
    QPushButton *m_btnExport;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *m_cboxExportType;
    QPushButton *pbtn_read;
    QPushButton *pbtn_mvpp;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DlgExportData)
    {
        if (DlgExportData->objectName().isEmpty())
            DlgExportData->setObjectName(QString::fromUtf8("DlgExportData"));
        DlgExportData->resize(641, 318);
        verticalLayout_2 = new QVBoxLayout(DlgExportData);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_read = new QGroupBox(DlgExportData);
        groupBox_read->setObjectName(QString::fromUtf8("groupBox_read"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_read->sizePolicy().hasHeightForWidth());
        groupBox_read->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_read);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_lbName = new QLabel(groupBox_read);
        m_lbName->setObjectName(QString::fromUtf8("m_lbName"));

        horizontalLayout->addWidget(m_lbName);

        m_leName = new QLineEdit(groupBox_read);
        m_leName->setObjectName(QString::fromUtf8("m_leName"));

        horizontalLayout->addWidget(m_leName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_lbLocalPath = new QLabel(groupBox_read);
        m_lbLocalPath->setObjectName(QString::fromUtf8("m_lbLocalPath"));

        horizontalLayout_2->addWidget(m_lbLocalPath);

        m_leLocalPath = new QLineEdit(groupBox_read);
        m_leLocalPath->setObjectName(QString::fromUtf8("m_leLocalPath"));

        horizontalLayout_2->addWidget(m_leLocalPath);

        m_btnExport = new QPushButton(groupBox_read);
        m_btnExport->setObjectName(QString::fromUtf8("m_btnExport"));

        horizontalLayout_2->addWidget(m_btnExport);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_cboxExportType = new QComboBox(groupBox_read);
        m_cboxExportType->setObjectName(QString::fromUtf8("m_cboxExportType"));

        horizontalLayout_5->addWidget(m_cboxExportType);

        pbtn_read = new QPushButton(groupBox_read);
        pbtn_read->setObjectName(QString::fromUtf8("pbtn_read"));

        horizontalLayout_5->addWidget(pbtn_read);

        pbtn_mvpp = new QPushButton(groupBox_read);
        pbtn_mvpp->setObjectName(QString::fromUtf8("pbtn_mvpp"));

        horizontalLayout_5->addWidget(pbtn_mvpp);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox_read);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        lineEdit = new QLineEdit(groupBox_read);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_2 = new QLabel(groupBox_read);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        label_3 = new QLabel(groupBox_read);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_3);

        lineEdit_2 = new QLineEdit(groupBox_read);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy2.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(lineEdit_2);

        label_4 = new QLabel(groupBox_read);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(groupBox_read);


        retranslateUi(DlgExportData);

        QMetaObject::connectSlotsByName(DlgExportData);
    } // setupUi

    void retranslateUi(QDialog *DlgExportData)
    {
        DlgExportData->setWindowTitle(QCoreApplication::translate("DlgExportData", "Dialog", nullptr));
        groupBox_read->setTitle(QCoreApplication::translate("DlgExportData", "\345\257\274\345\207\272\346\226\207\344\273\266", nullptr));
        m_lbName->setText(QCoreApplication::translate("DlgExportData", "\345\255\230\345\202\250\347\211\210\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        m_lbLocalPath->setText(QCoreApplication::translate("DlgExportData", "\346\234\254\345\234\260\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        m_btnExport->setText(QCoreApplication::translate("DlgExportData", "\351\200\211\346\213\251\346\234\254\345\234\260\346\226\207\344\273\266", nullptr));
        pbtn_read->setText(QCoreApplication::translate("DlgExportData", "\345\274\200\345\247\213\345\257\274\345\207\272", nullptr));
        pbtn_mvpp->setText(QCoreApplication::translate("DlgExportData", "\344\275\277\347\224\250mvpp\346\240\274\345\274\217\345\257\274\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("DlgExportData", "\345\212\237\347\216\207\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("DlgExportData", "DB/M", nullptr));
        label_3->setText(QCoreApplication::translate("DlgExportData", "\351\207\207\346\240\267\347\216\207\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("DlgExportData", "Hz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgExportData: public Ui_DlgExportData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGEXPORTDATA_H
