#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

    //菜单栏样式配置
    menubarInit();
    //状态栏设置
    statebarInit();

}

MainWindow::~MainWindow()
{
    if(m_tcpWorkThread->isRunning())
    {
        m_tcpWorkThread->quit();
        m_tcpWorkThread->wait();
    }
    delete ui;
}

//菜单栏配置函数
void MainWindow::menubarInit()
{
    //磁盘管理
    auto disk_manager =  ui->menubar->addMenu("磁盘管理");
    auto *diskOneAction = new QAction(QIcon(":/my/images/disk.png"), tr("磁盘格式化"), this);
    auto *diskTwoAction = new QAction(QIcon(":/my/images/disk.png"), tr("磁盘重新挂载"), this);
    auto *diskThreeAction = new QAction(QIcon(":/my/images/disk.png"), tr("磁盘解挂载"), this);

    disk_manager->addAction(diskOneAction);
    disk_manager->addAction(diskTwoAction);
    disk_manager->addSeparator();       //添加分割线
    disk_manager->addAction(diskThreeAction);

    auto connect_manager = ui->menubar->addMenu("连接配置");
    auto *tcpAction = new QAction("千兆网连接配置",this);
    auto *udpAction = new QAction("万兆网连接配置",this);
    connect_manager->addAction(tcpAction);
    connect_manager->addAction(udpAction);

    connect(udpAction,&QAction::triggered,this,&MainWindow::slot_udpInfo);

    connect(diskOneAction, &QAction::triggered, this, &MainWindow::slot_diskFormat);
    connect(diskTwoAction, &QAction::triggered, this, &MainWindow::slot_diskAgainMount);
    connect(diskThreeAction, &QAction::triggered, this, &MainWindow::slot_diskUnmount);

    // 创建一个包含 QLabel 的 QWidget
    QWidget *rightWidget = new QWidget(this);

    QHBoxLayout *hbox = new QHBoxLayout(rightWidget);
    hbox->addStretch(); // 添加弹性空间，将 QLabel 推到右侧

    m_pSocklLabel = new QLabel("等待千兆网连接", this);
    m_pSocklLabel->setFixedSize(180,32);
    m_pSocklLabel->setStyleSheet(
        "background-color: yellow; "
        "color: red; "
        "font-family: 'SimHei'; "
        "font-size: 14pt; "
        "font-weight: bold;"
        );

    m_udpLabel = new QLabel("等待万兆网连接",this);
    m_udpLabel->setFixedSize(180,32);
    m_udpLabel->setStyleSheet(
        "background-color: yellow; "
        "color: red; "
        "font-family: 'SimHei'; "
        "font-size: 14pt; "
        "font-weight: bold;"
        );

    hbox->addWidget(m_pSocklLabel);
    hbox->addSpacing(50);
    hbox->addWidget(m_udpLabel);
    hbox->setContentsMargins(0, 0, 20, 0); // 去掉布局的边距

    // 将包含 QLabel 的 QWidget 添加到 QMenuBar
    ui->menubar->setCornerWidget(rightWidget, Qt::TopRightCorner);

}


//状态栏设置
void MainWindow::statebarInit() {
    // 创建一个状态栏
    //QStatusBar *statusBar = ui->statusbar;

    // 在状态栏上添加控件
    QLabel *totalLabel = new QLabel("总容量:", this);
    totalShow = new QLabel(this);
    totalShow->setFixedWidth(60);
    QLabel *GBLabel1 = new QLabel("MB", this);
    QLabel *usedLabel = new QLabel("已用容量:", this);
    usedShow = new QLabel(this);
    usedShow->setFixedWidth(60);
    QLabel *GBLabel2 = new QLabel("MB", this);
    QLabel *restLabel = new QLabel("剩余容量:", this);
    restShow = new QLabel(this);
    restShow->setFixedWidth(60);
    QLabel *GBLabel3 = new QLabel("MB", this);
    QLabel *fileNumLabel = new QLabel("文件数量:", this);
    fileNumShow = new QLabel(this);
    fileNumShow->setFixedWidth(50);
    QLabel *stateLabel = new QLabel("工作状态:", this);
    stateShow = new QLabel(this);
    stateShow->setFixedWidth(70);
    QLabel *tLabel = new QLabel("温度:", this);
    tShow = new QLabel(this);
    tShow->setFixedWidth(50);
    QLabel *T = new QLabel("℃", this);
    QLabel *powerLabel = new QLabel("功耗:", this);
    powerShow = new QLabel(this);
    powerShow->setFixedWidth(50);
    QLabel *W = new QLabel("W", this);
    QLabel *kaijiLabel = new QLabel("存盘速度:", this);
    kaijiShow = new QLabel(this);
    kaijiShow->setFixedWidth(50);
    QLabel *ci = new QLabel("MB/s", this);
    pbtn_stateBarRefresh = new QPushButton("刷新磁盘状态", this);
    pbtn_stateBarRefresh->setFixedWidth(120);
    //状态栏的刷新
    connect(pbtn_stateBarRefresh, &QPushButton::clicked, this, &MainWindow::slot_stateBarRefresh);

    QLabel *spacer1 = new QLabel();
    spacer1->setFixedWidth(30);
    QLabel *spacer2 = new QLabel();
    spacer2->setFixedWidth(30);
    QLabel *spacer3 = new QLabel();
    spacer3->setFixedWidth(30);
    QLabel *spacer4 = new QLabel();
    spacer4->setFixedWidth(30);
    QLabel *spacer5 = new QLabel();
    spacer5->setFixedWidth(30);
    QLabel *spacer6 = new QLabel();
    spacer6->setFixedWidth(30);
    QLabel *spacer7 = new QLabel();
    spacer7->setFixedWidth(30);
    QLabel *spacer8 = new QLabel();
    spacer8->setFixedWidth(30);

    //将添加的控件放到状态栏上
    ui->statusbar->addWidget(totalLabel);
    ui->statusbar->addWidget(totalShow);
    ui->statusbar->addWidget(GBLabel1);
    ui->statusbar->addWidget(spacer1);

    ui->statusbar->addWidget(usedLabel);
    ui->statusbar->addWidget(usedShow);
    ui->statusbar->addWidget(GBLabel2);
    ui->statusbar->addWidget(spacer2);

    ui->statusbar->addWidget(restLabel);
    ui->statusbar->addWidget(restShow);
    ui->statusbar->addWidget(GBLabel3);
    ui->statusbar->addWidget(spacer3);

    ui->statusbar->addWidget(fileNumLabel);
    ui->statusbar->addWidget(fileNumShow);
    ui->statusbar->addWidget(spacer4);

    ui->statusbar->addWidget(stateLabel);
    ui->statusbar->addWidget(stateShow);
    ui->statusbar->addWidget(spacer5);

    ui->statusbar->addWidget(tLabel);
    ui->statusbar->addWidget(tShow);
    ui->statusbar->addWidget(T);
    ui->statusbar->addWidget(spacer6);

    ui->statusbar->addWidget(powerLabel);
    ui->statusbar->addWidget(powerShow);
    ui->statusbar->addWidget(W);
    ui->statusbar->addWidget(spacer7);

    ui->statusbar->addWidget(kaijiLabel);
    ui->statusbar->addWidget(kaijiShow);
    ui->statusbar->addWidget(ci);
    ui->statusbar->addWidget(spacer8);

    ui->statusbar->addWidget(pbtn_stateBarRefresh);
}


