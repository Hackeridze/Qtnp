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
	QApplication a(argc, argv);

	QSplashScreen *splash = new QSplashScreen;

	splash->setPixmap(QPixmap(":/res/splash.png")); 
	splash->show();

	Qt::Alignment bottomLeft = Qt::AlignBottom | Qt::AlignLeft;

	splash->showMessage(QObject::tr("Setting up the main window..."),
	                    bottomLeft, Qt::black);

	//QTranslator ru;// устанавливаем русский
	//ru.load(":/res/qtnp_ru");// устанавливаем русский
	//qApp->installTranslator(&ru); // устанавливаем русский
	Qtnp mainWindow;

	splash->showMessage(QObject::tr("Making SIGNAL->SLOT connections..."),
	                    bottomLeft, Qt::black);
	mainWindow.connections();

	splash->showMessage(QObject::tr("Making buttons size normal..."),
	                    bottomLeft, Qt::black);
	mainWindow.buttons_resize();

	splash->showMessage(QObject::tr("Loading status bar..."),
	                    bottomLeft, Qt::black);
	mainWindow.load_status_bar();

	qApp->setStyle("cleanlooks");

	mainWindow.showMaximized();
	splash->finish(&mainWindow);

	delete splash;

	return a.exec();
}
