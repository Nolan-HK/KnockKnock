#include "ContactsPage.h"
#include "friendList.h"
#include "friendWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QWheelEvent>
#include <QScrollBar>


Contacts::Contacts(QWidget* parent) : QScrollArea(parent)
{
	InitWdiget();
	this->setWidgetResizable(true);
	this->setFixedWidth(250);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setStyleSheet("border:none;background-color:#fcfcfc;");
	QObject::connect(groupSwitchList, SIGNAL(idClicked(int)), this, SLOT(on_show_switchPage(int)));
	//connect(groupSwitchList, &QButtonGroup::idClicked,this, &Contacts::on_show_switchPage);
}
Contacts::~Contacts()
{
	
}

void Contacts::InitWdiget()
{
	content = new QWidget(this);
	this->setWidget(content);
	

	//好友管理器按钮
	buddyManager = new QLabel(content);
	buddyManager->setFixedHeight(40);
	btn_buddyManager = new QPushButton(buddyManager);
	btn_buddyManager->setText("好友管理器");
	btn_buddyManager->setStyleSheet("QPushButton{border:1px solid #c7c7c7;border-radius:10px;font-size:14px;}QPushButton:hover{background-color:#ebebeb;}");
	btn_buddyManager->setGeometry(25, 5, 200, 30);
	//好友通知
	buddyNotes = new QLabel(content);
	buddyNotes->setText("好友通知");
	buddyNotes->setFixedHeight(40);
	buddyNotes->setStyleSheet("QLabel{padding-left:25px;font-size:14px;}QLabel:hover{background-color:#ebebeb;}");
	//群通知
	groupNotes = new QLabel(content);
	groupNotes->setText("群通知");
	groupNotes->setFixedHeight(40);
	groupNotes->setStyleSheet("QLabel{padding-left:25px;font-size:14px;}QLabel:hover{background-color:#ebebeb;}");
	//并排按钮
	btn_buddy = new QPushButton();
	btn_buddy->setText("好友");
	btn_buddy->setFixedHeight(35);
	btn_buddy->setStyleSheet("padding-left:25px;font-size:14px;}QLabel:hover{background-color:#ebebeb;");

	btn_group = new QPushButton();
	btn_group->setText("群聊");
	btn_group->setFixedHeight(35);
	btn_group->setStyleSheet("padding-left:25px;font-size:14px;}QLabel:hover{background-color:#ebebeb;");

	groupSwitchList = new QButtonGroup(content);
	groupSwitchList->addButton(btn_buddy, 0);
	groupSwitchList->addButton(btn_group, 1);
	

	groupSwitch_layout = new QHBoxLayout;
	groupSwitch_layout->addWidget(btn_buddy);
	groupSwitch_layout->addWidget(btn_group);

	//切换列表页面控件
	contactsList_page = new QStackedWidget(content);

	//联系人列表页面
	/*
	读取数据库好友列表，map<分组名称，好友数量>存储好友分组数量，读取map中的key数量得到分组数量。
	int 分组数量 = key.count，int j = 好友数量
	*/
	listWidget_friend = new FriendList();
	//默认分组：我的好友
	defaultGroup = new FriendWidget("我的好友", content);
	listWidget_friend->addDrawer(defaultGroup);

	defaultContact = new FriendCell("头像","昵称", 1,"签名");
	FriendCell* friend2 = new FriendCell("头像", "Nolan", 1, "qwertyuiop");

	//增加好友单元
	defaultGroup->addFriendCell(defaultContact);
	defaultGroup->addFriendCell(friend2);

	//10:有10个分组，addWidget出现几次代表几个好友
	//for (int i = 0; i < 10; i++)
	//{
	//	QWidget* content = new QWidget();
	//	QVBoxLayout* c1 = new QVBoxLayout(content);
	//	c1->addWidget(new QLabel(QString("friend_%1").arg(i)));

	//	FriendWidget* fw = new FriendWidget("好友—"+QString::number(i+1), content);
	//	listWidget_friend->addDrawer(fw);
	//}

	//群聊列表页面
	listWidget_group = new GroupList();


	//添加页面
	contactsList_page->addWidget(listWidget_friend);
	contactsList_page->addWidget(listWidget_group);
	contactsList_page->setCurrentIndex(friendPage);

	//联系人页面布局
	verticalContacts_layout = new QVBoxLayout();
	verticalContacts_layout->addWidget(buddyManager);
	verticalContacts_layout->addWidget(buddyNotes);
	verticalContacts_layout->addWidget(groupNotes);
	verticalContacts_layout->addLayout(groupSwitch_layout);
	verticalContacts_layout->addWidget(contactsList_page);

	//verticalContacts_layout->addStretch();
	verticalContacts_layout->setSpacing(0);
	verticalContacts_layout->setContentsMargins(0, 0, 0, 0);

	content->setLayout(verticalContacts_layout);
}

void Contacts::on_show_switchPage(int index)
{
	contactsList_page->setCurrentIndex(index);
}

//可滚动到并排按钮处
//void Contacts::wheelEvent(QWheelEvent* event)
//{
//	int delta = event->angleDelta().y();
//
//	// 滚动速度（可调）
//	m_offsetY += delta / 3;
//
//	// ⭐ 允许的滚动范围（即使内容没超）
//	int maxUp = 0;     // 向上最多 0px
//	int maxDown = -120;  // 向下最多 50px
//
//	m_offsetY = qBound(maxDown, m_offsetY, maxUp);
//	content->move(0, m_offsetY);
//	event->accept();
//}
