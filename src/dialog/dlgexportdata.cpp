#include "dlgexportdata.h"
#include "ui_dlgexportdata.h"

#include  <QFileDialog>
#include  <QDebug>
#include  <QMessageBox>

DlgExportData::DlgExportData(const QString &path,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgExportData), m_pDsvPath(path)
{
    ui->setupUi(this);
    initUI();
    initConnect();
    isMvpp = false;
}

DlgExportData::~DlgExportData()
{
    delete ui;
}

void DlgExportData::initUI()
{
    ui->m_leName->setText(m_pDsvPath);
    ui->m_leName->setReadOnly(true);
    QStringList strListType;
    strListType<<"千兆网口"<<"万兆网口";
    ui->m_cboxExportType->addItems(strListType);
}
void DlgExportData::initConnect()
{
    connect(ui->m_btnExport,&QPushButton::clicked,this,&DlgExportData::slotBtnExportClicked);
    connect(ui->pbtn_read,&QPushButton::clicked,this,&DlgExportData::slotBtnStartExportClicked);
    connect(ui->pbtn_mvpp,&QPushButton::clicked,this,&DlgExportData::slotBtnMvppExportClicked);

}

void DlgExportData::slotBtnExportClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("请选择文件"), "", tr("All Files (*.*)"));
    // 检查是否选择了文件
    if (!fileName.isEmpty()) {
        m_pLocalPath = fileName;
        //qDebug() << "Selected file:" << fileName;
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
        isMvpp = false;
        DlgExportData::accept();
    }

}

void DlgExportData::slotBtnMvppExportClicked()
{
    if(m_pLocalPath.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
        return;
    }
    else
    {
        QString power = ui->lineEdit->text();
        QString hz = ui->lineEdit_2->text();
        if(power.isEmpty() && hz.isEmpty()){
            QMessageBox::critical(this, tr("错误"), tr("请输入参数再开始导出数据"));
        }
        else{
            m_power = power.toDouble();
            m_hz = hz.toDouble();
            isMvpp = true;
            DlgExportData::accept();
        }

    }
}

int DlgExportData::getExportType()
{
    return  ui->m_cboxExportType->currentIndex();
}
