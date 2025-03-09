#ifndef DLG_ACQUISITION_H
#define DLG_ACQUISITION_H

#include <QDialog>

namespace Ui {
class dlg_acquisition;
}

class dlg_acquisition : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_acquisition(const QString &name,QWidget *parent = nullptr);
    ~dlg_acquisition();

    //获取选中的文件路径
    QString getLocalPath();

    int getMode()
    {
        return m_mode;
    }

private slots:
    void slotBtnAcquisitionClicked();
    void slotBtnStopAcquisitionClicked();

private:
    Ui::dlg_acquisition *ui;
    QString m_pLocalPath;//本地路径
    int m_mode = -1;
};

#endif // DLG_ACQUISITION_H