void MainWindow::init()
{
    //m_pSocklLabel = new QLabel(this);
    //m_pSocklBtn = new QPushButton(this);


    //初始化右键菜单栏
    m_pContextMenu = new ContextMenu(this);
    //右键菜单操作
    connect(m_pContextMenu, &ContextMenu::sigRefresh, this, &MainWindow::slotRefresh);
    connect(m_pContextMenu, &ContextMenu::signalNewFolder, this, &MainWindow::slotFolder);
    connect(m_pContextMenu, &ContextMenu::signalNewFile, this, &MainWindow::slotFile);
    connect(m_pContextMenu, &ContextMenu::signalDelete, this, &MainWindow::slotDelete);
    connect(m_pContextMenu, &ContextMenu::signalOpen, this, &MainWindow::slotOpen);
    connect(m_pContextMenu, &ContextMenu::signalClose, this, &MainWindow::slotClose);
    connect(m_pContextMenu, &ContextMenu::signalRename, this, &MainWindow::slotRename);
    connect(m_pContextMenu, &ContextMenu::signalMove, this, &MainWindow::slotMove);
    connect(m_pContextMenu, &ContextMenu::signalCopy, this, &MainWindow::slotCopy);
    connect(m_pContextMenu, &ContextMenu::signalExport, this, &MainWindow::slotExport);
    connect(m_pContextMenu, &ContextMenu::signalWrite, this, &MainWindow::slotWrite);
    connect(m_pContextMenu, &ContextMenu::signalPlayback, this, &MainWindow::slotPlayBack);
    connect(m_pContextMenu, &ContextMenu::signalAcquisition, this, &MainWindow::slotAcquisition);

    ui->treeView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);// 启用自定义菜单
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    //树操作
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::slot_CustomContextMenuRequested);
    //connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::showMenu);
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::slot_onItemSelected);

    m_tcp = new TCPThread();
    m_tcpWorkThread = new QThread(this);
    m_tcp->moveToThread(m_tcpWorkThread);
    m_tcpWorkThread->start();
    connect(m_tcp,&TCPThread::sign_waitConnect,this,[=](){
        //qDebug() << "Server started!" << DSV_PORT;
        QString log = QString("%1: 服务器等待连接中...").arg(getNowTime());
        ui->textBrowser_log->append(log);
    });
    connect(m_tcp,&TCPThread::sign_getNewConnect,this,&MainWindow::slot_haveNewConnection);
    connect(this,&MainWindow::sign_sendCmd,m_tcp,&TCPThread::slot_getCmd);
    connect(m_tcp,&TCPThread::sign_tcpNotConnect,this,[=](){
        QString log = QString("%1: 传输连接并未建立，请等待连接建立完成后，再进行操作！！！").arg(getNowTime());
        ui->textBrowser_log->append(log);
    });
    connect(m_tcp,&TCPThread::sign_tellMainDisconnect,this,[=](){
        m_pSocklLabel->setText("当前千兆网连接已断开");
        m_pSocklLabel->setFixedSize(220,32);
        m_pSocklLabel->setStyleSheet(
            "background-color: yellow; "
            "color: red; "
            "font-family: 'SimHei'; "
            "font-size: 14pt; "
            "font-weight: bold;"
            );

        QString log = QString("当前千兆网连接已断开").arg(getNowTime());
        ui->textBrowser_log->append(log);
    });

    //解析的应答帧
    connect(m_tcp,&TCPThread::sign_diskData,this,&MainWindow::slot_recvDiskData);
    connect(m_tcp,&TCPThread::sign_sendDirectoryParser,this,&MainWindow::slot_StandardItemModel);
    //connect(m_tcp,&TCPThread::sign_commonData,this,&MainWindow::slot_recvCommonRespon);
    connect(m_tcp,&TCPThread::sign_newCommonData,this,&MainWindow::slot_newrecvCommonRespon);


    connect(this,&MainWindow::sign_addTcpFileHead,m_tcp,&TCPThread::slot_addTcpHead);
    connect(m_tcp,&TCPThread::sign_speed,this,&MainWindow::slot_showSpeed);

    m_udpInfoWidget = new udpWidget(this);
    m_udpInfoWidget->hide();

    m_udp = new UDPThread();
    m_udpWorkThread = new QThread(this);
    //m_udp->moveToThread(m_udpWorkThread);
    //m_udpWorkThread->start();

    connect(m_udpInfoWidget,&udpWidget::sign_setNewConnectInfo,this,[=](){
        QString ip = m_udpInfoWidget->m_ip;
        quint16 port = m_udpInfoWidget->m_port;
        m_udp->startConnect(ip,port);
    });
    connect(m_udp,&UDPThread::sign_tellMainUdpDisconnect,this,[=](){
        m_udpLabel->setText("当前万兆网连接已断开");
        m_udpLabel->setFixedSize(220,32);
        m_udpLabel->setStyleSheet(
            "background-color: yellow; "
            "color: red; "
            "font-family: 'SimHei'; "
            "font-size: 14pt; "
            "font-weight: bold;"
            );

        QString log = QString("当前千兆网连接已断开").arg(getNowTime());
        ui->textBrowser_log->append(log);
    });
    connect(m_udp,&UDPThread::sign_mainShowUDP,this,&MainWindow::slot_haveNewUdpConnect);
    connect(this,&MainWindow::sign_addUdpFileHead,m_udp,&UDPThread::slot_addHead);
    connect(this,&MainWindow::sign_setUdpFilePath,m_udp,&UDPThread::slot_setPath);

    connect(m_udp,&UDPThread::sign_recvFinished,this,[=](){
        QString log = QString("万兆网导出数据完成").arg(getNowTime());
        ui->textBrowser_log->append(log);
    });

}

