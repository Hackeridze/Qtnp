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

	QTranslator ru;// устанавливаем русский
	ru.load(":/res/qtnp_ru");// устанавливаем русский
	qApp->installTranslator(&ru); // устанавливаем русский
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
