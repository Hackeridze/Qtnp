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

#include <QtGui/QApplication>
#include <QtGui/QPixmap>
#include "qtnp.h"

int main(int argc, char *argv[]) 
{
	QApplication a(argc, argv); // прога

	QSplashScreen *splash = new QSplashScreen; // сплэшскрин

	splash->setPixmap(QPixmap(":/res/splash.png")); // грузим из ресов
	splash->show();// показываем

	Qt::Alignment bottomLeft = Qt::AlignBottom | Qt::AlignLeft;

	splash->showMessage(QObject::tr("Setting up the main window..."), // пишем сообщения
	                    bottomLeft, Qt::black);

	//QTranslator ru;// устанавливаем русский
	//ru.load(":/res/qtnp_ru");// устанавливаем русский
	//qApp->installTranslator(&ru); // устанавливаем русский
	Qtnp mainWindow;

	splash->showMessage(QObject::tr("Making SIGNAL->SLOT connections..."), // пишем сообщения
	                    bottomLeft, Qt::black);
	mainWindow.connections();

	splash->showMessage(QObject::tr("Making buttons size normal..."), // пишем сообщения
	                    bottomLeft, Qt::black);
	mainWindow.buttons_resize();

	splash->showMessage(QObject::tr("Loading status bar..."), // пишем сообщения...
	                    bottomLeft, Qt::black);
	mainWindow.load_status_bar();

	qApp->setStyle("cleanlooks");

	mainWindow.showMaximized();
	splash->finish(&mainWindow);

	delete splash;

	return a.exec();
}
