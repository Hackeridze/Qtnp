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

#include "qtnp.h"
#include "ui_qtnp.h"

#define NORMAL_BUTTON_SIZE 33

Qtnp::Qtnp(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Qtnp)
{
	statusbar_clock = new digital_clock(this);

	ui->setupUi(this);
	is_fullscreen = 0;
	image = new QtnpImage;

	opened_file_location = "0";

	rpen_widget = new QtnpColorWidget(255,255,255);
	rpen_widget->setStatusTip(tr("Right pen color!"));
	pen_widget = new QtnpColorWidget(0,0,0);
	pen_widget->setStatusTip(tr("Pen color!"));

	tricksess_box = new QSpinBox(this);
	tricksess_box->setRange(1,200);
	tricksess_box->setValue(1);

	prev_button = new QPushButton(this);
	prev_button->setIcon(QIcon(":/res/prev.png"));
	prev_button->setStatusTip(tr("Previous!"));

	new_file_button = new QPushButton(this);
	new_file_button->setIcon(QIcon(":/res/new.png"));
	new_file_button->setStatusTip(tr("New!"));

	add_grid_button = new QPushButton(this);
	add_grid_button->setIcon(QIcon(":/res/grid.png"));
	add_grid_button->setStatusTip(tr("Grid!"));

	draw_graphic_button = new QPushButton(this);
	draw_graphic_button->setIcon(QIcon(":/res/graphic.png"));
	draw_graphic_button->setStatusTip(tr("graphic!"));


	tools_menu = new QtnpMenuWidget;
	tools_menu->setStatusTip(tr("Tools"));

	change_pens_button = new QPushButton(this);
	change_pens_button->setIcon(QIcon(":/res/change_pens_ico.png"));
	change_pens_button->setStatusTip(tr("Change your pens!"));

	fullscreen_button = new QPushButton(this);
	fullscreen_button->setIcon(QIcon(":/res/fullscreen.png"));
	fullscreen_button->setStatusTip(tr("MAAAX!"));

	sticky_draw_check_box = new QCheckBox(this);
	sticky_draw_check_box->setStatusTip(tr("Stick to web's points"));
	sticky_draw_check_box->setChecked(false);

	this->ui->scrollArea->setWidget(image);
	this->ui->scrollArea->setBackgroundRole(QPalette::Dark);
	this->ui->scrollArea->setAlignment(Qt::AlignTop);
	this->setCentralWidget(this->ui->scrollArea);

	resize(1050,850);
}
Qtnp::~Qtnp()
{
	delete ui;
	delete image;
	delete tricksess_box;
	delete pen_widget;
	delete rpen_widget;
	//delete tricksessBox;
	delete prev_button;
	delete new_file_button;
	delete add_grid_button;
	delete draw_graphic_button;
	delete tools_menu;
	delete change_pens_button;
	delete fullscreen_button;
	delete statusbar_clock;
}

void Qtnp::closeEvent(QCloseEvent *event)
{
	save_file_because(tr("Save before closing?"));
	event->accept();
}

