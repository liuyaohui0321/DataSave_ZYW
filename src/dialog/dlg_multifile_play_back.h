#ifndef DLG_MULTIFILE_PLAY_BACK_H
#define DLG_MULTIFILE_PLAY_BACK_H

#include <QDialog>
#include "dsv_define.h"

namespace Ui {
class dlg_multifile_play_back;
}

class dlg_multifile_play_back : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_multifile_play_back(const QString &name,QWidget *parent = nullptr);
    ~dlg_multifile_play_back();
//    //获取读取模式
//    int getReadMode();

//    //获取循环回读次数
//    int getLoopCnt();

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
    void slotBtnPlayBackClicked();  //点击开始回放

private:
    void initUI();
    void initConnect();

    Ui::dlg_multifile_play_back *ui;
    QString m_dsvFileName;//磁盘中文件名称
    int m_mode = -1;
};

#endif // DLG_MULTIFILE_PLAY_BACK_H
