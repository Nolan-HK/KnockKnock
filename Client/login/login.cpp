#include "login.h"
#include "../register/register.h"
#include "../util/avatar.h"
#include "../util/title.h"
#include "../socket/clientSocket.h"
#include "../util/util.h"

#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QWindow>
#include <QMovie>
#include <QMessageBox>
#include <QDir>


#define window_h 460
#define window_w 320


LoginBase::LoginBase(QWidget* parent) : QWidget(parent)
{
	this->setFixedSize(QSize(window_w, window_h));
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动销毁,自动断开所有signal
	InitWidget();
    connect(btn_close, &QPushButton::clicked, this, &LoginBase::close);
    connect(btn_registerPage, &QPushButton::clicked, this, &LoginBase::ShowRegister);
    

    //初始化tcpSocket
    tcpSocket = new ClientSocket;
    tcpSocket->connectedToHost("127.0.0.1", 65535); //TODO
}

LoginBase::~LoginBase()
{
}

void LoginBase::InitWidget()
{
    
    // 设置背景
    QLabel* bgLabel = new QLabel(this);
    bgLabel->setGeometry(this->rect());
    bgLabel->lower();
    bgLabel->setScaledContents(true);

    QPixmap pixmap(":/Image/resource/login_background.png");
    bgLabel->setPixmap(pixmap);

    //顶部容器
    label_topBar = new QLabel;
    label_topBar->installEventFilter(this);
    label_topBar->setFixedHeight(40);

    btn_close = new QPushButton;
    btn_close->setFixedSize(30, 30);
    btn_close->setIcon(QIcon(":/Image/resource/close.png"));
    btn_close->setStyleSheet(
        "QPushButton:hover{background-color:#c42b1c;}"
        "QPushButton{border-radius:5px;}"
    );
    //顶部容器布局
    hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(btn_close);
    hlayout->setContentsMargins(4, 4, 4, 4);

    label_topBar->setLayout(hlayout);

    //账密登录页
    loginPage = new QWidget;
    loginPage->setFixedWidth(window_w);

    //LOGO
    //label_logo = new Title;
    //label_logo->setText("Knock Knock");
    //label_logo->setFont(QFont("微软雅黑", 20, QFont::Bold));
    //label_logo->setAlignment(Qt::AlignHCenter);
     
    //头像
    label_avatar = new Avatar(nullptr,":/Image/resource/default.jpg", 80, 80);
    //label_avatar->setPixmap(QPixmap(":/Image/resource/avatar.jpg"));

    //账号框
    lineEdit_account = new QLineEdit;
    lineEdit_account->setMaxLength(255);
    lineEdit_account->setPlaceholderText("输入Knock Knock号");
    lineEdit_account->setFixedHeight(40);
    lineEdit_account->setFont(QFont("Microsoft YaHei UI", 12));
    lineEdit_account->setAlignment(Qt::AlignCenter);
    lineEdit_account->setStyleSheet(
        "QLineEdit {"
        " padding: 10px 70px;" //上下 左右
        "border:none;"
        "border-radius: 10px;"
        "}"
    );
    //根据输入的账号显示对应头像
    connect(lineEdit_account, &QLineEdit::textChanged, this, [this](const QString& uid) {
        QString fileName;
        QDir dir;
        QStringList avatarList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot); //排除.和..这两个特殊目录
        QString fileSuffix;
        for (const QString& filePrefixName : avatarList)
        {
            QFileInfo info(filePrefixName);
            if (info.completeBaseName() == uid) //TODO后期改为读取最新时间名称的头像文件(uid_time.jpg)
            {
                fileSuffix = info.suffix(); //获取头像文件夹下的头像文件名称后缀
                fileName = info.fileName();
                break;
            }
        }
        
        qDebug() << fileName;
        label_avatar->setAvatar("recv/" + uid + "/avatar/" + fileName);
        });

    //密码框
    lineEdit_passwd = new QLineEdit;
    lineEdit_passwd->setMaxLength(255);
    lineEdit_passwd->setPlaceholderText("输入密码");
    lineEdit_passwd->setFixedHeight(40);
    lineEdit_passwd->setFont(QFont("Microsoft YaHei UI", 12));
    lineEdit_passwd->setAlignment(Qt::AlignCenter);
    lineEdit_passwd->setEchoMode(QLineEdit::Password);
    lineEdit_passwd->setStyleSheet(
        "QLineEdit {"
        " padding: 10px 70px;" //上下 左右
        "border:none;"
        "border-radius: 10px;"
        "}"
    );

    //隐藏按钮跟随输入框
    btn_showPwd = new QPushButton(lineEdit_passwd);
    btn_showPwd->setStyleSheet("border:none; padding: 0px;");
    btn_showPwd->setIcon(QIcon(":/Image/resource/eye_hide.png"));
    btn_showPwd->setIconSize(QSize(23, 23));	// 设置图标大小
    btn_showPwd->setCursor(Qt::ArrowCursor);
    btn_showPwd->setGeometry(lineEdit_passwd->width() - 410, 10, 25, 25);
    // 长按显示密码
    connect(btn_showPwd, &QPushButton::pressed, [=]() {
        lineEdit_passwd->setEchoMode(QLineEdit::Normal);
        btn_showPwd->setIcon(QIcon(":/Image/resource/eye_show.png"));
        });
    connect(btn_showPwd, &QPushButton::released, [=]() {
        lineEdit_passwd->setEchoMode(QLineEdit::Password);
        btn_showPwd->setIcon(QIcon(":/Image/resource/eye_hide.png"));
        });

    checkBox_autoLogin = new QCheckBox;
    checkBox_autoLogin->setText("自动登录");
    checkBox_autoLogin->setStyleSheet(
        "QCheckBox{color:#6d6d6d;}"
        "QCheckBox::indicator {"
        "  width: 14px;"
        "  height: 14px;"
        "  border-radius: 8px;"
        "  border: 1px solid #6d6d6d;"
        "  background: none;"
        "}"
        "QCheckBox::indicator:checked {"
        "  border: 1px solid #409EFF;"
        "  image: url(:/Image/resource/selected.png);"
        "}"
        "QCheckBox::indicator::hover {"
        "background-color: #d0d0d0;"
        "}"
    );


    checkBox_savePasswd = new QCheckBox;
    checkBox_savePasswd->setText("记住密码");
    checkBox_savePasswd->setStyleSheet(
        "QCheckBox{color:#6d6d6d;}"
        "QCheckBox::indicator {"
        "  width: 14px;"
        "  height: 14px;"
        "  border-radius: 8px;"
        "  border: 1px solid #6d6d6d;"
        "  background: none;"
        "}"
        "QCheckBox::indicator:checked {"
        "  border: 1px solid #409EFF;"
        "  image: url(:/Image/resource/selected.png);"
        "}"
        "QCheckBox::indicator::hover {"
        "background-color: #d0d0d0;"
        "}"
    );

    //登录按钮
    btn_login = new QPushButton("登录");
    btn_login->setFixedSize(256, 40);
    btn_login->setStyleSheet(
        "QPushButton{"
            "background-color: #0094f7; "
            "font: 12pt Microsoft YaHei UI;"
            "color: #ffffff;"
            "border-radius: 10px;"
        "}"
        "QPushButton::hover{"
            "background-color: #008deb;"
        "}"
        "QPushButton::pressed{"
            "background-color: #0081d6;"
        "}"
    );
    //执行登录
    connect(btn_login, &QPushButton::clicked, [=]() {
        QJsonObject json;
        tcpSocket->setUserID(lineEdit_account->text().toInt());
        json.insert("uid", lineEdit_account->text());
        json.insert("passwd", lineEdit_passwd->text());
        emit signalLogin(json);
        });

    connect(this, &LoginBase::signalLogin, this, [this](const QJsonObject& data){
        tcpSocket->sltSendMessage(Login, data);
        });
    //登录结果
    //connect(msgProcess, &MessageParser::msgReturn, this, [this](const QJsonObject& data) {
    //    LoginResult(data);
    //    });


    //接收错误消息
    //connect(MessageParser::getInstance(), &MessageParser::connectStatus, [](const QString& status) {
    //    QMessageBox::warning(nullptr, "错误", "服务器连接失败：" + status, QMessageBox::Ok);
    //    qDebug() << "连接服务器失败：" << status;
    //    });

    //注册按钮
    btn_registerPage = new QPushButton("注册账号");
    //btn_registerPage->setFixedSize()
    btn_registerPage->setStyleSheet("QPushButton{border:none;font: 10pt Microsoft YaHei UI;color:#2d77e5;}");
    btn_registerPage->setCursor(Qt::PointingHandCursor);


    hlayout_loginPage = new QHBoxLayout;
    hlayout_loginPage->addWidget(checkBox_autoLogin);
    hlayout_loginPage->addStretch();
    hlayout_loginPage->addWidget(checkBox_savePasswd);

    vlayout_loginPage = new QVBoxLayout;
    //vlayout_loginPage->addWidget(label_logo);
    vlayout_loginPage->addWidget(label_avatar, 0, Qt::AlignHCenter);  //水平居中，垂直不变
    vlayout_loginPage->addSpacing(20);
    vlayout_loginPage->addWidget(lineEdit_account);
    vlayout_loginPage->addSpacing(5);
    vlayout_loginPage->addWidget(lineEdit_passwd);
    vlayout_loginPage->addSpacing(10);
    vlayout_loginPage->addLayout(hlayout_loginPage);
    vlayout_loginPage->addSpacing(30);
    vlayout_loginPage->addWidget(btn_login);
    vlayout_loginPage->addStretch();
    vlayout_loginPage->addWidget(btn_registerPage);

    vlayout_loginPage->setContentsMargins(30, 0, 30, 0);
    loginPage->setLayout(vlayout_loginPage);


    //添加页面
    stackedWidget = new QStackedWidget(this);
    stackedWidget->setFixedWidth(window_w);
    stackedWidget->addWidget(loginPage);
    stackedWidget->setCurrentWidget(loginPage);



    //全体布局
    vlayout_base = new QVBoxLayout;
    vlayout_base->addWidget(label_topBar);
    vlayout_base->addWidget(stackedWidget);
    //vlayout->addWidget(label_logo);
    //vlayout->addSpacing(20);
    //vlayout->addWidget(label_avatar, 0, Qt::AlignHCenter);  //水平居中，垂直不变
    vlayout_base->setContentsMargins(0, 0, 0, 0);
    vlayout_base->addStretch();
    this->setLayout(vlayout_base);

    
}

