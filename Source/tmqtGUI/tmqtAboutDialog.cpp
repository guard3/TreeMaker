/*******************************************************************************
File:         tmqtAboutDialog.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for TreeMaker 'About' window class
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-24
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#include "tmVersion.h"
#include "tmqtAboutDialog.h"
#include "ui_tmqtAboutDialog.h"

tmqtAboutDialog::tmqtAboutDialog(QWidget* parent) : QDialog(parent), ui(new Ui::tmqtAboutDialog) {
	ui->setupUi(this);
#ifdef Q_OS_MACOS
	/* The checkbox must ignore the layout rect on macOS because, for some reason, it breaks the layout margins */
	ui->checkBox->setAttribute(Qt::WA_LayoutUsesWidgetRect);
#endif
	ui->checkBox->setChecked(tmqtGlobals::settings().value(tmqtKey::ShowAboutAtStartup, true).toBool());
	ui->label->setText(TM_APP_ABOUT_NAME_STR);
	setFixedSize(640, 560);
	connect(ui->dialogButtonBox, &QDialogButtonBox::clicked, this, &tmqtAboutDialog::close);
	connect(ui->checkBox, &QCheckBox::checkStateChanged, this, [](Qt::CheckState e) {
		tmqtGlobals::settings().setValue(tmqtKey::ShowAboutAtStartup, e == Qt::Checked);
	});
}

tmqtAboutDialog::~tmqtAboutDialog() {
	delete ui;
}