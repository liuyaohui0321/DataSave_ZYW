#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QDebug>

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),dlg(nullptr),dlg1(nullptr),dlg2(nullptr),dlg3(nullptr),dlg4(nullptr),dlg5(nullptr),dlg6(nullptr)
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
    auto *diskFourAction = new QAction(QIcon(":/my/images/disk.png"), tr("磁盘IP地址设置"), this);

    disk_manager->addAction(diskOneAction);
    disk_manager->addSeparator();       //添加分割线
    disk_manager->addAction(diskTwoAction);
    disk_manager->addSeparator();       //添加分割线
    disk_manager->addAction(diskThreeAction);
    disk_manager->addSeparator();       //添加分割线
    disk_manager->addAction(diskFourAction);

    auto connect_manager = ui->menubar->addMenu("连接配置");
//    auto *tcpAction = new QAction("千兆网连接配置",this);
    auto *udpAction = new QAction("万兆网连接配置",this);
//    connect_manager->addAction(tcpAction);
    connect_manager->addAction(udpAction);

    connect(udpAction,&QAction::triggered,this,&MainWindow::slot_udpInfo);

    connect(diskOneAction, &QAction::triggered, this, &MainWindow::slot_diskFormat);
    connect(diskTwoAction, &QAction::triggered, this, &MainWindow::slot_diskAgainMount);
    connect(diskThreeAction, &QAction::triggered, this, &MainWindow::slot_diskUnmount);
    connect(diskFourAction, &QAction::triggered, this, &MainWindow::showIPDialog);

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
    QLabel *SpeedShowLabel = new QLabel("存盘/读盘速度:", this);
    SpeedShow = new QLabel(this);
    SpeedShow->setFixedWidth(50);
    QLabel *ci = new QLabel("MB/s", this);

    QLabel *fiberState = new QLabel("光纤通断状态:", this);
    fiberStateShow = new QLabel(this);
    fiberStateShow->setFixedWidth(50);
    setFiberStatus(StatusUnknown);
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
    QLabel *spacer9 = new QLabel();
    spacer9->setFixedWidth(20);

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

    ui->statusbar->addWidget(SpeedShowLabel);
    ui->statusbar->addWidget(SpeedShow);
    ui->statusbar->addWidget(ci);
    ui->statusbar->addWidget(spacer8);

    ui->statusbar->addWidget(fiberState);
    ui->statusbar->addWidget(fiberStateShow);
    ui->statusbar->addWidget(spacer9);

    ui->statusbar->addWidget(pbtn_stateBarRefresh);
}

// 定义一个函数来提取字符串中的数字部分
QString MainWindow::extractNumbers(const QString &input)
{
    QRegularExpression re("\\d+"); // 匹配一个或多个数字
    QRegularExpressionMatchIterator i = re.globalMatch(input);
    QString result;

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        result += match.captured(0); // 将匹配到的数字添加到结果中
    }

    return result;
}

// 定义一个函数来计算单个字符串对应的数值
quint64 MainWindow::calculateSize(const QString &input)
{
    QRegularExpression re("(\\d+)\\s*(MB|GB|Byte)",QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = re.match(input);

    if (match.hasMatch()) {
        bool ok;
        quint64 number = match.captured(1).toULongLong(&ok);
        // 打印匹配到的数字和单位
//        qDebug() << "Matched number:" << number;
//        qDebug() << "Matched unit:" << match.captured(2);
        if (ok) {
            QString unit = match.captured(2).toUpper();
            if (unit == "MB") {
                return number * 0x100000ULL; // 1MB = 1048576 Byte
            } else if (unit == "GB") {
                return number * 0x40000000ULL; // 1GB = 1073741824 Byte
            } else if (unit == "BYTE") {
                return number;
            }
        }
        else {
                qDebug() << "No match found for input:" << input;
        }
    }

    return 0;
}

quint64 MainWindow::countSize(QModelIndexList &indexlist)
{
    quint64 totalSize = 0;
    foreach (const QModelIndex &index, indexlist)
    {
        if (index.column() == 2)
        {
            // 获取该索引对应的数据（假设是显示的文本）
            QString text = index.data(Qt::DisplayRole).toString();
//            QString numbers = extractNumbers(text); // 提取数字部分
            quint64 size = calculateSize(text); // 计算单个字符串对应的数值
            totalSize += size; // 累加到总大小
//            qDebug() <<"size"<<size;
        }

    }
    return totalSize;
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
//    connect(m_pContextMenu, &ContextMenu::signalWrite, this, &MainWindow::slotWrite);
    connect(m_pContextMenu, &ContextMenu::signalPlayback, this, &MainWindow::slotPlayBack);
    connect(m_pContextMenu, &ContextMenu::signalAcquisition, this, &MainWindow::slotAcquisition);

    ui->treeView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);// 启用自定义菜单
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    //树操作
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::slot_CustomContextMenuRequested);
    //connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::showMenu);
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::slot_onItemSelected);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);//LYH 2.14

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
    connect(this,&MainWindow::sign_sendLenCmd,m_tcp,&TCPThread::slot_getLenCmd);
    connect(this,&MainWindow::sign_sendExportCap,m_tcp,&TCPThread::slot_getExportCap);
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

    connect(m_tcp, &TCPThread::sign_exportProgress, this, &MainWindow::onExportProgress);
    connect(m_tcp, &TCPThread::sign_exportFinished, this, &MainWindow::onExportFinished);
//    connect(m_tcp, &TCPThread::sign_SetexportProgress, this, &MainWindow::SetExportProgress);

//    connect(this,&MainWindow::sign_addTcpFileHead,m_tcp,&TCPThread::slot_addTcpHead);
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
//    connect(this,&MainWindow::sign_addUdpFileHead,m_udp,&UDPThread::slot_addHead);
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
    stateShow->setText("空闲");
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
//void MainWindow::slotDelete()  //之前的写法
//{
//    auto ret = QMessageBox::information(this, "确认是否删除", "是否确定删除，删除后不可恢复",
//                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    if (ret == QMessageBox::No) {
//        return;
//    }

//    //qDebug() << "删除操作.";

//    if (m_TreeItemInfo.type == Folder)    //删除文件夹
//    {
//        //下发的内容
//        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
//        cmd_folder_and_file_info.order_head = ORDERHEAD;
//        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
//        cmd_folder_and_file_info.source_ID = 0;
//        cmd_folder_and_file_info.dest_ID = 0;
//        cmd_folder_and_file_info.oper_type = 0xA2;
//        cmd_folder_and_file_info.oper_ID = 0x01;
//        cmd_folder_and_file_info.package_num = 0;
//        cmd_folder_and_file_info.fun_type = 0x04;   //删除文件夹 4
//        cmd_folder_and_file_info.fun_para1[1024] = {0};
//        QString temp_para1 = m_TreeItemInfo.path;
//        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
//        size_t length = utf16Str_para1.size();
//        for (size_t i = 0; i < 1024; ++i) {
//            if (i < length)
//                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
//            else
//                cmd_folder_and_file_info.fun_para1[i] = 0;
//        }
//        cmd_folder_and_file_info.fun_para2[1024] = {0};
//        cmd_folder_and_file_info.check = 0;
//        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
//        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

//        QString log = QString("%1:正在执行删除文件夹[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
//        ui->textBrowser_log->append(log);
//        //记录操作类型
//        lastOrderType = TYPE::DELETE;
//        emit sign_sendCmd(sendData);
//    }
//    else if (m_TreeItemInfo.type == File)      //删除文件
//    {
//        //下发的内容
//        Cmd_Folder_And_File_Info cmd_folder_and_file_info;
//        cmd_folder_and_file_info.order_head = ORDERHEAD;
//        cmd_folder_and_file_info.head = DSV_PACKET_HEADER;
//        cmd_folder_and_file_info.source_ID = 0;
//        cmd_folder_and_file_info.dest_ID = 0;
//        cmd_folder_and_file_info.oper_type = 0xA2;
//        cmd_folder_and_file_info.oper_ID = 0x01;
//        cmd_folder_and_file_info.package_num = 0;
//        cmd_folder_and_file_info.fun_type = 0x03;   //删除文件 3
//        cmd_folder_and_file_info.fun_para1[1024] = {0};
//        QString temp_para1 = m_TreeItemInfo.path;
//        std::u16string utf16Str_para1 = temp_para1.toStdU16String();
//        size_t length = utf16Str_para1.size();
//        for (size_t i = 0; i < 1024; ++i) {
//            if (i < length)
//                cmd_folder_and_file_info.fun_para1[i] = utf16Str_para1[i];
//            else
//                cmd_folder_and_file_info.fun_para1[i] = 0;
//        }
//        cmd_folder_and_file_info.fun_para2[1024] = {0};
//        cmd_folder_and_file_info.check = 0;
//        cmd_folder_and_file_info.end = DSV_PACKET_TAIL;
//        QByteArray sendData = QByteArray((char *) (&cmd_folder_and_file_info), sizeof(Cmd_Folder_And_File_Info));

