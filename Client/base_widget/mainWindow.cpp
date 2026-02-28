#include "MainWindow.h"

//#include "ui_QQ.h"
#include <QGroupBox>
#include <QStackedWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QWindow>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>


QQ::QQ(QWidget *parent) : QMainWindow(parent)
{   
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    this->resize(1025, 655);
    this->setMinimumSize(820, 580);
    this->setStyleSheet("QMainWindow{background-color:#ffffff;}");
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    widgetInit();
    signal();

}

QQ::~QQ()
{}

void QQ::widgetInit()
{
    //---------------------GroupBox_top 标题栏----------------------
    groupBox_top = new QGroupBox(centralWidget);
    groupBox_top->setFixedHeight(35);
    groupBox_top->setStyleSheet("QGroupBox{border:none;border-bottom:1px solid #cccccc;background-color:#fafafa;}");
    groupBox_top->installEventFilter(this);

    //btn
    btn_MainWindow_min = new QPushButton(groupBox_top);
    btn_MainWindow_min->setFixedSize(30, 30);
    //TODO按钮样式
    /*btn_MainWindow_min->setStyleSheet(
        "QPushButton:hover{background-color:#f8f8f8;}"
        "QPushButton{border-radius:5px;}"
    );*/
    btn_MainWindow_max = new QPushButton(groupBox_top);
    btn_MainWindow_max->setFixedSize(30, 30);

    btn_MainWindow_close = new QPushButton(groupBox_top);
    btn_MainWindow_close->setFixedSize(30, 30);

    //SpacerItem 顶部弹簧
    spacer_groupBoxTop = new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Preferred);

    //顶部布局
    horizontal_groupBoxTop = new QHBoxLayout(groupBox_top);
    horizontal_groupBoxTop->addItem(spacer_groupBoxTop);
    horizontal_groupBoxTop->addWidget(btn_MainWindow_min);
    horizontal_groupBoxTop->addWidget(btn_MainWindow_max);
    horizontal_groupBoxTop->addWidget(btn_MainWindow_close);
    horizontal_groupBoxTop->setSpacing(3);  //控件间距
    horizontal_groupBoxTop->setContentsMargins(0, 0, 5, 0);



    //------------------GroupBox_left 侧边栏------------------
    groupBox_left = new QGroupBox(centralWidget);
    groupBox_left->setFixedWidth(55);
    groupBox_left->setStyleSheet("border:none;");
    groupBox_left->installEventFilter(this);
    leftBar = new LeftBar(centralWidget);
    QVBoxLayout* groupBox_left_layout = new QVBoxLayout(groupBox_left);
    groupBox_left_layout->setContentsMargins(0, 0, 0, 0);
    groupBox_left_layout->addWidget(leftBar);



    //-------------------groupBox_mid 中间列表区域-----------------
    groupBox_mid = new QGroupBox(centralWidget);
    groupBox_mid->setFixedWidth(250);
    //groupBox_mid->setStyleSheet("QGroupBox{border:none;border-left:1px solid #cccccc;border-right:1px solid #cccccc;background-color:#ccffff;}");

    //搜索框
    search_label = new QLabel;
    search_label->setFixedHeight(40);
    

    lineEdit_search = new QLineEdit(search_label);
    lineEdit_search->setFixedHeight(30);
    lineEdit_search->setStyleSheet("QLineEdit{border:1px solid #c7c7c7;border-radius:10px;font-size:14px;}");
    lineEdit_search->setPlaceholderText("搜索");
    QAction* searchIcon = new QAction(QIcon(":/Image/resource/search.png"), "", lineEdit_search);
    lineEdit_search->addAction(searchIcon, QLineEdit::LeadingPosition);

    btn_menu = new QPushButton(search_label);
    btn_menu->setFixedSize(30, 30);

    menu_more = new QMenu(btn_menu);
    QAction* action_createGroup = menu_more->addAction("创建群聊");
    QAction* action_addFriend = menu_more->addAction("加好友/群");
    btn_menu->setMenu(menu_more);
    connect(action_addFriend, &QAction::triggered, this, &QQ::raiseAddFriendWindow);

    search_layout = new QHBoxLayout(search_label);
    search_layout->addWidget(lineEdit_search);
    search_layout->addWidget(btn_menu);
    search_layout->setContentsMargins(25, 0, 25, 0);

    //Page 页面切换控件
    stackedWidget_left = new QStackedWidget(groupBox_mid);
    stackedWidget_left->setFixedWidth(250);
    //stackedWidget_left->setStyleSheet("border:none;border-left:1px solid #cccccc;border-right:1px solid #cccccc;background-color:#ccffff;");


    //消息页面
    messageList = new MessageList(groupBox_mid);
    //联系人页面
    contacts = new Contacts(groupBox_mid);

    //添加页面
    stackedWidget_left->addWidget(messageList);    //消息页面
    stackedWidget_left->addWidget(contacts);  //联系人页面
    stackedWidget_left->setCurrentIndex(messagePage);



    //中间列表区域布局
    verticalMessage_layout = new QVBoxLayout;
    verticalMessage_layout->addWidget(search_label);
    verticalMessage_layout->addWidget(stackedWidget_left);
    verticalMessage_layout->setSpacing(0);
    verticalMessage_layout->setContentsMargins(0, 0, 0, 0);
    groupBox_mid->setLayout(verticalMessage_layout);
    

    //--------------------------groupBox_right 聊天区域------------------------
    groupBox_right = new QGroupBox(centralWidget);
    //widget_Message->setStyleSheet("background-color: rgb(225, 225, 225);");


    //---------------------------主窗口布局-------------------------------
    //horizontal
    horizontal_Main = new QHBoxLayout;
    horizontal_Main->addWidget(groupBox_left);
    horizontal_Main->addWidget(groupBox_mid);
    horizontal_Main->addWidget(groupBox_right);
    horizontal_Main->setSpacing(0);
    horizontal_Main->setContentsMargins(0, 0, 0, 0);

    //vertical
    vertical_Main = new QVBoxLayout;
    vertical_Main->addWidget(groupBox_top);
    vertical_Main->addLayout(horizontal_Main);
    vertical_Main->setSpacing(0);
    vertical_Main->setContentsMargins(0, 0, 0, 0);

    centralWidget->setLayout(vertical_Main);
}

