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

#ifndef QTNPNEWFILEDIALOG_H
#define QTNPNEWFILEDIALOG_H

#include <QDialog>
#include <QSpacerItem>
#include <QSpinBox>
#include "QtnpGridAndCoordPlane.h"

namespace Ui {
class QtnpNewFileDialog;
}

class QtnpNewFileDialog : public QDialog
{
	Q_OBJECT
public:
	explicit QtnpNewFileDialog(QWidget *parent = 0);
	~QtnpNewFileDialog();

private:
	Ui::QtnpNewFileDialog *ui;
	QtnpGridAndCoordPlane *GridAndCoordWidget;
	void templates_setup();
	void add_template(uint x, uint y);

private slots:
	void ok_clicked(QColor gridColor, int gridStep, int gridWidth, bool coordPlane, QColor planeColor, int planeWidth, int planeStep);
	void set_template(int i);

signals:
	void new_image(int x, int y, QColor color);
	void add_grid(int step, QColor color, int width = 1);
	void add_coord_plane(int step,QColor color, int width = 1);
};

#endif // QTNPNEWFILEDIALOG_H
