#ifndef DLGEXPORTDATA_H
#define DLGEXPORTDATA_H

#include <QDialog>

namespace Ui {
class DlgExportData;
}

class DlgExportData : public QDialog
{
    Q_OBJECT

public:
    explicit DlgExportData(const QString &path,QWidget *parent = nullptr);
    ~DlgExportData();

    //获取选中的文件路径
    QString getLocalPath()
    {
        return m_pLocalPath;
    }

    bool getIfMvpp()
    {
        return isMvpp;
    }

    double m_power,m_hz;

    int getExportType();    //获取千兆网还是万兆网

private slots:
    void slotBtnExportClicked();        //选择路径
    void slotBtnStartExportClicked();   //点击导出
    void slotBtnMvppExportClicked();    //使用mvpp模式导出数据

private:
    void initUI();
    void initConnect();

private:
    Ui::DlgExportData *ui;
    QString m_pLocalPath;//本地路径
    QString m_pDsvPath;//存储版路径
    //QString m_name;

    bool isMvpp;
};

#endif // DLGEXPORTDATA_H
