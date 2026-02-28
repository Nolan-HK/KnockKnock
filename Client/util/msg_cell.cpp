#include "msg_cell.h"

Message_Cell::Message_Cell(QString name, qint8 friendCount, QWidget* parent) : QWidget(parent)
{
	btn = new QPushButton();
	btn->setText(name);
	btn->setStyleSheet("QPushButton{border:1px solid #c7c7c7;border-radius:10px;font-size:14px;}QPushButton:hover{background-color:#ebebeb;}");
	widget = new QWidget();
	widget->setVisible(false);
	widget->setFixedHeight(60*friendCount);
	widget->setStyleSheet("background-color:#ccffff;");
	layout = new QVBoxLayout();
	layout->addWidget(btn);
	layout->addWidget(widget);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	this->setLayout(layout);

	QObject::connect(btn, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));

}

void Message_Cell::on_btn_clicked()
{
	if (widget->isVisible())
		widget->setVisible(false);
	else
		widget->setVisible(true);
	emit heightChanged();
	qDebug() << "Signal Emitted!";
}