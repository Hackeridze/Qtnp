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

#ifndef FPARSER_H
#define FPARSER_H

#include "muparser/muParser.h"
#include <QString>
#include <QObject>

using namespace mu;

class QtnpParser : public QObject
{
	Q_OBJECT
private:
	Parser p;
public:
	QtnpParser();
	void setE(QString str);
	double getR(value_type x);
signals:
	void bad_exp(QString);
};

#endif // FPARSER_H
