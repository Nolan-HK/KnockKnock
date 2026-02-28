#include "MessageListPage.h"

MessageList::MessageList(QWidget* parent) : QListWidget(parent)
{
	this->setFixedWidth(250);
	this->setStyleSheet("border:none;");
	InitWidget();
}
MessageList::~MessageList()
{}

void MessageList::InitWidget()
{

	msg_item = new QListWidgetItem(this);
	msg_item->setSizeHint(QSize(0, 35));
	widget_ = new Message_Cell("HELLO", 20);
	this->setItemWidget(msg_item, widget_);

	QObject::connect(widget_, &Message_Cell::heightChanged, [=]() {
		int newHeight = widget_->sizeHint().height();
		widget_->setStyleSheet("background-color:ffffff;");
		msg_item->setSizeHint(QSize(0, newHeight));
		});

}

