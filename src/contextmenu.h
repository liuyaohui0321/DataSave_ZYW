#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include <QObject>
#include "src/helper/dsv_define.h"

class QWidgetAction;
class QCheckBox;

class ContextMenu : public QMenu
{
    Q_OBJECT
public:
    explicit ContextMenu(QWidget *parent = nullptr);

signals:

    void sigRefresh();          //刷新
    void signalOpen();          //打开
    void signalClose();         //关闭
    void signalNewFolder();     // 新建文件夹
    void signalNewFile();       //新建文件
    void signalDelete();        //删除
    void signalMove();          //移动
    void signalCopy();          //复制
    void signalRename();        //重命名
    void signalWrite();         //写入
    void signalPlayback();      //回放
    void signalExport();        //导出
    void signalAcquisition();   //采集


private:
    /**
     * @brief 初始化界面
     */
    void initUI();
    /**
     * @brief 初始化槽函数连接
     */
    void initConnect();
    /**
     * @brief 创建菜单项
     */
    void createActions();

private:
    /**
     * @brief 创建action
     * @param  text：菜单文字
     * @param  iconurl：菜单图片
     * @param  shortCut：快捷键
     */
    QAction *createAction(const QString &text,
                          const QString &iconurl,
                          const QString &shortCut = "");

    /**
     * @brief 增加图标
     * @param  text：菜单文字
     * @param  iconurl：菜单图片
     * @param  menu：所属菜单
     * @param  shortCut：快捷键
     */
    void addLargeAction(const QString &text,
                        const QString &iconurl,
                        const char *slotAction,
                        const ButtonType &type,
                        QMenu *menu = nullptr,
                        const QString &shortCut = "");
};

#endif // CONTEXTMENU_H
