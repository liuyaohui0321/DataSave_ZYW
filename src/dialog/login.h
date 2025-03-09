#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>

namespace Ui
{
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public:
signals:
    void signal_mainshow();

private slots:
    void on_pbtn_login_clicked();

    void on_pbtn_logout_clicked();

    void on_pbtn_show_clicked();

    void hidePassword();

private:
    Ui::Login *ui;
    QTimer *timer;
};

#endif // LOGIN_H
