/*******************************************************************************
File:         tmModelTester.cpp
Project:      TreeMaker 5.x
Purpose:      Implementation file for testing the TreeMaker model (no GUI)
Author:       Robert J. Lang
Modified by:  Konstantinos Bolosis
Created:      2004-05-29
Copyright:    ©2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

/*
This file tests all of the tmTree classes in a console-based format. It's
intended to detect compilation errors and to profile the optimizers when
working with real tree structures.
*/

// standard libraries
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

// TreeMaker model classes
#include "tmModel.h"
#include "tmNLCO.h"


// The path to the test files
static fs::path testdir;

/*****
Write the number of function and gradient calls for a single function.
*****/
void ReportCalls(std::string_view name, tmDifferentiableFn* f) {
#if TM_PROFILE_OPTIMIZERS
	std::cout << name << " calls = (" << f->GetNumFuncCalls() << ", " << f->GetNumGradCalls() << ")\n";
#endif
};


/*****
Write the total number of function and gradient calls for a list of functions.
*****/
void ReportCalls(std::string_view name, const std::vector<tmDifferentiableFn*>& flist) {
#if TM_PROFILE_OPTIMIZERS
	std::size_t numFunc = 0, numGrad = 0;
	for (auto f : flist) {
		numFunc += f->GetNumFuncCalls();
		numGrad += f->GetNumGradCalls();
	}
	std::cout << name << " calls = (" << numFunc << ", " << numGrad << ")\n";
#endif
};


/*****
Read the tree in from a file. The previous tree will be overwritten. Note that
the path to the directory of test files is hard-coded; users should change the
value of testdir to reflect their own file organization.
*****/
void DoReadFile(tmTree* theTree, std::string_view filename) {
	auto fullname = testdir / filename;
	std::cout << "Reading in file " << fullname << '\n';
	std::ifstream fin(fullname);
	if (!fin.good()) {
		std::cout << "Unable to find file " << fullname << '\n';
		std::exit(EXIT_FAILURE);
	}
	try {
		theTree->GetSelf(fin);
	} catch(...) {
		std::cout << "Unexpected exception reading file " << fullname << '\n';
		std::exit(EXIT_FAILURE);
	}
}


/*****
Read in a file and perform a scale optimization on it.
*****/
template <class NLCO>
void DoScaleOptimization(const std::string& filename) {
	using namespace std::chrono;
	
	tmTree* theTree = new tmTree();
	DoReadFile(theTree, filename);
	std::cout << "Optimizing scale of " << filename << "...\n";
	NLCO* theNLCO = new NLCO();
	tmScaleOptimizer* theOptimizer = new tmScaleOptimizer(theTree, theNLCO);
	theOptimizer->Initialize();
	auto startTime = steady_clock::now();
	try {
		theOptimizer->Optimize();
	} catch (const tmNLCO::EX_BAD_CONVERGENCE& ex) {
		std::cout << "Scale optimization failed with result code " << ex.GetReason() << '\n';
	} catch (const tmScaleOptimizer::EX_BAD_SCALE&) {
		std::cout << "Scale optimization failed with scale too small.\n";
	}
	auto stopTime = steady_clock::now();
	ReportCalls(filename + " objective", theOptimizer->GetNLCO()->GetObjective());
	ReportCalls(filename + " constraint", theOptimizer->GetNLCO()->GetConstraints());
	delete theOptimizer;
	delete theNLCO;
	std::cout
		<< "New scale is " << theTree->GetScale() << '\n'
		<< "Feasibility after optimization is " << theTree->IsFeasible() << '\n'
		<< "Elapsed time = " << floor<milliseconds>(stopTime - startTime).count() << "ms\n\n";
	delete theTree;
}


/*****
Read in a file and perform an edge optimization on it.
*****/
template <class NLCO>
void DoEdgeOptimization(const std::string& filename) {
	using namespace std::chrono;
	
	tmTree* theTree = new tmTree();
	DoReadFile(theTree, filename);
	std::cout << "Maximizing edge strain of " << filename << "...\n";
	NLCO* theNLCO = new NLCO();
	tmEdgeOptimizer* theOptimizer = new tmEdgeOptimizer(theTree, theNLCO);
	tmDpptrArray<tmNode> movingNodes = theTree->GetOwnedNodes();
	tmDpptrArray<tmEdge> stretchyEdges = theTree->GetOwnedEdges();
	theOptimizer->Initialize(movingNodes, stretchyEdges);
	auto startTime = steady_clock::now();
	try {
		theOptimizer->Optimize();
	} catch (const tmNLCO::EX_BAD_CONVERGENCE& ex) {
		std::cout << "Edge optimization failed with result code " << ex.GetReason() << '\n';
	}
	auto stopTime = steady_clock::now();
	ReportCalls(filename + " objective", theOptimizer->GetNLCO()->GetObjective());
	ReportCalls(filename + " constraint", theOptimizer->GetNLCO()->GetConstraints());
	delete theOptimizer;
	delete theNLCO;
	std::cout
		<< "Optimized over " << movingNodes.size() << " nodes and " << stretchyEdges.size() << " edges.\n"
		<< "Edge strain is " << stretchyEdges.front()->GetStrain() << '\n'
		<< "Feasibility after optimization is " << theTree->IsFeasible() << '\n'
		<< "Elapsed time = " << floor<milliseconds>(stopTime - startTime).count() << "ms\n\n";
	delete theTree;
}