void Qtnp::connections()
{
	connect(ui->actionExit, SIGNAL(triggered()), this,SLOT(exit_clicked()));
	connect(pen_widget,SIGNAL(send_color(QColor)),image,SLOT(set_pen_color(QColor)));
	connect(rpen_widget,SIGNAL(send_color(QColor)),image,SLOT(set_rpen_color(QColor)));
	connect(change_pens_button,SIGNAL(clicked()),this,SLOT(change_pens()));
	connect(tricksess_box,SIGNAL(valueChanged(int)),image,SLOT(pen_trickness(int)));
	connect(fullscreen_button,SIGNAL(clicked()),this,SLOT(full_screen()));
	connect(ui->actionAbout_Qtnp,SIGNAL(triggered()),this,SLOT(about()));
	connect(ui->actionFullScreen,SIGNAL(triggered()),this,SLOT(full_screen()));
	connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(new_file()));
	connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open_file()));
	connect(ui->actionSave_as,SIGNAL(triggered()),this,SLOT(save_as()));
	connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save_file()));
	connect(ui->actionGrid,SIGNAL(triggered()),this,SLOT(add_grid()));
	connect(ui->actionCursor,SIGNAL(triggered()),this,SLOT(set_tool_NONE()));
	connect(ui->actionPen,SIGNAL(triggered()),this,SLOT(set_tool_PEN()));
	connect(ui->actionLine,SIGNAL(triggered()),this,SLOT(set_tool_LINE()));
	connect(ui->actionSquare,SIGNAL(triggered()),this,SLOT(set_tool_SQUARE()));
	connect(ui->actionEllipse,SIGNAL(triggered()),this,SLOT(set_tool_ELLIPSE()));
	connect(ui->actionNegative,SIGNAL(triggered()),image,SLOT(negative()));
	connect(ui->actionGrayscale,SIGNAL(triggered()),image,SLOT(grayscale()));
	connect(ui->actionGraphic,SIGNAL(triggered()),this,SLOT(draw_graphic()));
	connect(new_file_button,SIGNAL(clicked()),this,SLOT(new_file()));
	connect(add_grid_button,SIGNAL(clicked()),this,SLOT(add_grid()));
	connect(draw_graphic_button,SIGNAL(clicked()),this,SLOT(draw_graphic()));
	connect(prev_button,SIGNAL(clicked()),image,SLOT(prev()));
	connect(image,SIGNAL(reset_tool_menu()),tools_menu,SLOT(none()));
	connect(tools_menu,SIGNAL(choosen_tool(QtnpTool)),image,SLOT(set_active_tool(QtnpTool)));
	connect(sticky_draw_check_box,SIGNAL(clicked(bool)),image,SLOT(set_sticky(bool)));
	connect(image,SIGNAL(bad_graphic_exp_error()),this,SLOT(wrong_exp()));
	
	//style actions
	connect(ui->actionGTK,SIGNAL(triggered()),this,SLOT(set_style_gtk()));
	connect(ui->actionWindows,SIGNAL(triggered()),this,SLOT(set_style_win()));
	connect(ui->actionWindows_XP,SIGNAL(triggered()),this,SLOT(set_style_winxp()));
	connect(ui->actionCDE,SIGNAL(triggered()),this,SLOT(set_style_cde()));
	connect(ui->actionPlastique,SIGNAL(triggered()),this,SLOT(set_style_plastique()));
	connect(ui->actionMotif,SIGNAL(triggered()),this,SLOT(set_style_motif()));

	connect(image,SIGNAL(parser_strings(QString)),this,SLOT(text_to_statusbar(QString)));
}

void Qtnp::load_status_bar()
{
	this->ui->statusBar->addPermanentWidget(statusbar_clock);
	this->ui->statusBar->addPermanentWidget(new_file_button);
	this->ui->statusBar->addPermanentWidget(add_grid_button);
	this->ui->statusBar->addPermanentWidget(draw_graphic_button);
	this->ui->statusBar->addPermanentWidget(prev_button);
	this->ui->statusBar->addPermanentWidget(tools_menu);
	this->ui->statusBar->addPermanentWidget(sticky_draw_check_box);
	this->ui->statusBar->addPermanentWidget(pen_widget);
	this->ui->statusBar->addPermanentWidget(rpen_widget);
	this->ui->statusBar->addPermanentWidget(change_pens_button);
	this->ui->statusBar->addPermanentWidget(tricksess_box);
	this->ui->statusBar->addPermanentWidget(fullscreen_button);
}

