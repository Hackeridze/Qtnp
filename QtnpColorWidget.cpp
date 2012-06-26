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

#include "QtnpColorWidget.h"

QtnpColorWidget::QtnpColorWidget(int r, int g, int b, int b_s)
{
	box_size = b_s;
	setFrameStyle(QFrame::Box | QFrame::Raised);// квадратный и выпуклый фрейм
	current_color = new QColor(r,g,b);
	pixmap_color = new QPixmap(box_size, box_size);
	painter_color = new QPainter(pixmap_color);
	painter_color->fillRect(0,0,box_size,box_size, *current_color);
	painter_color->end();
	setPixmap(*pixmap_color);
	setAlignment(Qt::AlignTop);
}

QtnpColorWidget::~QtnpColorWidget()
{
	delete current_color;
	delete pixmap_color;
	delete painter_color;
}

void QtnpColorWidget::set_color(QColor color)
{
	*current_color = color;
	clr = color;
	painter_color->begin(pixmap_color);
	painter_color->fillRect(0, 0, box_size, box_size, *current_color);
	painter_color->end();
	setPixmap(*pixmap_color);
}

void QtnpColorWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		clr = QColorDialog::getColor(*current_color, this); // вызываем стд диалог выбора цвета
		if(clr.isValid()) {
			set_color(clr); // устанавливаем выбранный цвет для самого виджета
			emit send_color(clr); // отсылаем цвет
		}
	}
}

QColor QtnpColorWidget::get_current_color()
{
	return clr;
}
