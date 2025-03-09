#include "mymenu.h"
#include <QDebug>

#pragma execution_character_set("utf-8")

MyMenu::MyMenu(QWidget *parent, QObject *receiver)
    : QMenu(parent), m_receiver(receiver)
{
    initUI();
}


// void MyMenu::addMenuItem(const QString &text, const QString &iconPath, const char *slot)
// {
//     QAction *action = new QAction(QIcon(iconPath), text, this);
//     action->setObjectName(text);  // 设置对象名称，方便调试

//     // 设置菜单项的文字和图标
//     action->setText(text);
//     action->setIcon(QIcon(iconPath));

//     // 添加动作到菜单
//     this->addAction(action);

//     // 连接信号槽
//     connect(action, SIGNAL(triggered()), this, slot);
// }



void MyMenu::initUI()
{
    // 创建菜单项
    addMenuItem("刷新", ":/images/refresh_icon.png", SLOT(onRefresh()));
    addMenuItem("打开", ":/images/open_icon.png", SLOT(onOpen()));
    addMenuItem("保存", ":/images/save_icon.png", SLOT(onSave()));
    addMenuItem("退出", ":/images/exit_icon.png", SLOT(onExit()));
}

void MyMenu::addMenuItem(const QString &text, const QString &iconPath, const char *slot)
{
    QAction *action = new QAction(QIcon(iconPath), text, this);
    action->setObjectName(text);  // 设置对象名称，方便调试

    // 添加动作到菜单
    this->addAction(action);

    // 连接信号槽，槽函数在 MainWindow 中
    connect(action, SIGNAL(triggered()), m_receiver, slot);
}