void MainWindow::slotRefresh()
{
    //qDebug()<<"---------刷新目录列表操作---------";

    QString time = getNowTime();
    QString log = QString("%1: 展示存储版下所有文件和文件夹.").arg(time);
    ui->textBrowser_log->append(log);

    //下发的内容
    Cmd_Folder_And_File_Info cmd_folder_and_file_info;
    cmd_folder_and_file_info.order_head = ORDERHEAD;
    cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
    cmd_folder_and_file_info.source_ID = 0;
    cmd_folder_and_file_info.dest_ID = 0;
    cmd_folder_and_file_info.oper_type = 0xA2;
    cmd_folder_and_file_info.oper_ID = 0x01;
    cmd_folder_and_file_info.package_num = 0;
    cmd_folder_and_file_info.fun_type = 0x13;   //13.获取目录中的文件和子目录列表（dir）
    cmd_folder_and_file_info.fun_para1[1024] = {0};
    QString temp_para1 = "0:";
    std::u16string utf16Str_para1 = temp_para1.toStdU16String();
    size_t length1 = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i) {
        if (i < length1)
            cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
        else
            cmd_folder_and_file_info.fun_para1[i] = 0;
    }
    cmd_folder_and_file_info.fun_para2[1024] = {0};
    cmd_folder_and_file_info.check = 0;
    cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));
    //qDebug()<<sendData.toHex();

    emit sign_sendCmd(sendData);

}

void MainWindow::slotFolder()
{
    //qDebug()<<"新增文件夹操作";
    if (m_TreeItemInfo.type == ItemType::Folder) {
        DlgFileOrFolder dlg(DlgType::DlgFolder, m_TreeItemInfo.path, this);
        if (dlg.exec() == QDialog::Accepted) {
            if (dlg.getName().isEmpty()) {
                QMessageBox::critical(this, tr("新增文件夹失败"), tr("名称为空，不可新增"));
            } else {
                addNewFolder(dlg.getName(), m_TreeItemInfo.path);
            }
        } else {
            //点击取消
        }
    } else {
        QMessageBox::critical(this, tr("新增文件失败"), tr("当前项是文件，无法新增文件夹，请重新选择"));
        QString log = QString("%1:当前项是文件，无法新增文件夹，请重新选择.").arg(getNowTime());
        ui->textBrowser_log->append(log);
    }

}

void MainWindow::addNewFolder(const QString &name, const QString &path)
{
    //qDebug() << "新建文件夹.";

    //下发的内容
    Cmd_Folder_And_File_Info cmd_folder_and_file_info;
    cmd_folder_and_file_info.order_head = ORDERHEAD;
    cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
    cmd_folder_and_file_info.source_ID = 0;
    cmd_folder_and_file_info.dest_ID = 0;
    cmd_folder_and_file_info.oper_type = 0xA2;
    cmd_folder_and_file_info.oper_ID = 0x01;
    cmd_folder_and_file_info.package_num = 0;
    cmd_folder_and_file_info.fun_type = 0x02;   //新建文件夹
    cmd_folder_and_file_info.fun_para1[1024] = {0};
    QString temp_para1 = path + "/" + name;
    std::u16string utf16Str_para1 = temp_para1.toStdU16String();
    size_t length = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i) {
        if (i < length)
            cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
        else
            cmd_folder_and_file_info.fun_para1[i] = 0;
    }
    cmd_folder_and_file_info.fun_para2[1024] = {0};
    cmd_folder_and_file_info.check = 0;
    cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));


    QString log = QString("%1:正在执行新建文件夹[%2]操作.").arg(getNowTime().arg(name));
    ui->textBrowser_log->append(log);

    //记录操作类型
    lastOrderType = TYPE::ADDFOLDER;
    emit sign_sendCmd(sendData);

}

void MainWindow::slotFile()
{
    //qDebug()<<"新增文件操作";
    if (m_TreeItemInfo.type == ItemType::Folder)
    {
        DlgFileOrFolder dlg(DlgType::DlgFile, m_TreeItemInfo.path, this);
        if (dlg.exec() == QDialog::Accepted)
        {
            if (dlg.getName().isEmpty())
            {
                QMessageBox::critical(this, tr("新增文件失败"), tr("名称为空，不可新增"));
            }
            else
            {
                addNewFile(dlg.getName(), m_TreeItemInfo.path);
            }
        } else {
            //点击取消
        }
    } else {
        QMessageBox::critical(this, tr("新增文件失败"), tr("当前项是文件，无法新增文件，请重新选择"));
        QString log = QString("%1:当前项是文件，无法新增文件，请重新选择.").arg(getNowTime());
        ui->textBrowser_log->append(log);
    }
}

//新建文件
void MainWindow::addNewFile(const QString &name, const QString &path)
{
    //qDebug() << "新建文件.";
    qDebug()<<"新建文件的名字 = "<<name;
    //下发的内容
    Cmd_Folder_And_File_Info cmd_folder_and_file_info;
    cmd_folder_and_file_info.order_head = ORDERHEAD;
    cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
    cmd_folder_and_file_info.source_ID = 0;
    cmd_folder_and_file_info.dest_ID = 0;
    cmd_folder_and_file_info.oper_type = 0xA2;
    cmd_folder_and_file_info.oper_ID = 0x01;
    cmd_folder_and_file_info.package_num = 0;
    cmd_folder_and_file_info.fun_type = 0x01;       //新建文件
    cmd_folder_and_file_info.fun_para1[1024] = {};
    QString temp_para1 = path + "/" + name;
    std::u16string utf16Str_para1 = temp_para1.toStdU16String();
    size_t length = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i) {
        if (i < length)
            cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
        else
            cmd_folder_and_file_info.fun_para1[i] = 0;
    }
    cmd_folder_and_file_info.fun_para2[1024] = {0};
    cmd_folder_and_file_info.check = 0;
    cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

    QString log = QString("%1:正在执行新建文件[%2]操作.").arg(getNowTime()).arg(name);
    ui->textBrowser_log->append(log);

    //记录操作类型
    lastOrderType = TYPE::ADDFILE;
    emit sign_sendCmd(sendData);
}

void MainWindow::slotOpen()    //打开
{
    //qDebug()<<"打开操作";
}

