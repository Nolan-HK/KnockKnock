#include "friendWidget.h"
#include "friendCell.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>


FriendWidget::FriendWidget(QString groupName_, QWidget* parent) : groupName(groupName_)
{
	InitWidget();
	connect(btn_groupName, &QPushButton::clicked, this, &FriendWidget::onHeaderClicked);
}

void FriendWidget::InitWidget()
{
	is_expanded = false;
	btn_groupName = new QPushButton(this);
	btn_groupName->setText(groupName);
	btn_groupName->setFixedHeight(35);

	cellContainer = new QWidget(this);
	//cellContainer->setStyleSheet("background-color:#ccffff;");
	//cellContainer->setFixedHeight(300);
	widgetLayout = new QVBoxLayout(cellContainer);	//分组内布局
	//分组布局
	QVBoxLayout* vlayout = new QVBoxLayout(this);
	vlayout->addWidget(btn_groupName);
	vlayout->addWidget(cellContainer);
	vlayout->setSpacing(0);
	vlayout->setContentsMargins(0, 0, 0, 0);

	cellContainer->setVisible(false);

	//展开收缩动画
	m_anim = new QPropertyAnimation(cellContainer, "maximumHeight", this);
	m_anim->setDuration(200);	// 动画时长
	m_anim->setEasingCurve(QEasingCurve::InOutCubic);

}

//初始化获取好友
void FriendWidget::InitFriendCell()
{

}

//分组中添加好友
void FriendWidget::addFriendCell(FriendCell* friendCell)
{
	widgetLayout->addWidget(friendCell);
	//friendCell间距
	widgetLayout->setSpacing(2);
	widgetLayout->setContentsMargins(2, 2, 2, 2);
}

QString FriendWidget::title() const
{
	return btn_groupName->text();
}

void FriendWidget::onHeaderClicked()
{
	setExpanded(!is_expanded);
	emit toggled();
}

void FriendWidget::setExpanded(bool expand)
{
	if (is_expanded == expand) return;

	is_expanded = expand;
	//收缩动画实现
	m_anim->stop();
	if (expand)
	{
		cellContainer->setVisible(true);
		int cellContainerHeight = cellContainer->layout()->sizeHint().height();
		m_anim->setStartValue(0);
		m_anim->setEndValue(cellContainerHeight);
	}
	else
	{
		int cellContainerHeight = cellContainer->height();
		m_anim->setStartValue(cellContainerHeight);
		m_anim->setEndValue(0);

		connect(m_anim, &QPropertyAnimation::finished, this, [this]() {
			if (!is_expanded)
				cellContainer->setVisible(false);
			});
	}
	m_anim->start();

}

