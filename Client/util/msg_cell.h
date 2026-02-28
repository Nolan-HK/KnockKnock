#pragma once

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class Message_Cell : public QWidget
{
	Q_OBJECT
public:
	explicit Message_Cell(QString text, qint8 friendCount, QWidget* parent = nullptr);

private:
		QPushButton* btn;
		QWidget* widget;
		QVBoxLayout* layout;

public slots:
	void on_btn_clicked();

signals:
	void heightChanged();
};