//选中一个文件或者文件夹进行删除
void MainWindow::slotDelete()
{
    auto ret = QMessageBox::information(this, "确认是否删除", "是否确定删除，删除后不可恢复",
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (ret == QMessageBox::No) {
        return;
    }

    //qDebug() << "删除操作.";

    if (m_TreeItemInfo.type == Folder)    //删除文件夹
    {
        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x04;   //删除文件夹 4
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.path;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }
        cmd_folder_and_file_info.fun_para2[1024] = {0};
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

        QString log = QString("%1:正在执行删除文件夹[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::DELETE;
        emit sign_sendCmd(sendData);
    }
    else if (m_TreeItemInfo.type == File)      //删除文件
    {
        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x03;   //删除文件 3
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.path;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }
        cmd_folder_and_file_info.fun_para2[1024] = {0};
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

        QString log = QString("%1:正在执行删除文件[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::DELETE;
        emit sign_sendCmd(sendData);
    } else {
        //qDebug() << "文件类型错误！";
    }

}
void MainWindow::slotClose()   //关闭文件
{
    //qDebug()<<"关闭文件操作";
}

void MainWindow::slotRename() //重命名
{
    //qDebug()<<"重命名操作";
    DlgFileOrFolder dlg(DlgType::DlgRename, m_TreeItemInfo.name, this);
    if (dlg.exec() == QDialog::Accepted) {
        if (dlg.getName().isEmpty()) {
            QMessageBox::critical(this, tr("重命名失败"), tr("名称为空，不可重命名"));
        } else {
            reName(dlg.getName());
        }
    } else {
        //点击取消
    }
}

//重命名的具体操作
void MainWindow::reName(const QString &newname)
{
    //下发指令
    if (m_TreeItemInfo.type == Folder)    //重命名文件夹
    {
        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x06;   //6.文件夹重命名（ren）；
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.path;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length1 = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length1)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }

        cmd_folder_and_file_info.fun_para2[1024] = {0};
        QString temp_para2 = m_TreeItemInfo.prefixPath + "/" + newname;
        std::u16string utf16Str_para2 = temp_para2.toStdU16String();
        size_t length2 = utf16Str_para2.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length2)
                cmd_folder_and_file_info.fun_para2[i] = utf16Str_para2[i];
            else
                cmd_folder_and_file_info.fun_para2[i] = 0;
        }
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

        QString log = QString("%1:正在执行重命名文件夹[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::RENAME;
        emit sign_sendCmd(sendData);
    }
    else if (m_TreeItemInfo.type == File)     //重命名文件
    {
        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x05;   //5.文件重命名（ren）
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.prefixPath + "/" + m_TreeItemInfo.name;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length1 = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length1)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }
        cmd_folder_and_file_info.fun_para2[1024] = {0};
        QString temp_para2 = m_TreeItemInfo.prefixPath + "/" + newname;
        std::u16string utf16Str_para2 = temp_para2.toStdU16String();
        size_t length2 = utf16Str_para2.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length2)
                cmd_folder_and_file_info.fun_para2[i] = utf16Str_para2[i];
            else
                cmd_folder_and_file_info.fun_para2[i] = 0;
        }
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info)); 

        QString log = QString("%1:正在执行重命名文件[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::RENAME;
        emit sign_sendCmd(sendData);
    }
}

void MainWindow::slotMove() //移动
{
    //qDebug()<<"移动操作";
    DlgFileOrFolder dlg(DlgType::DlgMove, m_TreeItemInfo.path, this);
    if (dlg.exec() == QDialog::Accepted) {
        if (dlg.getName().isEmpty()) {
            QMessageBox::critical(this, tr("移动失败"), tr("路径为空，不可重命名"));
        } else {
            moveFileOrFolder(dlg.getName());
        }
    } else {
        //点击取消
    }
}

//移动操作
void MainWindow::moveFileOrFolder(const QString &newpath)
{
    //qDebug() << "移动操作在这里执行。";
    if (m_TreeItemInfo.type == File)
    {
        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x08;   //8.移动文件（move）
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.prefixPath + "/" + m_TreeItemInfo.name;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length1 = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length1)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }

        cmd_folder_and_file_info.fun_para2[1024] = {0};
        QString temp_para2 = newpath + "/" + m_TreeItemInfo.name;    //填充新文件目录，不用名字？
        std::u16string utf16Str_para2 = temp_para2.toStdU16String();
        size_t length2 = utf16Str_para2.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length2)
                cmd_folder_and_file_info.fun_para2[i] = utf16Str_para2[i];
            else
                cmd_folder_and_file_info.fun_para2[i] = 0;
        }
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

        QString log = QString("%1:正在执行移动文件[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::MOVE;
        emit sign_sendCmd(sendData);

    }
    else if (m_TreeItemInfo.type == Folder)  //--------------------- 移动文件夹 -----------------------------
    {
        //qDebug() << "移动文件夹";
        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x07;   //7.移动文件夹（move）
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.prefixPath + "/" + m_TreeItemInfo.name;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length1 = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length1)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }

        cmd_folder_and_file_info.fun_para2[1024] = {0};
        QString temp_para2 = newpath + "/" + m_TreeItemInfo.name;    //填充新文件目录，不用名字？
        std::u16string utf16Str_para2 = temp_para2.toStdU16String();
        size_t length2 = utf16Str_para2.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length2)
                cmd_folder_and_file_info.fun_para2[i] = utf16Str_para2[i];
            else
                cmd_folder_and_file_info.fun_para2[i] = 0;
        }
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

        QString log = QString("%1:正在执行移动文件夹[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::MOVE;
        emit sign_sendCmd(sendData);
    }
}

void MainWindow::slotCopy() //复制
{
    //qDebug()<<"复制操作";
    DlgFileOrFolder dlg(DlgType::DlgCopy, m_TreeItemInfo.path, this);
    if (dlg.exec() == QDialog::Accepted) {
        if (dlg.getName().isEmpty()) {
            QMessageBox::critical(this, tr("拷贝失败"), tr("路径为空，不可拷贝"));
        } else {
            copyFileOrFolder(dlg.getName());
        }
    } else {
        //点击取消
    }
}

