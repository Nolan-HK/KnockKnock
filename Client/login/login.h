#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QStackedWidget;
class QLineEdit;
class QCheckBox;
class Avatar;
class Title;
class ClientSocket;


class LoginBase : public QWidget
{
	Q_OBJECT

public:
	explicit LoginBase(QWidget* parent = nullptr);
	~LoginBase();

	float offset() const { return m_offset; }
	void setOffset(float o) {
		if (qFuzzyCompare(m_offset, o)) return;
		m_offset = o;
		update(); // 属性改变时，强制触发窗口重绘
	}

private:
	//Base
	float m_offset = 0.0f;
	QLabel* label_topBar;
	QPushButton* btn_close;
	QHBoxLayout* hlayout;
	QVBoxLayout* vlayout_base;
	QStackedWidget* stackedWidget;
	Avatar* label_avatar;	//自定义圆形label
	ClientSocket* tcpSocket;

	//loginPage
	QWidget* loginPage;
	QLineEdit* lineEdit_account;
	QLineEdit* lineEdit_passwd;
	QPushButton* btn_login;
	QPushButton* btn_showPwd;
	QPushButton* btn_registerPage;
	QCheckBox* checkBox_autoLogin;
	QCheckBox* checkBox_savePasswd;
	QVBoxLayout* vlayout_loginPage;
	QHBoxLayout* hlayout_loginPage;

	Title* label_logo;	//自定义渐变文字
	QWidget* autoLoginPage;
	

private:
	void InitWidget();
	void ShowRegister();
	void LoginResult(const QJsonObject& data);
	
signals:
	void signalLogin(const QJsonObject& data);
	void signalLoginSuccess();

protected:
	//重写鼠标移动事件
	bool eventFilter(QObject* watched, QEvent* event) override;
};


#endif

