#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <vector>
#include <QWidget>

class FriendWidget;
class QPushButton;
class QScrollArea;

class FriendList : public QWidget
{
	Q_OBJECT

public:
	explicit FriendList(QWidget* parent = nullptr);
	void addDrawer(FriendWidget* drawer);
	~FriendList();

//Widget
private:
	QWidget* container;
	QScrollArea* scrollArea;
	QPushButton* m_floatingHeader;
	std::vector<FriendWidget*> m_drawers;
	int m_currentIndex;

//Function
private:
	void InitWidget();

private slots:
	void updateFloatingHeader();
	void onFloatingClicked();

signals:

};

#endif