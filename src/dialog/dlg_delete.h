#ifndef DLG_DELETE_H
#define DLG_DELETE_H

#include <QDialog>
#include "dsv_define.h"
#include <QDebug>

namespace Ui {
class dlg_delete;
}

class dlg_delete : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_delete(const QString &name,QWidget *parent = nullptr);
    ~dlg_delete();
    //获取选中的文件路径
    QString getLocalPath();

    int getMode()
    {
        return m_mode;
    }
    void setPath(const QString& path); // LYH 2.19
    void LineEditSet(void);// LYH 2.21
    void Dialog_Set(const QString &path);// LYH 2.21
signals:
    void accepted();
    void rejected();

private slots:
    void on_deleteButton_clicked();

private:
    void initUI();
    void initConnect();
    Ui::dlg_delete *ui;
    QString m_dsvFileName;//磁盘中文件名称
    int m_mode = -1;
};

#endif // DLG_DELETE_H
