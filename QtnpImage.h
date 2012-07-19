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

#ifndef QTNPIMAGE
#define QTNPIMAGE

#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QFont>
#include "QtnpTool.h"

class QtnpImage : public QLabel {
	Q_OBJECT;
public:
	QtnpImage();
	~QtnpImage();
	void load_image(const QString ImageFile);
	void save_image(const QString ImageFile);
	QColor get_pen_color(bool pen);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	void refresh();
	void draw_line(QPen p);
	void draw_square(QPen p);
	void draw_ellipse(QPen p);
	void draw_circle(QPen p);
	void remember();
	QPoint neares_grid_point(QPoint p);

	int width_, height_;
	bool painting, jogged_line_first_click_done;
	QtnpTool active_tool;
	QPoint start, end;
	QImage *image;
	QImage image_copy;
	QPen pen, rpen;
	QBrush brush;
	QPainter *painter;
	QPoint get_grid_point(QPoint gridPoint,int step);
	QList<QImage> prev_list;
	int c_x, c_y;
	int grid_max_x, grid_max_y, grid_min_x, grid_min_y;
	int grid_step;

public slots:
	void set_pen_color(QColor color);
	void set_rpen_color(QColor color);
	void set_brush_color(QColor color); // check
	void pen_trickness(int size);
	void prev();
	void set_active_tool(QtnpTool);
	void new_image(int x, int y, QColor color);
	void negative();
	void grayscale();
	void make_grid(int step, QColor color,int width = 1);
	void make_coord_plane(int CoordPlaneStep, QColor clr,int width = 1);
	void draw_graphic(QString str, QColor color, int width);

signals:
	void reset_tool_menu();
};

#endif // QTNPIMAGE
