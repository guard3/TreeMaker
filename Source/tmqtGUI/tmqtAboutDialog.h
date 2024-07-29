/*******************************************************************************
File:         tmqtAboutDialog.h
Project:      TreeMaker 5.x
Purpose:      Header file for TreeMaker 'About' window class
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-24
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#ifndef TREEMAKER_TMQTABOUTDIALOG_H
#define TREEMAKER_TMQTABOUTDIALOG_H

#include "tmqtCommon.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class tmqtAboutDialog; }
QT_END_NAMESPACE

class tmqtAboutDialog : public QDialog {
	Q_OBJECT

public:
	explicit tmqtAboutDialog(QWidget* parent = nullptr);

	~tmqtAboutDialog() override;

private:
	Ui::tmqtAboutDialog *ui;
};
#endif /* TREEMAKER_TMQTABOUTDIALOG_H */