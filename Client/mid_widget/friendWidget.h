#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QPropertyAnimation;
class FriendCell;

class FriendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FriendWidget(QString groupName_, QWidget* parent = nullptr);


//函数
public:
    void setExpanded(bool expand);  //设置抽屉展开/收起状态
    bool isExpanded() const { return is_expanded; } //获取抽屉的状态
    void addFriendCell(FriendCell* friendCell); //添加好友单元
    QString title() const;  //获取分组名称

//变量
public:
    QMap<QString, FriendWidget> groupWidgets;   //分组名称，分组Widget

signals:
    void toggled();

private slots:
    void onHeaderClicked();

private:
    QPushButton* btn_groupName;
    QString groupName;
    QWidget* cellContainer;
    QPropertyAnimation* m_anim;
    QVBoxLayout* widgetLayout;
    bool is_expanded;

private:
    void InitWidget();
    void InitFriendCell();
};


#endif