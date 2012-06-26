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

#ifndef QTNPCOLORWIDGET_H
#define QTNPCOLORWIDGET_H

#include <QtGui/QLabel>
#include <QColor>
#include <QPainter>
#include <QColorDialog>
#include <QPixmap>
#include <QMouseEvent>



// виджет выбора цвета
class QtnpColorWidget : public QLabel
{
	Q_OBJECT
public:
	QtnpColorWidget(int, int, int, int b_s = 30);
	~QtnpColorWidget();
	QColor get_current_color();

private:
	QColor *current_color, clr;
	QPixmap *pixmap_color;
	QPainter *painter_color;
	int box_size;

public slots:
	void set_color(QColor);

signals:
	void send_color(QColor);

protected:
	void mousePressEvent(QMouseEvent *event);
};

#endif // QTNPCOLORWIDGET_H
