/*******************************************************************************
File:         tmqtSplashScreen.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for TreeMaker splash screen class
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-20
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#include "tmqtSplashScreen.h"

/* Use the TreeMaker splashscreen PNG */
tmqtSplashScreen::tmqtSplashScreen() : QSplashScreen(QPixmap(":/images/SplashScreen.png"), Qt::WindowStaysOnTopHint) {}

/* Ignore mouse click events because, by default, QSplashScreen hides when clicked */
void tmqtSplashScreen::mousePressEvent(QMouseEvent*) {}