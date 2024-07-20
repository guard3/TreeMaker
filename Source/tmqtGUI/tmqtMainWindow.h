/*******************************************************************************
File:         tmqtMainWindow.h
Project:      TreeMaker 5.x
Purpose:      Header file for TreeMaker main window class
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-21
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#ifndef TREEMAKER_TMQTMAINWINDOW_H
#define TREEMAKER_TMQTMAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class tmqtMainWindow; }
QT_END_NAMESPACE

class tmqtMainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit tmqtMainWindow(QWidget *parent = nullptr);

	~tmqtMainWindow() override;

private:
	Ui::tmqtMainWindow *ui;
};


#endif //TREEMAKER_TMQTMAINWINDOW_H
