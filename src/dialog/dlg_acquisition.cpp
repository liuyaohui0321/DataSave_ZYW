#include "dlg_acquisition.h"
#include "ui_dlg_acquisition.h"
#include  <QMessageBox>

dlg_acquisition::dlg_acquisition(const QString &name,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dlg_acquisition)
{
    ui->setupUi(this);
    ui->m_leName->setText(name);

    connect(ui->pushButton,&QPushButton::clicked,this,&dlg_acquisition::slotBtnAcquisitionClicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&dlg_acquisition::slotBtnStopAcquisitionClicked);
}

dlg_acquisition::~dlg_acquisition()
{
    delete ui;
}

QString dlg_acquisition::getLocalPath()
{
    return ui->m_leName->text();
}

void dlg_acquisition::setPath(const QString &path)
{
    ui->m_leName->setText(path);// 设置路径到输入框  LYH 2.14
}

void dlg_acquisition::slotBtnAcquisitionClicked()
{
    m_pLocalPath =   ui->m_leName->text();
    if(m_pLocalPath.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
        return;
    }
    else{
        m_mode = 1;
//        dlg_acquisition::accept();
        emit accepted(); //LYH 2.14
        close();
    }
}

void dlg_acquisition::slotBtnStopAcquisitionClicked()
{
    m_pLocalPath =   ui->m_leName->text();
    if(m_pLocalPath.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("请选择路径"));
        return;
    }
    else{
        m_mode = 2;
//        dlg_acquisition::accept();
        emit accepted();
        close();
    }
}
