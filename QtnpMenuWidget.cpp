/*
 *This file is part of Qtnp.
 *
 * Qtnp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Qtnp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qtnp.  If not, see <http://www.gnu.org/licenses/>.
 */

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
