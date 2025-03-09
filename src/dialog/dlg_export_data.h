#ifndef DLG_EXPORT_DATA_H
#define DLG_EXPORT_DATA_H

#include <QDialog>

#include <QDialog>

namespace Ui {
class dlg_export_data;
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

    int getMode()
    {
        return m_mode;
    }
    int getExportType();
    void setPath(const QString &path);

signals:
    void accepted();
    void rejected();

private slots:
    void slotBtnExportClicked();//选择路径
    void slotBtnStartExportClicked();  //点击导出
    void slotBtnPercentExportClicked();//点击百分比导出
    void slotBtnPiliangExportClicked();//点击批量导出

private:
    void initUI();
    void initConnect();

private:
    Ui::dlg_export_data *ui;
    QString m_pLocalPath;//本地路径
    QString m_pDsvPath;//存储版路径
    int m_mode = -1;
};

#endif // DLG_EXPORT_DATA_H
