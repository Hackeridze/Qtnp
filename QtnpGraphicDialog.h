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

private slots:
	void ok_clicked();
};

#endif // QTNPGRAPHICDIALOG_H
