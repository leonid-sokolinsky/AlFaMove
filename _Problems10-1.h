/*==============================================================================
Project: LiFe
Theme: Surface movement method (MPI)
Module: Problems10-1.h (LP problems of dimension 10 with 1 randome inequality)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
LP problems were obtained using BSF-LPP-Generator.
Initial surface points for these problems were calculated using BSF-Apex-Quest.
==============================================================================*/
#pragma once

//=========================== Method Parameters =========================
#define PP_EPS_ZERO			1E-8		// Accuracy for comparison with zero
#define PP_EPS_P_PROJ_ON_EDGE			1E-12	// Precision for calculating pseudoprojection onto edge
//#define PP_EPS_PPROJ_ON_POLYTOPE		1E-9	// Precision for calculating pseudoprojection onto edge
#define PP_OBJECTIVE_VECTOR_LENGTH		100000	// Starting length of Objective Vector
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_MAX_B_NO_CORRECT				200		// Maximum b that does not require correction
#define PP_RND_EPS_POINT_IN_POLYTOPE	1E-6	// Precision for random inequality in PointInPolytope()

/*============================== rnd10-0 LP problem ==============================*
// Start point:	200	0...0
// Exact solution:	100  200  200  200  200  200  200  200  200  200
// Face dimension: 5.      Generating hyperplanes: {5, 6, 7, 8, 9}.         Shift length: 296.64794        F(x) = 10200
// Face dimension: 4.      Generating hyperplanes: {4, 5, 6, 7, 8, 9}.      Shift length: 54.772256        F(x) = 10500
// Face dimension: 3.      Generating hyperplanes: {3, 4, 5, 6, 7, 8, 9}.   Shift length: 62.360956        F(x) = 10733.333
// Face dimension: 2.      Generating hyperplanes: {2, 3, 4, 5, 6, 7, 8, 9}.Shift length: 74.535599        F(x) = 10900
#define PP_PROBLEM_NAME	"rnd10-0"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------

#define PP_OPTIMAL_OBJ_VALUE		10900			// Exact maximum value of objective function


//------------------------------------------------------------------/**/

/*============================== rnd10-1-1 LP problem ==============================*
// Start point:	200	0	200	200	0	200	200	0	0	200
// Face dimension: 4. Generating hyperplanes: {0, 2, 3, 5, 6, 9}. Shift length: 104.13206  F(x) = 9336.3249
// Relative error = 0.02
#define PP_PROBLEM_NAME	"rnd10-1-1"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------

#define PP_OPTIMAL_OBJ_VALUE		9551.38289		// Exact maximum value of objective function


//------------------------------------------------------------------/**/

/*============================== rnd10-1-2 LP problem ==============================*
// Start point:	0	200	200	200	0	0	200	200	0	200
// Face dimension: 4. Generating hyperplanes: {1, 2, 3, 6, 7, 9}.		Shift length: 86.170754  F(x) = 9015.3823
// Face dimension: 3. Generating hyperplanes: {1, 2, 3, 6, 7, 9, 10}.	Shift length: 27.156722  F(x) = 9063.8588
// Relative error = 0.007
#define PP_PROBLEM_NAME	"rnd10-1-2"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------

#define PP_OPTIMAL_OBJ_VALUE		9123.804558373	// Exact maximum value of objective function


//------------------------------------------------------------------/**/

/*============================== rnd10-1-3 LP problem ==============================*
// Start point:	200	200	200	200	0	200	0	200	0	200
// Face dimension: 3.      Generating hyperplanes: {0, 1, 2, 3, 5, 7, 9}.   Shift length: 24.979362        F(x) = 9893.4642
// Relative error = 0.007
#define PP_PROBLEM_NAME	"rnd10-1-3"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------

#define PP_OPTIMAL_OBJ_VALUE		9960.7893		// Exact maximum value of objective function


//------------------------------------------------------------------/**/

/*============================== rnd10-1-4 LP problem ==============================*
// Start point:	200	0	200	200	200	0	0	0	200	0
// Face dimension: 5.      Generating hyperplanes: {0, 2, 3, 4, 8}.         Shift length: 167.88899        F(x) = 9092.23
// Relative error = 0.036
#define PP_PROBLEM_NAME	"rnd10-1-4"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------

#define PP_OPTIMAL_OBJ_VALUE		9430.597672		// Exact maximum value of objective function


//------------------------------------------------------------------/**/

/*============================== rnd10-1-5 LP problem ==============================*
// u0 = 200	200	200	0	0	0	200	200	200	200
// Face dimension: 3.      Generating hyperplanes: {0, 1, 2, 6, 7, 8, 9}.   Shift length: 78.509654        F(x) = 10093.756
// Face dimension: 2.      Generating hyperplanes: {0, 1, 2, 6, 7, 8, 9, 10}.       Shift length: 30.037233        F(x) = 10138.241
// Starting point does not belong to the feasible polytope with precision PP_EPS_ZERO = 1e-08!!!
#define PP_PROBLEM_NAME	"rnd10-1-5"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------

#define PP_OPTIMAL_OBJ_VALUE		10248.35532		// Exact maximum value of objective function


//------------------------------------------------------------------/**/

/*============================== rnd10-1-6 LP problem ==============================*/
// Start point:	200	200	200	0	200	0	200	200	0	0
// Face dimension: 4.      Generating hyperplanes: {0, 1, 2, 4, 6, 7}.      Shift length: 154.54518        F(x) = 9846.4788
// Relative error = 0.02
#define PP_PROBLEM_NAME	"rnd10-1-6"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)

#define PP_OPTIMAL_OBJ_VALUE 	10022.935663


//------------------------------------------------------------------/**/