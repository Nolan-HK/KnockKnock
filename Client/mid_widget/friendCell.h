#ifndef FRIENDCELL_H
#define FRIENDCELL_H

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;

class FriendCell : public QWidget
{
	Q_OBJECT

public:
	explicit FriendCell(QString avatar, QString nickname, int status, QString signature, QWidget* parent = nullptr);

	~FriendCell();

private:
	void InitWidget();
	void setStyle();

private:
	QWidget* content;
	QString avatar;
	QString nickname;
	std::map<int, QString> map_status{ {0,QString("离线")},{1,QString("在线")} };
	int status;
	QString signature;

	QHBoxLayout* hlayout;
	QVBoxLayout* vlayout;

signals:
	void clicked();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif
