/*******************************************************************************
File:         tmNLCOTester.cpp
Project:      TreeMaker 5.x
Purpose:      Test application for the nonlinear constr. optimization algorithms
Author:       Robert J. Lang
Modified by:  Konstantinos Bolosis
Created:      2004-03-05
Copyright:    ©2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include "tmNLCO.h"
#include "tmNLCOTester.h"

/**********
Utility routines for reporting output
**********/

/*****
Write the value of a vector to the console
*****/
void ReportVector(std::string_view name, const std::vector<double>& v) {
	std::cout << name << " = (";
	if (auto it = v.begin(); it != v.end()) {
		std::cout << *it;
		while (++it != v.end())
			std::cout << ", " << *it;
	}
	std::cout << ")\n";
}

/*****
Write the value of a vector in which consecutive values make up ordered pairs.
*****/
void ReportPairVector(std::string_view name, const std::vector<double>& v) {
	for (std::size_t n = v.size() / 2, i = 0; i < n; ++i)
		std::cout << name << '[' << i << "] = " << v[2*i] << ", " << v[2*i+1] << ")\n";
}

/*****
Write the number of function and gradient calls for a single function.
*****/
void ReportCalls(std::string_view name, tmDifferentiableFn* f) {
#if TM_PROFILE_OPTIMIZERS 
	std::cout << name << " calls = (" << f->GetNumFuncCalls() << ", " << f->GetNumGradCalls() << ")\n";
#endif
}


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
}
  

/*****
Write the feasibility for the given lists of equality and inequality constraints
*****/
void ReportFeasibility(const std::vector<double>& x, const std::vector<tmDifferentiableFn*>& eq_list, const std::vector<tmDifferentiableFn*>& ineq_list) {
	// Record worst-case violation of equality constraint for this x
	double eq_bad = 0.0;
	for (auto f : eq_list) {
		if (double fval = std::fabs(f->Func(x)); eq_bad < fval)
			eq_bad = fval;
	}
	// Record worst-case violation of inequality constraint for this x
	double ineq_bad = 0.0;
	for (auto f : ineq_list) {
		if (double fval = f->Func(x); eq_bad < fval)
			ineq_bad = fval;
	}
	std::cout << "equality violation = " << eq_bad << ", inequality violation = " << ineq_bad << '\n';
}


/*****
Main program. Run all of our test routines.
*****/

int main() {
#ifdef tmUSE_CFSQP
	std::cout << "***************************************\n"
	             "Testing class tmNLCO_cfsqp.\n";
	             "***************************************\n\n\n";
	Test_all<tmNLCO_cfsqp>();
#endif // tmUSE_CFSQP

#ifdef tmUSE_RFSQP
	std::cout << "***************************************\n"
	             "Testing class tmNLCO_rfsqp.\n"
	             "***************************************\n\n\n";
	Test_all<tmNLCO_rfsqp>();
#endif // tmUSE_RFSQP
  
#ifdef tmUSE_ALM
	std::cout << "***************************************\n"
	             "Testing class tmNLCO_alm.\n"
	             "***************************************\n\n\n";
	Test_all<tmNLCO_alm>();
#endif // tmUSE_ALM
  
#ifdef tmUSE_WNLIB
	std::cout << "***************************************\n"
	             "Testing class tmNLCO_wnlib.\n"
				 "***************************************\n\n\n";
	Test_all<tmNLCO_wnlib>();
#endif // tmUSE_WNLIB
  return 0;
}