//        QString log = QString("%1:正在执行删除文件[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
//        ui->textBrowser_log->append(log);
//        //记录操作类型
//        lastOrderType = TYPE::DELETE;
//        emit sign_sendCmd(sendData);
//    } else {
//        //qDebug() << "文件类型错误！";
//    }

//}
void MainWindow::slotDelete()
{
        int num=0;
        // 创建并显示一个消息框
        QMessageBox messageBox;
        messageBox.setWindowTitle("确认删除");
        messageBox.setInformativeText("是否确定删除，删除后不可恢复");
        // 添加三个按钮：确认、取消和批量删除
        messageBox.addButton("确认", QMessageBox::AcceptRole);
        messageBox.addButton("取消", QMessageBox::RejectRole);
    //    messageBox.addButton("批量删除", QMessageBox::NoRole);
        QPushButton* batchDeleteButton = messageBox.addButton("批量删除", QMessageBox::NoRole);

        // 显示消息框，并获取用户的选择
        int ret = messageBox.exec();
        // 根据用户的选择执行相应的操作
        if (ret == QMessageBox::AcceptRole)
        {
            qDebug() << "用户选择了确认删除";
            // 在这里添加确认删除的代码
            if (dlg2)
            {
                dlg2->show();
                return; // 如果对话框已经存在，直接返回
            }
            // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
             dlg2 = new dlg_delete(m_TreeItemInfo.path, this);
            // 设置关闭时自动删除（重要！防止内存泄漏）
             dlg2->setAttribute(Qt::WA_DeleteOnClose);
    //         connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);//不屏蔽的话，dlg_delete::accepted会触发两次

            // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
             connect(dlg2, &dlg_delete::finished, this, [=]() {
                dlg2 = nullptr; // 对话框关闭时将指针置为nullptr
            });
             // 使用show()代替exec()显示非模态对话框
            dlg2->show();
            connect(dlg2, &dlg_delete::accepted, this, [=]()
            {
                qDebug() << "单个删除操作";
                DeleteOne();  //单个删除
        //      isWaitingResponse = true;
        //      之后需要接收下位机发送过来的执行指令，如果准备好了再发，否则发执行错误
            });
        }
        else if (ret == QMessageBox::RejectRole)
        {
            qDebug() << "用户选择了取消";
            // 在这里添加取消删除的代码
        }
        else if (batchDeleteButton == messageBox.clickedButton())
        {
            qDebug() << "用户选择了批量删除";
            // 在这里添加批量删除的代码
    //        ui->treeView->setSelectionMode(QAbstractItemView::MultiSelection);
            ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
            if (dlg2)
            {
                dlg2->show();
                return; // 如果对话框已经存在，直接返回
            }
            // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
             dlg2 = new dlg_delete(m_TreeItemInfo.path, this);
            // 设置关闭时自动删除（重要！防止内存泄漏）
             dlg2->setAttribute(Qt::WA_DeleteOnClose);
    //         connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);
             dlg2->LineEditSet();
             dlg2->Dialog_Set("选中文件");
             dlg2->resize(360,250);
            // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
             connect(dlg2, &dlg_delete::finished, this, [=]() {
                dlg2 = nullptr; // 对话框关闭时将指针置为nullptr
                ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
            });
             // 使用show()代替exec()显示非模态对话框
            dlg2->show();
            // 连接对话框的完成信号（使用lambda捕获this指针）
            connect(dlg2, &dlg_delete::accepted, this, [=]()mutable
    //        connect(dlg2, &dlg_delete::accepted, this, [=]()
            {
                qDebug() << "批量删除操作";
    #if   0 //相对地址
                // 获取选中项
                QItemSelectionModel *selection = ui->treeView->selectionModel();
                QModelIndexList indexes = selection->selectedIndexes();
                // 提取数据（假设为QStandardItemModel）
                QStringList selectedTexts;
                foreach (const QModelIndex &index, indexes) {
                    if (index.column() == 0) {
                        QStandardItem *item = Model->itemFromIndex(index);
                        if (item) {
                            selectedTexts << item->text();
                            qDebug() <<item->text();
                        }
                    }
                }
                // 使用selectedTexts进行后续操作
                qDebug() << "选中的项：" << selectedTexts;
    #else //绝对地址
                // 获取选中项
                QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
                QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
                // 提取数据（假设为QStandardItemModel）
                QStringList selectedTexts;
                foreach (const QModelIndex &index, selectedIndexes)
                {
                    if (index.column() == 0)
                    {
                        QString path = buildPath(index);
    //                    qDebug() << "path：" << path;
                        selectedTexts << path;
                        num++;
                    }
                }
                // 使用selectedTexts进行后续操作
    //            qDebug() << "选中的项：" << selectedTexts;
    //            qDebug() << "num：" << num;
    #endif
                DeleteMore(num,selectedTexts);
                ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
            });
        } else {
            qDebug() << "用户关闭了对话框";
        }

}

void MainWindow::DeleteOne()
{
//    stateShow->setText("删除中...");
//    stateShow->setStyleSheet("color: green;");
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
    }
    else
    {
        qDebug() << "文件类型错误！";
    }
}

