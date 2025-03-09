#include "dlgfileorfolder.h"
#include "ui_dlgfileorfolder.h"

#pragma execution_character_set("utf-8")

DlgFileOrFolder::DlgFileOrFolder(DlgType type, const QString &path,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgFileOrFolder),m_pixPath(path)
{
    ui->setupUi(this);
    initUI(type);
    initConnect();
}

DlgFileOrFolder::~DlgFileOrFolder()
{
    delete ui;
}

void DlgFileOrFolder::initUI(DlgType type)
{
    ui->m_lbTitle->setFixedHeight(60);
    ui->lineEdit_address->setReadOnly(true);
    ui->lineEdit_address->setText(m_pixPath);

    if(type==DlgType::DlgFolder)
    {
        ui->m_lbTitle->setText("创建文件夹");

        ui->lineEdit_name->setPlaceholderText("请输入文件夹名称");
    }
    else if(type==DlgType::DlgFile)
    {
        ui->lineEdit_name->setPlaceholderText("请输入文件名称");
    }
    else if(type==DlgType::DlgRename)
    {
        ui->m_lbTitle->setText(("重命名"));
        ui->l_name->setText(("新名称"));
        ui->label_address->setText(("原来的名称"));

        ui->lineEdit_name->setPlaceholderText("请输入新名称");
    }
    else if(type==DlgType::DlgMove)
    {
        ui->m_lbTitle->setText(("移动"));
        ui->l_name->setText(("新的路径"));
        ui->label_address->setText(("原始路径"));

        ui->lineEdit_name->setPlaceholderText("请输入移动路径");
    }

    else if(type==DlgType::DlgCopy)
    {
        ui->m_lbTitle->setText(("复制"));
        ui->l_name->setText(("新的路径"));
        ui->label_address->setText(("原始路径"));

        ui->lineEdit_name->setPlaceholderText("请输入复制的位置");
    }


}
void DlgFileOrFolder::initConnect()
{

}

QString DlgFileOrFolder::getPath() {

    QString path ="";

    if (ui->lineEdit_name->text().isEmpty())
    {
        return  "";
    }
    else{
        return   m_pixPath+"/"+ui->lineEdit_name->text();
    }
}


QString DlgFileOrFolder::getName()
{
    return  ui->lineEdit_name->text();
}

void DlgFileOrFolder::on_buttonBox_accepted()
{
    DlgFileOrFolder::accept();
}

