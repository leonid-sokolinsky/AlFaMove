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
// PP_EPS_VECTOR_ROUND - inverse dependence on PP_OBJECTIVE_VECTOR_LENGTH. 
//						This parameter affects terminate condition when 
//						calculating pseudoprojection.
//-----------------------------------------------------------------------
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
#define PP_EPS_ZERO					1E-6					// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	PP_EPS_ZERO				// Precision for point to be in halfspace
#define 		(PP_EPS_ZERO/10)		// Precision for moving bounds
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/100)		// Precision for moving on polytope
#define PP_EPS_VECTOR_ROUND			PP_EPS_ZERO			// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+8					// Length of Objective Vector
// _________________________________________________ 1 _____________________________________________________
// Face code: 1.    Dimension : 4    Hyperplanes : {5}.       Shift = 5.7622153       F(x) = 106.25
// New point: 5             2.5            1.25           0.625               0
// Including hyperplanes:  {0, 5}
// _________________________________________________ 2 _____________________________________________________
// Face code: 1.    Dimension : 4    Hyperplanes : {0}.       Shift = 2.8811076       F(x) = 132.8125
// New point: 5               5             2.5            1.25          0.3125
// Including hyperplanes: {0, 1}
// _________________________________________________ 3 _____________________________________________________
// Face code: 2.    Dimension : 4    Hyperplanes : {1}.       Shift = 31.901031       F(x) = 324.375
// New point: 0              25           23.75          11.875           5.625
// Including hyperplanes: {1, 9}
// _________________________________________________ 4 _____________________________________________________
// Face code: 3.    Dimension : 3    Hyperplanes : {1, 9}.    Shift = 1.4320549       F(x) = 330.9375
// New point: 0              25              25            12.5          5.9375
// Including hyperplanes: {1, 2, 9}
// _________________________________________________ 5 _____________________________________________________
// Face code: 6.    Dimension : 3    Hyperplanes : {2, 9}.    Shift = 157.27787       F(x) = 796.5625
// New point: 0               0             125          118.75         59.0625
// Including hyperplanes: {2, 8, 9}
// _________________________________________________ 6 _____________________________________________________
// Face code: 7.    Dimension : 2    Hyperplanes : {2, 8, 9}. Shift = 6.9877124       F(x) = 812.1875
// New point: 0               0             125             125         62.1875
// Including hyperplanes: {2, 3, 8, 9}
// _________________________________________________ 7 _____________________________________________________
// Face code: 14.   Dimension : 2    Hyperplanes : {3, 8, 9}. Shift = 740.16996       F(x) = 1843.4375
// New point: 0               0               0             625        593.4375
// Including hyperplanes: {3, 7, 8, 9}
// _________________________________________________ 8 _____________________________________________________
// Face code: 15.   Dimension : 1    Hyperplanes : {3, 7, 8, 9}.      Shift = 31.5625 F(x) = 1875
// New point: 0               0               0             625             625
// Including hyperplanes: {3, 4, 7, 8, 9}
// _________________________________________________ 9 _____________________________________________________
// Face code: 30.   Dimension : 1    Hyperplanes : {4, 7, 8, 9}.      Shift = 2576.941        F(x) = 3125
// New point: 0               0               0               0            3125
// Including hyperplanes: {4, 6, 7, 8, 9}
//=============================================================================

/*============================== Klee-Minty6 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	15625
#define PP_PROBLEM_NAME	"Klee-Minty6"
#define PP_KK 63	// Maximal number of faces that include surface point 2^m-1
#define PP_D 6			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 15625
//---------------------------------- Method parameters ------------------------
#define PP_EPS_ZERO					1E-7					// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	PP_EPS_ZERO				// Precision for point to be in halfspace
#define 		(PP_EPS_ZERO/10)		// Precision for moving bounds
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/100)		// Precision for moving on polytope
#define PP_EPS_VECTOR_ROUND			1E-6				// Precision of rounding vector r

#define PP_OBJECTIVE_VECTOR_LENGTH	1E+13					// Length of Objective Vector
//=============================================================================

/*============================== Klee-Minty7 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	78125
#define PP_PROBLEM_NAME	"Klee-Minty7"
#define PP_D 7			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 127	// Maximal number of faces that include surface point 2^m-1
#define PP_MAX_OBJ_VALUE 78125
//---------------------------------- Method parameters ------------------------
#define PP_EPS_ZERO					1E-6					// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	PP_EPS_ZERO				// Precision for point to be in halfspace
#define 		(PP_EPS_ZERO/10)		// Precision for moving bounds
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/100)		// Precision for moving on polytope
#define PP_EPS_VECTOR_ROUND			1E-4				// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+14					// Length of Objective Vector
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
#define PP_EPS_ZERO					1E-2					// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	PP_EPS_ZERO				// Precision for point to be in halfspace
#define 		(PP_EPS_ZERO/10)		// Precision for moving bounds
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/100)		// Precision for moving on polytope
#define PP_EPS_VECTOR_ROUND			9.999E-1				// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+22					// Length of Objective Vector
//=============================================================================

/*============================== Klee-Minty9 LP problem =======================*
// Not solved!
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
//=============================================================================

/*=============================================================================*/