//复制操作
void MainWindow::copyFileOrFolder(const QString &newpath) {
    //qDebug() << "复制操作在这里执行。";

    if (m_TreeItemInfo.type == File)  //复制文件
    {
        //qDebug() << "复制文件";

        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x11;   //11.复制文件（copy）
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.prefixPath + "/" + m_TreeItemInfo.name;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length1 = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length1)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }
        cmd_folder_and_file_info.fun_para2[1024] = {0};
        QString temp_para2 = newpath;    //填充新文件目录，不用名字？
        std::u16string utf16Str_para2 = temp_para2.toStdU16String();
        size_t length2 = utf16Str_para2.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length2)
                cmd_folder_and_file_info.fun_para2[i] = utf16Str_para2[i];
            else
                cmd_folder_and_file_info.fun_para2[i] = 0;
        }
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

        QString log = QString("%1:正在执行复制文件[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::COPY;
        emit sign_sendCmd(sendData);

    }
    else if (m_TreeItemInfo.type == Folder)   //--------------------------复制文件夹----------------------------
    {
        //qDebug() << "复制文件夹";
        //****************************需要注释掉的内容结尾****************************

        //下发的内容
        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
        cmd_folder_and_file_info.order_head = ORDERHEAD;
        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
        cmd_folder_and_file_info.source_ID = 0;
        cmd_folder_and_file_info.dest_ID = 0;
        cmd_folder_and_file_info.oper_type = 0xA2;
        cmd_folder_and_file_info.oper_ID = 0x01;
        cmd_folder_and_file_info.package_num = 0;
        cmd_folder_and_file_info.fun_type = 0x12;   //12.复制文件夹（copy）
        cmd_folder_and_file_info.fun_para1[1024] = {0};
        QString temp_para1 = m_TreeItemInfo.prefixPath + "/" + m_TreeItemInfo.name;
        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
        size_t length1 = utf16Str_para1.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length1)
                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
            else
                cmd_folder_and_file_info.fun_para1[i] = 0;
        }

        cmd_folder_and_file_info.fun_para2[1024] = {0};
        QString temp_para2 = newpath;    //填充新文件目录，不用名字？
        std::u16string utf16Str_para2 = temp_para2.toStdU16String();
        size_t length2 = utf16Str_para2.size();
        for (size_t i = 0; i < 1024; ++i) {
            if (i < length2)
                cmd_folder_and_file_info.fun_para2[i] = utf16Str_para2[i];
            else
                cmd_folder_and_file_info.fun_para2[i] = 0;
        }
        cmd_folder_and_file_info.check = 0;
        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

        QString log = QString("%1:正在执行复制文件夹[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::COPY;
        emit sign_sendCmd(sendData);
    }
}

void MainWindow::slotWrite() //写入
{
    //qDebug()<<"写入操作";
}


void MainWindow::slotStopWrite() //停止写入
{
    //qDebug()<<"停止写入操作";
}

void MainWindow::slotPlayBack() //回放
{
    //qDebug()<<"回放操作";
}

void MainWindow::slotExport() //导出
{
    //qDebug()<<"--------------------------导出数据槽函数-----------------------------------";
    DlgExportData dlg(m_TreeItemInfo.path, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        if (dlg.getLocalPath().isEmpty())
        {
            QMessageBox::critical(this, tr("错误"), tr("请选择导出到本地的文件"));
        }
        else
        {
            int type = dlg.getExportType();        //获取是千兆还是万兆网
            exportFile(static_cast<NetworkPortType>(type));     //只是下发导出命令
            bool b = dlg.getIfMvpp();
            if(NetworkPortType::GigabitEthernet == static_cast<NetworkPortType>(type))
            {
                //qDebug()<<"使用千兆网来接收数据";
                QString log = QString("%1: 正在使用千兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                m_ExportFileInfo.localPath = dlg.getLocalPath();
                m_ExportFileInfo.isReceivingFileInfo =true;
                //qDebug()<<"导出数据时的标志位，应该为true = "<<m_ExportFileInfo.isReceivingFileInfo;

                m_tcp->setExportModule(b);
                m_tcp->setExportFileInfo(m_ExportFileInfo);
                //如果是mvpp模式，先向这个文件中写入功率和hz
                if(b)
                {
                    emit sign_addTcpFileHead(dlg.getLocalPath(),dlg.m_power,dlg.m_hz);
                }
            }
            else
            {
                //qDebug()<<"使用万兆网来接收数据";
                QString log = QString("%1: 正在使用万兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                m_udp->setUdpModule(b);
                QString path = dlg.getLocalPath();
                //m_udp->setPath(dlg.getLocalPath());
                //m_udp->m_path = dlg.getLocalPath();
                emit sign_setUdpFilePath(path);
                if(b)
                {
                    emit sign_addUdpFileHead(dlg.getLocalPath(),dlg.m_power,dlg.m_hz);
                }
            }
        }
    }
    else
    {
        //点击取消
    }
}

//下发导出命令
void MainWindow::exportFile(const NetworkPortType &type)
{
    //qDebug() << "开始下发导出指令";
    //下发内容,我只需要选择文件，读取就可以了，其他不用管
    Cmd_Export_File_Func_Info cmd_export_file_func_info;
    cmd_export_file_func_info.order_head = ORDERHEAD;
    cmd_export_file_func_info.head = DSV_PACKET_HEADER;
    cmd_export_file_func_info.source_ID = 0;
    cmd_export_file_func_info.dest_ID = 0;
    cmd_export_file_func_info.oper_type = 0xD2;
    cmd_export_file_func_info.oper_ID = 0x07;
    cmd_export_file_func_info.package_num = 0;
    std::u16string utf16Str_para1 = m_TreeItemInfo.path.toStdU16String();
    size_t length1 = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i)
    {
        if(i<length1)
            cmd_export_file_func_info.file_address[i] = utf16Str_para1[i];
        else
            cmd_export_file_func_info.file_address[i]=0;
    }

    if(NetworkPortType::GigabitEthernet ==type)
    {
        cmd_export_file_func_info.export_type = 0x00;
    }else{
        cmd_export_file_func_info.export_type = 0x01;
    }

    cmd_export_file_func_info.check = 0;
    cmd_export_file_func_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_export_file_func_info), sizeof(Cmd_Export_File_Func_Info));

    QString log = QString("%1:正在执行导出文件[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
    ui->textBrowser_log->append(log);
    //记录操作类型
    lastOrderType = TYPE::EXPORT;
    emit sign_sendCmd(sendData);

}

void MainWindow::slotAcquisition() //采集
{
    //qDebug()<<"采集操作";
}

