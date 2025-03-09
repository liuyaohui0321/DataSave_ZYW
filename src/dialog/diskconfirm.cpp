#include "diskconfirm.h"
#include "ui_diskconfirm.h"

DiskConfirm::DiskConfirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiskConfirm)
{
    ui->setupUi(this);
}

DiskConfirm::~DiskConfirm()
{
    delete ui;
}


//磁盘格式化操作确认
void DiskConfirm::on_pbtn_ok_clicked()
{
    emit sig_disk_check(true);

}
