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

#include "QtnpNewFileDialog.h"
#include "ui_QtnpNewFileDialog.h"

QtnpNewFileDialog::QtnpNewFileDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QtnpNewFileDialog)
{
	ui->setupUi(this);


	GridAndCoordWidget = new QtnpGridAndCoordPlane(this);
	GridAndCoordWidget->make_grid_checkable();
	ui->GridAndCoordWidgetLayout->addWidget(GridAndCoordWidget);

	connect(ui->okButton,SIGNAL(clicked()),GridAndCoordWidget,SLOT(emit_get_data()));
	connect(GridAndCoordWidget,SIGNAL(get_data(QColor,int,int,bool,QColor,int,int)),this,SLOT(ok_clicked(QColor,int,int,bool,QColor,int,int)));
	connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
	connect(ui->TemplateCB,SIGNAL(currentIndexChanged(int)),this,SLOT(set_template(int)));

	templates_setup();
}

QtnpNewFileDialog::~QtnpNewFileDialog()
{
	delete ui;
	delete GridAndCoordWidget;
}

void QtnpNewFileDialog::templates_setup()
{
	add_template(640,480);
	add_template(800,600);
	add_template(1024,768);
	add_template(1280,1024);
	add_template(1600,1200);
	ui->TemplateCB->setCurrentIndex(3);
}

void QtnpNewFileDialog::add_template(uint x, uint y)
{
	QString *str = new QString;
	str->append(QString::number(x));
	str->append("x");
	str->append(QString::number(y));
	ui->TemplateCB->addItem(QIcon(":/res/template.png"),*str,QPoint(x,y));
	delete str;
}

void QtnpNewFileDialog::set_template(int i)
{
	ui->widthSpinBox->setValue(ui->TemplateCB->itemData(i).toPoint().x());
	ui->heightSpinBox->setValue(ui->TemplateCB->itemData(i).toPoint().y());
}

void QtnpNewFileDialog::ok_clicked(QColor gridColor,
                                   int gridStep,
                                   int gridWidth,
                                   bool coordPlane,
                                   QColor planeColor,
                                   int planeWidth,
                                   int planeStep)
{
	this->setCursor(Qt::WaitCursor);

	emit new_image(ui->widthSpinBox->value(), 
	               ui->heightSpinBox->value(), 
	               Qt::white);

	if (GridAndCoordWidget->is_checked()) {
		emit add_grid(gridStep,gridColor,gridWidth);
		if (coordPlane)
			emit add_coord_plane(planeStep,planeColor,planeWidth);
	}
	//this->accept();
	this->setCursor(Qt::ArrowCursor);
	this->deleteLater();
}
