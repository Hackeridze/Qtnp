#include <QtGui>

#include "digital_clock.h"

digital_clock::digital_clock(QWidget *parent)
        : QLCDNumber(parent)
{
	setSegmentStyle(Filled);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
	timer->start(1000);

	show_time();

	setWindowTitle(tr("Digital Clock"));
	resize(100, 33);
}

void digital_clock::show_time()
{
	QTime time = QTime::currentTime();
	QString text = time.toString("hh:mm");
	if ((time.second() % 2) == 0)
		text[2] = ' ';
	display(text);
}
