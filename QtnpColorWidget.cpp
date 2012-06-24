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
