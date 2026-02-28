#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../mid_widget/contactsPage.h"
#include "../mid_widget/messageListPage.h"
#include "../left_widget/leftBar.h"
#include "../mid_widget/addFriendWidget.h"

#include <QMainWindow>

class QGroupBox;
class QPushbutton;
class QGroupBox;
class QHBoxLayout;
class QVBoxLayout;
class QEvent;
class QMouseEvent;
class QSpacerItem;
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QLabel;
class QScrollArea;
class QlineEdit;
class QMenu;


class QQ : public QMainWindow
{
    Q_OBJECT

public:
    QQ(QWidget *parent = nullptr);
    ~QQ();


//Widgets
private:

    QWidget* centralWidget;

    //标题栏
    QGroupBox* groupBox_top;
    QPushButton* btn_MainWindow_min;    
    QPushButton* btn_MainWindow_max;
    QPushButton* btn_MainWindow_close;
    QSpacerItem* spacer_groupBoxTop;    //弹簧
    QHBoxLayout* horizontal_groupBoxTop;    //水平布局

    //侧边栏
    QGroupBox* groupBox_left;
    LeftBar* leftBar;


    //中间区域
    QGroupBox* groupBox_mid;
    //搜索框
    QLabel* search_label;
    QLineEdit* lineEdit_search;
    QPushButton* btn_menu;
    QHBoxLayout* search_layout;
    QMenu* menu_more;

    QStackedWidget* stackedWidget_left; //mid切换页面控件
    Contacts* contacts; //联系人页面
    MessageList* messageList;   //消息列表页面
    QVBoxLayout* verticalMessage_layout;   //消息页面垂直布局

    //右边区域
    QGroupBox* groupBox_right;


    //布局
    QHBoxLayout* horizontal_Main;   //主页面水平布局
    QVBoxLayout* vertical_Main; //主页面垂直布局

private:
    //切换页面定义
    int messagePage = 0;
    int contactsPage = 1;


//Functions
private:
    void widgetInit();
    bool eventFilter(QObject *watched, QEvent *event);
    void signal();
    void raiseAddFriendWindow();

//SLOT
private slots:
    void on_btn_Max_clicked();
    void on_change_page(int page);
};

#endif