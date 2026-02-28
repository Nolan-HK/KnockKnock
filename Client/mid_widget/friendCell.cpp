#include "friendCell.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <map>
#include <QMouseEvent>
#include <QStyle>

FriendCell::FriendCell(QString avatar, QString nickname, int status, QString signature, QWidget* parent)
	: avatar(avatar), nickname(nickname), status(status), signature(signature)
{
	this->setFixedHeight(60);
	InitWidget();
	
}

FriendCell::~FriendCell()
{}

void FriendCell::InitWidget()
{
	content = new QWidget(this);
	content->setAttribute(Qt::WA_StyledBackground, true);
	content->setFixedSize(QSize(250, 60));
	content->setStyleSheet(
		"QWidget:hover{background-color:#ebebeb;}"
		"QWidget[pressed=true]{background-color:#e2e2e2;}"
		"QWidget:hover QLabel{background-color:transparent;}"//跟随父类style

	);

	QLabel* avatar_ = new QLabel(avatar);
	//QLabel* signature_ = new QLabel(signature, this);

	//文字过长省略
	int maxWidth = 150;
	QLabel* nickname_ = new QLabel();
	QFontMetrics metrics1(nickname_->font());
	QString elidedText1 = metrics1.elidedText(nickname, Qt::ElideRight, maxWidth);
	nickname_->setText(elidedText1);

	//状态和签名合并到一起
	QLabel* status_ = new QLabel();
	QFontMetrics metrics2(status_->font());
	QString elidedText2 = metrics2.elidedText(map_status[status] + "  " + signature, Qt::ElideRight, maxWidth);
	status_->setText(elidedText2);

	vlayout = new QVBoxLayout();
	vlayout->addWidget(nickname_);
	vlayout->addWidget(status_);
	vlayout->setSpacing(15);

	hlayout = new QHBoxLayout();
	hlayout->addWidget(avatar_);
	hlayout->addLayout(vlayout);
	hlayout->setSpacing(30); // 设置头像和文字的间距
	hlayout->setStretchFactor(vlayout, 1); // 让文字区域占据剩余的所有空间
	QHBoxLayout* widgetlayout = new QHBoxLayout();
	content->setLayout(hlayout);
}
void FriendCell::setStyle()
{
	
}
//模拟好友框点击效果
void FriendCell::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		content->setProperty("pressed", true);
		content->style()->unpolish(content);
		content->style()->polish(content);
		content->update();
	}
}

void FriendCell::mouseReleaseEvent(QMouseEvent* event)
{
	content->setProperty("pressed", false);
	content->style()->unpolish(content);
	content->style()->polish(content);
	content->update();
}
