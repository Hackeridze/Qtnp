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
