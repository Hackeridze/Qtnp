#ifndef QTNPGRIDANDCOORDPLANE_H
#define QTNPGRIDANDCOORDPLANE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSpacerItem>
#include "QtnpColorWidget.h"

namespace Ui {
class QtnpGridAndCoordPlane;
}
// Виджет для выбора сетки и координатной плоскости
class QtnpGridAndCoordPlane : public QWidget {
	Q_OBJECT

public:
	explicit QtnpGridAndCoordPlane(QWidget *parent = 0);
	~QtnpGridAndCoordPlane();
	void make_grid_checkable();
	bool is_checkable();

public slots:
	void emit_get_data(); // Вызывает сигнал передачи данных из виджета

signals:
	void get_data(QColor grid_color,
		      int grid_step,
		      int grid_width,
		      bool coord_plane,
		      QColor plane_color,
		      int plane_width,
		      int plane_step);

private:
	Ui::QtnpGridAndCoordPlane *ui;
	QLabel *step_l, *step_grid_l,
	*color_and_width_l, *alternate_coord_plane_color_and_width_l;
	QSpinBox *step_spin_b, *step_grid_spin_b, *width_spin_b, *alternate_width_spin_b;
	QtnpColorWidget *grid_color_widget, *plane_color_widget;
	QSpacerItem *spacer;
};

#endif // QTNPGRIDANDCOORDPLANE_H
