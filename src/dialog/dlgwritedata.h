#ifndef DLGWRITEDATA_H
#define DLGWRITEDATA_H

#include <QDialog>
#pragma execution_character_set("utf-8")

namespace Ui {
class DlgWriteData;
}

class DlgWriteData : public QDialog
{
    Q_OBJECT

public:
    explicit DlgWriteData(const QString &path,QWidget *parent = nullptr);
    ~DlgWriteData();

    //获取一共有多少包
    qint64 getPackageNum()
    {
        return m_packageNum;
    }

    //获取选中的文件路径
    QString getLocalPath()
    {
        return m_pLocalPath;
    }

private slots:
    void slotBtnChooseDataPathClicked();  //选择windows下的要写入的文件
    void slotBtnWriteClicked();  //点击开始写入

private:
    Ui::DlgWriteData *ui;

    void initUI();
    void initConnect();
    QString m_pPath;//文件路径
    qint64 m_packageNum = 0 ;//选中的文件有多少包

    QString m_pLocalPath;//选中的本地文件路径
};

#endif // DLGWRITEDATA_H