void MainWindow::showMenu()
{
    // 创建一个 QMenu 对象
    QMenu contextMenu(this);

    // 创建菜单项
    QAction *action1 = new QAction("打开", this);
    QAction *action2 = new QAction("保存", this);
    QAction *action3 = new QAction("退出", this);

    // 将菜单项添加到菜单
    contextMenu.addAction(action1);
    contextMenu.addAction(action2);
    contextMenu.addSeparator(); // 添加分隔线
    contextMenu.addAction(action3);

    // 连接每个菜单项的信号到相应的槽函数
    connect(action1, &QAction::triggered, this, &MainWindow::slotRefresh);
    connect(action2, &QAction::triggered, this, &MainWindow::slotCopy);
    connect(action3, &QAction::triggered, this, &MainWindow::slotCopy);

    // 在鼠标右键点击位置弹出菜单
    //contextMenu.exec(event());
}

void MainWindow::slot_diskFormat()
{
    QMessageBox::StandardButton rb = QMessageBox::information(this, "确认是否进行操作", "是否进行磁盘格式化？",
                                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //qDebug() << "磁盘格式化.";
        QString log = QString("%1: 磁盘格式化操作").arg(getNowTime());
        ui->textBrowser_log->append(log);
        Cmd_Disk_Info cmd_disk_info;
        cmd_disk_info.order_head = ORDERHEAD;
        cmd_disk_info.head = DSV_PACKET_HEADER;
        cmd_disk_info.source_ID = 0;
        cmd_disk_info.dest_ID = 0;
        cmd_disk_info.oper_type = 0xB2;
        cmd_disk_info.oper_ID = 0x01;
        cmd_disk_info.package_num = 0;
        cmd_disk_info.fun_type = 0x01;
        cmd_disk_info.check = 0;
        cmd_disk_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_disk_info), sizeof(Cmd_Disk_Info));
        lastOrderType = TYPE::DISK_FORMAT;
        emit sign_sendCmd(sendData);

    }
}
void MainWindow::slot_diskAgainMount()
{
    QMessageBox::StandardButton rb = QMessageBox::information(NULL, "确认是否进行操作", "是否进行磁盘重新挂载？",
                                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //qDebug() << "磁盘重新挂载.";
        QString log = QString("%1: 磁盘重新挂载操作").arg(getNowTime());
        ui->textBrowser_log->append(log);
        Cmd_Disk_Info cmd_disk_info;
        cmd_disk_info.order_head = ORDERHEAD;
        cmd_disk_info.head = DSV_PACKET_HEADER;
        cmd_disk_info.source_ID = 0;
        cmd_disk_info.dest_ID = 0;
        cmd_disk_info.oper_type = 0xB2;
        cmd_disk_info.oper_ID = 0x01;
        cmd_disk_info.package_num = 0;
        cmd_disk_info.fun_type = 0x02;
        cmd_disk_info.check = 0;
        cmd_disk_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_disk_info), sizeof(Cmd_Disk_Info));
        lastOrderType = TYPE::DISK_AGAINMOUNT;
        emit sign_sendCmd(sendData);

    }
}

void MainWindow::slot_diskUnmount()
{
    QMessageBox::StandardButton rb = QMessageBox::information(NULL, "确认是否进行操作", "是否进行磁盘解挂载？",
                                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //qDebug() << "磁盘解挂载.";
        QString log = QString("%1: 磁盘解挂载操作").arg(getNowTime());
        ui->textBrowser_log->append(log);

        Cmd_Disk_Info cmd_disk_info;
        cmd_disk_info.order_head = ORDERHEAD;
        cmd_disk_info.head = DSV_PACKET_HEADER;
        cmd_disk_info.source_ID = 0;
        cmd_disk_info.dest_ID = 0;
        cmd_disk_info.oper_type = 0xB2;
        cmd_disk_info.oper_ID = 0x01;
        cmd_disk_info.package_num = 0;
        cmd_disk_info.fun_type = 0x03;
        cmd_disk_info.check = 0;
        cmd_disk_info.end = DSV_PACKET_TAIL;
        QByteArray sendData = QByteArray((char *) (&cmd_disk_info), sizeof(Cmd_Disk_Info));
        lastOrderType = TYPE::DISK_UNMOUNT;
        emit sign_sendCmd(sendData);
    }
}

void MainWindow::slot_stateBarRefresh()
{
    //qDebug() << "刷新磁盘状态";
    QString log = QString("%1: 刷新磁盘状态操作").arg(getNowTime());
    ui->textBrowser_log->append(log);
    //下发的内容
    Cmd_Ask_Disk_State_Info cmd_ask_disk_state_info;
    cmd_ask_disk_state_info.order_head = ORDERHEAD;
    cmd_ask_disk_state_info.head = DSV_PACKET_HEADER;
    cmd_ask_disk_state_info.source_ID = 0;
    cmd_ask_disk_state_info.dest_ID = 0;
    cmd_ask_disk_state_info.oper_type = 0xF2;
    cmd_ask_disk_state_info.oper_ID = 0x01;
    cmd_ask_disk_state_info.package_num = 0;
    cmd_ask_disk_state_info.check = 0;
    cmd_ask_disk_state_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_ask_disk_state_info), sizeof(Cmd_Ask_Disk_State_Info));
    emit sign_sendCmd(sendData);

}

void MainWindow::slot_CustomContextMenuRequested(const QPoint &pos)
{
    //qDebug()<<"新工程中，右键显示自定义菜单栏菜单";
    foreach (QAction *action, m_pContextMenu->actions())
    {
        action->setVisible(true);
        if (m_TreeItemInfo.type == ItemType::Folder) {
            // 编辑画面
            if (action->data().toInt() == static_cast<int>(ButtonType::Open)
                || action->data().toInt() == static_cast<int>(ButtonType::Close)
                || action->data().toInt() == static_cast<int>(ButtonType::Write)
                || action->data().toInt() == static_cast<int>(ButtonType::Export)) {
                action->setVisible(false);
            }
        } else {
            action->setVisible(true);
            if ( action->data().toInt() == static_cast<int>(ButtonType::AddFolder)
                || action->data().toInt() == static_cast<int>(ButtonType::AddFile)
                ) {
                action->setVisible(false);
            }
        }
    }

    m_pContextMenu->exec(QCursor::pos());
}

void MainWindow::slot_haveNewConnection(const QString &client)
{
    //qDebug()<<"有新的客户端连接！";
    QString log = QString("%1: 客户端[%2]连接成功.").arg(getNowTime()).arg(client);
    ui->textBrowser_log->append(log);
    QString str = QString(client+":已连接");
    m_pSocklLabel->setText(str);
    m_pSocklLabel->setFixedSize(250,32);

    m_pSocklLabel->setStyleSheet(
        "background-color: green; "     // 设置背景颜色为绿色
        "color: red; "                   // 设置字体颜色为红色
        "font-family: 'SimHei'; "        // 设置字体为黑体
        "font-size: 14pt; "              // 设置字体大小为 14pt
        "font-weight: bold;"             // 设置字体加粗
        );

}

