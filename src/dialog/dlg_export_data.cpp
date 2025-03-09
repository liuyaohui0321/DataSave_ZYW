#include "dlg_export_data.h"
#include "ui_dlg_export_data.h"

#include  <QFileDialog>
#include  <QDebug>
#include  <QMessageBox>

DlgExportData::DlgExportData(const QString &path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_export_data), m_pDsvPath(path)
{
    ui->setupUi(this);
    initUI();
    initConnect();
}

DlgExportData::~DlgExportData()
{
    delete ui;
}

void DlgExportData::initUI()
{
    ui->m_leName->setText(m_pDsvPath);
//    ui->m_leName->setReadOnly(true);
    QStringList strListType;
    strListType<<"千兆网口"<<"万兆网口";
    ui->m_cboxExportType->addItems(strListType);
}
void DlgExportData::initConnect()
{
    connect(ui->m_btnExport,&QPushButton::clicked,this,&DlgExportData::slotBtnExportClicked);
    connect(ui->pbtn_read,&QPushButton::clicked,this,&DlgExportData::slotBtnStartExportClicked);
    connect(ui->percentButton,&QPushButton::clicked,this,&DlgExportData::slotBtnPercentExportClicked);
    connect(ui->piliangButton,&QPushButton::clicked,this,&DlgExportData::slotBtnPiliangExportClicked);
}

void DlgExportData::slotBtnExportClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("请选择文件"), "", tr("All Files (*.*)"));
    // 检查是否选择了文件
    if (!fileName.isEmpty()) {
        m_pLocalPath = fileName;
        qDebug() << "Selected file:" << fileName;
         ui->m_leLocalPath->setText(fileName);
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open file for reading:" << file.errorString();
    }
}

void DlgExportData::slotBtnStartExportClicked()
{
    if(m_pLocalPath.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
        return;
    }
    else{
//        DlgExportData::accept();
        m_mode =1;
        emit accepted();
        close();
    }

}

void DlgExportData::slotBtnPercentExportClicked()
{
//    if(m_pLocalPath.isEmpty())
//    {
//        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
//        return;
//    }
//    else{
////        DlgExportData::accept();
//        m_mode =2;
//        emit accepted();
//        close();
//    }
    m_mode =2;
    emit accepted();
    close();
}

void DlgExportData::slotBtnPiliangExportClicked()
{
//    if(m_pLocalPath.isEmpty())
//    {
//        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
//        return;
//    }
//    else{
////        DlgExportData::accept();
//        m_mode =3;
//        emit accepted();
//        close();
//    }
    m_mode =3;
    emit accepted();
    close();
}

int DlgExportData::getExportType()
{
    return  ui->m_cboxExportType->currentIndex();
}

void DlgExportData::setPath(const QString &path)
{
    ui->m_leName->setText(path);// 设置路径到输入框  LYH 2.21
}
