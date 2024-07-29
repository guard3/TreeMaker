/*******************************************************************************
File:         tmqtCommon.h
Project:      TreeMaker 5.x
Purpose:      Common header file for all Qt TreeMaker source code
Author:       Konstantinos Bolosis
Modified by:
Created:      2024-07-29
Copyright:    ©2024 Konstantinos Bolosis. All Rights Reserved.
*******************************************************************************/

#ifndef TREEMAKER_TMQTCOMMON_H
#define TREEMAKER_TMQTCOMMON_H

#include "tmHeader.h"
#include <QSettings>

class tmqtGlobals final {
	static inline QSettings* ms_settings{};
public:
	tmqtGlobals() = delete;

	static void initialize(QSettings& settings) noexcept { ms_settings = &settings; }
	static QSettings& settings() noexcept { return *ms_settings; }
};

struct tmqtKey {
	static inline constexpr auto ShowAboutAtStartup = "ShowAboutAtStartup";
	static inline constexpr auto Algorithm = "Algorithm";
};
#endif /* TREEMAKER_TMQTCOMMON_H */