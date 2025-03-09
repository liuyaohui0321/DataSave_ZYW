#include "login.h"
#include "ui_login.h"
#include <QIcon>
#pragma execution_character_set("utf-8")

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    timer = new QTimer(this);
    timer->setSingleShot(true);
    QIcon icon(":/my/images/hide.png");
    ui->pbtn_show->setIcon(icon);
    ui->pbtn_show->setStyleSheet("QPushButton { border: none; background: transparent; }");
    connect(timer, &QTimer::timeout, this, &Login::hidePassword);

}

Login::~Login()
{
    delete ui;
}

//点击登录发送一个信号,让主界面显示出来
//void Login::on_pbtn_login_clicked()
//{
//    QString name = ui->lineEdit_name->text();
//    QString passward = ui->lineEdit_password->text();
//    if(name=="ucas" &&passward=="1234")
//    {
//        ui->label_error->setText("");
//        emit signal_mainshow();
//        hide();
//    }
//    else
//    {
//        ui->label_error->setText("用户名或密码错误，请重新输入.");
//    }
//}

void Login::on_pbtn_login_clicked()
{
    emit signal_mainshow();
    hide();
}


void Login::on_pbtn_logout_clicked()
{
    this->close();
}


void Login::on_pbtn_show_clicked()
{
    QIcon icon(":/my/images/show.png");
    ui->pbtn_show->setIcon(icon);
    ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    timer->start(2000);
}

void Login::hidePassword()
{
    // 恢复密码模式
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    QIcon icon(":/my/images/hide.png");
    ui->pbtn_show->setIcon(icon);
}

