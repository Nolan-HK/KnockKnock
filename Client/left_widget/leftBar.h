#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QSpacerItem;

class LeftBar : public QWidget
{
	Q_OBJECT

public:
	LeftBar(QWidget* parent = nullptr);
	~LeftBar();

//Widget
private:
	QPushButton* btn_messageList;
	QPushButton* btn_contact;
	QPushButton* btn_setting;
	QVBoxLayout* vertical_layout;
	QSpacerItem* spacer_item;

//Function
private:
	void InitWidget();

public:
	QPushButton* get_btn_messageList() { return btn_messageList; }
	QPushButton* get_btn_contact() { return btn_contact; }
	QPushButton* get_btn_setting() { return btn_setting; }
};

#endif