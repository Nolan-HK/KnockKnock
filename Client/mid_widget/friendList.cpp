#include "friendList.h"
#include "friendWidget.h"

#include <QScrollBar>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>

FriendList::FriendList(QWidget* parent) : QWidget(parent)
{
	this->setFixedWidth(250);
	this->setStyleSheet("border:none;");
	InitWidget();
}
FriendList::~FriendList()
{}

void FriendList::InitWidget()
{
	m_currentIndex = 0;
	m_floatingHeader = new QPushButton(this);
	container = new QWidget();
	scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(container);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QVBoxLayout* containerLayout = new QVBoxLayout(container);
	containerLayout->setSpacing(0);
	containerLayout->setContentsMargins(0, 0, 0, 0);
	containerLayout->setAlignment(Qt::AlignTop);

	QVBoxLayout* vlayout = new QVBoxLayout(this);
	vlayout->setContentsMargins(0, 0, 0, 0);
	vlayout->addWidget(scrollArea);

	m_floatingHeader->setFixedHeight(35);
	m_floatingHeader->setStyleSheet("background-color:#ffffcc;");
	m_floatingHeader->raise();


	connect(scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &FriendList::updateFloatingHeader);
	connect(m_floatingHeader, &QPushButton::clicked, this, &FriendList::onFloatingClicked);


}

void FriendList::addDrawer(FriendWidget* drawer)
{
	container->layout()->addWidget(drawer);
	m_drawers.push_back(drawer);

	connect(drawer, &FriendWidget::toggled, this, &FriendList::updateFloatingHeader);
	updateFloatingHeader();
}

//模拟抽屉头跟随滚动条浮动
void FriendList::updateFloatingHeader()
{
	if (m_drawers.empty())
		return;
	int active = -1;
	for (int i = 0; i < (int)m_drawers.size(); ++i)
	{
		
		QPoint p = m_drawers[i]->mapTo(scrollArea->viewport(), QPoint(0, 0));	//p:第i个抽屉的左上角在this坐标系中的位置
		int bottom = p.y() + m_drawers[i]->height();
		if (p.y() <= 0 && bottom >0 && m_drawers[i]->isExpanded())	//已经到第i个抽屉的区域且抽屉是打开状态
		{
			active = i;
		}
	}
	
	if (active == -1)
	{
		m_floatingHeader->setVisible(false);
		return;
	}
	m_currentIndex = active;
	m_floatingHeader->setText(m_drawers[active]->title());

	QPoint topLeft = this->mapTo(this, scrollArea->viewport()->pos());
	m_floatingHeader->setGeometry(topLeft.x(), topLeft.y(), scrollArea->viewport()->width(), 35);
	m_floatingHeader->setVisible(true);
}

//点击浮动头展开/收起
void FriendList::onFloatingClicked()
{
	FriendWidget* fw = m_drawers[m_currentIndex];
	fw->setExpanded(!fw->isExpanded());
}