#include "QtnpImage.h"
#include "fparser/fparser.h"
#include <iostream>
#include <math.h>
using namespace std;

// виджет изображения и функци изменения оного
QtnpImage::QtnpImage()
{
	new_image(1280,1024,Qt::white);

	grid_max_x = 0;
	grid_max_y = 0;
	grid_min_x = 0;
	grid_min_y = 0;

	setAlignment(Qt::AlignTop);

	// устанавливаем стандартные цвета карандашей
	pen.setColor(Qt::black);
	rpen.setColor(Qt::white);

	brush.setColor(Qt::green);
	// ДЕЛАЕМ ОКРУГЛЫМ КАРАНДАШ  >(надо прикрутить функцию смены стилей)<
	pen.setStyle(Qt::SolidLine); // непрерывистая
	pen.setCapStyle(Qt::RoundCap); // закругленные края
	pen.setJoinStyle(Qt::RoundJoin); // закругленные соединения
	rpen.setCapStyle(Qt::RoundCap); // закругленные края
	rpen.setJoinStyle(Qt::RoundJoin); // закругленные соединения
}

QtnpImage::~QtnpImage()
{
	delete image;
	delete image_pixmap;
	delete painter;
}



// новое изображение
void QtnpImage::new_image(int x, int y, QColor color)
{
	image = new QImage();
	image_pixmap = new QPixmap(x,y);
	painter = new QPainter(image_pixmap);
	painter->fillRect(0,0, x,y, color);
	painter->end();
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();
	height_ = image->height();
	width_ = image->width();
	emit reset_tool_menu();
	set_active_tool(NONE);
	prev_list.append(*image);
	c_x = width_/2;
	c_y = height_/2;
	grid_step = -1;
	//resize(pixmap()->size()); // изменяем размер виджета по размеру пиксмапа
}
// Загрузка изображения
void QtnpImage::load_image(const QString ImageFile)
{
	image->load(ImageFile);
	image_pixmap->load(ImageFile);
	setPixmap(*image_pixmap);
	height_ = image->height();
	width_ = image->width();
	emit reset_tool_menu();
	set_active_tool(NONE);
	prev_list.append(*image);
	c_x = width_/2;
	c_y = height_/2;
	grid_step = -1;
}
// эффект негатива
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
// сепия
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
// сохранение изображения
void QtnpImage::save_image(const QString ImageFile)
{
	//imageImage->save(ImageFile);
	image_pixmap->save(ImageFile); // для верности, лол
}
// обновить изображение
void QtnpImage::refresh()
{
	*image_pixmap = image_pixmap->fromImage(*image);
	setPixmap(*image_pixmap);
}
// обработка клика мыши
void QtnpImage::mousePressEvent(QMouseEvent *event)
{
	// обработка левой кнопки
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
			image_pixmap_copy = *image_pixmap;
			start = end = event -> pos();
			break;
		case SQUARE:
			painting = 1;
			remember();
			image_pixmap_copy = *image_pixmap;
			start = end = event -> pos();
			break;
		case ELLIPSE:
			painting = 1;
			remember();
			image_pixmap_copy = *image_pixmap;
			start = end = event -> pos();
			break;
		case CIRCLE:
			painting = 1;
			remember();
			image_pixmap_copy = *image_pixmap;
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
				image_pixmap_copy = *image_pixmap;
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
			image_pixmap_copy = *image_pixmap;
			start = end = event -> pos();
			break;
		case SQUARE:
			painting = 1;
			remember();
			image_pixmap_copy = *image_pixmap;
			start = end = event -> pos();
			break;
		case ELLIPSE:
			painting = 1;
			remember();
			image_pixmap_copy = *image_pixmap;
			start = end = event -> pos();
			break;
		case CIRCLE:
			painting = 1;
			remember();
			image_pixmap_copy = *image_pixmap;
			start = end = event -> pos();
			break;
		case JOGGED_LINE:
			painting = 0;
			jogged_line_first_click_done = true;
			break;
		}
	}
}
// обработка движения мыши, дабы видеть получаемое изображение
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
			*image_pixmap = image_pixmap_copy;
			draw_line(pen);
			break;
		case SQUARE:
			*image_pixmap = image_pixmap_copy;
			draw_square(pen);
			break;
		case ELLIPSE:
			*image_pixmap = image_pixmap_copy;
			draw_ellipse(pen);
			break;
		case CIRCLE:
			*image_pixmap = image_pixmap_copy;
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
				*image_pixmap = image_pixmap_copy;
				draw_line(rpen);
				break;
			case SQUARE:
				*image_pixmap = image_pixmap_copy;
				draw_square(rpen);
				break;
			case ELLIPSE:
				*image_pixmap = image_pixmap_copy;
				draw_ellipse(rpen);
				break;
			case CIRCLE:
				*image_pixmap = image_pixmap_copy;
				draw_line(rpen);
				draw_circle(rpen);
				break;
			}
		}
}

