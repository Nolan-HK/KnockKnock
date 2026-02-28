#ifndef CONTACTSPAGE_H
#define CONTACTSPAGE_H

#include "friendList.h"
#include "groupList.h"
#include "friendCell.h"
#include "friendWidget.h"

#include <QScrollArea>

class QLabel;
class QPushButton;
class QButtonGroup;
class QVBoxLayout;
class QHBoxLayout;
class QStackedWidget;


class Contacts : public QScrollArea
{
	Q_OBJECT
public:
	explicit Contacts(QWidget* parent = nullptr);
	~Contacts();
//Widget
private:
	//-----------------------外层滚动区域--------------
	QWidget* content;
	QLabel* buddyManager;   //好友管理器
	QLabel* buddyNotes; //好友通知
	QLabel* groupNotes; //群通知

	QPushButton* btn_buddyManager;  //好友管理器按钮
	QButtonGroup* groupSwitchList;
	QPushButton* btn_buddy;
	QPushButton* btn_group;
	QHBoxLayout* groupSwitch_layout;
	QStackedWidget* contactsList_page;
	//-------------------------------------------------

	//-----------------------内层滚动区域--------------
	FriendList* listWidget_friend;
	FriendCell* defaultContact;
	FriendWidget* defaultGroup;

	GroupList* listWidget_group;


	QVBoxLayout* verticalContacts_layout;   //联系人页面垂直布局

//
private:
	int friendPage = 0;
	int groupPage = 1;
	int m_offsetY = 0;

//Function
	void InitWdiget();
	//void InitContactsList(QString groupName, QString contacts)
private slots:
	void on_show_switchPage(int);

protected:
	//void wheelEvent(QWheelEvent* event);
};

#endif