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

#include "QtnpGraphicDialog.h"
#include "ui_QtnpGraphicDialog.h"

QtnpGraphicDialog::QtnpGraphicDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QtnpGraphicDialog)
{
	ui->setupUi(this);
	line_color_widget = new QtnpColorWidget(0,0,0,24);
	QSpacerItem *prop_spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);

	ui->propLayout->addWidget(line_color_widget);
	ui->propLayout->addSpacerItem(prop_spacer);

	connect(ui->okB,SIGNAL(clicked()),this,SLOT(ok_clicked()));
}

QtnpGraphicDialog::~QtnpGraphicDialog()
{
	delete ui;
	delete line_color_widget;
}

void QtnpGraphicDialog::ok_clicked()
{
	this->setCursor(Qt::WaitCursor);// Может занять время =\

	emit get_data(ui->formula->text(),
	              line_color_widget->get_current_color(),
	              ui->spinBox->value());
	this->accept();

	this->setCursor(Qt::ArrowCursor);
}
