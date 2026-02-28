#ifndef ADDFRIENDWIDGET_H
#define ADDFRIENDWIDGET_H

#include <QWidget>
#include "../util/avatar.h"

class QLineEdit;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;


class ResultCell : public QWidget
{
	Q_OBJECT

public:
	explicit ResultCell(Avatar* avatar, QString nickname, QString uid, QString signature, QWidget* parent = nullptr);

private:
	QWidget* content;
	QString nickname;
	QString signature;
	QPushButton* btn_addFriend;

	QVBoxLayout* vlayout;
	QHBoxLayout* hlayout;
	QString m_uid;

public:
	QString getUid() const;
};

class AddFriendWindow : public QWidget
{
	Q_OBJECT
public:
	~AddFriendWindow();

	static AddFriendWindow* getInstance();


private:
	explicit AddFriendWindow(QWidget* parent = nullptr);
	static AddFriendWindow* instance;

	QLabel* search_label;
	QLineEdit* search_lineEdit;
	QHBoxLayout* search_hlayout;
	QPushButton* btn_search;

	QWidget* search_result;
	QVBoxLayout* result_vlayout;

	QVBoxLayout* window_vlayout;
	QMap<QString, ResultCell*> m_resultMap;

private:
	void addResultCell(ResultCell* resultCell, QVBoxLayout* vlayout);
	void clearResultCell();
	void onSearchReuslt(const QJsonObject& data);


};


#endif // !ADDFRIENDWIDGET_H
