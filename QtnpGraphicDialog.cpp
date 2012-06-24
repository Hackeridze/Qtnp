#include "QtnpGraphicDialog.h"
#include "ui_QtnpGraphicDialog.h"

QtnpGraphicDialog::QtnpGraphicDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QtnpGraphicDialog)
{
	ui->setupUi(this);
	line_color_widget = new QtnpColorWidget(0,0,0,24);
	prop_spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);

	ui->propLayout->addWidget(line_color_widget);
	ui->propLayout->addSpacerItem(prop_spacer);

	connect(ui->okB,SIGNAL(clicked()),this,SLOT(ok_clicked()));
}

QtnpGraphicDialog::~QtnpGraphicDialog()
{
	delete ui;
	delete line_color_widget;
	delete prop_spacer;
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
