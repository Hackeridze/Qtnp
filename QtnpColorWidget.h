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
	~QtnpColorWidget() {}
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
