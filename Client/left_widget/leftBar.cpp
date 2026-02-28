#include "LeftBar.h"

#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>


LeftBar::LeftBar(QWidget* parent)
{
	this->setFixedWidth(55);
	this->setStyleSheet("border:none;");
	InitWidget();
}
LeftBar::~LeftBar()
{}

void LeftBar::InitWidget()
{
	btn_messageList = new QPushButton(this);
	btn_messageList->setFixedSize(30, 30);
	btn_messageList->setStyleSheet("QPushButton{border:1px solid #c7c7c7;border-radius:10px;font-size:14px;}QPushButton:hover{background-color:#ebebeb;}");

	btn_contact = new QPushButton(this);
	btn_contact->setFixedSize(30, 30);
	btn_contact->setStyleSheet("QPushButton{border:1px solid #c7c7c7;border-radius:10px;font-size:14px;}QPushButton:hover{background-color:#ebebeb;}");

	btn_setting = new QPushButton(this);
	btn_setting->setFixedSize(30, 30);
	btn_setting->setStyleSheet("QPushButton{border:1px solid #c7c7c7;border-radius:10px;font-size:14px;}QPushButton:hover{background-color:#ebebeb;}");

	spacer_item = new QSpacerItem(0,0,QSizePolicy::Preferred, QSizePolicy::Expanding);

	vertical_layout = new QVBoxLayout(this);
	vertical_layout->addWidget(btn_messageList);
	vertical_layout->addWidget(btn_contact);
	vertical_layout->addSpacerItem(spacer_item);
	vertical_layout->addWidget(btn_setting);
	vertical_layout->setSpacing(5);
	vertical_layout->setContentsMargins(10,10,0,10);
	this->setLayout(vertical_layout);
}