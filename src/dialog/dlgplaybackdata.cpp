#include "dlgplaybackdata.h"
#include "ui_dlgplaybackdata.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

DlgPlayBackData::DlgPlayBackData(const QString &name,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgPlayBackData),m_dsvFileName(name)
{
    ui->setupUi(this);
    initUI();
    initConnect();
}

DlgPlayBackData::~DlgPlayBackData()
{
    delete ui;
}

int DlgPlayBackData::getReadMode()
{
    int selectedIndex = ui->comboBox_write_parrent->currentIndex();
    return   ui->comboBox_write_parrent->itemData(selectedIndex).toInt();
}

int DlgPlayBackData::getLoopCnt()
{
    return ui->lineEdit_xuhuan_cnt->text().toUInt();
}

int DlgPlayBackData::getPlaybackChannel()
{
    int selectedIndex = ui->m_comGth->currentIndex();
    return   ui->m_comGth->itemData(selectedIndex).toInt();
}

void DlgPlayBackData::initUI()
{
    ui->comboBox_write_parrent->addItem(QString("ReadOnce"), static_cast<int>(ReadMode::ReadOnce));
    ui->comboBox_write_parrent->addItem(QString("LoopRead"), static_cast<int>(ReadMode::LoopRead));
    ui->comboBox_write_parrent->setCurrentIndex(0);

    ui->tb_read_name->setText(m_dsvFileName);
    ui->tb_read_name->setReadOnly(true);


    ui->lineEdit_xuhuan_cnt->setText("1");

    ui->m_comGth->addItem(QString("NetWork"), static_cast<int>(BackGTH::GTH_NETWORK));
    ui->m_comGth->addItem(QString("GTH_1x"), static_cast<int>(BackGTH::GTH_1X));
    ui->m_comGth->addItem(QString("GTH_8x"), static_cast<int>(BackGTH::GTH_8X));




}
void DlgPlayBackData::initConnect()
{
    connect(ui->pbtn_read,&QPushButton::clicked,this,&DlgPlayBackData::slotBtnPlayBackClicked);
    connect(ui->pushButton,&QPushButton::clicked,this,&DlgPlayBackData::slotBtnStopPlayBackClicked);
}



void DlgPlayBackData::slotBtnPlayBackClicked()
{
    m_mode =1;
    DlgPlayBackData::accept();
}

void DlgPlayBackData::slotBtnStopPlayBackClicked()
{
    m_mode =2;
    DlgPlayBackData::accept();
}