/*****
Read in a file and perform a strain optimization on it.
*****/
template <class NLCO>
void DoStrainOptimization(const std::string& filename) {
	using namespace std::chrono;
	
	tmTree* theTree = new tmTree();
	DoReadFile(theTree, filename);
	std::cout << "Minimizing strain of " << filename << "...\n";
	NLCO* theNLCO = new NLCO();
	tmStrainOptimizer* theOptimizer = new tmStrainOptimizer(theTree, theNLCO);
	tmDpptrArray<tmNode> movingNodes = theTree->GetOwnedNodes();
	tmDpptrArray<tmEdge> stretchyEdges = theTree->GetOwnedEdges();
	theOptimizer->Initialize(movingNodes, stretchyEdges);
	auto startTime = steady_clock::now();
	try {
		theOptimizer->Optimize();
	} catch (const tmNLCO::EX_BAD_CONVERGENCE& ex) {
		std::cout << "Strain optimization failed with result code " << ex.GetReason() << '\n';
	}
	auto stopTime = steady_clock::now();
	ReportCalls(filename + " objective", theOptimizer->GetNLCO()->GetObjective());
	ReportCalls(filename + " constraint", theOptimizer->GetNLCO()->GetConstraints());
	delete theOptimizer;
	delete theNLCO;
	std::cout << "Optimized over " << movingNodes.size() << " nodes and " << stretchyEdges.size() << " edges.\n";
	// Compute and report the RMS edge strain, weighting each edge's strain by
	// its stiffness coefficient. (This is the objective function in the
	// minimization.)
	double ss = std::reduce(stretchyEdges.begin(), stretchyEdges.end(), 0.0, [](double value, const tmEdge* edge) {
		return value + edge->GetStiffness() * std::pow(edge->GetStrain(), 2.0);
	}) / stretchyEdges.size();
	std::cout
		<< "Stiffness-weighted RMS strain is " << 100 * std::sqrt(ss) << "%\n"
		<< "Feasibility after optimization is " << theTree->IsFeasible() << '\n'
		<< "Elapsed time = " << floor<milliseconds>(stopTime - startTime).count() << "ms\n";
	delete theTree;
}


/*****
Peform optimizations on several files using the templated optimization engine.
*****/
template <class NLCO>
void DoSeveralOptimizations() {
	// SCALE OPTIMIZATION

	// Read in a test structure from a file and do an optimization.
	// tmModelTest_1.tmd5 is a simple 3-star, which should optimize quickly.
	DoScaleOptimization<NLCO>("tmModelTester_1.tmd5");

	// tmModelText_2.tmd5 is a much more complex structure, a fully
	// unoptimized centipede, but no constraints on it.
	DoScaleOptimization<NLCO>("tmModelTester_2.tmd5");

	// tmModelTest_3.tmd5 is the same centipede, but this time with symmetry
	// constraints and an infeasible starting configuration.
	DoScaleOptimization<NLCO>("tmModelTester_3.tmd5");

	// EDGE OPTIMIZATION

	// tmModelTest_4.tmd5 is an optimized centipede, but now some of the nodes
	// are unpinned, so an edge optimization can be performed.
	DoEdgeOptimization<NLCO>("tmModelTester_4.tmd5");

	// STRAIN OPTIMIZATION

	// tmModelTest_5.tmd5 is a scorpion design with many path active constraints,
	// edge strain constraints, and an infeasible initial configuration.
	DoStrainOptimization<NLCO>("tmModelTester_5.tmd5");
}


/*****
Main Program
*****/
int main(int argc, const char** argv) {
	std::cout << "**************************************************\n"
	             "TreeMaker Model Test Program\n"
	             "**************************************************\n\n";

	if (argc != 2) {
		std::cout << "Please specify the path of test files\n";
		return 0;
	}
	/* Save the input path */
	testdir = argv[1];
  
	std::cout.setf(std::ios_base::fixed);
	std::cout.precision(6);
	std::cout << std::boolalpha;

	// Initialize our dynamic type system
	tmPart::InitTypes();
  
	// Do the optimization with all four engines
  
#ifdef tmUSE_ALM
	std::cout << "Using ALM optimizer\n";
	DoSeveralOptimizations<tmNLCO_alm>();
#endif // tmUSE_ALM

#ifdef tmUSE_WNLIB
	std::cout << "Using WNLIB optimizer\n";
	DoSeveralOptimizations<tmNLCO_wnlib>();
#endif // tmUSE_WNLIB

#ifdef tmUSE_CFSQP
	std::cout << "Using CFSQP optimizer\n"
	DoSeveralOptimizations<tmNLCO_cfsqp>();
#endif // tmUSE_CFSQP

#ifdef tmUSE_RFSQP
	std::cout << "Using RFSQP optimizer\n"
	DoSeveralOptimizations<tmNLCO_rfsqp>();
#endif // tmUSE_RFSQP
}
