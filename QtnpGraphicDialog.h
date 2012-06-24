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
