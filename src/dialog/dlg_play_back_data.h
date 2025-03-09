#pragma  once

#include "dsv_define.h"
#include <QDialog>
#include "dlg_multifile_play_back.h"

namespace Ui {
class dlg_play_back_data;
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
    void setPath(const QString& path); // LYH 2.14

signals:
    void accepted();
    void rejected();
private slots:

    void slotBtnPlayBackClicked();
    void slotBtnStopPlayBackClicked();
    void slotBtnMultiFilePlayBackClicked();  //点击多文件回放

private:
    void initUI();
    void initConnect();

    Ui::dlg_play_back_data *ui;
    QString m_dsvFileName;//磁盘中文件名称
    int m_mode = -1;
};


