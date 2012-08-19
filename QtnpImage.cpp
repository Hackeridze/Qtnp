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

#include "QtnpImage.h"
#include "fparser/fparser.h"
#include <iostream>
#include <math.h>
#include <QDebug>
#include <QPair>

using namespace std;

QtnpImage::QtnpImage()
{
	new_image(1280,1024,Qt::white);

	grid_max_x = 0;
	grid_max_y = 0;
	grid_min_x = 0;
	grid_min_y = 0;
	
	sticking = false;

	setAlignment(Qt::AlignTop);

	pen.setColor(Qt::black);
	rpen.setColor(Qt::white);

	brush.setColor(Qt::green);

	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	rpen.setCapStyle(Qt::RoundCap);
	rpen.setJoinStyle(Qt::RoundJoin);
}

QtnpImage::~QtnpImage()
{
	delete image;
	delete painter;
}

void QtnpImage::new_image(int x, int y, QColor color)
{
	image = new QImage(x,y,QImage::Format_RGB32);
	painter = new QPainter(image);
	painter->fillRect(0,0, x,y, color);
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
	height_ = image->height();
	width_ = image->width();
	emit reset_tool_menu();
	set_active_tool(NONE);
	prev_list.append(*image);
	c_x = width_/2;
	c_y = height_/2;
	grid_step = -1;
}

void QtnpImage::load_image(const QString ImageFile)
{
	image->load(ImageFile);
	setPixmap(QPixmap::fromImage(*image));
	height_ = image->height();
	width_ = image->width();
	emit reset_tool_menu();
	set_active_tool(NONE);
	prev_list.append(*image);
	c_x = width_/2;
	c_y = height_/2;
	grid_step = -1;
}

void QtnpImage::negative()
{
	int x,y;
	QRgb pixel;

	for(x=0; x<width_; x++){
		for(y=0; y<height_; y++){
			pixel = image->pixel(x,y);
			pixel = qRgb(255-qRed(pixel),255-qGreen(pixel),255-qBlue(pixel));
			image->setPixel(x,y,pixel);
		}
	}
	remember();
	refresh();
}

void QtnpImage::grayscale()
{
	int x,y,r,g,b;
	QRgb pixel;
	 for(x=0; x<width_; x++){
		for(y=0; y<height_; y++){
			pixel = image->pixel(x,y);
			r = g = b = (int) (0.299 * qRed(pixel) + 0.587 * qGreen(pixel) + 0.114 * qBlue(pixel));
			pixel = qRgb(r,g,b);
			image->setPixel(x,y,pixel);
		}
	}
	 remember();
	 refresh();
}

void QtnpImage::save_image(const QString ImageFile)
{
	refresh();
	image->save(ImageFile); 
}

void QtnpImage::refresh()
{
	setPixmap(QPixmap::fromImage(*image));
}

void QtnpImage::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		switch(active_tool) {
		case NONE:
			break;
		case PEN:
			painting = 1;
			remember();
			start = end = event -> pos();
			break;
		case LINE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case SQUARE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case ELLIPSE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case CIRCLE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case JOGGED_LINE:
			painting = 1;
			remember();
			if (jogged_line_first_click_done == true) {
				jogged_line_first_click_done = false;
				start = event->pos();
			} else {
				end = event->pos();
				draw_line(pen);
				start = end;
				image_copy = *image;
			}
			break;
		}
	} else if (event->button() == Qt::RightButton) {
		switch(active_tool) {
		case NONE:
			break;
		case PEN:
			painting = 1;
			remember();
			start = end = event -> pos();
			break;
		case LINE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case SQUARE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case ELLIPSE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case CIRCLE:
			painting = 1;
			remember();
			image_copy = *image;
			start = end = event -> pos();
			break;
		case JOGGED_LINE:
			painting = 0;
			jogged_line_first_click_done = true;
			break;
		}
	}
}

void QtnpImage::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && painting) {
		end = event -> pos();
		switch(active_tool) {
		case NONE:
			break;
		case PEN:
			draw_line(pen);
			start = end;
			break;
		case LINE:
			*image = image_copy;
			draw_line(pen);
			break;
		case SQUARE:
			*image = image_copy;
			draw_square(pen);
			break;
		case ELLIPSE:
			*image = image_copy;
			draw_ellipse(pen);
			break;
		case CIRCLE:
			*image = image_copy;
			draw_line(pen);
			draw_circle(pen);
			break;
		}
	} else if ((event->buttons() & Qt::RightButton) && painting) {
			end = event -> pos();
			switch(active_tool) {
			case NONE:
				break;
			case PEN:
				draw_line(rpen);
				start = end;
				break;
			case LINE:
				*image = image_copy;
				draw_line(rpen);
				break;
			case SQUARE:
				*image = image_copy;
				draw_square(rpen);
				break;
			case ELLIPSE:
				*image = image_copy;
				draw_ellipse(rpen);
				break;
			case CIRCLE:
				*image = image_copy;
				draw_line(rpen);
				draw_circle(rpen);
				break;
			}
		}
}

