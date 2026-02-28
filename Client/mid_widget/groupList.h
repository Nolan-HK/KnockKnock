#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QListWidget>

class GroupList : public QListWidget
{
	Q_OBJECT

public:
	explicit GroupList(QWidget* parent = nullptr);
	~GroupList();

private:
	void InitWidget();
};

#endif