cmake_minimum_required(VERSION 3.28)

project(tmArrayTester)
project(tmDpptrTester)
project(tmNewtonRaphsonTester)
project(TreeMaker)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
include_directories(
	Source
	Source/tmModel
	Source/tmModel/tmNLCO
	Source/tmModel/tmOptimizers
	Source/tmModel/tmPtrClasses
	Source/tmModel/tmSolvers
	Source/tmModel/tmTreeClasses
)

add_executable(tmArrayTester
	Source/tmHeader.cpp
	Source/test/tmArrayTester.cpp
)
add_executable(tmDpptrTester
	Source/tmHeader.cpp
	Source/test/tmDpptrTester.cpp
	Source/tmModel/tmPtrClasses/tmDpptrTarget.cpp
)
add_executable(tmNewtonRaphsonTester
	Source/tmHeader.cpp
	Source/tmModel/tmPtrClasses/tmDpptrTarget.cpp
	Source/test/tmNewtonRaphsonTester.cpp
)


find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_add_executable(TreeMaker
	Source/tmqtGUI/main.cpp
	Source/tmqtGUI/tmqtSplashScreen.h
	Source/tmqtGUI/tmqtSplashScreen.cpp
	Source/tmqtGUI/tmqtMainWindow.cpp
	Source/tmqtGUI/tmqtMainWindow.h
	Source/tmqtGUI/tmqtMainWindow.ui
	Source/tmqtGUI/tmqtAboutDialog.cpp
	Source/tmqtGUI/tmqtAboutDialog.h
	Source/tmqtGUI/tmqtAboutDialog.ui
)
target_link_libraries(TreeMaker PRIVATE Qt::Widgets)
target_compile_definitions(TreeMaker PRIVATE $<$<CONFIG:Debug>:TMDEBUG>)
qt_add_resources(TreeMaker imageresources
	BASE Source
	FILES Source/images/SplashScreen.png Source/about/about.htm
)
set_target_properties(TreeMaker PROPERTIES WIN32_EXECUTABLE ON MACOSX_BUNDLE ON)
