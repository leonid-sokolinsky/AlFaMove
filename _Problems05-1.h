/*==============================================================================
Project: LiFe - New Linear Programming Solvers
Theme: Surface movement method (MPI)
Module: Problems05-1.h (LP problems of dimension 5 with 1 randome inequality)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
LP problems were obtained using BSF-LPP-Generator.
Initial surface points for these problems were calculated using BSF-Apex-Quest.
==============================================================================*/
#pragma once

//=========================== problem Parameters ========================
// PP_OBJECTIVE_VECTOR_LENGTH - direct dependence on dimension PD_n.
// P_EPS_ZERO - inverse dependence on PP_OBJECTIVE_VECTOR_LENGTH.
// PP_EPS_VECTOR_ROUND - inverse dependence on PP_OBJECTIVE_VECTOR_LENGTH. 
//						This parameter affects terminate condition when 
//						calculating pseudoprojection.
//-----------------------------------------------------------------------
#define PP_KK						31					// Maximal number of faces that include surface point (compilator limit: 2 147 483 647)
#define PP_EPS_ZERO					1E-9				// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	PP_EPS_ZERO			// Precision for point to be in halfspace
#define PP_EPS_MOVING_BOUNDS		(PP_EPS_ZERO/10)	// Precision for mooving bounds
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/100)	// Precision for mooving on polytope (affects Shift = 0)
#define PP_EPS_VECTOR_ROUND			1E-7				// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+9				// Length of Objective Vector
#define PP_PROBE_LENGTH				1					// Length of probe shift
#define PP_START_SHIFT_LENGTH		100
//-------------------------------------------------------------------------------

/*============================== rnd3-10 LP problem =============================*
#define PP_PROBLEM_NAME	"rnd3-10"
#define PP_M 13		// Number of equations (number of rows in *.mtx)
#define PP_N 16		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		852.0289179009677
//-------------------------------------------------------------------------------

/*============================== rnd5-100 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd5-100"
#define PP_M 105		// Number of equations (number of rows in *.mtx)
#define PP_N 110		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE	1848.437080587865
//-------------------------------------------------------------------------------

/*============================== rnd5-0 LP problem ==============================*
// Starting point:	200		0	0	0	0
// Exact solution:	100   200   200   200   200
// Dimension: 4.      Hyperplanes: {0}.			Shift = 97979.59        F(x) = 2360
// Dimension: 3.      Hyperplanes: {0, 4}.		Shift = 17950.549       F(x) = 2650
// Dimension: 2.      Hyperplanes: {0, 3, 4}.	Shift = 12018.504       F(x) = 2780
// Dimension: 2.      Hyperplanes: {3, 4, 5}.	Shift = 9428.0902       F(x) = 2820
// Dimension: 1.      Hyperplanes: {2, 3, 4, 5}.Shift = 37712.362       F(x) = 2900
#define PP_PROBLEM_NAME	"rnd5-0"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		2900
//-------------------------------------------------------------------------------

/*============================== rnd5-1-1 LP problem ==============================*
// Start point:	200               0               0             200             200
// Dimension: 2.      Hyperplanes: {0, 3, 4}.      Shift = 26721.7		F(x) = 2579.2546
// Dimension: 1.      Hyperplanes: {0, 3, 4, 5}.   Shift = 54967.646	F(x) = 2584.3495
#define PP_PROBLEM_NAME	"rnd5-1-1"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 2584.349489709188
//------------------------------------------------------------------/**/

/*============================== rnd5-1-2 LP problem ==============================*/
// Start point:	0       199.99694       183.63843       188.16601       191.28208
// Dimension: 3.      Hyperplanes: {5, 6}.		Shift = 1.0520607       F(x) = 2647.8187
// Dimension: 2.      Hyperplanes: {1, 5, 6}.	Shift = 3497.6578       F(x) = 2652.9365
// Dimension: 1.      Hyperplanes: {1, 4, 5, 6}.Shift = 12053.422       F(x) = 2657.5256
#define PP_PROBLEM_NAME	"rnd5-1-2"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 2657.525612539946
//------------------------------------------------------------------/**/

/*============================== rnd5-1-3 LP problem ==============================*
// Start point:	200           200           200             0             0
// Dimension: 2.      Hyperplanes: {0, 1, 2}.      Shift = 21948.028       F(x) = 2408.2173
// Dimension: 1.      Hyperplanes: {0, 1, 2, 5}.   Shift = 8096.5775       F(x) = 2424.9192
#define PP_PROBLEM_NAME	"rnd5-1-3"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 2424.919153811913
//------------------------------------------------------------------/**/

/*============================== rnd5-1-4 LP problem ==============================*
// Start point:	200             0             0           200           200
// Dimension: 2.      Hyperplanes: {0, 3, 4}.      Shift = 22190.147       F(x) = 2274.477
// Dimension: 1.      Hyperplanes: {0, 3, 4, 5}.   Shift = 6409.9716       F(x) = 2300.1128
#define PP_PROBLEM_NAME	"rnd5-1-4"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 2300.112758698174
//------------------------------------------------------------------/**/

/*============================== rnd5-1-5 LP problem ==============================*
// Start point:	0           200           200             0             0
// Dimension: 3.      Hyperplanes: {1, 2}.			Shift = 65129.188       F(x) = 2531.0733
// Dimension: 2.      Hyperplanes: {1, 2, 5}.		Shift = 21689.588       F(x) = 2618.1681
// Dimension: 1.      Hyperplanes: {1, 2, 5, 10}.	Shift = 27943.645       F(x) = 2626.4732
#define PP_PROBLEM_NAME	"rnd5-1-5"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 2626.473236207306
//------------------------------------------------------------------/**/

/*============================== rnd5-1-6 LP problem ==============================*
// Start point:	200           200           200             0             0
// Dimension: 2.      Hyperplanes: {0, 1, 2}.      Shift = 31072.332       F(x) = 2608.4395
// Dimension: 1.      Hyperplanes: {0, 1, 2, 5}.   Shift = 54925.396       F(x) = 2675.352
#define PP_PROBLEM_NAME	"rnd5-1-6"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 2675.351994186643
//------------------------------------------------------------------/**/