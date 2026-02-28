#include "addFriendWidget.h"
//#include "../socket//msgMessageParser.h"
#include "../util/util.h"

#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


AddFriendWindow::AddFriendWindow(QWidget* parent) : QWidget(parent)
{
	
	this->resize(680, 480);
	this->setWindowTitle("搜索好友");
	this->setStyleSheet("QWidget{background-color:#f5f5f5;}");

	//搜索区域
	search_label = new QLabel;
	search_label->setFixedHeight(90);
	search_label->setStyleSheet("background-color:#ffffff;");

	search_lineEdit = new QLineEdit;
	search_lineEdit->setFixedHeight(30);
	search_lineEdit->setStyleSheet("QLineEdit{border:1px solid #c7c7c7;border-radius:10px;font-size:14px;}");
	search_lineEdit->setPlaceholderText("输入敲敲号搜索");
	QAction* searchIcon = new QAction(QIcon(":/Image/resource/search.png"), "", search_lineEdit);
	search_lineEdit->addAction(searchIcon, QLineEdit::LeadingPosition);

	btn_search = new QPushButton("搜索");
	btn_search->setFixedSize(75,30);
	btn_search->setStyleSheet(
		"QPushButton{"
		"background-color: #0094f7; "
		"font: 10pt Microsoft YaHei UI;"
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

	search_hlayout = new QHBoxLayout(search_label);
	search_hlayout->addWidget(search_lineEdit);
	search_hlayout->addWidget(btn_search);

	//结果区域
	search_result = new QWidget;

	result_vlayout = new QVBoxLayout;
	search_result->setLayout(result_vlayout);
	//search_result->setContentsMargins(5, 5, 5, 5);
	//connect(btn_search, &QPushButton::clicked, this, [this]() {
	//	//点击搜索时，先加载用户uid和昵称，头像文件异步加载
	//	QString uid = search_lineEdit->text();
	//	MessageParser::getInstance()->searchUser(uid);
	//	});
	//connect(MessageParser::getInstance(), &MessageParser::signalSearchResult, this, &AddFriendWindow::onSearchReuslt);


	window_vlayout = new QVBoxLayout;
	window_vlayout->setContentsMargins(0, 0, 0, 0);
	window_vlayout->addWidget(search_label);
	window_vlayout->addWidget(search_result);
	this->setLayout(window_vlayout);


}

void AddFriendWindow::addResultCell(ResultCell* resultCell, QVBoxLayout* vlayout)
{

	vlayout->addWidget(resultCell);
	vlayout->addStretch();
	vlayout->setContentsMargins(0, 0, 0, 0);
	m_resultMap.insert(resultCell->getUid(), resultCell);
}

void AddFriendWindow::onSearchReuslt(const QJsonObject& data)
{
	QByteArray avatarData = QByteArray::fromBase64(data.value("avatarData").toString().toUtf8());
	QString nickname = data.value("nickname").toString();
	QString uid = data.value("uid").toString();
	qDebug() << avatarData;
	Avatar* avatar = new Avatar(this);
	avatar->setAvatarFromBase64(avatarData);

	ResultCell* resultCell = new ResultCell(avatar, nickname, uid, "无签名");
	addResultCell(resultCell, result_vlayout);
}

AddFriendWindow::~AddFriendWindow()
{
}

AddFriendWindow* AddFriendWindow::instance = nullptr;
AddFriendWindow* AddFriendWindow::getInstance()
{
	if (!instance)
	{
		instance = new AddFriendWindow;
	}
	return instance;
}

ResultCell::ResultCell(Avatar* avatar, QString nickname, QString uid, QString signature, QWidget* parent)
	: QWidget(parent), m_uid(uid)
{
	this->setFixedHeight(65);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QVBoxLayout* cell_layout = new QVBoxLayout(this);
	cell_layout->setContentsMargins(5, 0, 5, 0);

	content = new QWidget(this);
	content->setStyleSheet(
		"QWidget:hover{background-color:#ebebeb;}"
		"QWidget:hover QLabel{background-color:transparent;}"//跟随父类style

	);
	content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QLabel* nickname_ = new QLabel(nickname + "(" + uid + ")");	//uid与昵称
	QLabel* signature_ = new QLabel(signature);
	btn_addFriend = new QPushButton;
	btn_addFriend->setFixedSize(60, 30);
	//TODO是好友setText改为发消息
	btn_addFriend->setText("添加");

	hlayout = new QHBoxLayout;
	vlayout = new QVBoxLayout;
	vlayout->addWidget(nickname_);
	vlayout->addWidget(signature_);

	hlayout->addWidget(avatar);
	hlayout->addLayout(vlayout, 1);
	hlayout->addStretch(0);
	hlayout->addWidget(btn_addFriend);

	content->setLayout(hlayout);

	cell_layout->addWidget(content);
}

QString ResultCell::getUid() const
{
	return m_uid;
}
