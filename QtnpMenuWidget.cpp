#include "QtnpMenuWidget.h"

QtnpMenuWidget::QtnpMenuWidget()
{
	m = new QMenu;
	this->setMenu(m);

	m->addAction(QIcon(":/res/cursor.png"),tr("Cursor"),this,SLOT(none()));
	m->addAction(QIcon(":/res/line_ico.png"),tr("Line"),this,SLOT(line()));
	m->addAction(QIcon(":/res/circle.png"),tr("Circle"),this,SLOT(circle()));
	m->addAction(QIcon(":/res/jogged_ico.png"),tr("Jogged Line"),this,SLOT(jogged_line()));
	m->addAction(QIcon(":/res/pencil_ico.png"),tr("Pen"),this,SLOT(pen()));

	setText(" ");
	none();
}

QtnpMenuWidget::~QtnpMenuWidget()
{
	delete m;
}

void QtnpMenuWidget::none()
{
	emit choosen_tool(NONE);
	setIcon(QIcon(":/res/cursor.png"));
}
void QtnpMenuWidget::pen()
{
	emit choosen_tool(PEN);
	setIcon(QIcon(":/res/pencil_ico.png"));
}
void QtnpMenuWidget::line()
{
	emit choosen_tool(LINE);
	setIcon(QIcon(":/res/line_ico.png"));
}
void QtnpMenuWidget::jogged_line()
{
	emit choosen_tool(JOGGED_LINE);
	setIcon(QIcon(":/res/jogged_ico.png"));
}
void QtnpMenuWidget::circle()
{
	emit choosen_tool(CIRCLE);
	setIcon(QIcon(":/res/circle.png"));
}
