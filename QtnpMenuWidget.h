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
