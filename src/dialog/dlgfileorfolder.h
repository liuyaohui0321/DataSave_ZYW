#ifndef DLGFILEORFOLDER_H
#define DLGFILEORFOLDER_H

#include <QDialog>
#include "../helper/dsv_define.h"

namespace Ui {
class DlgFileOrFolder;
}

class DlgFileOrFolder : public QDialog
{
    Q_OBJECT

public:
    explicit DlgFileOrFolder(DlgType type, const QString &pixPath, QWidget *parent = nullptr);
    ~DlgFileOrFolder();

    //获取文件夹路径
    QString getPath();

    //获取名称
    QString getName();


private slots:
    void on_buttonBox_accepted();

private:
    void initUI(DlgType type);
    void initConnect();


private:
    Ui::DlgFileOrFolder *ui;
    QString m_pixPath ="";//路径前缀
};

#endif // DLGFILEORFOLDER_H