void LoginBase::LoginResult(const QJsonObject& data)
{
    qDebug() << "登录结果：" <<data;
    //QJsonObject jsonObj = msgProcess->converToJson(data);
    if (data.value("type").toInt() != msg_type::LoginResult)
        return;

    //280x160
    QDialog* dialog = new QDialog(this);
	dialog->setFixedSize(280, 160);
	dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	dialog->setAttribute(Qt::WA_TranslucentBackground);

	QVBoxLayout* dialogLayout = new QVBoxLayout(dialog);
	dialogLayout->setContentsMargins(0, 0, 0, 0);

	QWidget* container = new QWidget;
	container->setObjectName("container");
	container->setStyleSheet(
		"QWidget#container {"
		"background-color:#ffffff;"
		"border-radius:15px;"
		"}"
	);

	QLabel* label = new QLabel;
	label->setAlignment(Qt::AlignLeft);
	//label->setFont(QFont("Microsoft YaHei UI", 16));
	QPushButton* btn_back = new QPushButton;
	btn_back->setFixedSize(80, 35);
	btn_back->setStyleSheet(
		"QPushButton{"
		"background-color: #ffffff; "
		"font: 12pt Microsoft YaHei UI;"
		"color: #000000;"
        "border:1px solid #0081d6;"
		"border-radius: 10px;"
		"}"
		"QPushButton::hover{"
		"background-color: #008deb;"
		"}"
		"QPushButton::pressed{"
		"background-color: #0081d6;"
		"}"
	);
    QPushButton* btn_findBack = new QPushButton;
    btn_findBack->setFixedSize(80, 35);
    btn_findBack->setStyleSheet(
        "QPushButton{"
        "background-color: #0094f7;"
        "font: 12pt Microsoft YaHei UI;"
        "color: #ffffff;"
        "border-radius: 10px;"
        "}"
        "QPushButton::hover{"
        "background-color: #008deb;"
        "}"
        "QPushButton::pressed{"
        "background-color: #0081d6;"
        "}"
    );
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(btn_findBack);
    hlayout->addWidget(btn_back);

	QVBoxLayout* vlayout = new QVBoxLayout(container);
	vlayout->addWidget(label);
	vlayout->addStretch();
	vlayout->addLayout(hlayout);  //水平居右，垂直不变

	dialogLayout->addWidget(container);
	int msg_type = data.value("status").toInt();

	if (msg_type == Failed)
	{
        btn_findBack->setText("忘记密码");
		btn_back->setText("重新登录");
		label->setText(
			"<div align='center' style='padding-left:20px; padding-right:20px;padding-top:50px;text-align:left;'>"
				"<div style='font-size:12pt; font-weight:bold;'>""登录失败""</div>""<br>"
				"<div style='font-size:11pt;'>""账号或密码错误，请重新输入。""</div>"
			"</div>"
		);
        dialog->setModal(true);	//阻止点击父窗口
        dialog->show();
		
	}
	else
	{
        emit signalLoginSuccess();
	}

	connect(btn_back, &QPushButton::clicked, this, [msg_type, dialog]() {
		if (msg_type == Failed)
            dialog->close();
		});
}

void LoginBase::ShowRegister()
{
    RegisterPage* registerPage = new RegisterPage(nullptr);
    connect(btn_close, &QPushButton::clicked, registerPage, &QWidget::close);   //不会与主窗口为一体，且随主窗口销毁TODO
    registerPage->show();
}

//移动事件
bool LoginBase::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == label_topBar && event->type() == QEvent::MouseButtonPress)
    {
        auto* e = static_cast<QMouseEvent*>(event);
        if (e->button() == Qt::LeftButton) {
            if (window()->windowHandle())
                window()->windowHandle()->startSystemMove();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}