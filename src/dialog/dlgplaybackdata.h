#ifndef DLGPLAYBACKDATA_H
#define DLGPLAYBACKDATA_H

#include <QDialog>
#include "../helper/dsv_define.h"

namespace Ui {
class DlgPlayBackData;
}

class DlgPlayBackData : public QDialog
{
    Q_OBJECT

public:
    explicit DlgPlayBackData(const QString &name,QWidget *parent = nullptr);
    ~DlgPlayBackData();

    //获取读取模式
    int getReadMode();

    //获取循环回读次数
    int getLoopCnt();

    //获取读取模式
    int getPlaybackChannel();

    int getMode()
    {
        return m_mode;
    }

private slots:

    void slotBtnPlayBackClicked();  //点击开始写入
    void slotBtnStopPlayBackClicked();  //点击停止写入

private:
    void initUI();
    void initConnect();
    Ui::DlgPlayBackData *ui;
    QString m_dsvFileName;//磁盘中文件名称
    int m_mode = -1;
};

#endif // DLGPLAYBACKDATA_H
