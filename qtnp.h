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

#ifndef QTNP_H
#define QTNP_H

#include <QMainWindow>
#include <QtGui>
#include "QtnpImage.h"
#include "QtnpColorWidget.h"
#include "QtnpNewFileDialog.h"
#include "QtnpAddGridDialog.h"
#include "QtnpGraphicDialog.h"
#include "QtnpMenuWidget.h"
#include "digital_clock.h"

namespace Ui {
class Qtnp;
}

class Qtnp : public QMainWindow {
	Q_OBJECT
public:
	explicit Qtnp(QWidget *parent = 0);
	~Qtnp();

	void connections();
	void buttons_resize();
	void load_status_bar();

private slots:
	void exit_clicked();
	void full_screen();
	void change_pens();
	void save_file();
	void new_file();
	void save_as(void);
	void save_file_because(QString reason);
	void open_file();
	void add_grid();
	void set_tool_NONE();
	void set_tool_PEN();
	void set_tool_LINE();
	void set_tool_SQUARE();
	void set_tool_ELLIPSE();
	void set_tool_JOGGED_LINE();
	void set_style_win();
	void set_style_winxp();
	void set_style_gtk();
	void set_style_cde();
	void set_style_plastique();
	void set_style_motif();
	void about();
	void draw_graphic();
	void wrong_exp();

private:
	digital_clock *statusbar_clock;
	QtnpImage *image;
	QtnpColorWidget *pen_widget, *rpen_widget;
	QSpinBox *tricksess_box;
	QCheckBox *sticky_draw_check_box;
	QPushButton *change_pens_button, *fullscreen_button,
	*new_file_button, *add_grid_button,
	*draw_graphic_button,*prev_button;
	QtnpMenuWidget *tools_menu;
	Ui::Qtnp *ui;
	QtnpNewFileDialog *new_file_dialog;
	QtnpAddGridDialog *add_grid_dialog;
	QtnpGraphicDialog *draw_graphic_dialog;
	bool is_fullscreen;
	QString opened_file_location;

	QHBoxLayout *l;

protected:
	void closeEvent(QCloseEvent*);
};

#endif // QTNP_H
