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
add_executable(TreeMaker
	Source/tmqtGUI/main.cpp
)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
target_link_libraries(TreeMaker Qt::Core Qt::Gui Qt::Widgets)
