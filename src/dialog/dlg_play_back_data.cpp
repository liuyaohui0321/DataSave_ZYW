
#include "dlg_play_back_data.h"
#include "ui_dlg_play_back_data.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

DlgPlayBackData::DlgPlayBackData(const QString &name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_play_back_data),
    m_dsvFileName(name)
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

void DlgPlayBackData::setPath(const QString &path)
{
    ui->tb_read_name->setText(path);// 设置路径到输入框  LYH 2.14
}

void DlgPlayBackData::initUI()
{
    ui->comboBox_write_parrent->addItem(QString("ReadOnce"), static_cast<int>(ReadMode::ReadOnce));
    ui->comboBox_write_parrent->addItem(QString("LoopRead"), static_cast<int>(ReadMode::LoopRead));
    ui->comboBox_write_parrent->setCurrentIndex(0);

    ui->tb_read_name->setText(m_dsvFileName);
//    ui->tb_read_name->setReadOnly(true);

    ui->lineEdit_xuhuan_cnt->setText("1");

    ui->m_comGth->addItem(QString("GTH_8x"), static_cast<int>(BackGTH::GTH_8X));
    ui->m_comGth->addItem(QString("NetWork"), static_cast<int>(BackGTH::GTH_NETWORK));
    ui->m_comGth->addItem(QString("GTH_1x"), static_cast<int>(BackGTH::GTH_1X));
}

void DlgPlayBackData::initConnect()
{
    connect(ui->pbtn_read,&QPushButton::clicked,this,&DlgPlayBackData::slotBtnPlayBackClicked);
    connect(ui->pushButton,&QPushButton::clicked,this,&DlgPlayBackData::slotBtnStopPlayBackClicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&DlgPlayBackData::slotBtnMultiFilePlayBackClicked);
}



void DlgPlayBackData::slotBtnPlayBackClicked()
{
    m_mode =1;
//    DlgPlayBackData::accept();  // LYH 2.14
    emit accepted();
    close();
}

void DlgPlayBackData::slotBtnStopPlayBackClicked()
{
    m_mode =2;
//    DlgPlayBackData::accept();  // LYH 2.14
//    emit rejected();
    emit accepted();
    close();
}

void DlgPlayBackData::slotBtnMultiFilePlayBackClicked()
{
    m_mode =3;
    emit accepted();
}
//void DlgPlayBackData::slotMultiFilePlayBack()
//{
//    dlg_multifile_play_back *dialog = new dlg_multifile_play_back(m_TreeItemInfo.path, this);
//    dialog->show();
//}
