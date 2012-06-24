#ifndef QTNPADDGRIDDIALOG_H
#define QTNPADDGRIDDIALOG_H

#include <QDialog>
#include "QtnpColorWidget.h"
#include <QSpacerItem>
#include <QSpinBox>
#include "QtnpGridAndCoordPlane.h"

namespace Ui {
class QtnpAddGridDialog;
}

class QtnpAddGridDialog : public QDialog {
	Q_OBJECT
public:
	explicit QtnpAddGridDialog(QWidget *parent = 0);
	~QtnpAddGridDialog();

private:
	Ui::QtnpAddGridDialog *ui;
	QtnpGridAndCoordPlane *grid_and_plane_widget;
private slots:
	void ok_clicked(QColor grid_color, int grid_step, int grid_width, bool coord_plane, QColor plane_color, int plane_width, int plane_step);

signals:
	void add_grid(int step, QColor color,int width = 1);
	void add_coord_plane(int step,QColor color,int width = 1);
};

#endif // QTNPADDGRIDDIALOG_H
