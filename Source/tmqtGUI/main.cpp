#include "tmqtMainWindow.h"
#include "tmqtSplashScreen.h"
#include <QApplication>
#include <QTimer>
#include <QMenuBar>

int main(int argc, char *argv[]) {
	using namespace std::chrono_literals;
	QApplication app(argc, argv);
	app.setOrganizationDomain("langorigami.com");
	app.setApplicationName("TreeMaker");
	/* Show a splashscreen early on */
	tmqtSplashScreen splash;
	splash.show();
	/* Show main window */
	tmqtMainWindow window;
	splash.finish(&window);
	QTimer::singleShot(1s, &window, &tmqtMainWindow::show);
	return app.exec();
}
