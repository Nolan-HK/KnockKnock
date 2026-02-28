#ifndef MESSAGELISTPAGE_H
#define MESSAGELISTPAGE_H

#include <QListWidget>
#include "../util/msg_cell.h"


class MessageList : public QListWidget
{
	Q_OBJECT

public:
	explicit MessageList(QWidget* parent = nullptr);
	~MessageList();

//Widget
private:
	QListWidgetItem* msg_item;
	Message_Cell* widget_;

//Function
private:
	void InitWidget();
};

#endif