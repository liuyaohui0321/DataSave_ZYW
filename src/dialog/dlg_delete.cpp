#include "dlg_delete.h"
#include "ui_dlg_delete.h"

dlg_delete::dlg_delete(const QString &name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_delete),
    m_dsvFileName(name)
{
    ui->setupUi(this);
    initUI();
//    initConnect();
}

dlg_delete::~dlg_delete()
{
    delete ui;
}

QString dlg_delete::getLocalPath()
{
    return ui->deleteline->text();
}

void dlg_delete::setPath(const QString &path)
{
    ui->deleteline->setText(path);// 设置路径到输入框  LYH 2.19
}

void dlg_delete::LineEditSet(void)
{
    ui->deleteline->setVisible(false);// LYH 2.21
}

void dlg_delete::Dialog_Set(const QString &path)
{
    ui->label->setText(path);// LYH 2.21
}

void dlg_delete::initUI()
{
    this->setWindowTitle("删除操作");
    ui->deleteline->setText(m_dsvFileName);
}

void dlg_delete::initConnect()
{
    //删除操作
    connect(ui->deleteButton,&QPushButton::released,this,&dlg_delete::on_deleteButton_clicked);
}

void dlg_delete::on_deleteButton_clicked()
{
//   qDebug() << "Emitting accepted signal";
   emit accepted();
    close();
}