void MainWindow::DeleteMore(int &num,QStringList &data)
{
//    stateShow->setText("删除中...");
//    stateShow->setStyleSheet("color: green;");
        int j=0;
        //下发的内容
        Cmd_File_Info cmd_file_info;
        cmd_file_info.order_head = ORDERHEAD;
        cmd_file_info.head = DSV_PACKET_HEADER;
        cmd_file_info.source_ID = 0;
        cmd_file_info.dest_ID = 0;
        cmd_file_info.oper_type = 0xA2;
        cmd_file_info.oper_ID = 0x09;
        cmd_file_info.package_num = 0;
        cmd_file_info.file_num=num;
        cmd_file_info.file_name = new File_Info[num];
        foreach (const QString& str, data)
        {
            qDebug() <<"str:"<< str;
            std::u16string utf16Str = str.toStdU16String();
            size_t length = utf16Str.size();
            for (size_t i = 0; i < 64; ++i)
            {
                if (i < length)
                    cmd_file_info.file_name[j].name[i] = utf16Str[i];
                else
                    cmd_file_info.file_name[j].name[i] = 0;
            }
            j++;
        }
        cmd_file_info.check = 0;
        cmd_file_info.end = DSV_PACKET_TAIL;

        // 1. 计算需要发送的总大小
        size_t totalSize = sizeof(uint32_t) * 10;  // 固定大小的成员
        qDebug() << "cmd_file_info.file_num:" << cmd_file_info.file_num;
        totalSize += sizeof(File_Info) * cmd_file_info.file_num;  // 文件信息数组的大小
        qDebug() << "totalSize:" << totalSize;
        // 2. 创建缓冲区
        QByteArray buffer;
        buffer.reserve(totalSize);
        QDataStream stream(&buffer, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);  // 设置字节序

        // 3. 写入固定大小的成员
        stream << cmd_file_info.order_head
              << cmd_file_info.head
              << cmd_file_info.source_ID
              << cmd_file_info.dest_ID
              << cmd_file_info.oper_type
              << cmd_file_info.oper_ID
              << cmd_file_info.package_num
              << cmd_file_info.file_num;

        // 4. 写入文件信息数组
        for (uint32_t i = 0; i < cmd_file_info.file_num; ++i) {
            // 写入每个文件名
            for (int j = 0; j < 64; ++j) {
                stream << quint16(cmd_file_info.file_name[i].name[j]);
            }
        }

        // 5. 写入校验码和包尾
        stream << cmd_file_info.check
              << cmd_file_info.end;

        // 6. 发送数据
        QString log = QString("%1:正在执行批量删除[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::DELETE;
        emit sign_sendLenCmd(buffer,totalSize);

//        qint64 bytesWritten = m_socket->write(buffer, totalSize);
////        qint64 bytesWritten = m_socket->write(buffer);
////        qint64 bytesWritten = m_socket->write(buffer, buffer.size());

//        // 确保数据被写入
//        m_socket->flush();


//        //主线程中解析回复
//        if (bytesWritten < 0)
//        {
//            qDebug() << "批量删除文件指令下发失败：" << m_socket->errorString();
//            QString time = StaticGlobalMethod::getNowTime();
//            QString log = QString("%1: 文件夹 [%2] 删除失败（指令下发失败）.").arg(time);
//            ui->textBrowser_log->append(log);
//        }
//        else
//        {
//            int replayType = checkCommonReplayType();
//            if (replayType == 11) {
//                QString time = StaticGlobalMethod::getNowTime();
//                QString log = QString("%1: 文件夹 [%2] 删除成功.").arg(time).arg(m_TreeItemInfo.name);
//                ui->textBrowser_log->append(log);

//                QMessageBox::information(this, tr("成功"), tr("删除文件夹指令下发成功"));
//                 //执行刷新树操作
//                QTimer::singleShot(1000, [this](){
//                    slotRefresh();
//                });

//            } else {
//                QString time = StaticGlobalMethod::getNowTime();
//                QString log = QString("%1: 文件夹 [%2] 删除失败(通用应答失败).").arg(time).arg(m_TreeItemInfo.name);
//                ui->textBrowser_log->append(log);
//            }
        //        }
}

void MainWindow::MultiFilePlayBack()
{
    int num=0,j=0;
    Cmd_MoreFilePlayBack_Info  cmd_MorefilePlayBack_info={0};
    QString strLog;
    if (dlg3)
    {
        dlg3->show();
        return; // 如果对话框已经存在，直接返回
    }
    // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
    dlg3 = new dlg_multifile_play_back(m_TreeItemInfo.path, this);
    // 设置关闭时自动删除（重要！防止内存泄漏）
    dlg3->setAttribute(Qt::WA_DeleteOnClose);

    // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
    connect(dlg3, &dlg_multifile_play_back::finished, this, [=]() {
        dlg3 = nullptr; // 对话框关闭时将指针置为nullptr
    });
    // 使用show()代替exec()显示非模态对话框
    dlg3->show();
    qDebug() << "多文件操作";
//    auto mode = dlg3->getReadMode();
//    auto cnt = dlg3->getLoopCnt();
    auto gth = dlg3->getPlaybackChannel();
    connect(dlg3, &dlg_multifile_play_back::accepted, this, [=]()mutable
    {
        // 获取选中项
        QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
        QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
        // 提取数据（假设为QStandardItemModel）
        QStringList selectedTexts;
        foreach (const QModelIndex &index, selectedIndexes)
        {
            if (index.column() == 0)
            {
                QString path = buildPath(index);
    //          qDebug() << "path：" << path;
                selectedTexts << path;
                num++;
            }
        }
        // 使用selectedTexts进行后续操作
        // qDebug() << "选中的项：" << selectedTexts;
         qDebug() << "num：" << num;
         PlayBackWaitfinished();
        cmd_MorefilePlayBack_info.order_head = ORDERHEAD;
        cmd_MorefilePlayBack_info.head = DSV_PACKET_HEADER;
        cmd_MorefilePlayBack_info.source_ID = 0;
        cmd_MorefilePlayBack_info.dest_ID = 0;
        cmd_MorefilePlayBack_info.oper_type = 0xD2;
        cmd_MorefilePlayBack_info.oper_ID = 0x08;
        cmd_MorefilePlayBack_info.package_num = 0;
        cmd_MorefilePlayBack_info.file_num=num;
        cmd_MorefilePlayBack_info.read_func=0;     //读取方式
//        cmd_MorefilePlayBack_info.read_xunhuan_cnt=cnt; //循环读取次数
        cmd_MorefilePlayBack_info.file_name = new File_Info[num];

        foreach (const QString& str, selectedTexts)
        {
            qDebug() <<"str:"<< str;
            std::u16string utf16Str = str.toStdU16String();
            size_t length = utf16Str.size();
            for (size_t i = 0; i < 64; ++i)
            {
                if (i < length)
                    cmd_MorefilePlayBack_info.file_name[j].name[i] = utf16Str[i];
                else
                    cmd_MorefilePlayBack_info.file_name[j].name[i] = 0;
            }
            j++;
        }
        cmd_MorefilePlayBack_info.check = 0;
        cmd_MorefilePlayBack_info.end = DSV_PACKET_TAIL;
        // 设置 X1 (回放通道)
        switch (gth)
        {
            case BackGTH::GTH_NETWORK:
                strLog ="单次读取网口";
                cmd_MorefilePlayBack_info.read_func = 0;
                break;
            case BackGTH::GTH_1X:
                strLog ="单次读取GTH_1X";
                cmd_MorefilePlayBack_info.read_func = 16;
                break;
            case BackGTH::GTH_8X:
                strLog ="单次读取GTH_8X";
                cmd_MorefilePlayBack_info.read_func = 32;
                break;
        }
        // 1. 计算需要发送的总大小
        size_t totalSize = sizeof(uint32_t) * 11;  // 固定大小的成员
        qDebug() << "cmd_Morefile_info.file_num:" << cmd_MorefilePlayBack_info.file_num;
        totalSize += sizeof(File_Info) * cmd_MorefilePlayBack_info.file_num;  // 文件信息数组的大小
        qDebug() << "totalSize:" << totalSize;
        // 2. 创建缓冲区
        QByteArray buffer;
        buffer.reserve(totalSize);
        QDataStream stream(&buffer, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);  // 设置字节序

        // 3. 写入固定大小的成员
        stream << cmd_MorefilePlayBack_info.order_head
              << cmd_MorefilePlayBack_info.head
              << cmd_MorefilePlayBack_info.source_ID
              << cmd_MorefilePlayBack_info.dest_ID
              << cmd_MorefilePlayBack_info.oper_type
              << cmd_MorefilePlayBack_info.oper_ID
              << cmd_MorefilePlayBack_info.package_num
              << cmd_MorefilePlayBack_info.read_func
              << cmd_MorefilePlayBack_info.file_num;
//              << cmd_MorefilePlayBack_info.read_xunhuan_cnt;

        // 4. 写入文件信息数组
        for (uint32_t i = 0; i < cmd_MorefilePlayBack_info.file_num; ++i) {
            // 写入每个文件名
            for (int j = 0; j < 64; ++j) {
                stream << quint16(cmd_MorefilePlayBack_info.file_name[i].name[j]);
            }
        }

        // 5. 写入校验码和包尾
        stream << cmd_MorefilePlayBack_info.check
              << cmd_MorefilePlayBack_info.end;

        // 6. 发送数据
        QString log = QString("%1:正在执行批量回放[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
        ui->textBrowser_log->append(log);
        //记录操作类型
        lastOrderType = TYPE::PLAYBACK;
        emit sign_sendLenCmd(buffer,totalSize);
        playbackdialog->exec();
        ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    });
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

void MainWindow::playBack(ReadMode mode, BackGTH gth, const int &count)
{
    if(m_TreeItemInfo.type != File)
    {
        qDebug()<<"选择的不是文件";
        QString log = QString("%1: [%2] 是一个文件夹，请选择一个文件开始读取.").arg(getNowTime()).arg(m_TreeItemInfo.name);
        ui->textBrowser_log->append(log);
        return;
    }

    stateShow->setText("读取中...");
    stateShow->setStyleSheet("color: green;");


    //下发内容,我只需要选择文件，读取就可以了，其他不用管
    Cmd_Read_File_Func_Info cmd_read_file_func_info;
    cmd_read_file_func_info.order_head = ORDERHEAD;
    cmd_read_file_func_info.head = DSV_PACKET_HEADER;
    cmd_read_file_func_info.source_ID = 0;
    cmd_read_file_func_info.dest_ID = 0;
    cmd_read_file_func_info.oper_type = 0xD2;
    cmd_read_file_func_info.oper_ID = 0x04;
    cmd_read_file_func_info.package_num = 0;
    std::u16string utf16Str_para1 = m_TreeItemInfo.path.toStdU16String();
    size_t length1 = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i)
    {
        if(i<length1)
            cmd_read_file_func_info.file_address[i] = utf16Str_para1[i];
        else
            cmd_read_file_func_info.file_address[i]=0;
    }

    // 初始化 read_func
    cmd_read_file_func_info.read_func = 0;
QString strLog;
// 设置 X1 (回放通道)
    if (ReadMode::ReadOnce == mode) {
        switch (gth) {
            case BackGTH::GTH_NETWORK:
                strLog ="单次读取网口";
                cmd_read_file_func_info.read_func = 0;
                break;
            case BackGTH::GTH_1X:
                strLog ="单次读取GTH_1X";
                cmd_read_file_func_info.read_func = 16;
                break;
            case BackGTH::GTH_8X:
                strLog ="单次读取GTH_8X";
                cmd_read_file_func_info.read_func = 32;
                break;
        }
    }
    else if(ReadMode::LoopRead == mode) {
            switch (gth) {
                case BackGTH::GTH_NETWORK:
                    strLog = QString(" 模式为：循环回放网口，次数为:%1").arg(count);
                    cmd_read_file_func_info.read_func = 256;
                    break;
                case BackGTH::GTH_1X:
                    strLog = QString(" 模式为：循环回放GTH_1X，次数为:%1").arg(count);
                    cmd_read_file_func_info.read_func = 272;
                    break;
                case BackGTH::GTH_8X:
                    strLog = QString(" 模式为：循环回放GTH_8X，次数为:%1").arg(count);
                    cmd_read_file_func_info.read_func = 288;
                    break;
            }
        }
    cmd_read_file_func_info.read_xunhuan_cnt = count;
    cmd_read_file_func_info.check = 0;
    cmd_read_file_func_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_read_file_func_info), sizeof(Cmd_Read_File_Func_Info));

    QString log = QString("%1:正在执行回放[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
    ui->textBrowser_log->append(log);
    //记录操作类型
    lastOrderType = TYPE::PLAYBACK;
    emit sign_sendCmd(sendData);
}

void MainWindow::stopPlayBack()
{
    //下发内容,我只需要选择文件，读取就可以了，其他不用管
    Cmd_File_Acquisition_Info cmd_file_acquisition_info;
    cmd_file_acquisition_info.order_head = ORDERHEAD;//0xBCBCAAAA
    cmd_file_acquisition_info.package_head = DSV_PACKET_HEADER;//0x55555555
    cmd_file_acquisition_info.source_ID = 0;
    cmd_file_acquisition_info.dest_ID = 0;
    cmd_file_acquisition_info.oper_type = 0xD2;
    cmd_file_acquisition_info.oper_ID = 0x06;
    cmd_file_acquisition_info.package_num = 0;
    std::u16string utf16Str_para1 = m_TreeItemInfo.path.toStdU16String();
    size_t length1 = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i)
    {
        if(i<length1)
            cmd_file_acquisition_info.file_address[i] = utf16Str_para1[i];
        else
            cmd_file_acquisition_info.file_address[i]=0;
    }

    cmd_file_acquisition_info.check_code = 0;
    cmd_file_acquisition_info.package_tail = DSV_PACKET_TAIL;//0xAAAAAAAA
    QByteArray sendData = QByteArray((char *) (&cmd_file_acquisition_info), sizeof(Cmd_File_Acquisition_Info));

    QString log = QString("%1:正在执行停止回放[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
    ui->textBrowser_log->append(log);
    //记录操作类型
    lastOrderType = TYPE::stopPLAYBACK;
    emit sign_sendCmd(sendData);

    qDebug()<<"发送停止回放指令，等待窗口关闭";
    // 使用定时器延迟关闭弹窗
    if (playbackdialog)
    {
       // 更新状态文本
       QLabel* statusLabel = playbackdialog->findChild<QLabel*>();
       if (statusLabel)
       {
           statusLabel->setText("已发送停止指令，等待设备响应...");
       }

       // 延迟1秒后关闭弹窗
       QTimer::singleShot(1000, [this]()
       {
           if (playbackdialog)
           {
               playbackdialog->accept();
               playbackdialog = nullptr;
           }
       });
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
    if (dlg)
    {
        dlg->show();
        return; // 如果对话框已经存在，直接返回
    }
    // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
//    DlgPlayBackData* dlg = new DlgPlayBackData(m_TreeItemInfo.path, this);
     dlg = new DlgPlayBackData(m_TreeItemInfo.path, this);
    // 设置关闭时自动删除（重要！防止内存泄漏）
    dlg->setAttribute(Qt::WA_DeleteOnClose);
//    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);

    // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
    connect(dlg, &DlgPlayBackData::finished, this, [=]() {
        dlg = nullptr; // 对话框关闭时将指针置为nullptr
    });
    // 使用show()代替exec()显示非模态对话框
    dlg->show();
    // 连接对话框的完成信号（使用lambda捕获this指针）
    connect(dlg, &DlgPlayBackData::accepted, this, [=](){
        if(dlg->getMode() == 1)
        {
            qDebug() << "点击开始回放";
            auto mode = dlg->getReadMode();
            auto cnt = dlg->getLoopCnt();
            auto channel = dlg->getPlaybackChannel();
            PlayBackWaitfinished();
//            // 创建并显示回放对话框
//            if (playbackdialog)
//            {
//                delete playbackdialog;  // 确保不会有多个实例
//            }

//            playbackdialog = new playbackDialog(this);

//            // 连接信号槽
//            connect(playbackdialog, &playbackDialog::stopRequested, this, &MainWindow::stopPlayBack);
//            connect(m_tcp, &TCPThread::stopplayback, playbackdialog, &playbackDialog::onPlaybackStopped);

//            // 处理长时间回放
//            connect(playbackdialog, &playbackDialog::playbackMaybeHanging, this, [this](int seconds)
//            {
//                // 这里使用 Qt::DirectConnection 确保在主线程处理
//                QMessageBox::information(this, "回放提示",QString("回放已持续 %1 秒，如果时间过长，可以点击停止回放按钮停止。").arg(seconds));
//            });

//            // 清理资源
//            connect(playbackdialog, &QDialog::finished, this, [this]()
//            {
//                if (playbackdialog)
//                {
//                    playbackdialog->deleteLater();
//                    playbackdialog = nullptr;
//                }
//            });
            playBack(static_cast<ReadMode>(mode), static_cast<BackGTH>(channel), cnt);
            // 显示对话框
            playbackdialog->exec(); // 使用exec()实现模态
//            isWaitingResponse = true;
        }
        else if (dlg->getMode() == 2)
        {
            qDebug() << "点击停止回放";
            stopPlayBack();
//            isWaitingResponse = true;
        }
        else if (dlg->getMode() == 3)
        {
            qDebug() << "点击多文件回放";
            dlg->close();
            ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
            MultiFilePlayBack();
        }
        else {
            qDebug() << "未知操作";
        }
    });

    // 可选：处理对话框取消/关闭的情况
    connect(dlg, &DlgPlayBackData::rejected, this, [](){
        qDebug() << "对话框被取消或关闭";
    });
}

void MainWindow::slotExport() //导出
{
    //qDebug()<<"--------------------------导出数据槽函数-----------------------------------";
    if (dlg4)
    {
        dlg4->show();
        return; // 如果对话框已经存在，直接返回
    }

    // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
    dlg4 = new DlgExportData(m_TreeItemInfo.path, this);
    // 设置关闭时自动删除（重要！防止内存泄漏）
    dlg4->setAttribute(Qt::WA_DeleteOnClose);
    // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
    connect(dlg4, &DlgExportData::finished, this, [=]() {
        dlg4 = nullptr; // 对话框关闭时将指针置为nullptr
    });
    // 使用show()代替exec()显示非模态对话框
    dlg4->show();
    // 连接对话框的完成信号（使用lambda捕获this指针）
    connect(dlg4, &DlgExportData::accepted, this, [=]()
    {
        if(dlg4->getMode() == 1 ) //单文件正常导出
        {
            if (dlg4->getLocalPath().isEmpty())
            {
                QMessageBox::critical(this, tr("错误"), tr("请选择导出到本地的文件"));
                return;
            }
            int type = dlg4->getExportType();        //获取是千兆还是万兆网
            exportFile(static_cast<NetworkPortType>(type));     //只是下发导出命令
//            emit sign_sendExportCap(m_ExportFileInfo.size);//3.15 by lyh
            if(NetworkPortType::GigabitEthernet == static_cast<NetworkPortType>(type))
            {
                emit sign_sendExportCap(m_ExportFileInfo.size);
                //qDebug()<<"使用千兆网来接收数据";
                QString log = QString("%1: 正在使用千兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                m_ExportFileInfo.localPath = dlg4->getLocalPath();
                m_ExportFileInfo.isReceivingFileInfo =true;
                //qDebug()<<"导出数据时的标志位，应该为true = "<<m_ExportFileInfo.isReceivingFileInfo;
                if(m_tcp)
                {
                    m_tcp->setExportFileInfo(m_ExportFileInfo);
                }
                stateShow->setText("导出中...");
                stateShow->setStyleSheet("color: green;");
            }           
            else
            {
                emit sign_send10GExportCap(m_ExportFileInfo.size);
                //qDebug()<<"使用万兆网来接收数据";
                QString log = QString("%1: 正在使用万兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                QString path = dlg4->getLocalPath();
                emit sign_setUdpFilePath(path);
                stateShow->setText("导出中...");
                stateShow->setStyleSheet("color: green;");
            }
        }
        else if(dlg4->getMode() == 2) //单文件百分比导出
        {
            dlg4->close();
            PercentExport();
        }
        else if(dlg4->getMode() == 3) //批量导出
        {
            dlg4->close();
            ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
            MoreFileExport();
        }
        else {
            qDebug() << "未知操作";
        }
    });

    // 可选：处理对话框取消/关闭的情况
    connect(dlg4, &DlgExportData::rejected, this, [](){
        qDebug() << "对话框被取消或关闭";
    });
}

void MainWindow::stopExport()
{
    //下发内容
    Cmd_Export_File_Func_Info cmd_stop_exportinfo;
    cmd_stop_exportinfo.order_head = ORDERHEAD;
    cmd_stop_exportinfo.head = DSV_PACKET_HEADER;
    cmd_stop_exportinfo.source_ID = 0;
    cmd_stop_exportinfo.dest_ID = 0;
    cmd_stop_exportinfo.oper_type = 0xD2;
    cmd_stop_exportinfo.oper_ID = 0x0A;
    cmd_stop_exportinfo.package_num = 0;
    cmd_stop_exportinfo.check = 0;
    cmd_stop_exportinfo.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_stop_exportinfo), sizeof(Cmd_Export_File_Func_Info));
    QString log = QString("%1:正在执行停止导出文件操作.").arg(getNowTime());
    ui->textBrowser_log->append(log);
    //记录操作类型
    lastOrderType = TYPE::STOP_EXPORT;
    emit sign_sendCmd(sendData);
}
//void MainWindow::slotExport() //导出
//{
//    //qDebug()<<"--------------------------导出数据槽函数-----------------------------------";
//    DlgExportData dlg(m_TreeItemInfo.path, this);
//    if (dlg.exec() == QDialog::Accepted)
//    {
//        if (dlg.getLocalPath().isEmpty())
//        {
//            QMessageBox::critical(this, tr("错误"), tr("请选择导出到本地的文件"));
//        }
//        else
//        {
//            int type = dlg.getExportType();        //获取是千兆还是万兆网
//            exportFile(static_cast<NetworkPortType>(type));     //只是下发导出命令
//            bool b = dlg.getIfMvpp();
//            if(NetworkPortType::GigabitEthernet == static_cast<NetworkPortType>(type))
//            {
//                //qDebug()<<"使用千兆网来接收数据";
//                QString log = QString("%1: 正在使用千兆网导出数据中...").arg(getNowTime());
//                ui->textBrowser_log->append(log);
//                m_ExportFileInfo.localPath = dlg.getLocalPath();
//                m_ExportFileInfo.isReceivingFileInfo =true;
//                //qDebug()<<"导出数据时的标志位，应该为true = "<<m_ExportFileInfo.isReceivingFileInfo;

//                m_tcp->setExportModule(b);
//                m_tcp->setExportFileInfo(m_ExportFileInfo);
//                //如果是mvpp模式，先向这个文件中写入功率和hz
//                if(b)
//                {
//                    emit sign_addTcpFileHead(dlg.getLocalPath(),dlg.m_power,dlg.m_hz);
//                }
//            }
//            else
//            {
//                //qDebug()<<"使用万兆网来接收数据";
//                QString log = QString("%1: 正在使用万兆网导出数据中...").arg(getNowTime());
//                ui->textBrowser_log->append(log);
//                m_udp->setUdpModule(b);
//                QString path = dlg.getLocalPath();
//                //m_udp->setPath(dlg.getLocalPath());
//                //m_udp->m_path = dlg.getLocalPath();
//                emit sign_setUdpFilePath(path);
//                if(b)
//                {
//                    emit sign_addUdpFileHead(dlg.getLocalPath(),dlg.m_power,dlg.m_hz);
//                }
//            }
//        }
//    }
//    else
//    {
//        //点击取消
//    }
//}

//下发导出命令
void MainWindow::exportFile(const NetworkPortType &type,uint32_t percent,uint32_t cap)
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

    cmd_export_file_func_info.export_percent = percent;
    cmd_export_file_func_info.export_cap = cap;
    cmd_export_file_func_info.check = 0;
    cmd_export_file_func_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_export_file_func_info), sizeof(Cmd_Export_File_Func_Info));

    QString log = QString("%1:正在执行导出文件[%2]操作.").arg(getNowTime()).arg(m_TreeItemInfo.name);