bool QQ::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == groupBox_top || watched == groupBox_left)
    {
        auto* e = static_cast<QMouseEvent*>(event); //鼠标按下或释放事件
        //鼠标双击
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            if (e->button() == Qt::LeftButton)
                on_btn_Max_clicked();
        }
        if (e->button() == Qt::LeftButton)
        {
            if (window()->windowHandle())
                window()->windowHandle()->startSystemMove();
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void QQ::signal()
{
    QObject::connect(btn_MainWindow_min, SIGNAL(clicked()), this, SLOT(showMinimized()));
    QObject::connect(btn_MainWindow_max, SIGNAL(clicked()), this, SLOT(on_btn_Max_clicked()));
    QObject::connect(btn_MainWindow_close, SIGNAL(clicked()), this, SLOT(close()));

    connect(leftBar->get_btn_messageList(), &QPushButton::clicked, this, [=]() {
        on_change_page(messagePage);
        });

    QObject::connect(leftBar->get_btn_contact(), &QPushButton::clicked, this, [=]() {
        on_change_page(contactsPage);
        });
}

void QQ::raiseAddFriendWindow()
{
    //680x420
    AddFriendWindow::getInstance()->show();
    //唤起窗口到前台
    AddFriendWindow::getInstance()->setWindowState(
        AddFriendWindow::getInstance()->windowState() & ~Qt::WindowMinimized
    );
    AddFriendWindow::getInstance()->raise();
    AddFriendWindow::getInstance()->activateWindow();


}

void QQ::on_btn_Max_clicked()
{
    if (this->isMaximized())
    {
        this->showNormal();
        //TODO更换图标
    }
    else
    {
        this->showMaximized();
        //TODO更换图标
    }
}

void QQ::on_change_page(int page)
{
    stackedWidget_left->setCurrentIndex(page);
}





