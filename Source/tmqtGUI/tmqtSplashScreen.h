/*******************************************************************************
File:         tmqtSplashScreen.h
Project:      TreeMaker 5.x
Purpose:      Header file for TreeMaker splash screen class
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-20
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#ifndef TREEMAKER_TMQTSPLASHSCREEN_H
#define TREEMAKER_TMQTSPLASHSCREEN_H

#include "tmqtCommon.h"
#include <QSplashScreen>

class tmqtSplashScreen final : public QSplashScreen {
	void mousePressEvent(QMouseEvent*) override;

public:
	tmqtSplashScreen();
};
#endif /* TREEMAKER_TMQTSPLASHSCREEN_H */