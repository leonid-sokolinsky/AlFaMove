/*==============================================================================
Project: LiFe
Theme: Quest (No MPI)
Module: _Problems-NetLib-LP.h (Problems from the NETLIB LP Test Problem Set)
Prefix: PP
Author: Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
LP problems were obtained using BSF-LPP-Generator.
===============================================================================*/
#pragma once

//============================== Method Parameters ============================
#define PP_KK							7		// Maximal number of faces that include surface point
#define PP_EPS_ZERO						1E-8	// Accuracy for comparison with zero
#define PP_EPS_TINY_PPROJ_VEC	1E-10	// Tiny pseudoprojection vector

#define PP_EPS_POINT_IN_HALFSPACE		1E-10	// Precision for point to be in halfspace
#define PP_OBJECTIVE_VECTOR_LENGTH		100000	// Length of Objective Vector
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_PROBE_LENGTH					1	// length of probe shift
//-----------------------------------------------------------------------------
#define PP_MAX_B_NO_CORRECT				1E+308	// Maximum b that does not require correction
#define PP_RND_EPS_POINT_IN_POLYTOPE	0		// Not used
//=============================================================================

/*============================== cone3-0 LP problem ===========================*/
// Exact solution:              7.5              25              25
#define PP_PROBLEM_NAME	"cone3-0"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 14		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 132.5
//-----------------------------------------------------------------------------/**/