void Qtnp::buttons_resize()
{
	tricksess_box->setFixedSize(NORMAL_BUTTON_SIZE+20,NORMAL_BUTTON_SIZE);
	change_pens_button->setFixedSize(NORMAL_BUTTON_SIZE,NORMAL_BUTTON_SIZE);
	change_pens_button->setIconSize(QSize(NORMAL_BUTTON_SIZE-6,NORMAL_BUTTON_SIZE-6));
	fullscreen_button->setFixedSize(QSize(NORMAL_BUTTON_SIZE,NORMAL_BUTTON_SIZE));
	fullscreen_button->setIconSize(QSize(NORMAL_BUTTON_SIZE-1,NORMAL_BUTTON_SIZE-1));
	tools_menu->setFixedSize(QSize(NORMAL_BUTTON_SIZE+4,NORMAL_BUTTON_SIZE));
	tools_menu->setIconSize(QSize(NORMAL_BUTTON_SIZE-1,NORMAL_BUTTON_SIZE-1));
	add_grid_button->setIconSize(QSize(NORMAL_BUTTON_SIZE-1,NORMAL_BUTTON_SIZE-1));
	add_grid_button->setFixedSize(QSize(NORMAL_BUTTON_SIZE,NORMAL_BUTTON_SIZE));
	new_file_button->setIconSize(QSize(NORMAL_BUTTON_SIZE-1,NORMAL_BUTTON_SIZE-1));
	new_file_button->setFixedSize(QSize(NORMAL_BUTTON_SIZE,NORMAL_BUTTON_SIZE));
	draw_graphic_button->setIconSize(QSize(NORMAL_BUTTON_SIZE-1,NORMAL_BUTTON_SIZE-1));
	draw_graphic_button->setFixedSize(QSize(NORMAL_BUTTON_SIZE,NORMAL_BUTTON_SIZE));
	prev_button->setIconSize(QSize(NORMAL_BUTTON_SIZE,NORMAL_BUTTON_SIZE));
	prev_button->setFixedSize(QSize(NORMAL_BUTTON_SIZE-1,NORMAL_BUTTON_SIZE));

	ui->actionSave->setIcon(QIcon(":/res/save.png"));
	ui->actionSave_as->setIcon(QIcon(":/res/save_as.png"));
	ui->actionNew->setIcon(QIcon(":/res/new.png"));
	ui->actionAbout_Qtnp->setIcon(QIcon(":/res/about.png"));
	ui->actionFullScreen->setIcon(QIcon(":/res/fullscreen.png"));
	ui->actionExit->setIcon(QIcon(":/res/exit.png"));
	ui->actionOpen->setIcon(QIcon(":/res/open.png"));
	ui->actionPen->setIcon(QIcon(":/res/pencil_ico.png"));
	ui->actionLine->setIcon(QIcon(":/res/line_ico.png"));
	ui->actionGrid->setIcon(QIcon(":/res/grid.png"));
	ui->actionGraphic->setIcon(QIcon(":/res/graphic.png"));
	ui->actionCursor->setIcon(QIcon(":/res/cursor.png"));
}

void Qtnp::about()
{
	QMessageBox::about(this, tr("About Qtnp"),
	                   tr(
	                           "<p align=\"center\"><span style=\" font-size:14pt; font-weight:600; color:#20AA20;\">Cute Noob-Painter</span></p>"
	                           "<br>"
	                           "&nbsp; Qtnp  Copyright (C) 2012  Victor Hackeridze<br>"
	                           "&nbsp; This program comes with ABSOLUTELY NO WARRANTY.<br>"
	                           "&nbsp; This is free software, and you are welcome to<br>"
	                           "&nbsp; redistribute it under certain conditions.<br>"
	                           "&nbsp; For more look at <a href=\"http://www.gnu.org/licenses/gpl-3.0.html\">www.gnu.org</a><br>"
	                           "<p align=\"center\"><img src=\":res/GNU_GPLv3_Logo.png\" width=\"250\" height=\"124\" /></p>"
	                           "&nbsp; Official git repo: <a href=\"https://github.com/Hackeridze/Qtnp\">https://github.com/Hackeridze/Qtnp</a><br>"
	                           "<br>"
	                           "&nbsp; E-mail: <a href=\"mailto:hackeridze@gmail.com\">hackeridze@gmail.com</a>"
	                      ));
}

void Qtnp::new_file()
{
	new_file_dialog = new QtnpNewFileDialog(this);
	connect(new_file_dialog,SIGNAL(new_image(int,int,QColor)),image,SLOT(new_image(int,int,QColor)));
	connect(new_file_dialog,SIGNAL(add_grid(int,QColor,int)),image,SLOT(make_grid(int,QColor,int)));
	connect(new_file_dialog,SIGNAL(add_coord_plane(int,QColor,int)),image,SLOT(make_coord_plane(int,QColor,int)));
	new_file_dialog->show();
}

void Qtnp::open_file()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image..."));
	if (!fileName.isEmpty()) {
		image->load_image(fileName);
		ui->statusBar->showMessage(tr("Image openned!"), 2000);
		image->resize(image->pixmap()->size());
		opened_file_location = fileName;
	} else {
		ui->statusBar->showMessage(tr("Can't open Image!"), 2000);
	}
}