void MainWindow::slot_haveNewUdpConnect(const QString ip, const quint16 port)
{
    ////qDebug()<<"有新的客户端连接！";
    QString log = QString("%1: 万兆网[%2]连接成功.").arg(getNowTime()).arg(ip);
    ui->textBrowser_log->append(log);
    QString str = QString(ip+" "+port+":已连接");
    m_udpLabel->setText(str);
    m_udpLabel->setFixedSize(250,32);

    m_udpLabel->setStyleSheet(
        "background-color: green; "     // 设置背景颜色为绿色
        "color: red; "                   // 设置字体颜色为红色
        "font-family: 'SimHei'; "        // 设置字体为黑体
        "font-size: 14pt; "              // 设置字体大小为 14pt
        "font-weight: bold;"             // 设置字体加粗
        );
}

//接收磁盘的信息
void MainWindow::slot_recvDiskData(const Cmd_Disk_State_Info *data)
{
    //qDebug() << "收到了磁盘的状态信息";
    ui->textBrowser_log->append(QString("%1: 收到了回复的磁盘状态信息.").arg(getNowTime()));

    QString diskTotal = QString::number((data->disk_total) / (1024 * 1024));
    totalShow->setText(diskTotal);
    QString diskUsed = QString::number((data->disk_used) / (1024 * 1024));
    usedShow->setText(diskUsed);
    QString diskRest = QString::number((data->disk_rest) / (1024 * 1024));
    restShow->setText(diskRest);
    QString fileNum = QString::number(data->file_num);
    fileNumShow->setText(fileNum);

    QString state = QString::number(data->disk_state);
    if (state == "1")
        stateShow->setText("空闲");
    if (state == "2")
        stateShow->setText("读取中");
    if (state == "3")
        stateShow->setText("写入中");
    if (state == "4")
        stateShow->setText("格式化");
    if (state == "5")
        stateShow->setText("删除文件中");
    if (state == "6")
        stateShow->setText("容量已满");
    if (state == "7")
        stateShow->setText("模块故障");
    else
        stateShow->setText("无效");

    QString T = QString::number(data->disk_t);
    tShow->setText(T);
    QString power = QString::number(data->disk_power);
    powerShow->setText(power);

}

void MainWindow::slot_StandardItemModel(QStandardItemModel *data)
{

    //qDebug() << "接收到目录树信息";
    ui->treeView->setModel(data);
    ui->treeView->expandAll();

    ui->treeView->setColumnWidth(0, 300);  // 设置第 0 列的宽度
    ui->treeView->setColumnWidth(1, 150);  // 设置第 1 列的宽度
    ui->treeView->setColumnWidth(2, 250);  // 设置第 2 列的宽度
    auto index = ui->treeView->currentIndex();

    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
    if (selectionModel) {
        connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
                &MainWindow::slot_onItemSelected);
    } else {
        //qDebug() << "Selection model is null!";
    }
}

// void MainWindow::slot_recvCommonRespon(const Cmd_Response_Common_Info *data)
// {
//     qDebug()<<"收到了通用应答，判断是什么操作";
//     qDebug()<<"上一步执行的操作类型 ："<<lastOrderType;

//     qDebug()<<"main 收到的通用应答包操作类型："<<hex << data->res_type;
//     qDebug()<<"main 收到的通用应答包操作ID："<<hex << data->res_ID;
//     qDebug()<<"main 收到的通用应答包jieguo："<<hex << data->res_result;

//     if((data->res_type == 0xA2) && (data->res_ID == 0x01) && (data->res_result==0x77bb8014))  //成功
//     {
//         qDebug()<<"####################";
//         if(lastOrderType==TYPE::ADDFOLDER)
//         {
//             lastOrderType = TYPE::UNUSE;
//             QString log1 = QString("%1:新建文件夹[%2]成功.").arg(getNowTime().arg(m_TreeItemInfo.name));
//             ui->textBrowser_log->append(log1);
//             slotRefresh();
//         }
//         if(lastOrderType==TYPE::ADDFILE)
//         {
//             lastOrderType = TYPE::UNUSE;
//             QString log2 = QString("%1:新建文件[%2]成功.").arg(getNowTime().arg(m_TreeItemInfo.name));
//             ui->textBrowser_log->append(log2);
//             slotRefresh();
//         }
//         if(lastOrderType==TYPE::DELETE)
//         {
//             qDebug()<<"删除文件"<<lastOrderType;
//             lastOrderType = TYPE::UNUSE;
//             QString log3 = QString("%1:删除文件[%2]成功.").arg(getNowTime().arg(m_TreeItemInfo.name));
//             ui->textBrowser_log->append(log3);
//             slotRefresh();
//         }
//         if(lastOrderType==TYPE::RENAME)
//         {

//             lastOrderType = TYPE::UNUSE;
//             QString log4 = QString("%1:重命名文件[%2]成功.").arg(getNowTime().arg(m_TreeItemInfo.name));
//             ui->textBrowser_log->append(log4);
//             slotRefresh();
//         }
//         if(lastOrderType==TYPE::MOVE)
//         {

//             lastOrderType = TYPE::UNUSE;
//             QString log5 = QString("%1:移动文件[%2]成功.").arg(getNowTime().arg(m_TreeItemInfo.name));
//             ui->textBrowser_log->append(log5);
//             slotRefresh();
//         }
//         if(lastOrderType==TYPE::COPY)
//         {

//             lastOrderType = TYPE::UNUSE;
//             QString log6 = QString("%1:复制文件[%2]成功.").arg(getNowTime().arg(m_TreeItemInfo.name));
//             ui->textBrowser_log->append(log6);
//             slotRefresh();
//         }
//         else
//         {
//             //qDebug()<<"刚刚执行的操作，不需要刷新目录树";
//             lastOrderType = TYPE::UNUSE;
//         }
//     }
//     if(data->res_type==0xB2&& data->res_ID == 0x01 &&data->res_result==0x77bb8014)
//     {
//         if(lastOrderType==TYPE::DISK_FORMAT)
//         {
//             lastOrderType = TYPE::UNUSE;
//             QString log = QString("%1:磁盘挂载成功.").arg(getNowTime());
//             ui->textBrowser_log->append(log);
//         }
//         if(lastOrderType==TYPE::DISK_FORMAT)
//         {
//             lastOrderType = TYPE::UNUSE;
//             QString log2 = QString("%1:磁盘重新挂载成功.").arg(getNowTime());
//             ui->textBrowser_log->append(log2);
//         }
//         if(lastOrderType==TYPE::DISK_FORMAT)
//         {
//             lastOrderType = TYPE::UNUSE;
//             QString log3 = QString("%1:磁盘解挂载成功.").arg(getNowTime());
//             ui->textBrowser_log->append(log3);
//         }
//     }
// }

