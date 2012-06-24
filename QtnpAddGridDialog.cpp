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
