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

#ifndef QTNPGRAPHICDIALOG_H
#define QTNPGRAPHICDIALOG_H

#include <QDialog>
#include "QtnpColorWidget.h"
#include <QSpacerItem>

namespace Ui {
class QtnpGraphicDialog;
}

class QtnpGraphicDialog : public QDialog {
	Q_OBJECT

public:
	explicit QtnpGraphicDialog(QWidget *parent = 0);
	~QtnpGraphicDialog();

signals:
	void get_data(QString str, QColor color, int width);

private:
	Ui::QtnpGraphicDialog *ui;
	QtnpColorWidget *line_color_widget;
	QSpacerItem *prop_spacer;
	
	void insert(QString t);
	void insert_f(QString t);

private slots:
	void ok_clicked();
	void on_mult_clicked();
	void on_zero_clicked();
	void on_one_clicked();
	void on_two_clicked();
	void on_three_clicked();
	void on_four_clicked();
	void on_five_clicked();
	void on_six_clicked();
	void on_seven_clicked();
	void on_eight_clicked();
	void on_nine_clicked();
	void on_div_clicked();
	void on_minus_clicked();
	void on_plus_clicked();
	void on_clear_clicked();
	void on_dot_clicked();
	void on_del_left_clicked();
	void on_del_right_clicked();
	void on_cursor_right_clicked();
	void on_cursor_left_clicked();
	void on_pi_clicked();
	void on_pi_3_clicked();
	void on_pi_6_clicked();
	void on_pi_4_clicked();
	void on_X_clicked();
	void on_sin_clicked();
	void on_cos_clicked();
	void on_tan_clicked();
	void on_ctg_clicked();
	void on_asin_clicked();
	void on_acos_clicked();
	void on_atan_clicked();
	void on_sqrt_clicked();
	void on_min_clicked();
	void on_komma_clicked();
	void on_max_clicked();
	void on_sum_clicked();
	void on_avg_clicked();
	void on_and__clicked();
	void on_or__clicked();
	void on_if_else_clicked();
	void on_assign__clicked();
	void on_greater_clicked();
	void on_less_clicked();
	void on_not_equal_clicked();
	void on_pow_clicked();
	void on_undo_clicked();
	void on_redo_clicked();
	void on_bracket_left_2_clicked();
	void on_bracket_right_2_clicked();
};

#endif // QTNPGRAPHICDIALOG_H
