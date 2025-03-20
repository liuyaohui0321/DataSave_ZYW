#include "dlg_multifile_play_back.h"
#include "ui_dlg_multifile_play_back.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

dlg_multifile_play_back::dlg_multifile_play_back(const QString &name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_multifile_play_back),
    m_dsvFileName(name)
{
    ui->setupUi(this);
    initUI();
    initConnect();
}

dlg_multifile_play_back::~dlg_multifile_play_back()
{
    delete ui;
}

//int dlg_multifile_play_back::getReadMode()
//{
//    int selectedIndex = ui->comboBox_write_parrent->currentIndex();
//    return   ui->comboBox_write_parrent->itemData(selectedIndex).toInt();
//}

//int dlg_multifile_play_back::getLoopCnt()
//{
//    return ui->xuhuan_cnt->text().toUInt();
//}

int dlg_multifile_play_back::getPlaybackChannel()
{
    int selectedIndex = ui->m_comGth->currentIndex();
    return   ui->m_comGth->itemData(selectedIndex).toInt();
}

void dlg_multifile_play_back::setPath(const QString &path)
{
    ui->filename->setText(path);// 设置路径到输入框  LYH 2.21
}

void dlg_multifile_play_back::initUI()
{
//    ui->comboBox_write_parrent->addItem(QString("ReadOnce"), static_cast<int>(ReadMode::ReadOnce));
//    ui->comboBox_write_parrent->addItem(QString("LoopRead"), static_cast<int>(ReadMode::LoopRead));
//    ui->comboBox_write_parrent->setCurrentIndex(0);

    ui->filename->setText(m_dsvFileName);
//    ui->tb_read_name->setReadOnly(true);


//    ui->xuhuan_cnt->setText("1");

//    ui->m_comGth->addItem(QString("GTH_8x"), static_cast<int>(BackGTH::GTH_8X));
//    ui->m_comGth->addItem(QString("NetWork"), static_cast<int>(BackGTH::GTH_NETWORK));
    ui->m_comGth->addItem(QString("GTH_4x"), static_cast<int>(BackGTH::GTH_4X));
}

void dlg_multifile_play_back::initConnect()
{
    connect(ui->startButton,&QPushButton::clicked,this,&dlg_multifile_play_back::slotBtnPlayBackClicked);
//    connect(ui->stopButton,&QPushButton::clicked,this,&dlg_multifile_play_back::slotBtnStopPlayBackClicked);
}

void dlg_multifile_play_back::slotBtnPlayBackClicked()
{
    emit accepted();
    close();
}
