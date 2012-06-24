#ifndef QTNPMENUWIDGET_H
#define QTNPMENUWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QIcon>
#include <QPushButton>
#include <QLayout>
#include <QString>
#include "QtnpTool.h"

class QtnpMenuWidget : public QPushButton
{
	Q_OBJECT;
private:
	QMenu *m;

public:
	QtnpMenuWidget();
	~QtnpMenuWidget();

private slots:
	void line();
	void jogged_line();
	void pen();
	void circle();

public slots:
	void none();

signals:
	void choosen_tool(QtnpTool tool);
};

#endif // QTNPMENUWIDGET_H
