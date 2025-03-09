#ifndef DLG_PERCENT_EXPORT_DATA_H
#define DLG_PERCENT_EXPORT_DATA_H

#include <QDialog>

namespace Ui {
class dlg_percent_export_data;
}

class dlg_percent_export_data : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_percent_export_data(const QString &path,QWidget *parent = nullptr);
    ~dlg_percent_export_data();
    void setPath(const QString &path);
    //获取选中的文件路径
    QString getLocalPath()
    {
        return m_pLocalPath;
    }
    int getExportType();
    int getExportPercent();
    int getExportCap();
private:
    void initUI();
    void initConnect();

private slots:
    void slotBtnExportClicked();//选择路径
    void slotBtnStartExportClicked();  //点击导出

signals:
    void accepted();
    void rejected();

private:
    Ui::dlg_percent_export_data *ui;
    QString m_pLocalPath;//本地路径
    QString m_pDsvPath;//存储版路径
};

#endif // DLG_PERCENT_EXPORT_DATA_H
