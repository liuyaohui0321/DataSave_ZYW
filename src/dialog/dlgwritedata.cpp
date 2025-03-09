#include "dlgwritedata.h"
#include "ui_dlgwritedata.h"
#include "../helper/dsv_define.h"

#include  <QFileInfo>
#include  <QDebug>
#include  <QFileDialog>
#include  <QMessageBox>
#include  <cmath>

#pragma execution_character_set("utf-8")

DlgWriteData::DlgWriteData(const QString &path,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgWriteData),m_pPath(path)
{
    ui->setupUi(this);
    initUI();
    initConnect();
}

DlgWriteData::~DlgWriteData()
{
    delete ui;
}


void DlgWriteData::initUI()
{
    QFileInfo fileInfo(m_pPath);
    // 获取文件名称
    auto fileName = fileInfo.fileName();

    ui->tb_write_name->setText(fileName);
    ui->tb_write_name->setReadOnly(true);
    ui->tb_write_address->setText(m_pPath);
    ui->tb_write_address->setReadOnly(true);
}

void DlgWriteData::initConnect()
{
    connect(ui->pbtn_chooseDataPath,&QPushButton::clicked,this,&DlgWriteData::slotBtnChooseDataPathClicked);
    connect(ui->pbtn_write,&QPushButton::clicked,this,&DlgWriteData::slotBtnWriteClicked);
}


void DlgWriteData::slotBtnChooseDataPathClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("请选择文件"), "", tr("All Files (*.*)"));
    // 检查是否选择了文件
    if (!fileName.isEmpty()) {
        m_pLocalPath = fileName;
        //qDebug() << "Selected file:" << fileName;
        ui->lineEdit_3->setText(fileName);
        //        ui->textBrowser_log->append(
        //                QString("%1: 选择本地要写入的文件为[%2].").arg(StaticGlobalMethod::getNowTime()).arg(fileName));
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open file for reading:" << file.errorString();
    }
    qint64 fileSize = file.size();
    //    qDebug() << "打开的文件大小为：" << fileSize;

    qint64 getPackageNum = std::ceil(static_cast<double>(fileSize) / (DSV_WRITE_PACKAGE_SIZE));//ceil 向上取整 floor向下取整
    getPackageNum = (getPackageNum == 0) ? 1 : getPackageNum;
    m_packageNum = getPackageNum;
    //    qDebug() << "打开的文件有多少包：" << m_packageNum;

    //    qint64 lastsize = fileSize % (BUFFERSIZE);
    //    uint32_t  lastsliceNum = std::floor(lastsize / 1446);
    //    lastPackageSliceNum = lastsliceNum;
    //    lastPackageLastSliceLen = lastsize % 1446;


    //    qDebug()<<"打开的文件有多少包n = "<<packageNum;
    //    qDebug()<<"最后一包的分片数m = "<<lastPackageSliceNum;
    //    qDebug()<<"最后一包最后一片的长度len = "<<lastPackageLastSliceLen;

}

void DlgWriteData::slotBtnWriteClicked()
{
    if(m_pPath.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
        return;
    }
    else{
        DlgWriteData::accept();
    }

}
