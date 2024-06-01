/*==============================================================================
Project: LiFe
Theme: Surface movement method (MPI)
Module: Problems05-1.h (LP problems of dimension 5 with 1 randome inequality)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
LP problems were obtained using BSF-LPP-Generator.
Initial surface points for these problems were calculated using BSF-Apex-Quest.
==============================================================================*/
#pragma once

//============================== Method Parameters ============================
#define PP_KK							31		// Maximal number of faces that include surface point:  2^5-1
#define PP_EPS_ZERO						1E-8	// Accuracy for comparison with zero
#define PP_EPS_TINY_PPROJ_VEC			1E-10	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE		1E-10	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_EPS_COS						1E-8	// Precision for cos == 1
#define PP_OBJECTIVE_VECTOR_LENGTH		100000	// Length of Objective Vector
#define PP_PROBE_LENGTH					0.003	// length of probe shift
//-----------------------------------------------------------------------------
#define PP_MAX_B_NO_CORRECT				200		// Maximum b that does not require correction
#define PP_RND_EPS_POINT_IN_POLYTOPE	1E-6	// Precision for random inequality in PointInPolytope()
//=============================================================================

/*============================== rnd3-10 LP problem =============================*
#define PP_PROBLEM_NAME	"rnd3-10"
#define PP_M 13		// Number of equations (number of rows in *.mtx)
#define PP_N 16		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		852.028917919
//-------------------------------------------------------------------------------

//------------------------------------------------------------------/**/