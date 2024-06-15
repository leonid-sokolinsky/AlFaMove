/*==============================================================================
Project: LiFe - New Linear Programming Solvers
Theme: Surface movement method (No MPI)
Module: _Problems-Cone-LP.h (Problems from the LP-Cone-Problems Set)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
==============================================================================*/
#pragma once

//=========================== Method Parameters =========================
#define PP_KK						55					// Maximal number of edges that include surface point (compilator limit: 2 147 483 647)
#define PP_EPS_ZERO					1E-9				// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	1E-5				// Precision for PF_MakeHyperplaneList()
#define 		(PP_EPS_ZERO/10)	// Precision for moving bounds
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/100)	// Precision for moving on polytope
#define PP_EPS_VECTOR_ROUND			PP_EPS_ZERO			// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1					// Length of Objective Vector
#define PP_PROBE_LENGTH				1					// Length of probe shift
#define PP_START_SHIFT_LENGTH		100
/*============================== cone3-0 LP problem ==============================*/
// Face code:3.    Dimension: 1       Hyperplanes: {9, 10}.        Shift = 7.5     F(x) = 132.5
#define PP_PROBLEM_NAME	"cone3-0"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 14		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		132.5
//---------------------------------------------------------------------------------/**/