// обработка отпуска мыши
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
			*image_pixmap = image_pixmap_copy;
			draw_line(pen);
			painting = 0;
			break;
		case SQUARE:
			*image_pixmap = image_pixmap_copy;
			draw_square(pen);
			painting = 0;
			break;
		case ELLIPSE:
			*image_pixmap = image_pixmap_copy;
			draw_ellipse(pen);
			painting = 0;
			break;
		case CIRCLE:
			*image_pixmap = image_pixmap_copy;
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
			*image_pixmap = image_pixmap_copy;
			draw_line(rpen);
			painting = 0;
			break;
		case SQUARE:
			*image_pixmap = image_pixmap_copy;
			draw_square(rpen);
			painting = 0;
			break;
		case ELLIPSE:
			*image_pixmap = image_pixmap_copy;
			draw_ellipse(rpen);
			painting = 0;
			break;
		case CIRCLE:
			*image_pixmap = image_pixmap_copy;
			draw_circle(rpen);
			painting = 0;
			break;
		}
	}
}
// функция, рисующая линию
void QtnpImage::draw_line(QPen p)
{
	painter->begin(image_pixmap);
	painter->setPen(p);
	painter->drawLine(start, end);
	painter->end();
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();
}
// функция, рисующая прямогольник
void QtnpImage::draw_square(QPen p)
{
	painter->begin(image_pixmap);
	painter->setPen(p);
	painter->drawRect(QRect(start,end));
	painter->end();
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();
}
// функция, рисующая эллипс
void QtnpImage::draw_ellipse(QPen p)
{
	painter->begin(image_pixmap);
	painter->setPen(p);
	painter->drawEllipse(QRect(start,end));
	painter->end();
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();
}
void QtnpImage::draw_circle(QPen p)
{
	painter->begin(image_pixmap);
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
	painter->drawEllipse(QRect(QPoint(x_F,y_F),QPoint(x_F2,y_F2)));
	painter->end();
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();
}

// устаналвивает цвет левой кн. мыши
void QtnpImage::set_pen_color(QColor color)
{
	pen.setColor(color);
}
// устаналвивает цвет правой кн. мыши
void QtnpImage::set_rpen_color(QColor color)
{
	rpen.setColor(color);
}
// устаналвивает цвет бруша
void QtnpImage::set_brush_color(QColor color)
{
	pen.setColor(color);
	pen.setBrush(brush);
}
// устанавливаем толщину мыши
void QtnpImage::pen_trickness(int size)
{
	pen.setWidth(size); // толщина
	rpen.setWidth(size);
}
// отмена действия
void QtnpImage::prev(void)
{
	if (!(prev_list.size() < 3)) {
		*image = prev_list.last();
		prev_list.pop_back();
		refresh();
	}
}

//запоминаем изменения
void QtnpImage::remember(void)
{
	if (prev_list.size() > 7) prev_list.pop_front();
	prev_list.append(*image);
}

// выбираем нужный инструмент
void QtnpImage::set_active_tool(QtnpTool whichTool)
{
	active_tool = whichTool;
	painting = 0;
	jogged_line_first_click_done = true;
	switch(active_tool) {
	case NONE:
		this->setCursor(Qt::ArrowCursor); // усатнавливам стандартный курсор для инструмента НИЧЕГО(МВАХАХА)
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

// возвращает цвет левой кн. если pen=0 и правой если 1
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

	painter->begin(image_pixmap);
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
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();

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

	painter->begin(image_pixmap);
	painter->setPen(coordPlanePen);

	// Крестовина
	{
		painter->drawLine(QPoint(c_x,c_start_v),QPoint(c_x,c_end_v));
		painter->drawLine(QPoint(c_start_h,c_y),QPoint(c_end_h,c_y));
	}

	// Рисование стрелочек
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

	// Метки
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
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();

	remember();
	refresh();
}

QPoint QtnpImage::get_grid_point(QPoint gPoint, int step)
{
	return QPoint(c_x+step*gPoint.x(), c_y-step*gPoint.y());
}

void QtnpImage::draw_graphic(QString str, QColor color, int width)
{
	//cout << globalGridStep << ' ' << str.toStdString() << endl;
	if (grid_step == -1 || str.isEmpty()) return;

	painter->begin(image_pixmap);
	QPen gpen;
	gpen.setColor(color);
	gpen.setWidth(width);
	gpen.setJoinStyle(Qt::RoundJoin);
	gpen.setCapStyle(Qt::RoundCap);
	painter->setPen(gpen);

	QtnpParser fparser;
	fparser.setE(str.toStdString());
	
	int i = grid_min_x;
	QPoint buf(grid_min_x, fparser.getR(i));
	QPoint fpoint;
	QPoint spoint = get_grid_point(buf,grid_step);

	for (; i < grid_max_x; i += 1) {
		fpoint = spoint;
		buf.setX(i);;
		buf.setY(fparser.getR(i));
		//cout << buf.x() << ' ' << buf.y() << endl;
		spoint = get_grid_point(buf,grid_step);
		painter->drawLine(QPoint(fpoint.x(),fpoint.y()),QPoint(spoint.x(),spoint.y()));
		//cout << fpoint.x << ' ' << fpoint.y << endl;
	}

	painter->end();
	setPixmap(*image_pixmap);
	*image = image_pixmap->toImage();

	remember();
	refresh();
}

