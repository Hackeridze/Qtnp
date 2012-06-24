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
