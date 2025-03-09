#ifndef DISKCONFIRM_H
#define DISKCONFIRM_H

#include <QWidget>

namespace Ui {
class DiskConfirm;
}

class DiskConfirm : public QWidget
{
    Q_OBJECT

public:
    explicit DiskConfirm(QWidget *parent = nullptr);
    ~DiskConfirm();

private slots:
    void on_pbtn_ok_clicked();

signals:
    void sig_disk_check(bool b);

private:
    Ui::DiskConfirm *ui;
};

#endif // DISKCONFIRM_H
