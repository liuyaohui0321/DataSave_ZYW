#include "dlg_export_morefile_data.h"
#include "ui_dlg_export_morefile_data.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

dlg_export_moreFile_data::dlg_export_moreFile_data(const QString &path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_export_moreFile_data), m_pDsvPath(path)
{
    ui->setupUi(this);
    initUI();
    initConnect();
}

dlg_export_moreFile_data::~dlg_export_moreFile_data()
{
    delete ui;
}

void dlg_export_moreFile_data::setPath(const QString &path)
{
    ui->m_leName_3->setText(path);// 设置路径到输入框  LYH 2.25
}

int dlg_export_moreFile_data::getExportType()
{
    return  ui->m_cboxExportType->currentIndex();
}

void dlg_export_moreFile_data::initUI()
{
    ui->m_leName_3->setText(m_pDsvPath);
//    ui->m_leName_2->setReadOnly(true);
    QStringList strListType;
    strListType<<"千兆网口"<<"万兆网口";
    ui->m_cboxExportType->addItems(strListType);
}

void dlg_export_moreFile_data::initConnect()
{
    connect(ui->m_btnExport,&QPushButton::clicked,this,&dlg_export_moreFile_data::slotBtnExportClicked);
    connect(ui->pbtn_read,&QPushButton::clicked,this,&dlg_export_moreFile_data::slotBtnStartExportClicked);
}

void dlg_export_moreFile_data::slotBtnExportClicked()
{
    QString fileName2 = QFileDialog::getOpenFileName(this, tr("请选择文件"), "", tr("All Files (*.*)"));
    // 检查是否选择了文件
    if (!fileName2.isEmpty()) {
        m_pLocalPath = fileName2;
        qDebug() << "Selected file:" << fileName2;
         ui->m_leLocalPath_3->setText(fileName2);
    }

    QFile file2(fileName2);
    if (!file2.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open file for reading:" << file2.errorString();
    }
}

void dlg_export_moreFile_data::slotBtnStartExportClicked()
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
