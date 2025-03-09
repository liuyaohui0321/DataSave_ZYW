#include "dlg_percent_export_data.h"
#include "ui_dlg_percent_export_data.h"
#include<QFileDialog>
#include<QDebug>
#include<QMessageBox>

dlg_percent_export_data::dlg_percent_export_data(const QString &path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_percent_export_data), m_pDsvPath(path)
{
    ui->setupUi(this);
    initUI();
    initConnect();
}

dlg_percent_export_data::~dlg_percent_export_data()
{
    delete ui;
}

void dlg_percent_export_data::setPath(const QString &path)
{
    ui->m_leName_2->setText(path);// 设置路径到输入框  LYH 2.21
}

int dlg_percent_export_data::getExportType()
{
    return  ui->m_cboxExportType_2->currentIndex();
}

int dlg_percent_export_data::getExportPercent()
{
    return ui->PercentLine->text().toUInt();
}

int dlg_percent_export_data::getExportCap()
{
    return ui->Rongliangline->text().toUInt();
}

void dlg_percent_export_data::initUI()
{
    ui->m_leName_2->setText(m_pDsvPath);
//    ui->m_leName_2->setReadOnly(true);
    QStringList strListType;
    strListType<<"千兆网口"<<"万兆网口";
    ui->m_cboxExportType_2->addItems(strListType);
}

void dlg_percent_export_data::initConnect()
{
    connect(ui->m_btnExport_2,&QPushButton::clicked,this,&dlg_percent_export_data::slotBtnExportClicked);
    connect(ui->pbtn_read_2,&QPushButton::clicked,this,&dlg_percent_export_data::slotBtnStartExportClicked);
}

void dlg_percent_export_data::slotBtnExportClicked()
{
    QString fileName1 = QFileDialog::getOpenFileName(this, tr("请选择文件"), "", tr("All Files (*.*)"));
    // 检查是否选择了文件
    if (!fileName1.isEmpty()) {
        m_pLocalPath = fileName1;
        qDebug() << "Selected file:" << fileName1;
         ui->m_leLocalPath_2->setText(fileName1);
    }

    QFile file1(fileName1);
    if (!file1.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open file for reading:" << file1.errorString();
    }
}

void dlg_percent_export_data::slotBtnStartExportClicked()
{
    if(m_pLocalPath.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
        return;
    }
    else{
//        DlgExportData::accept();
        emit accepted();
        close();
    }
}