void Qtnp::save_as()
{
	save_file_because(tr("Save current image as..."));
}

void Qtnp::save_file()
{
	if(opened_file_location == "0") {
		save_file_because(tr("Where save?"));
	} else {
		image->save_image(opened_file_location);
		ui->statusBar->showMessage(tr("Save completed"), 2000);
	}
	ui->statusBar->showMessage(tr("Save earlier"), 2000);
}

void Qtnp::save_file_because(QString reason)
{
	QFileDialog::Options options;
	QString filter;
	options |= QFileDialog::DontUseNativeDialog;
	QString fileName = QFileDialog::getSaveFileName(
	                           this, reason,
	                           "",
	                           tr("*.png;;*.jpg;;*.jpeg;;*.bmp;;*.xbm;;*.xpm"),
	                           &filter,
	                           options
	                           );
	if(!fileName.isEmpty()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		int length(filter.size());
		for(int i(length - 1); i > 0; i--) {
			if(filter[i] != fileName[fileName.size() - length + i]) {
				fileName += filter.mid(1);
				break;
			}
		}
		image->save_image(fileName);
		ui->statusBar->showMessage(tr("Save completed"), 2000);
		opened_file_location = fileName;
		QApplication::restoreOverrideCursor();
	}
}

void Qtnp::exit_clicked()
{
	this->close();
}

void Qtnp::add_grid()
{
	add_grid_dialog = new QtnpAddGridDialog(this);
	connect(add_grid_dialog,SIGNAL(add_grid(int,QColor,int)),image,SLOT(make_grid(int,QColor,int)));
	connect(add_grid_dialog,SIGNAL(add_coord_plane(int,QColor,int)),image,SLOT(make_coord_plane(int,QColor,int)));
	add_grid_dialog->show();
}

void Qtnp::full_screen()
{
	if (is_fullscreen == 0) {
		this->showFullScreen();
		this->ui->menuBar->setVisible(0);
		is_fullscreen = 1;
	} else {
		this->showNormal();
		this->ui->menuBar->setVisible(1);
		is_fullscreen = 0;
	}
}

void Qtnp::change_pens()
{
	QColor buff;
	buff = image->get_pen_color(1);
	image->set_rpen_color(image->get_pen_color(0));
	image->set_pen_color(buff);
	pen_widget->set_color(buff);
	rpen_widget->set_color(image->get_pen_color(1));
}

void Qtnp::draw_graphic()
{
	draw_graphic_dialog = new QtnpGraphicDialog(this);
	connect(draw_graphic_dialog,SIGNAL(get_data(QString,QColor,int)),image,SLOT(draw_graphic(QString,QColor,int)));
	draw_graphic_dialog->show();
}

void Qtnp::wrong_exp()
{
	QMessageBox::warning(this, tr("WRONG EXPRESSION"),
	                     tr("Wrong expression!\n"
	                        "It's can't be drawn"),
	                     QMessageBox::Ok);
}

void Qtnp::text_to_statusbar(QString text)
{
	ui->statusBar->showMessage(text, 10000);
}

void Qtnp::set_tool_NONE()
{
	image->set_active_tool(NONE);
}
void Qtnp::set_tool_PEN()
{
	image->set_active_tool(PEN);
}
void Qtnp::set_tool_LINE()
{
	image->set_active_tool(LINE);
}
void Qtnp::set_tool_SQUARE()
{
	image->set_active_tool(SQUARE);
}
void Qtnp::set_tool_ELLIPSE()
{
	image->set_active_tool(ELLIPSE);
}
void Qtnp::set_tool_JOGGED_LINE()
{
	image->set_active_tool(JOGGED_LINE);
}

void Qtnp::set_style_win()
{
	qApp->setStyle("windows");
}

void Qtnp::set_style_winxp()
{
	qApp->setStyle("windowsxp");
}

void Qtnp::set_style_gtk()
{
	qApp->setStyle("gtk");
}

void Qtnp::set_style_cde()
{
	qApp->setStyle("cde");
}

void Qtnp::set_style_plastique()
{
	qApp->setStyle("plastique");
}

void Qtnp::set_style_motif()
{
	qApp->setStyle("motif");
}
