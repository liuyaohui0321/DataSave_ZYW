#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include <QDialog>

namespace Ui {
class udpWidget;
}

class udpWidget : public QDialog
{
    Q_OBJECT

public:
    explicit udpWidget(QWidget *parent = nullptr);
    ~udpWidget();
    QString m_ip;
    quint16 m_port;

private slots:
    void slot_connect();

signals:
    void sign_setNewConnectInfo();

private:
    Ui::udpWidget *ui;

};

#endif // UDPWIDGET_H
