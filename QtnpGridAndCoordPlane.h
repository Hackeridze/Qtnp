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

#ifndef QTNPGRIDANDCOORDPLANE_H
#define QTNPGRIDANDCOORDPLANE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSpacerItem>
#include "QtnpColorWidget.h"

namespace Ui {
class QtnpGridAndCoordPlane;
}
class QtnpGridAndCoordPlane : public QWidget {
	Q_OBJECT

public:
	explicit QtnpGridAndCoordPlane(QWidget *parent = 0);
	~QtnpGridAndCoordPlane();
	void make_grid_checkable();
	bool is_checked();

public slots:
	void emit_get_data();

signals:
	void get_data(QColor grid_color,
	              int grid_step,
	              int grid_width,
	              bool coord_plane,
	              QColor plane_color,
	              int plane_width,
	              int plane_step
	              );

private:
	Ui::QtnpGridAndCoordPlane *ui;
	QLabel *step_l, *step_grid_l,
	*color_and_width_l, *alternate_coord_plane_color_and_width_l;
	QSpinBox *step_spin_b, *step_grid_spin_b, *width_spin_b, *alternate_width_spin_b;
	QtnpColorWidget *grid_color_widget, *plane_color_widget;
	QSpacerItem *spacer;
};

#endif // QTNPGRIDANDCOORDPLANE_H