void MainWindow::slot_newrecvCommonRespon(const quint32 &type,const quint32 &id,const quint32 &result)
{
    qDebug()<<"----------收到了通用应答，判断是什么操作";
    qDebug()<<"上一步执行的操作类型 ："<<lastOrderType;

    qDebug()<<"main 收到的通用应答包操作类型："<<hex << type;
    qDebug()<<"main 收到的通用应答包操作ID："<<hex << id;
    qDebug()<<"main 收到的通用应答包jieguo："<<hex << result;

    if((type == 0xA2) && (id == 0x01) && (result==0x11))  //成功
    {
        qDebug()<<"####################";
        if(lastOrderType==TYPE::ADDFOLDER)
        {
            lastOrderType = TYPE::UNUSE;
            QString log1 = QString("%1:文件夹新建成功.").arg(getNowTime());
            ui->textBrowser_log->append(log1);
            slotRefresh();
        }
        if(lastOrderType==TYPE::ADDFILE)
        {
            lastOrderType = TYPE::UNUSE;
            QString log2 = QString("%1:文件新建成功.").arg(getNowTime());
            ui->textBrowser_log->append(log2);
            slotRefresh();
        }
        if(lastOrderType==TYPE::DELETE)
        {
            qDebug()<<"删除文件"<<lastOrderType;
            lastOrderType = TYPE::UNUSE;
            QString log3 = QString("%1:文件删除成功.").arg(getNowTime());
            ui->textBrowser_log->append(log3);
            slotRefresh();
        }
        if(lastOrderType==TYPE::RENAME)
        {
            lastOrderType = TYPE::UNUSE;
            QString log4 = QString("%1:文件重命名成功.").arg(getNowTime());
            ui->textBrowser_log->append(log4);
            slotRefresh();
        }
        if(lastOrderType==TYPE::MOVE)
        {
            lastOrderType = TYPE::UNUSE;
            QString log5 = QString("%1:文件移动成功.").arg(getNowTime());
            ui->textBrowser_log->append(log5);
            slotRefresh();
        }
        if(lastOrderType==TYPE::COPY)
        {
            lastOrderType = TYPE::UNUSE;
            QString log6 = QString("%1:文件复制成功.").arg(getNowTime());
            ui->textBrowser_log->append(log6);
            slotRefresh();
        }
        else
        {
            //qDebug()<<"刚刚执行的操作，不需要刷新目录树";
            lastOrderType = TYPE::UNUSE;
        }
    }
    if(type==0xB2 && id == 0x01 && result==0x11)
    {
        if(lastOrderType==TYPE::DISK_FORMAT)
        {
            lastOrderType = TYPE::UNUSE;
            QString log = QString("%1:磁盘挂载成功.").arg(getNowTime());
            ui->textBrowser_log->append(log);
        }
        if(lastOrderType==TYPE::DISK_FORMAT)
        {
            lastOrderType = TYPE::UNUSE;
            QString log2 = QString("%1:磁盘重新挂载成功.").arg(getNowTime());
            ui->textBrowser_log->append(log2);
        }
        if(lastOrderType==TYPE::DISK_FORMAT)
        {
            lastOrderType = TYPE::UNUSE;
            QString log3 = QString("%1:磁盘解挂载成功.").arg(getNowTime());
            ui->textBrowser_log->append(log3);
        }
    }
    if((type==0xD2) && (id == 0x07) && (result==0x11))
    {
        qDebug()<<"收到了导出完成的回复";
        if(lastOrderType==TYPE::EXPORT)
        {
            qDebug()<<"上一次的操作是导出";
            lastOrderType = TYPE::UNUSE;
            QString log = QString("%1:文件导出成功.").arg(getNowTime());
            ui->textBrowser_log->append(log);
        }
    }
}

QString MainWindow::buildPath(QModelIndex index) {
    // 获取当前节点的第一列的值
    QString path = index.sibling(index.row(), 0).data().toString();

    // 向上递归查找父节点
    QModelIndex parentIndex = index.parent();
    while (parentIndex.isValid()) {
        QString parentName = parentIndex.sibling(parentIndex.row(), 0).data().toString();
        path = parentName + "/" + path;
        parentIndex = parentIndex.parent();
    }

    return path;
}

void MainWindow::slot_onItemSelected()
{
    // 获取当前选中的项
    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        // 获取选中的行的索引
        QModelIndex selectedIndex = selectedIndexes.at(0);
        int selectedRow = selectedIndex.row();

        // 获取第一列的值
        QString firstColumnValue = selectedIndex.sibling(selectedRow, 0).data().toString();
        qDebug()<<"name = "<<firstColumnValue;

        uint64_t fileSize = selectedIndex.sibling(selectedRow, 0).data(Qt::UserRole + 2).toULongLong();

        // 获取第二列的值
        QString secondColumnValue = selectedIndex.sibling(selectedRow, 1).data().toString();

        // 根据第一列的值拼接路径
        QString path = buildPath(selectedIndex);

        m_TreeItemInfo.name = firstColumnValue;
        m_TreeItemInfo.path = path;

        m_ExportFileInfo.name = m_TreeItemInfo.name;
        m_ExportFileInfo.path = m_TreeItemInfo.path;
        m_ExportFileInfo.size = fileSize;


        QFileInfo fileInfo(path);
        m_TreeItemInfo.prefixPath = fileInfo.path();   // 路径中去掉名称部分

        QString time = getNowTime();
        QString log = QString("%1: 选中的项为:[%2]，类型为[%3],路径为[%4]").arg(time).arg(firstColumnValue).arg(secondColumnValue).arg(path);
        ui->textBrowser_log->append(log);


        if (secondColumnValue == "File") {
            m_TreeItemInfo.type = ItemType::File;
        } else if (secondColumnValue == "Folder") {
            m_TreeItemInfo.type = ItemType::Folder;
        } else {
            m_TreeItemInfo.type = ItemType::Error;
        }
    }
}

void MainWindow::slot_showSpeed(uint data)
{
    kaijiShow->setText(QString::number(data));
}

void MainWindow::slot_udpInfo()
{
    m_udpInfoWidget->show();
}





