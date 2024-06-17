/*==============================================================================
Project: LiFe - New Linear Programming Solvers - New Linear Programming Solvers
Theme: Surface movement method (No MPI)
Module: _Problems-Klee-Minty-Cube.h (Problems from the LP-Klee-Minty-Cube Set)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
==============================================================================*/
#pragma once

//============================== Problem Parameters ======================
// PP_OBJECTIVE_VECTOR_LENGTH - direct dependence on dimension PD_n.
// P_EPS_ZERO - inverse dependence on PP_OBJECTIVE_VECTOR_LENGTH.
// PP_EPS_PROJECTION_ROUND - inverse dependence on PP_OBJECTIVE_VECTOR_LENGTH. 
//						This parameter affects terminate condition when 
//						calculating pseudoprojection.
//-----------------------------------------------------------------------
#define PP_MAX_PROJECTING_ITER		1E+7	// Maximum acceptable number of iterations in PF_PseudoprojectionOnFace()
#define PP_PROBE_LENGTH				1		// Length of probe shift
#define PP_START_SHIFT_LENGTH		100
//=============================================================================

/*============================== Klee-Minty5 LP problem =======================*/
// Starting point:	0 ... 0
// Exact solution:	0 ... 0	3125
#define PP_PROBLEM_NAME	"Klee-Minty5"
#define PP_KK 31		// Maximal number of faces that include surface point 2^m-1
#define PP_D 5			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 3125
//---------------------------------- Method parameters ------------------------
#define PP_EPS_ZERO					1E-9			// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	1E-7			// Precision for PF_MakeHyperplaneList()
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/10)// Precision for moving on polytope
#define PP_EPS_PROJECTION_ROUND		1E-9			// Precision of rounding pseudoprojecting vectors
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+9			// Length of Objective Vector
//-----------------------------------------------------------------------------
// Elapsed time: 0.2794484
// Number of iterations: 9
// Computed objective value: 3125.000000598362
// Maximal objective value:  3125
// Relative error = 1.91e-10
//=============================================================================

/*============================== Klee-Minty6 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	15625
#define PP_PROBLEM_NAME	"Klee-Minty6"
#define PP_KK 63		// Maximal number of faces that include surface point 2^m-1
#define PP_D 6			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 15625
//---------------------------------- Method parameters ------------------------
#define PP_EPS_ZERO					1E-9			// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	1E-7			// Precision for point to be in halfspace
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/10)// Precision for moving on polytope
#define PP_EPS_PROJECTION_ROUND		1E-6			// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+13			// Length of Objective Vector
//-----------------------------------------------------------------------------
// Elapsed time: 1.6808084
// Number of iterations: 11
// Computed objective value: 15625.00001247148
// Maximal objective value:  15625
// Relative error = 7.98e-10
//=============================================================================

/*============================== Klee-Minty7 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	78125
#define PP_PROBLEM_NAME	"Klee-Minty7"
#define PP_D 7			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 127		// Maximal number of faces that include surface point 2^m-1
#define PP_MAX_OBJ_VALUE 78125
//---------------------------------- Method parameters ------------------------
#define PP_EPS_ZERO					1E-6			// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	1E-6			// Precision for point to be in halfspace
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/10)// Precision for moving on polytope
#define PP_EPS_PROJECTION_ROUND		1E-4			// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+14			// Length of Objective Vector
//-----------------------------------------------------------------------------
// Elapsed time: 8.8617283
// Number of iterations: 13
// Computed objective value: 78125.00024711063
// Maximal objective value:  78125
// Relative error = 3.16e-09
//=============================================================================

/*============================== Klee-Minty8 LP problem =======================*
// Not solved!
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	390625
#define PP_PROBLEM_NAME	"Klee-Minty8"
#define PP_D 8			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 255	// Maximal number of faces that include surface point 2^m-1
#define PP_MAX_OBJ_VALUE 390625
//---------------------------------- Method parameters ------------------------
#define PP_EPS_ZERO					1E-9			// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	1E-6			// Precision for point to be in halfspace
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/10)// Precision for moving on polytope
#define PP_EPS_PROJECTION_ROUND		1E-1			// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+17			// Length of Objective Vector
//-----------------------------------------------------------------------------
// Elapsed time: 32.748673
// Number of iterations: 20
// Computed objective value: 385891.9469352126
// Maximal objective value:  390625
// Relative error = 0.0121
//=============================================================================

/*============================== Klee-Minty9 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	1953125
#define PP_PROBLEM_NAME	"Klee-Minty9"
#define PP_D 9			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 511		// Maximal number of faces that include surface point 2^m-1
#define PP_MAX_OBJ_VALUE 1953125
//---------------------------------- Method parameters ------------------------
#define PP_EPS_TINY_PPROJ_VEC		1E-8	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE	1E-2	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST	1E-2	// Precision for MakeHyperplaneList()
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+9	// Length of Objective Vector
//-----------------------------------------------------------------------------
// Not solved!!!
//=============================================================================

/*=============================================================================*/