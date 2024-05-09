/*==============================================================================
Project: LiFe - New Linear Programming Solvers - New Linear Programming Solvers
Theme: Surface movement method (No MPI)
Module: _Problems-Klee-Minty-Cube.h (Problems from the LP-Klee-Minty-Cube Set)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
==============================================================================*/
#pragma once

//============================== Method Parameters ============================
#define PP_EPS_ZERO						1E-8	// Accuracy for comparison with zero
#define PP_EPS_PPROJ_ON_FACE_RESIDUAL	1E-8	// Residual precision for calculating pseudoprojection onto face
#define PP_EPS_PPROJ_ON_POLYTOPE		1E-8	// Precision for calculating pseudoprojection onto polytope
#define PP_PROBE_LENGTH					1		// Length of probe shift
//-----------------------------------------------------------------------------
#define PP_MAX_B_NO_CORRECT				1E+308	// Maximum b that does not require correction
#define PP_RND_EPS_POINT_IN_POLYTOPE	0		// Not used
//=============================================================================

/*============================== Klee-Minty5 LP problem =======================*/
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	3125
#define PP_PROBLEM_NAME	"Klee-Minty5"
#define PP_D 5			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 31		// Maximal number of faces that include surface point 2^m-1
#define PP_OPTIMAL_OBJ_VALUE 3125
//---------------------------------- Method parameters ------------------------
#define PP_EPS_PPROJ_ON_FACE_TINY_VEC	1E-10	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE		1E-5	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_OBJECTIVE_VECTOR_LENGTH		1E+5	// Length of Objective Vector
//=============================================================================

/*============================== Klee-Minty6 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	15625
#define PP_PROBLEM_NAME	"Klee-Minty6"
#define PP_D 6			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 63	// Maximal number of faces that include surface point 2^m-1
#define PP_OPTIMAL_OBJ_VALUE 15625
//---------------------------------- Method parameters ------------------------
#define PP_EPS_PPROJ_ON_FACE_TINY_VEC	1E-10	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE		1E-5	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_OBJECTIVE_VECTOR_LENGTH		1E+6	// Length of Objective Vector
//=============================================================================

/*============================== Klee-Minty7 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	78125
#define PP_PROBLEM_NAME	"Klee-Minty7"
#define PP_D 7			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 127	// Maximal number of faces that include surface point 2^m-1
#define PP_OPTIMAL_OBJ_VALUE 78125
//---------------------------------- Method parameters ------------------------
#define PP_EPS_PPROJ_ON_FACE_TINY_VEC	1E-10	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE		1E-5	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_OBJECTIVE_VECTOR_LENGTH		1E+7	// Length of Objective Vector
//=============================================================================

/*============================== Klee-Minty8 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	390625
#define PP_PROBLEM_NAME	"Klee-Minty8"
#define PP_D 8			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 255	// Maximal number of faces that include surface point 2^m-1
#define PP_OPTIMAL_OBJ_VALUE 390625
//---------------------------------- Method parameters ------------------------
#define PP_EPS_PPROJ_ON_FACE_TINY_VEC	1E-10	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE		1E-5	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_OBJECTIVE_VECTOR_LENGTH		1E+7	// Length of Objective Vector
//=============================================================================

/*============================== Klee-Minty9 LP problem =======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	1953125
#define PP_PROBLEM_NAME	"Klee-Minty9"
#define PP_D 9			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 511	// Maximal number of faces that include surface point 2^m-1
#define PP_OPTIMAL_OBJ_VALUE 1953125
//---------------------------------- Method parameters ------------------------
#define PP_EPS_PPROJ_ON_FACE_TINY_VEC	1E-6	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE		1E-1	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST		1E-1	// Precision for MakeHyperplaneList()
#define PP_OBJECTIVE_VECTOR_LENGTH		1E+11	// Length of Objective Vector
//=============================================================================

/*============================== Klee-Minty10 LP problem ======================*
// Start point:	   0 ... 0
// Exact solution: 0 ... 0	9765625
#define PP_PROBLEM_NAME	"Klee-Minty10"
#define PP_D 10			// Space dimension
#define PP_M PP_D		// Number of equations (number of rows in *.mtx)
#define PP_N (2*PP_D)	// Number of variables (number of cols in *.mtx)
#define PP_KK 1023	// Maximal number of faces that include surface point:  2^m-1
#define PP_OPTIMAL_OBJ_VALUE 9765625
/*=============================================================================*/