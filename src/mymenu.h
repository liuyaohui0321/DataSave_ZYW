#ifndef MYMENU_H
#define MYMENU_H

#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QWidget>
#include <QHBoxLayout>
#include <QPainter>
#include <QApplication>
#include <QPushButton>
#pragma execution_character_set("utf-8")

class MyMenu : public QMenu
{
    Q_OBJECT
public:
    explicit MyMenu(QWidget *parent = nullptr, QObject *receiver = nullptr);

    void addMenuItem(const QString &text, const QString &iconPath, const char *slot);
    void initUI();

    //void addMenuItem(const QString &text, const QString &iconPath, const char *slot);

private:
    QObject *m_receiver;  // 用于保存 MainWindow 的指针
};

#endif // MYMENU_H