void QtnpImage::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && painting) {
		end = event -> pos();
		switch(active_tool) {
		case NONE:
			break;
		case PEN:
			draw_line(pen);
			painting = 0;
			break;
		case LINE:
			*image = image_copy;
			draw_line(pen);
			painting = 0;
			break;
		case SQUARE:
			*image = image_copy;
			draw_square(pen);
			painting = 0;
			break;
		case ELLIPSE:
			*image = image_copy;
			draw_ellipse(pen);
			painting = 0;
			break;
		case CIRCLE:
			*image = image_copy;
			draw_circle(pen);
			painting = 0;
			break;
		}
	} else if (event->button() == Qt::RightButton && painting){
		end = event -> pos();
		switch(active_tool) {
		case NONE:
			break;
		case PEN:
			draw_line(rpen);
			painting = 0;
			break;
		case LINE:
			*image = image_copy;
			draw_line(rpen);
			painting = 0;
			break;
		case SQUARE:
			*image = image_copy;
			draw_square(rpen);
			painting = 0;
			break;
		case ELLIPSE:
			*image = image_copy;
			draw_ellipse(rpen);
			painting = 0;
			break;
		case CIRCLE:
			*image = image_copy;
			draw_circle(rpen);
			painting = 0;
			break;
		}
	}
}

