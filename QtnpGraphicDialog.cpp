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
	prop_spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);

	ui->propLayout->addWidget(line_color_widget);
	ui->propLayout->addSpacerItem(prop_spacer);

	connect(ui->okB,SIGNAL(clicked()),this,SLOT(ok_clicked()));
}

QtnpGraphicDialog::~QtnpGraphicDialog()
{
	prop_spacer->~QLayoutItem();
	//delete prop_spacer;
	delete ui;
	delete line_color_widget;
}

void QtnpGraphicDialog::ok_clicked()
{
	this->setCursor(Qt::WaitCursor);

	emit get_data(ui->formula->text(),
	              line_color_widget->get_current_color(),
	              ui->spinBox->value());
	this->accept();

	this->setCursor(Qt::ArrowCursor);
	this->deleteLater();
}

void QtnpGraphicDialog::insert(QString t)
{
	int p = ui->formula->cursorPosition();
	ui->formula->insert(t);
	ui->formula->setCursorPosition(p+t.size());
}

void QtnpGraphicDialog::insert_f(QString t)
{
	int p = ui->formula->cursorPosition();
	ui->formula->insert(t + QString("()"));
	ui->formula->setCursorPosition(p+t.size()+1);
}

void QtnpGraphicDialog::on_zero_clicked()
{
	insert("0");
}

void QtnpGraphicDialog::on_one_clicked()
{
	insert("1");
}

void QtnpGraphicDialog::on_two_clicked()
{
	insert("2");
}

void QtnpGraphicDialog::on_three_clicked()
{
	insert("3");
}

void QtnpGraphicDialog::on_four_clicked()
{
	insert("4");
}

void QtnpGraphicDialog::on_five_clicked()
{
	insert("5");
}

void QtnpGraphicDialog::on_six_clicked()
{
	insert("6");
}

void QtnpGraphicDialog::on_seven_clicked()
{
	insert("7");
}

void QtnpGraphicDialog::on_eight_clicked()
{
	insert("8");
}

void QtnpGraphicDialog::on_nine_clicked()
{
	insert("9");
}

void QtnpGraphicDialog::on_div_clicked()
{
	insert("/");
}

void QtnpGraphicDialog::on_mult_clicked()
{
	insert("*");
}

void QtnpGraphicDialog::on_minus_clicked()
{
	insert("-");
}

void QtnpGraphicDialog::on_plus_clicked()
{
	insert("+");
}

void QtnpGraphicDialog::on_clear_clicked()
{
	ui->formula->clear();
}

void QtnpGraphicDialog::on_dot_clicked()
{
	insert(".");
}

void QtnpGraphicDialog::on_del_left_clicked()
{
	ui->formula->backspace();
}

void QtnpGraphicDialog::on_del_right_clicked()
{
	ui->formula->del();
}

void QtnpGraphicDialog::on_cursor_right_clicked()
{
	ui->formula->setCursorPosition(ui->formula->cursorPosition()+1);
}

void QtnpGraphicDialog::on_cursor_left_clicked()
{
	ui->formula->setCursorPosition(ui->formula->cursorPosition()+1);
}

void QtnpGraphicDialog::on_pi_clicked()
{
	insert("_pi");
}

void QtnpGraphicDialog::on_pi_3_clicked()
{
	insert("_pi/3");
}

void QtnpGraphicDialog::on_pi_6_clicked()
{
	insert("_pi/6");
}

void QtnpGraphicDialog::on_pi_4_clicked()
{
	insert("_pi/4");
}

void QtnpGraphicDialog::on_X_clicked()
{
	insert("x");
}

void QtnpGraphicDialog::on_sin_clicked()
{
	insert_f("sin");
}

void QtnpGraphicDialog::on_cos_clicked()
{
	insert_f("cos");
}

void QtnpGraphicDialog::on_tan_clicked()
{
	insert_f("tan");
}

void QtnpGraphicDialog::on_ctg_clicked()
{
	insert_f("(1/tan");
	insert(")");
	ui->formula->setCursorPosition(ui->formula->cursorPosition()-1);
}

void QtnpGraphicDialog::on_asin_clicked()
{
	insert_f("asin");
}

void QtnpGraphicDialog::on_acos_clicked()
{
	insert_f("acos");
}

void QtnpGraphicDialog::on_atan_clicked()
{
	insert_f("atan");
}

void QtnpGraphicDialog::on_sqrt_clicked()
{
	insert_f("sqrt");
}

void QtnpGraphicDialog::on_komma_clicked()
{
	insert(", ");
}

void QtnpGraphicDialog::on_min_clicked()
{
	insert_f("min");
}

void QtnpGraphicDialog::on_max_clicked()
{
	insert_f("max");
}

void QtnpGraphicDialog::on_sum_clicked()
{
	insert_f("sum");
}

void QtnpGraphicDialog::on_avg_clicked()
{
	insert_f("avg");
}

void QtnpGraphicDialog::on_and__clicked()
{
	insert(" && ");
}

void QtnpGraphicDialog::on_or__clicked()
{
	insert(" || ");
}

void QtnpGraphicDialog::on_if_else_clicked()
{
	insert(" ? : ");
}

void QtnpGraphicDialog::on_assign__clicked()
{
	insert("=");
}

void QtnpGraphicDialog::on_greater_clicked()
{
	insert(">");
}

void QtnpGraphicDialog::on_less_clicked()
{
	insert("<");
}

void QtnpGraphicDialog::on_not_equal_clicked()
{
	insert("!=");
}

void QtnpGraphicDialog::on_pow_clicked()
{
	insert("^");
}

void QtnpGraphicDialog::on_undo_clicked()
{
	ui->formula->undo();
}

void QtnpGraphicDialog::on_redo_clicked()
{
	ui->formula->redo();
}