//    QString log = QString("%1:正在执行导出文件[%2]操作 大小:[%3].").arg(getNowTime()).arg(m_TreeItemInfo.name).arg(m_ExportFileInfo.size);
    ui->textBrowser_log->append(log);
    //记录操作类型
    lastOrderType = TYPE::EXPORT;
    emit sign_sendCmd(sendData);
}

void MainWindow::PercentExport()
{
    if (dlg5)
    {
        dlg5->show();
        return; // 如果对话框已经存在，直接返回
    }
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
    dlg5 = new dlg_percent_export_data(m_TreeItemInfo.path, this);
    // 设置关闭时自动删除（重要！防止内存泄漏）
    dlg5->setAttribute(Qt::WA_DeleteOnClose);

    // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
    connect(dlg5, &dlg_percent_export_data::finished, this, [=]() {
        dlg5 = nullptr; // 对话框关闭时将指针置为nullptr
    });
    // 使用show()代替exec()显示非模态对话框
    dlg5->show();
    qDebug() << "百分比导出操作开始";

    // 连接对话框的完成信号（使用lambda捕获this指针）
    connect(dlg5, &dlg_percent_export_data::accepted, this, [=]()
    {
        if (dlg5->getLocalPath().isEmpty())
        {
            QMessageBox::critical(this, tr("错误"), tr("请选择导出到本地的文件"));
        }
        else
        {
            auto type = dlg5->getExportType();  //获取是千兆还是万兆网
            auto percent = dlg5->getExportPercent();
            auto cap = dlg5->getExportCap();
            if((percent>100)||(percent<=0))   percent=100;
            if(cap<=0)
                export_cap=static_cast<quint64>(m_ExportFileInfo.size*percent/100);
            else
            {
                 if(cap>(m_ExportFileInfo.size/0x100000)) cap=m_ExportFileInfo.size/0x100000;
//                qDebug()<<"cap:"<<cap;
                 export_cap=static_cast<quint64>(cap*percent/100*0x100000);
            }
            exportFile(static_cast<NetworkPortType>(type),percent,cap);
            emit sign_sendExportCap(export_cap);
            if(NetworkPortType::GigabitEthernet == static_cast<NetworkPortType>(type))
            {
                //qDebug()<<"使用千兆网来接收数据";
                QString log = QString("%1: 正在使用千兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                m_ExportFileInfo.localPath = dlg5->getLocalPath();
                m_ExportFileInfo.isReceivingFileInfo =true;
                //qDebug()<<"导出数据时的标志位，应该为true = "<<m_ExportFileInfo.isReceivingFileInfo;
                m_tcp->setExportFileInfo(m_ExportFileInfo);
                stateShow->setText("导出中...");
                stateShow->setStyleSheet("color: green;");
            }
            else
            {
                //qDebug()<<"使用万兆网来接收数据";
                QString log = QString("%1: 正在使用万兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                QString path = dlg5->getLocalPath();
                emit sign_setUdpFilePath(path);
            }
        }
    });

    // 可选：处理对话框取消/关闭的情况
    connect(dlg5, &dlg_percent_export_data::rejected, this, [](){
        qDebug() << "对话框被取消或关闭";
    });
}

void MainWindow::MoreFileExport()
{
    int num=0;
    if (dlg6)
    {
        dlg6->show();
        return; // 如果对话框已经存在，直接返回
    }
    qDebug() << "对话框被取消或关闭";
    // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
    dlg6 = new dlg_export_moreFile_data(m_TreeItemInfo.path, this);
    // 设置关闭时自动删除（重要！防止内存泄漏）
    dlg6->setAttribute(Qt::WA_DeleteOnClose);

    // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
    connect(dlg6, &dlg_export_moreFile_data::finished, this, [=]() {
        dlg6 = nullptr; // 对话框关闭时将指针置为nullptr
    });
    // 使用show()代替exec()显示非模态对话框
    dlg6->show();
    qDebug() << "批量导出操作开始";

    // 连接对话框的完成信号（使用lambda捕获this指针）
    connect(dlg6, &dlg_export_moreFile_data::accepted, this, [=]()mutable
    {
        if (dlg6->getLocalPath().isEmpty())
        {
            QMessageBox::critical(this, tr("错误"), tr("请选择导出到本地的文件"));
        }
        else
        {
            auto type = dlg6->getExportType();  //获取是千兆还是万兆网
            // 获取选中项
            QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
            QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
            // 提取数据（假设为QStandardItemModel）
            QStringList selectedTexts;
            foreach (const QModelIndex &index, selectedIndexes)
            {
                if (index.column() == 0)
                {
                    QString path = buildPath(index);
        //          qDebug() << "path：" << path;
                    selectedTexts << path;
                    num++;
                }

            }
            // 使用selectedTexts进行后续操作
            // qDebug() << "选中的项：" << selectedTexts;
            qDebug() << "num：" << num;
            exportMoreFile(static_cast<NetworkPortType>(type),&selectedTexts,num);
            //计算批量导出文件的总大小
            quint64 totalSize = countSize(selectedIndexes);
            emit sign_sendExportCap(totalSize);
            if(NetworkPortType::GigabitEthernet == static_cast<NetworkPortType>(type))
            {
                //qDebug()<<"使用千兆网来接收数据";
                QString log = QString("%1: 正在使用千兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                m_ExportFileInfo.localPath = dlg6->getLocalPath();
                m_ExportFileInfo.isReceivingFileInfo =true;
                //qDebug()<<"导出数据时的标志位，应该为true = "<<m_ExportFileInfo.isReceivingFileInfo;
                m_tcp->setExportFileInfo(m_ExportFileInfo);
                stateShow->setText("导出中...");
                stateShow->setStyleSheet("color: green;");
            }
            else
            {
                //qDebug()<<"使用万兆网来接收数据";
                QString log = QString("%1: 正在使用万兆网导出数据中...").arg(getNowTime());
                ui->textBrowser_log->append(log);
                QString path = dlg6->getLocalPath();
                emit sign_setUdpFilePath(path);
            }
        }
    });

    // 可选：处理对话框取消/关闭的情况
    connect(dlg6, &dlg_export_moreFile_data::rejected, this, [](){
        qDebug() << "对话框被取消或关闭";
    });
}

void MainWindow::exportMoreFile(const NetworkPortType &type, QStringList *strlist, int Num)
{
    int j=0;
    qDebug() << "开始下发导出指令";
    //下发内容,我只需要选择文件，读取就可以了，其他不用管
    Cmd_Export_More_File_Info cmd_export_Morefile_info={0};
    cmd_export_Morefile_info.order_head = ORDERHEAD;
    cmd_export_Morefile_info.head = DSV_PACKET_HEADER;
    cmd_export_Morefile_info.source_ID = 0;
    cmd_export_Morefile_info.dest_ID = 0;
    cmd_export_Morefile_info.oper_type = 0xD2;
    cmd_export_Morefile_info.oper_ID = 0x09;
    cmd_export_Morefile_info.package_num = 0;
    cmd_export_Morefile_info.export_num = Num;

    if(NetworkPortType::GigabitEthernet == type)
    {
        cmd_export_Morefile_info.export_type = 0x00;
    }
    else
    {
        cmd_export_Morefile_info.export_type = 0x01;
    }

    cmd_export_Morefile_info.file_name=new File_Info[Num];
    foreach (const QString& str, *strlist)
    {
        qDebug() <<"str:"<< str;
        std::u16string utf16Str = str.toStdU16String();
        size_t length = utf16Str.size();
        for (size_t i = 0; i < 64; ++i)
        {
            if (i < length)
                cmd_export_Morefile_info.file_name[j].name[i] = utf16Str[i];
            else
                cmd_export_Morefile_info.file_name[j].name[i] = 0;
        }
        j++;
    }
    cmd_export_Morefile_info.check = 0;
    cmd_export_Morefile_info.end = DSV_PACKET_TAIL;

    // 1. 计算需要发送的总大小
    size_t totalSize = sizeof(uint32_t) * 11;  // 固定大小的成员
    totalSize += sizeof(File_Info) * cmd_export_Morefile_info.export_num;  // 文件信息数组的大小
    qDebug() << "totalSize:" << totalSize;
    qDebug() << "export_num:" << cmd_export_Morefile_info.export_num;
    // 2. 创建缓冲区
    QByteArray buffer;
    buffer.reserve(totalSize);
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);  // 设置字节序

    // 3. 写入固定大小的成员
    stream << cmd_export_Morefile_info.order_head
          << cmd_export_Morefile_info.head
          << cmd_export_Morefile_info.source_ID
          << cmd_export_Morefile_info.dest_ID
          << cmd_export_Morefile_info.oper_type
          << cmd_export_Morefile_info.oper_ID
          << cmd_export_Morefile_info.package_num
          << cmd_export_Morefile_info.export_type
          << cmd_export_Morefile_info.export_num;

    // 4. 写入文件信息数组
    for (uint32_t i = 0; i < cmd_export_Morefile_info.export_num; ++i) {
        // 写入每个文件名
        for (int j = 0; j < 64; ++j)
        {
            stream << quint16(cmd_export_Morefile_info.file_name[i].name[j]);
        }
    }

    // 5. 写入校验码和包尾
    stream << cmd_export_Morefile_info.check
          << cmd_export_Morefile_info.end;


    // 6. 发送数据
    QString log = QString("%1:正在执行批量回放[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
    ui->textBrowser_log->append(log);
    //记录操作类型
    lastOrderType = TYPE::EXPORT;
    emit sign_sendLenCmd(buffer,totalSize);
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::acquisition(const QString &path)
{
    //下发内容,我只需要选择文件，读取就可以了，其他不用管
    Cmd_File_Acquisition_Info cmd_file_acquisition_info;
    cmd_file_acquisition_info.order_head = ORDERHEAD;//0xBCBCAAAA
    cmd_file_acquisition_info.package_head = DSV_PACKET_HEADER;//0x55555555
    cmd_file_acquisition_info.source_ID = 0;
    cmd_file_acquisition_info.dest_ID = 0;
    cmd_file_acquisition_info.oper_type = 0xD2;
    cmd_file_acquisition_info.oper_ID = 0x03;
    cmd_file_acquisition_info.package_num = 0;
    std::u16string utf16Str_para1 = path.toStdU16String();
    size_t length1 = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i)
    {
        if(i<length1)
            cmd_file_acquisition_info.file_address[i] = utf16Str_para1[i];
        else
            cmd_file_acquisition_info.file_address[i]=0;
    }

    cmd_file_acquisition_info.check_code = 0;
    cmd_file_acquisition_info.package_tail = DSV_PACKET_TAIL;//0xAAAAAAAA
    QByteArray sendData = QByteArray((char *) (&cmd_file_acquisition_info), sizeof(Cmd_File_Acquisition_Info));

    QString log = QString("%1:正在执行采集[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
    ui->textBrowser_log->append(log);

    //记录操作类型
    lastOrderType = TYPE::Acquisition;
    emit sign_sendCmd(sendData);
}

void MainWindow::stopAcquisition(const QString &path)
{
    //下发内容,我只需要选择文件，读取就可以了，其他不用管
    Cmd_File_Acquisition_Info cmd_file_acquisition_info;
    cmd_file_acquisition_info.order_head = ORDERHEAD;//0xBCBCAAAA
    cmd_file_acquisition_info.package_head = DSV_PACKET_HEADER;//0x55555555
    cmd_file_acquisition_info.source_ID = 0;
    cmd_file_acquisition_info.dest_ID = 0;
    cmd_file_acquisition_info.oper_type = 0xD2;
    cmd_file_acquisition_info.oper_ID = 0x05;
    cmd_file_acquisition_info.package_num = 0;
    std::u16string utf16Str_para1 = path.toStdU16String();
    size_t length1 = utf16Str_para1.size();
    for (size_t i = 0; i < 1024; ++i)
    {
        if(i<length1)
            cmd_file_acquisition_info.file_address[i] = utf16Str_para1[i];
        else
            cmd_file_acquisition_info.file_address[i]=0;
    }

    cmd_file_acquisition_info.check_code = 0;
    cmd_file_acquisition_info.package_tail = DSV_PACKET_TAIL;//0xAAAAAAAA

    QByteArray sendData = QByteArray((char *) (&cmd_file_acquisition_info), sizeof(Cmd_File_Acquisition_Info));

    QString log = QString("%1:正在执行停止采集[%2]操作.").arg(getNowTime().arg(m_TreeItemInfo.name));
    ui->textBrowser_log->append(log);

    //记录操作类型
    lastOrderType = TYPE::STOPAcquisition;
    emit sign_sendCmd(sendData);
}

void MainWindow::slotAcquisition() //采集
{
    //qDebug()<<"采集操作";
    if (dlg1)
    {
        dlg1->show();
        return; // 如果对话框已经存在，直接返回
    }
    // 创建对话框对象时使用new分配在堆上（防止局部变量被销毁）
     dlg1 = new dlg_acquisition(m_TreeItemInfo.path, this);
    // 设置关闭时自动删除（重要！防止内存泄漏）
    dlg1->setAttribute(Qt::WA_DeleteOnClose);
//    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);

    // 连接对话框的关闭信号，确保在关闭时将指针置为nullptr
    connect(dlg1, &dlg_acquisition::finished, this, [=]() {
        dlg1 = nullptr; // 对话框关闭时将指针置为nullptr
    });
    // 使用show()代替exec()显示非模态对话框
    dlg1->show();
    // 连接对话框的完成信号（使用lambda捕获this指针）
    connect(dlg1, &dlg_acquisition::accepted, this, [=](){
        auto strPath = dlg1->getLocalPath();
        if(dlg1->getMode() == 1) {
            qDebug() << "发送开始采集";
            acquisition(strPath);
//            isWaitingResponse = true;
            //  之后需要接收下位机发送过来的执行指令，如果准备好了再发，否则发执行错误
        }
        else if (dlg1->getMode() == 2) {
            qDebug() << "发送停止采集指令" ;
            stopAcquisition(strPath);
//            isWaitingResponse = true;
        }
        else {
            qDebug() << "未知操作";
        }
    });

    // 可选：处理对话框取消/关闭的情况
    connect(dlg1, &dlg_acquisition::rejected, this, [](){
        qDebug() << "对话框被取消或关闭";
    });
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

void MainWindow::updateStatusLabel(const QColor &color)
{
    QPixmap pixmap(20, 20);
    if (pixmap.isNull()) return;
    pixmap.fill(Qt::transparent); // 透明背景

    QPainter painter(&pixmap);
    if (!painter.isActive()) return;
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter.setBrush(color);       // 设置画刷颜色
    painter.setPen(Qt::NoPen);     // 无边线
    painter.drawEllipse(0, 0, 20, 20); // 绘制圆形

    fiberStateShow->setPixmap(pixmap); // 设置图标
    fiberStateShow->setText("");       // 清除文本
}

void MainWindow::setFiberStatus(FiberStatus status)
{
    switch (status)
    {
        case StatusUnknown:
            fiberStateShow->setPixmap(QPixmap()); // 清除图标
            fiberStateShow->setText("未知");       // 显示文本
            break;
        case StatusConnected:
            updateStatusLabel(Qt::green);     // 绿色图标
            break;
        case StatusDisconnected:
            updateStatusLabel(Qt::red);        // 红色图标
            break;
    }
}

void MainWindow::showIPDialog()
{
    IPDialog *dialog = new IPDialog(this);
    connect(dialog, &IPDialog::ipSelected, this, &MainWindow::updateIPData);
    dialog->exec();
    delete dialog;
}

void MainWindow::updateIPData(const QString &ipAddress)
{
    uint ips[4];
    QStringList parts = ipAddress.split(".");
    for (int i = 0; i < 4; ++i)
    {
        ips[i] = parts[i].toUInt();
//        qDebug()<<value;
    }
    // 将 4 个部分合并为一个 uint
    uint combinedIP = (ips[0] << 24) | (ips[1] << 16) | (ips[2] << 8) | ips[3];
//    qDebug()<<combinedIP;

    Cmd_Disk_IPSET cmd_disk_info;
    cmd_disk_info.order_head = ORDERHEAD;
    cmd_disk_info.head = DSV_PACKET_HEADER;
    cmd_disk_info.source_ID = 0;
    cmd_disk_info.dest_ID = 0;
    cmd_disk_info.oper_type = 0xB2;
    cmd_disk_info.oper_ID = 0x02;
    cmd_disk_info.package_num = 0;
    cmd_disk_info.IPADDR = combinedIP;
    cmd_disk_info.check = 0;
    cmd_disk_info.end = DSV_PACKET_TAIL;
    QByteArray sendData = QByteArray((char *) (&cmd_disk_info), sizeof(Cmd_Disk_IPSET));
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
void MainWindow::slot_recvDiskData(const Cmd_Disk_State_Info &data)
{
    //qDebug() << "收到了磁盘的状态信息";
    ui->textBrowser_log->append(QString("%1: 收到了回复的磁盘状态信息.").arg(getNowTime()));

    QString diskTotal = QString::number((data.disk_total) / (1024 * 1024));
    totalShow->setText(diskTotal);
    QString diskUsed = QString::number((data.disk_used) / (1024 * 1024));
    usedShow->setText(diskUsed);
    QString diskRest = QString::number((data.disk_rest) / (1024 * 1024));
    restShow->setText(diskRest);
    QString fileNum = QString::number(data.file_num);
    fileNumShow->setText(fileNum);

    QString state = QString::number(data.disk_state);
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

    QString T = QString::number(data.disk_t);
    tShow->setText(T);
    QString power = QString::number(data.disk_power);
    powerShow->setText(power);

}

void MainWindow::slot_StandardItemModel(QStandardItemModel *data)
{

    //qDebug() << "接收到目录树信息";
    Model=data;//LYH 2.20
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

void MainWindow::onExportProgress(int percent)
{
    if (!progressDialog)
    {
        progressDialog = new QProgressDialog(this);
        //设置尺寸策略
        progressDialog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        // 设置最小尺寸
        progressDialog->setMinimumSize(400, 150);
        // 设置最大尺寸（如果需要限制最大尺寸）
        progressDialog->setMaximumSize(800, 300);
        progressDialog->setWindowTitle(tr("导出进度"));
        progressDialog->setCancelButtonText(tr("停止导出")); // 修改取消按钮文本
//        progressDialog->setCancelButton(nullptr); // 禁用取消按钮
        progressDialog->setMinimumDuration(0);    // 立即显示
        //如果使用非模态窗口，则注释掉下面语句
        progressDialog->setModal(true); // 强制模态
        // 移除关闭按钮（需保留其他标志，避免影响窗口行为）
        progressDialog->setWindowFlags(progressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);

        // 连接取消按钮点击信号
        connect(progressDialog, &QProgressDialog::canceled, this, &MainWindow::onStopExport);
    }
    // 只在进度小于100时更新进度条
    if (percent < 100) {
        progressDialog->setValue(percent);
        progressDialog->show();
    }
}

//void MainWindow::SetExportProgress(int percent)
//{
//    progressDialog->setValue(percent);
//    progressDialog->show();
//}

void MainWindow::onExportFinished()
{
    if (progressDialog)
    {
        // 在关闭对话框前断开信号连接
        disconnect(progressDialog, &QProgressDialog::canceled, this, &MainWindow::onStopExport);
        progressDialog->close();
        delete progressDialog;
        progressDialog = nullptr;
    }
    QMessageBox::information(this, tr("完成"), tr("文件导出成功！"));
}

void MainWindow::onStopExport()
{
    // 只有在导出过程中才处理中止操作
    if (progressDialog && progressDialog->value() < 100)
    {
        stopExport();
//        QThread::usleep(1000);
        if (m_tcp)
        {
             m_tcp->abortExport(); // 调用TCPThread的中止方法
        }
        // 关闭进度对话框
        progressDialog->close();
        delete progressDialog;
        progressDialog = nullptr;
        QMessageBox::information(this, tr("提示"), tr("导出已中止"));
    }
}

void MainWindow::PlayBackWaitfinished()
{
    // 创建并显示回放对话框
    if (playbackdialog)
    {
        delete playbackdialog;  // 确保不会有多个实例
    }

    playbackdialog = new playbackDialog(this);

    // 连接信号槽
    connect(playbackdialog, &playbackDialog::stopRequested, this, &MainWindow::stopPlayBack);
    connect(m_tcp, &TCPThread::stopplayback, playbackdialog, &playbackDialog::onPlaybackStopped);

    // 处理长时间回放
    connect(playbackdialog, &playbackDialog::playbackMaybeHanging, this, [this](int seconds)
    {
        // 这里使用 Qt::DirectConnection 确保在主线程处理
        QMessageBox::information(this, "回放提示",QString("回放已持续 %1 秒，如果时间过长，可以点击停止回放按钮停止。").arg(seconds));
    });

    // 清理资源
    connect(playbackdialog, &QDialog::finished, this, [this]()
    {
        if (playbackdialog)
        {
            playbackdialog->deleteLater();
            playbackdialog = nullptr;
        }
    });
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
    SpeedShow->setText(QString::number(data));
}

void MainWindow::slot_udpInfo()
{
    m_udpInfoWidget->show();
}

void MainWindow::onTreeViewClicked(const QModelIndex &index)
{
    if(!index.isValid()) return; //确认索引有效

    if(dlg)
    {
        dlg->setPath(m_TreeItemInfo.path);
    }
    if(dlg1)
    {
        dlg1->setPath(m_TreeItemInfo.path);
    }
    if(dlg2)
    {
        dlg2->setPath(m_TreeItemInfo.path);
    }
    if(dlg3)
    {
        dlg3->setPath(m_TreeItemInfo.path);
    }
    if(dlg4)
    {
        dlg4->setPath(m_TreeItemInfo.path);
    }
    if(dlg5)
    {
        dlg5->setPath(m_TreeItemInfo.path);
    }
    if(dlg6)
    {
        dlg6->setPath(m_TreeItemInfo.path);
    }
}

IPDialog::IPDialog(QWidget *parent): QDialog(parent)
{
        setWindowTitle("设置IP地址");
        setFixedSize(800, 600);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 添加说明标签
        QLabel *descLabel = new QLabel("IP地址对应关系:", this);
        descLabel->setStyleSheet("font-weight: bold; margin-bottom: 5px;");
        mainLayout->addWidget(descLabel);

        // 创建对应关系表格
        QGridLayout *ipMapLayout = new QGridLayout();
        ipMapLayout->addWidget(new QLabel("选项", this), 0, 0);
        ipMapLayout->addWidget(new QLabel("对应IP地址", this), 0, 1);

        // 添加对应关系
        for(int i = 1; i <= 3; i++) {
            QLabel *numLabel = new QLabel(QString::number(i), this);
            QLabel *ipLabel = new QLabel(getIPAddressForType(i), this);

            numLabel->setStyleSheet("padding: 5px; background-color: #f0f0f0;");
            ipLabel->setStyleSheet("padding: 5px; background-color: #f0f0f0;");

            ipMapLayout->addWidget(numLabel, i, 0);
            ipMapLayout->addWidget(ipLabel, i, 1);
        }

        // 添加默认值说明
        QLabel *defaultLabel = new QLabel("默认值/其他: 192.168.0.32", this);
        defaultLabel->setStyleSheet("color: #666666; padding: 5px;");
        ipMapLayout->addWidget(defaultLabel, 5, 0, 1, 2);

        // 将对应关系表格添加到主布局
        mainLayout->addLayout(ipMapLayout);

        // 添加分隔线
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        mainLayout->addWidget(line);

        // 添加选择区域
        QGridLayout *selectionLayout = new QGridLayout();
        QLabel *selectLabel = new QLabel("请选择IP类型:", this);
        ipComboBox = new QComboBox(this);
        ipComboBox->addItem("1");
        ipComboBox->addItem("2");
        ipComboBox->addItem("3");
//        ipComboBox->addItem("4");

        selectionLayout->addWidget(selectLabel, 0, 0);
        selectionLayout->addWidget(ipComboBox, 0, 1);
        mainLayout->addLayout(selectionLayout);

        // 添加当前选择的IP显示
        QLabel *currentSelectionLabel = new QLabel("当前选择的IP地址:", this);
        QLabel *currentIPLabel = new QLabel(getIPAddressForType(1), this);
        currentIPLabel->setStyleSheet("font-weight: bold; color: #0066cc;");

        QHBoxLayout *currentSelectionLayout = new QHBoxLayout();
        currentSelectionLayout->addWidget(currentSelectionLabel);
        currentSelectionLayout->addWidget(currentIPLabel);
        mainLayout->addLayout(currentSelectionLayout);

        // 添加弹簧
        mainLayout->addStretch();

        // 添加IP地址输入区域（移到底部）
        QHBoxLayout *ipInputLayout = new QHBoxLayout();
        QLabel *ipLabel = new QLabel("IP地址:", this);
        ipLineEdit = new QLineEdit(this);
        ipLineEdit->setPlaceholderText("请输入IP地址");
        ipLineEdit->setMinimumWidth(300); // 设置最小宽度

        ipInputLayout->addWidget(ipLabel);
        ipInputLayout->addWidget(ipLineEdit);
        mainLayout->addLayout(ipInputLayout);

        // 按钮布局
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        QPushButton *okButton = new QPushButton("确定", this);
        QPushButton *cancelButton = new QPushButton("取消", this);

        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        mainLayout->addLayout(buttonLayout);

        // 连接信号槽
        connect(okButton, &QPushButton::clicked, this, &IPDialog::onOKClicked);
        connect(cancelButton, &QPushButton::clicked, this, &IPDialog::reject);
        connect(ipComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                [=](int index) {
                    currentIPLabel->setText(getIPAddressForType(index + 1));
                });

        // 设置边距
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(15);
}




//IPDialog::IPDialog(QWidget *parent): QDialog(parent)
//{
//    setWindowTitle("设置IP地址");
//    setFixedSize(500, 200);

//    QVBoxLayout *mainLayout = new QVBoxLayout(this);
//    // 添加IP地址输入区域（移到底部）
//    QHBoxLayout *ipInputLayout = new QHBoxLayout();
//    QLabel *ipLabel = new QLabel("IP地址:", this);
//    ipLineEdit = new QLineEdit(this);
//    ipLineEdit->setPlaceholderText("请输入IP地址");
//    ipLineEdit->setMinimumWidth(300); // 设置最小宽度

//    ipInputLayout->addWidget(ipLabel);
//    ipInputLayout->addWidget(ipLineEdit);
//    mainLayout->addLayout(ipInputLayout);

//    // 按钮布局
//    QHBoxLayout *buttonLayout = new QHBoxLayout();
//    QPushButton *okButton = new QPushButton("确定", this);
//    QPushButton *cancelButton = new QPushButton("取消", this);

//    buttonLayout->addStretch();
//    buttonLayout->addWidget(okButton);
//    buttonLayout->addWidget(cancelButton);
//    mainLayout->addLayout(buttonLayout);
//    // 连接信号槽
//    connect(okButton, &QPushButton::clicked, this, &IPDialog::onOKClicked);
//    connect(cancelButton, &QPushButton::clicked, this, &IPDialog::reject);
//}

void IPDialog::onOKClicked()
{
    QString ipAddress = ipLineEdit->text().trimmed();

    if (ipAddress.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入IP地址");
//        return;
    }

    if (!validateIPAddress(ipAddress)) {
        QMessageBox::warning(this, "警告", "请输入有效的IP地址");
//        return;
    }
    emit ipSelected(ipAddress);
    accept();
}

bool IPDialog::validateIPAddress(const QString &ip)
{
    QStringList parts = ip.split(".");
    if (parts.size() != 4) return false;

    for (const QString &part : parts) {
        bool ok;
        int value = part.toInt(&ok);
        if ((!ok)||(value < 0) || (value > 255)) return false;
    }
    return true;
}
