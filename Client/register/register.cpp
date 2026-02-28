#include "register.h"
#include "../util/avatar.h"
#include "avatar_popup.h"
//#include "../socket/networkManager.h"
#include "../util/util.h"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QGridLayout>
#include <QApplication>
#include <QClipboard>


RegisterPage::RegisterPage(QWidget* parent) : QDialog(parent)
{
	this->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动销毁,自动断开所有signal
	this->setFixedSize(400, 428);
	this->setWindowFlags(Qt::Window);
	this->setWindowTitle("注册Knock Knock");
	this->setObjectName("baseWidget");	//对象名称
	//设置背景渐变
	this->setStyleSheet(
		"QWidget#baseWidget"
		"{background: qlineargradient("
			"x1:0,y1:0,"
			"x2:0,y2:1,"
			"stop:0 #fde7f3,"
			"stop:0.35 #f3e8ff,"
			"stop:0.65 #e8f6ff,"
			"stop:1 #e6fff9"
			");"
		"}"
	);
	InitWidget();

}

RegisterPage::~RegisterPage()
{
}

void RegisterPage::InitWidget()
{
	label_avatar = new Avatar(nullptr,":/Image/resource/default.jpg", 80, 80);
	
	btn_chooseAvatar = new QPushButton("更换头像  ∨");
	btn_chooseAvatar->setFixedSize(80, 35);
	btn_chooseAvatar->setStyleSheet(
		"QPushButton{border: none;}"
		"QPushButton::hover{background-color:#dcdcdc}"
	);
	//弹窗
	avatar_popup = new AvatarPopup(this);
	connect(btn_chooseAvatar, &QPushButton::clicked, this, [this]() {
		QPoint pos = btn_chooseAvatar->mapToGlobal(QPoint(-100, 50));
		avatar_popup->move(pos);
		avatar_popup->show();
	});
	connect(avatar_popup, &AvatarPopup::avatarSelected, this, [this](const QString& imgPath) {
		label_avatar->setAvatar(imgPath);
		avatarPath = imgPath;
		avatar_popup->hide();
		});
	
	//昵称框
	lineEdit_nickName = new QLineEdit;
	lineEdit_nickName->setMaxLength(255);
	lineEdit_nickName->setPlaceholderText("输入昵称");
	lineEdit_nickName->setFixedHeight(40);
	lineEdit_nickName->setFont(QFont("Microsoft YaHei UI", 12));
	lineEdit_nickName->setAlignment(Qt::AlignCenter);
	lineEdit_nickName->setStyleSheet(
		"QLineEdit {"
			"padding: 10px 70px;" //上下 左右
			"border:none;"
			"border-radius: 10px;"
		"}"
	);
	label_LineEdit_1_warning = new QLabel;
	//label_LineEdit_1_warning->setFixedHeight(40);
	label_LineEdit_1_warning->hide();
	label_LineEdit_1_warning->setStyleSheet("color:#ff0000;font: 10pt;");
	//昵称验证
	connect(lineEdit_nickName, &QLineEdit::textChanged, this, [this](const QString &text) {
		if (text.size() > 20) {
			checked = false;
			label_LineEdit_1_warning->setText("昵称过长!请输入少于20个字符的昵称");
			label_LineEdit_1_warning->show();
		}
		else {
			checked = true;
			label_LineEdit_1_warning->hide();
		}
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
	//TODO密码验证

	//隐藏按钮跟随输入框
	btn_showPasswd = new QPushButton(lineEdit_passwd);
	btn_showPasswd->setStyleSheet("border:none; padding: 0px;");
	btn_showPasswd->setIcon(QIcon(":/Image/resource/eye_hide.png"));
	btn_showPasswd->setIconSize(QSize(23,23));	// 设置图标大小
	btn_showPasswd->setCursor(Qt::ArrowCursor);
	btn_showPasswd->setGeometry(lineEdit_passwd->width()-410, 10, 25, 25);
	// 长按显示密码
	connect(btn_showPasswd, &QPushButton::pressed, [=]() {
		lineEdit_passwd->setEchoMode(QLineEdit::Normal);
		btn_showPasswd->setIcon(QIcon(":/Image/resource/eye_show.png"));
		});
	connect(btn_showPasswd, &QPushButton::released, [=]() {
		lineEdit_passwd->setEchoMode(QLineEdit::Password);
		btn_showPasswd->setIcon(QIcon(":/Image/resource/eye_hide.png"));
		});

	//按钮
	btn_register = new QPushButton("注册");
	btn_register->setFixedSize(256, 40);
	btn_register->setStyleSheet(
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

	//msgProcess = new MessageParser;
	//向服务器发送注册消息
	connect(btn_register, &QPushButton::clicked, this, &RegisterPage::sendRegisterMsg);	//点击按钮发送注册消息
	//connect(btn_register, &QPushButton::clicked, this, &RegisterPage::sendFileMsg);
	//connect(this, &RegisterPage::signalRegister, msgProcess, &MessageParser::MessageProcess);	//通过该函数将注册消息发送出去
	//connect(msgProcess, &MessageParser::msgReturn, this, &RegisterPage::registerResult);	//取得注册返回状态

	//布局
	layout_vertical = new QVBoxLayout;
	layout_vertical->addSpacing(20);
	layout_vertical->addWidget(label_avatar, 0, Qt::AlignHCenter);  //水平居中，垂直不变
	layout_vertical->addSpacing(3);
	layout_vertical->addWidget(btn_chooseAvatar,0,Qt::AlignHCenter);
	layout_vertical->addSpacing(10);
	layout_vertical->addWidget(lineEdit_nickName);
	layout_vertical->addWidget(label_LineEdit_1_warning);
	layout_vertical->addSpacing(5);
	
	layout_vertical->addWidget(lineEdit_passwd);
	layout_vertical->addSpacing(10);
	layout_vertical->addWidget(btn_register);
	layout_vertical->addStretch();

	layout_vertical->setContentsMargins(70, 0, 70, 0);

	this->setLayout(layout_vertical);
}

void RegisterPage::sendRegisterMsg()
{
	QJsonObject json;
	json.insert("type", Register);
	json.insert("nickname", lineEdit_nickName->text());
	json.insert("passwd", lineEdit_passwd->text());




	//json.insert("avatarPath", avatarPath);
	////直接传入base64格式文件数据
	//QByteArray avatarByte;
	//QFile file(avatarPath);
	//if (file.open(QIODevice::ReadOnly))
	//{
	//	avatarByte = file.readAll();
	//	file.close();
	//}
	//QString avatarData = QString::fromUtf8(avatarByte.toBase64());
	//json.insert("avatarData", avatarData);
	emit signalRegister(json);	//msgMessageParser接收该消息

}

//void RegisterPage::sendFileMsg()
//{
//	QJsonObject json;
//	json.insert("type", File);
//	QFileInfo fileInfo(avatarPath);
//	QString fileName = fileInfo.fileName();
//	json.insert("filePath", fileName);
//	emit signalRegister(json);	//msgMessageParser接收该消息
//}


void RegisterPage::registerResult(const QJsonObject& data)
{
	if (data.value("type") != RegisterResult)
		return;

	QDialog* dialog = new QDialog(this);
	dialog->setFixedSize(300, 300);
	dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	dialog->setAttribute(Qt::WA_TranslucentBackground);

	QVBoxLayout* dialogLayout = new QVBoxLayout(dialog);
	dialogLayout->setContentsMargins(0, 0, 0, 0);

	QWidget* container = new QWidget;
	container->setFixedSize(280, 160);
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
	QPushButton* btn_OK = new QPushButton;
	btn_OK->setFixedSize(100, 35);
	btn_OK->setStyleSheet(
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

	QVBoxLayout* layout = new QVBoxLayout(container);
	layout->addWidget(label);
	layout->addStretch();
	layout->addWidget(btn_OK, 0, Qt::AlignRight);  //水平居右，垂直不变

	dialogLayout->addWidget(container);

	int msg_type = data.value("status").toInt();
	QString uid;
	QString msg;

	if (msg_type == OK)
	{
		uid = data.value("uid").toString();
		//创建本地文件夹存放账号数据
		QDir dir;
		QString savedPath = "recv/" + uid + "/avatar/";
		if (!dir.exists(savedPath))
			dir.mkpath(savedPath);
		//移动头像文件到指定文件夹
		QFileInfo fileInfo(avatarPath);
		QString avatarName = fileInfo.fileName();
		QFile::copy(avatarPath, savedPath + avatarName);

		//注册成功后将传输头像数据给服务器
		QJsonObject json;
		json.insert("fileName", avatarName);
		json.insert("size", QFile(savedPath + avatarName).size());
		json.insert("uid", uid);
		//NetworkManager::getInstance()->sendPacket(msgProcess->converToByteArray(json), FileInfo);

		//发送实际文件
		


		//MessageParser::getInstance()->sendFiles(savedPath + avatarName, uid);
		btn_OK->setText("复制账号");
		label->setText(
			"<div align='center' style='padding-left:20px; padding-right:20px;padding-top:50px;text-align:left;'>"
				"<div style='font-size:12pt; font-weight:bold;'>""注册成功""</div>""<br>"
				"<div style='font-size:12pt;'>""您的敲敲账号为："
					"<span style='color:#0094f7; font-size:13pt;'>"
						+ uid +
					"</span>"
				"</div>"
			"</div>"
		);
		
	}
	else
	{
		btn_OK->setText("返回注册");
		msg = data.value("msg").toString();
		QMessageBox::warning(nullptr, "错误", "注册失败："+msg, QMessageBox::Ok);
		label->setText(
			"<div align='center' style='padding-left:20px; padding-right:20px;padding-top:50px;text-align:left;'>"
				"<div style='font-size:12pt; font-weight:bold;'>""注册失败""</div>"
			"</div>"
		);
	}

	connect(btn_OK, &QPushButton::clicked, this, [msg_type, dialog, uid, this]() {
		if (msg_type == OK)
		{
			QClipboard* clipboard = QApplication::clipboard();
			clipboard->setText(uid);
			dialog->close();
			this->close();
		}
		else {
			dialog->close();
		}
		});

	dialog->setModal(true);	//阻止点击父窗口
	dialog->show();

}
