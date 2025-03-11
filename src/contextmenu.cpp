#include "contextmenu.h"
#include <QUrl>
#include <QDesktopServices>
#include <QWidgetAction>
#include <QCheckBox>
#include <memory>

#pragma execution_character_set("utf-8")

ContextMenu::ContextMenu(QWidget *widget): QMenu(widget)
{
    initUI();
    initConnect();
}

void ContextMenu::createActions()
{
    addLargeAction(tr("刷新"), ":/my/images/refurbish_primary_blue.png", SIGNAL(sigRefresh()),ButtonType::Refresh);
    this->addSeparator();
    addLargeAction(tr("打开"), ":/my/images/folder_open_primary_blue.png", SIGNAL(signalOpen()),ButtonType::Open);
    addLargeAction(tr("关闭"), ":/my/images/close_rectangle_primary_blue.png", SIGNAL(signalClose()),ButtonType::Close);

    this->addSeparator();
    addLargeAction("新建文件夹", ":/my/images/folder_add_primary_blue.png", SIGNAL(signalNewFolder()),ButtonType::AddFolder);
    addLargeAction(tr("新建文件"), ":/my/images/file_add_primary_blue.png", SIGNAL(signalNewFile()),ButtonType::AddFile);
    addLargeAction(tr("删除"), ":/my/images/delete_fill_primary_blue.png", SIGNAL(signalDelete()),ButtonType::Delete);
    this->addSeparator();

    addLargeAction(tr("移动"), ":/my/images/move_primary_blue.png", SIGNAL(signalMove()),ButtonType::Move);
    addLargeAction(tr("复制"), ":/my/images/file_copy_primary_blue.png", SIGNAL(signalCopy()),ButtonType::Copy);
    addLargeAction(tr("重命名"), ":/my/images/report_forms_primary_blue.png", SIGNAL(signalRename()),ButtonType::Rename);

    this->addSeparator();
//    addLargeAction(tr("写入"), ":/my/images/edit_2_primary_blue.png", SIGNAL(signalWrite()),ButtonType::Write);
    addLargeAction(tr("回放"), ":/my/images/chevron_right_double_primary_blue.png", SIGNAL(signalPlayback()),ButtonType::PlayBack);
    addLargeAction(tr("导出"), ":/my/images/note_transpond_primary_blue.png", SIGNAL(signalExport()),ButtonType::Export);
    addLargeAction(tr("采集"), ":/my/images/edit_2_primary_blue.png", SIGNAL(signalAcquisition()),ButtonType::Acquisition);

}

void ContextMenu::initUI()
{
    this->createActions();
    this->setObjectName("main_menu");
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
}

void ContextMenu::initConnect()
{
}

QAction* ContextMenu::createAction(const QString &text,
                                   const QString &iconurl,
                                   const QString &shortCut )
{
    QAction *act = new QAction(this);
    act->setText(text);

    act->setIcon(QIcon(iconurl));

    act->setObjectName(text);
    if (!shortCut.isEmpty())
    {
        act->setShortcut(QKeySequence(shortCut));
    }
    return act;
}

void ContextMenu::addLargeAction(const QString &text,
                                 const QString &iconurl,
                                 const char *slotAction,
                                 const ButtonType &type,
                                 QMenu *menu,
                                 const QString &shortCut )
{
    QAction *action = createAction(text, iconurl, shortCut);
    action->setData(static_cast<int>(type));

    if (nullptr == menu){
        this->addAction(action);
    }else{
        menu->addAction(action);
    }
    connect(action, SIGNAL(triggered()), this, slotAction);

}

