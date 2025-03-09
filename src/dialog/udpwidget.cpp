#include "udpwidget.h"
#include "ui_udpwidget.h"

udpWidget::udpWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::udpWidget)
{
    ui->setupUi(this);
    //m_ip = "192.168.1.107";
    //m_port = 8511;

    m_ip = "192.168.1.107";
    m_port = 1024;
    ui->lineEdit_ip->setText(m_ip);
    ui->lineEdit_port->setText(QString::number(m_port));
    connect(ui->pbtn_connect,&QPushButton::clicked,this,&udpWidget::slot_connect);

    //ui->lineEdit_ip->setF
}

udpWidget::~udpWidget()
{
    delete ui;
}

void udpWidget::slot_connect()
{
    m_ip = ui->lineEdit_ip->text();
    m_port = ui->lineEdit_port->text().toUInt();
    emit sign_setNewConnectInfo();
    udpWidget::accept();
    //this->hide();
}
