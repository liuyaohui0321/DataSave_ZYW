#include "mainwindow.h"

#include <QApplication>
#include <QSysInfo>
#include <QScreen>
#include <QDebug>
#include <QFile>
#include <QLibraryInfo>
#include <QTranslator>


int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
    // // 创建翻译器对象
    // QTranslator translator;

    // // 加载 Qt 自带的中文翻译文件
    // if (translator.load(":/my/qt_zh_CN.qm", QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
    //     a.installTranslator(&translator);
    // }

    MainWindow w;
#if dbug
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize size = screen->size();
    qDebug() << "主屏幕大小:" << size;
#endif
    w.setWindowTitle("数据采集存储控制系统");

    QFile file(":/my/dsv.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
    qRegisterMetaType<Cmd_Disk_State_Info>("Cmd_Disk_State_Info");
    w.show();
    return a.exec();
}