void QtnpImage::draw_line(QPen p)
{
	painter->begin(image);
	painter->setPen(p);
	if (sticking)
		painter->drawLine(closest_grid_point(start), closest_grid_point(end));
	else painter->drawLine(start, end);
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

void QtnpImage::draw_square(QPen p)
{
	painter->begin(image);
	painter->setPen(p);
	if (sticking)
		painter->drawRect(QRect(closest_grid_point(start), closest_grid_point(end)));
	else painter->drawRect(QRect(start, end));
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

void QtnpImage::draw_ellipse(QPen p)
{
	painter->begin(image);
	painter->setPen(p);
	if (sticking)
		painter->drawEllipse(QRect(closest_grid_point(start), closest_grid_point(end)));
	else painter->drawEllipse(QRect(start, end));
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

void QtnpImage::draw_circle(QPen p)
{
	painter->begin(image);
	painter->setPen(p);
	int x_R, y_R, x_F, y_F, x_F2, y_F2;
	x_R = fabs(start.x() - end.x());
	y_R = fabs(start.y() - end.y());
	int R = sqrt(pow(x_R,2) + pow(y_R,2));
	if (end.x() > start.x()) {
		x_F = start.x() + R;
		x_F2 = start.x() - R;
	} else {
		x_F = start.x() - R;
		x_F2 = start.x() + R;
	}
	if (end.y() > start.y()) {
		y_F = start.y() + R;
		y_F2 = start.y() - R;
	} else {
		y_F = start.y() - R;
		y_F2 = start.y() + R;
	}
	if (sticking)
		painter->drawEllipse(QRect(closest_grid_point(QPoint(x_F,y_F)), closest_grid_point(QPoint(x_F2,y_F2))));
	else painter->drawEllipse(QRect(QPoint(x_F,y_F), QPoint(x_F2,y_F2)));
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

void QtnpImage::set_pen_color(QColor color)
{
	pen.setColor(color);
}

void QtnpImage::set_rpen_color(QColor color)
{
	rpen.setColor(color);
}

void QtnpImage::set_brush_color(QColor color)
{
	pen.setColor(color);
	pen.setBrush(brush);
}

void QtnpImage::pen_trickness(int size)
{
	pen.setWidth(size);
	rpen.setWidth(size);
}

void QtnpImage::prev(void)
{
	if (!(prev_list.size() < 3)) {
		*image = prev_list.last();
		prev_list.pop_back();
		refresh();
	}
}

void QtnpImage::remember(void)
{
	if (prev_list.size() > 7) prev_list.pop_front();
	prev_list.append(*image);
}

QPoint QtnpImage::closest_grid_point(QPoint p)
{
	double x,y;

	if (p.x() > c_x)
		x = (p.x()-c_x)/grid_step;
	else if (p.x() < c_x)
		x = -1*(c_x-p.x())/grid_step;
	else 
		x = 0;

	if (p.y() > c_y)
		y = -1*(p.y()-c_y)/grid_step;
	else if (p.y() < c_y)
		y = (c_y-p.y())/grid_step;
	else 
		y = 0;

	return get_grid_point_coordinates(QPoint(round(x),round(y)), grid_step);
}

int QtnpImage::round(double num)
{
//	int mul = 10;
//	if (num > 0)
//		return floor(num * mul + .5) / mul;
//	else
//		return ceil(num * mul - .5) / mul;
	return nearbyint(num);
}

void QtnpImage::set_active_tool(QtnpTool whichTool)
{
	active_tool = whichTool;
	painting = 0;
	jogged_line_first_click_done = true;
	switch(active_tool) {
	case NONE:
		this->setCursor(Qt::ArrowCursor);
		break;
	case PEN:
		this->setCursor(QCursor(QPixmap(":/res/pencil.png")));
		break;
	case LINE:
		this->setCursor(QCursor(QPixmap(":/res/line.png")));
		break;
	case JOGGED_LINE:
		this->setCursor(QCursor(QPixmap(":/res/jogged.png")));
		break;
	case CIRCLE:
		this->setCursor(QCursor(QPixmap(":/res/circle.png")));
		break;
	}
}

QColor QtnpImage::get_pen_color(bool pen)
{
	if (!pen) return this->pen.color();
	else return this->rpen.color();
}

void QtnpImage::make_grid(int step, QColor color,int width)
{
	int x,y;
	QPen gridPen;
	gridPen.setColor(color);
	gridPen.setWidth(width);

	grid_step = step;

	painter->begin(image);
	painter->setPen(gridPen);

	for(x=c_x; x<width_; x+=step) {
		painter->drawLine(QPoint(x,0), QPoint(x,height_));
	}
	for(y=c_y; y<height_; y+=step) {
		painter->drawLine(QPoint(0,y), QPoint(width_,y));
	}

	for(x=c_x; x>0; x-=step) {
		painter->drawLine(QPoint(x,0), QPoint(x,height_));
	}
	for(y=c_y; y>0; y-=step) {
		painter->drawLine(QPoint(0,y), QPoint(width_,y));
	}

	painter->end();
	setPixmap(QPixmap::fromImage(*image));

	remember();
	refresh();
}

void QtnpImage::make_coord_plane(int CoordPlaneStep, QColor clr, int width)
{
	int markSize;

	if (CoordPlaneStep >= 8) {
		markSize = CoordPlaneStep/4;
	} else {
		markSize = 2;
	}

	QPen coordPlanePen;
	coordPlanePen.setColor(clr);
	coordPlanePen.setWidth(width);
	//coordPlanePen.setCapStyle(Qt::RoundCap);
	coordPlanePen.setJoinStyle(Qt::RoundJoin);

	int c_start_h, c_end_h, c_start_v, c_end_v;
	c_end_v = height_*0.027;
	c_start_v = height_*0.973;
	c_end_h = width_*0.973;
	c_start_h = width_*0.027;

	painter->begin(image);
	painter->setPen(coordPlanePen);

	{
		painter->drawLine(QPoint(c_x,c_start_v),QPoint(c_x,c_end_v));
		painter->drawLine(QPoint(c_start_h,c_y),QPoint(c_end_h,c_y));
	}

	{
		painter->drawLine(QPoint(c_x,height_*0.027),QPoint(c_x-width_*0.01,height_*(0.037*1.5)));
		painter->drawLine(QPoint(c_x,height_*0.027),QPoint(c_x+width_*0.01,height_*(0.037*1.5)));

		painter->drawLine(QPoint(width_*0.973,c_y),QPoint(width_*(1-(0.037*1.5)),c_y-height_*0.01));
		painter->drawLine(QPoint(width_*0.973,c_y),QPoint(width_*(1-(0.037*1.5)),c_y+height_*0.01));
	}


	QFont markFont("Monospace");
	if (CoordPlaneStep >= 20) {
		markFont.setPointSize(CoordPlaneStep/2);
	} else {
		markFont.setPointSize(10);
	}
	markFont.setLetterSpacing(QFont::PercentageSpacing,75);
	painter->setFont(markFont);

	painter->setOpacity(0.65);

	{
		int mrk = 0;
		for (int i = c_x; i < (c_end_h-CoordPlaneStep); i += CoordPlaneStep) {
			painter->drawLine(QPoint(i,c_y-markSize),QPoint(i,c_y+markSize));
			if (mrk < 9) painter->drawText(
						i-markFont.pointSize()-width,
						c_y+markFont.pointSize()+width+1,
						QString::number(mrk++));
			else painter->drawText(
						i-markFont.pointSize()*1.5-width,
						c_y+markFont.pointSize()+width+1,
						QString::number(mrk++));
			grid_max_x = mrk;

		}
		mrk = 0;
		for (int i = c_x-CoordPlaneStep; i > c_start_h; i -= CoordPlaneStep) {
			painter->drawLine(QPoint(i,c_y-markSize),QPoint(i,c_y+markSize));
			if (mrk > -9) painter->drawText(
						i-markFont.pointSize()*1.3-width,
						c_y+markFont.pointSize()+width+1,
						QString::number(--mrk));
			else painter->drawText(
						i-markFont.pointSize()*1.8-width,
						c_y+markFont.pointSize()+width+1,
						QString::number(--mrk));
			grid_min_x = mrk;
		}
		mrk = 0;
		for (int i = c_y; i > (c_end_v+CoordPlaneStep); i -= CoordPlaneStep) {
			painter->drawLine(QPoint(c_x-markSize,i),QPoint(c_x+markSize,i));
			if (mrk < 9) painter->drawText(
						c_x-markFont.pointSize()+width,
						i+width-(CoordPlaneStep-markFont.pointSize()),
						QString::number(++mrk));
			else painter->drawText(
						c_x-markFont.pointSize()*1.5+width,
						i+width-(CoordPlaneStep-markFont.pointSize()),
						QString::number(++mrk));
			grid_max_y = mrk;
		}
		mrk = 0;
		for (int i = c_y; i < c_start_v; i += CoordPlaneStep) {
			painter->drawLine(QPoint(c_x-markSize,i),QPoint(c_x+markSize,i));
			if (mrk > -9) painter->drawText(
						c_x-markFont.pointSize()*1.5+width,
						i+width+markFont.pointSize()+CoordPlaneStep,
						QString::number(--mrk));
			else painter->drawText(
						c_x-markFont.pointSize()*2+width,
						i+width+markFont.pointSize()+CoordPlaneStep,
						QString::number(--mrk));
			grid_min_y = mrk;
		}
	}

	painter->end();
	setPixmap(QPixmap::fromImage(*image));

	remember();
	refresh();
}

QPoint QtnpImage::get_grid_point_coordinates(QPoint gPoint, int step)
{
	return QPoint(c_x+step*gPoint.x(), c_y-step*gPoint.y());
}

void QtnpImage::draw_graphic(QString str, QColor color, int width)
{
	//cout << globalGridStep << ' ' << str.toStdString() << endl;
	if (grid_step == -1 || str.isEmpty()) return;

	painter->begin(image);
	QPen gpen;
	gpen.setColor(color);
	gpen.setWidth(width);
	gpen.setJoinStyle(Qt::RoundJoin);
	gpen.setCapStyle(Qt::RoundCap);
	painter->setPen(gpen);

	QtnpParser fparser;
	fparser.setE(str.toStdString());
	
	double i = grid_min_x;
	double p_x, p_y, s_x, s_y, b_x, b_y;
	
	b_x = grid_min_x;
	b_y = fparser.getR(i);
	
	s_x = c_x+grid_step*b_x;
	s_y = c_y-grid_step*b_y;
	
	QPolygon grphc;
	grphc.append(QPoint(nearbyint(s_x),nearbyint(s_y)));
	
	for (; i < grid_max_x; i += 0.05) {
		p_x = s_x;
		p_y = s_y;
		b_x = i;
		b_y = fparser.getR(i);
		s_x = c_x+grid_step*b_x;
		s_y = c_y-grid_step*b_y;
//		painter->drawLine(
//		                  QPoint(nearbyint(p_x),nearbyint(p_y)),
//		                  QPoint(nearbyint(s_x),nearbyint(s_y))
//		                        );
		//grphc.append(QPoint(nearbyint(p_x),nearbyint(p_y)));
		grphc.append(QPoint(nearbyint(s_x),nearbyint(s_y)));
	}
	
	//painter->drawLines(lines);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawPolyline(grphc);

	painter->end();
	setPixmap(QPixmap::fromImage(*image));

	remember();
	refresh();
}

void QtnpImage::set_sticky(bool ans)
{
	sticking = ans;
}

