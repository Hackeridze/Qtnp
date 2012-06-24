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

namespace Ui {
class Qtnp;
}

class Qtnp : public QMainWindow {
	Q_OBJECT
public:
	explicit Qtnp(QWidget *parent = 0);
	~Qtnp();

	// функции загрузки в паблике, ибо надо иметь доступ к ним из main
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
	bool check_saving();
	void add_grid();
	void set_tool_NONE();
	void set_tool_PEN();
	void set_tool_LINE();
	void set_tool_SQUARE();
	void set_tool_ELLIPSE();
	void set_tool_JOGGED_LINE();
	void about();
	void draw_graphic();

private:
	QtnpImage *image, *saved_image;
	QtnpColorWidget *pen_widget, *rpen_widget;
	QSpinBox *tricksess_box;
	QPushButton *change_pens_button, *fullscreen_button,
	*new_file_button, *add_grid_button,
	*draw_graphic_button,*prev_button;
	QtnpMenuWidget *tools_menu;
	Ui::Qtnp *ui;
	QtnpNewFileDialog *new_file_dialog;
	QtnpAddGridDialog *add_grid_dialog;
	QtnpGraphicDialog *draw_graphic_dialog;
	bool is_fullscreen,/* is_saved, isSomeResOpenned,*/is_freshly;
	QString opened_file_location;

	QHBoxLayout *l;

protected:
	void closeEvent(QCloseEvent*);
};

#endif // QTNP_H
