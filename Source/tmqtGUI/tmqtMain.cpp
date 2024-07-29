/*******************************************************************************
File:         tmqtMain.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for TreeMaker Qt application entry point
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-17
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#include "tmqtAboutDialog.h"
#include "tmqtMainWindow.h"
#include "tmqtSplashScreen.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[]) {
	using namespace std::chrono;
	using namespace std::chrono_literals;
	/* Initialize the QApplication */
	QApplication app(argc, argv);
	/* Show a splashscreen early on */
	tmqtSplashScreen splash;
	splash.show();
	auto before = steady_clock::now();
	/* Initialize globals */
	app.setOrganizationName("Robert J. Lang");
	app.setOrganizationDomain("langorigami.com");
	app.setApplicationName("TreeMaker");
	QSettings settings;
	tmqtGlobals::initialize(settings);
	/* Create main window */
	tmqtMainWindow window;
	/* Show optional 'About' */
	if (settings.value(tmqtKey::ShowAboutAtStartup, true).toBool()) {
		tmqtAboutDialog dialog(&window);
		splash.finish(&dialog);
		QTimer::singleShot(std::max(0ms, ceil<milliseconds>(steady_clock::now() - before)), &dialog, &tmqtAboutDialog::show);
		dialog.exec();
		window.show();
	} else {
		splash.finish(&window);
		QTimer::singleShot(std::max(0ms, ceil<milliseconds>(steady_clock::now() - before)), &window, &tmqtMainWindow::show);
	}
	return app.exec();
}
