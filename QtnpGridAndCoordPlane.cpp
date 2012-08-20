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

#include "QtnpGridAndCoordPlane.h"
#include "ui_QtnpGridAndCoordPlane.h"

QtnpGridAndCoordPlane::QtnpGridAndCoordPlane(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::QtnpGridAndCoordPlane)
{
	ui->setupUi(this);

	ui->gridGB->setLayout(ui->GridLayout);
	ui->CoordPlaneGB->setLayout(ui->CoordLayout);

	step_l = new QLabel(this);
	step_l->setText(tr("Step:"));
	ui->GridLayout->addWidget(step_l);

	step_spin_b = new QSpinBox(this);
	step_spin_b->setMinimum(3);
	step_spin_b->setMaximum(9999);
	step_spin_b->setValue(30);
	ui->GridLayout->addWidget(step_spin_b);

	color_and_width_l = new QLabel(this);
	color_and_width_l->setText(tr("Color and width:"));
	ui->GridLayout->addWidget(color_and_width_l);

	grid_color_widget = new QtnpColorWidget(0,0,0,20);
	ui->GridLayout->addWidget(grid_color_widget);

	width_spin_b = new QSpinBox(this);
	width_spin_b->setMinimum(1);
	width_spin_b->setMaximum(999);
	width_spin_b->setValue(1);
	ui->GridLayout->addWidget(width_spin_b);

	step_grid_l = new QLabel(this);
	step_grid_l->setText(tr("Step:"));
	ui->CoordLayout->addWidget(step_grid_l);

	step_grid_spin_b = new QSpinBox(this);
	step_grid_spin_b->setMinimum(3);
	step_grid_spin_b->setMaximum(9999);
	step_grid_spin_b->setValue(30);
	ui->CoordLayout->addWidget(step_grid_spin_b);


	alternate_coord_plane_color_and_width_l = new QLabel;
	alternate_coord_plane_color_and_width_l->setText(tr("Color and width:"));
	ui->CoordLayout->addWidget(alternate_coord_plane_color_and_width_l);

	plane_color_widget = new QtnpColorWidget(0,0,0,20);
	ui->CoordLayout->addWidget(plane_color_widget);

	alternate_width_spin_b = new QSpinBox(this);
	alternate_width_spin_b->setMinimum(1);
	alternate_width_spin_b->setMaximum(999);
	alternate_width_spin_b->setValue(2);
	ui->CoordLayout->addWidget(alternate_width_spin_b);

	QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
	ui->CoordLayout->addSpacerItem(spacer);

	connect(width_spin_b,SIGNAL(valueChanged(int)),alternate_width_spin_b,SLOT(setValue(int)));
	connect(step_spin_b,SIGNAL(valueChanged(int)),step_grid_spin_b,SLOT(setValue(int)));
	connect(grid_color_widget,SIGNAL(send_color(QColor)),plane_color_widget,SLOT(set_color(QColor)));
}

QtnpGridAndCoordPlane::~QtnpGridAndCoordPlane() {
	delete ui;
	delete step_l;
	delete step_spin_b;
	delete color_and_width_l;
	delete grid_color_widget;
	delete width_spin_b;
	delete step_grid_l;
	delete step_grid_spin_b;
	delete alternate_coord_plane_color_and_width_l;
	delete plane_color_widget;
	delete alternate_width_spin_b;
}

void QtnpGridAndCoordPlane::emit_get_data() {
	emit get_data(grid_color_widget->get_current_color(),
	              step_spin_b->value(),width_spin_b->value(),
	              ui->CoordPlaneGB->isChecked(),
	              plane_color_widget->get_current_color(),
	              alternate_width_spin_b->value(),
	              step_grid_spin_b->value());
}

void QtnpGridAndCoordPlane::make_grid_checkable() {
	ui->gridGB->setCheckable(true);
	ui->gridGB->setChecked(false);
	ui->CoordPlaneGB->setEnabled(false);
	connect(ui->gridGB,SIGNAL(toggled(bool)),ui->CoordPlaneGB,SLOT(setEnabled(bool)));
}

bool QtnpGridAndCoordPlane::is_checked() {
	if (ui->gridGB->isChecked()) return true;
	else return false;
}
