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

#include "QtnpAddGridDialog.h"
#include "ui_QtnpAddGridDialog.h"

QtnpAddGridDialog::QtnpAddGridDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QtnpAddGridDialog)
{
	ui->setupUi(this);

	grid_and_plane_widget = new QtnpGridAndCoordPlane;
	ui->WL->addWidget(grid_and_plane_widget);

	connect(ui->okButton,SIGNAL(clicked()),grid_and_plane_widget,SLOT(emit_get_data()));
	connect(grid_and_plane_widget,SIGNAL(get_data(QColor,int,int,bool,QColor,int,int)),this,SLOT(ok_clicked(QColor,int,int,bool,QColor,int,int)));
	connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

QtnpAddGridDialog::~QtnpAddGridDialog()
{
	delete ui;
}

void QtnpAddGridDialog::ok_clicked(
                QColor grid_color,
                int grid_step,
                int grid_width,
                bool coord_plane,
                QColor plane_color,
                int plane_width,
                int plane_step
                )
{
	this->setCursor(Qt::WaitCursor);
	
	emit add_grid(grid_step,grid_color,grid_width);
	if (coord_plane) emit add_coord_plane(plane_step,plane_color,plane_width);
	this->accept();
	
	this->setCursor(Qt::ArrowCursor);
}
