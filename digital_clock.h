#ifndef DIGITAL_CLOCK_H
#define DIGITAL_CLOCK_H

#include <QLCDNumber>

class digital_clock : public QLCDNumber
{
	Q_OBJECT

public:
	digital_clock(QWidget *parent = 0);

private slots:
	void show_time();
};

#endif // DIGITAL_CLOCK_H
