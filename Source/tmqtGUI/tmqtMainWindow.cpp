/*******************************************************************************
File:         tmqtMainWindow.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for TreeMaker main window class
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-21
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#include "tmqtMainWindow.h"
#include "ui_tmqtMainWindow.h"


tmqtMainWindow::tmqtMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::tmqtMainWindow) {
	/* Setup UI and set default shortcuts on actions that support them */
	ui->setupUi(this);
	/* File */
	ui->actionNew->setShortcut(QKeySequence::New);
	ui->actionOpen->setShortcut(QKeySequence::Open);
	ui->actionClose->setShortcut(QKeySequence::Close);
	ui->actionSave->setShortcut(QKeySequence::Save);
	ui->actionSaveAs->setShortcut(QKeySequence::SaveAs);
	ui->actionPrint->setShortcut(QKeySequence::Print);
	ui->actionExit->setShortcut(QKeySequence::Quit);
	/* Edit */
	ui->actionUndo->setShortcut(QKeySequence::Undo);
	ui->actionRedo->setShortcut(QKeySequence::Redo);
	ui->actionCut->setShortcut(QKeySequence::Cut);
	ui->actionCopy->setShortcut(QKeySequence::Copy);
	ui->actionPaste->setShortcut(QKeySequence::Paste);
	ui->actionSelectAll->setShortcut(QKeySequence::SelectAll);
	/* TODO: Add debug options */
	/* Help */
	ui->actionHelp->setShortcut(QKeySequence::HelpContents);
	/* Quit app when 'Exit' is clicked */
	connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::quit);
}

tmqtMainWindow::~tmqtMainWindow() {
	delete ui;
}
