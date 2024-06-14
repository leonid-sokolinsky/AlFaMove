/*==============================================================================
Project: LiFe - New Linear Programming Solvers
Theme: Surface movement method (MPI)
Module: Problems20-1.h (LP problems of dimension 20 with 1 randome inequality)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This include file is part of Problem-Parameters.h
LP problems were obtained using BSF-LPP-Generator.
Initial surface points for these problems were calculated using BSF-Apex-Quest.
==============================================================================*/
#pragma once

//============================== Method Parameters ============================
#define PP_KK							16777215// Maximal number of faces that include surface point:  2^24-1
#define PP_EPS_ZERO						1E-8	// Accuracy for comparison with zero
#define PP_EPS_TINY_PPROJ_VEC			1E-10	// Tiny pseudoprojection vector
#define PP_EPS_POINT_IN_HALFSPACE		1E-10	// Precision for point to be in halfspace
#define PP_EPS_MAKE_H_PLANE_LIST		1E-5	// Precision for MakeHyperplaneList()
#define PP_EPS_COS						1E-8	// Precision for cos == 1
#define PP_OBJECTIVE_VECTOR_LENGTH		100000	// Length of Objective Vector
//#define PP_PROBE_LENGTH					0.003	// length of probe shift
#define PP_PROBE_LENGTH					1	// length of probe shift
//-----------------------------------------------------------------------------
#define PP_MAX_B_NO_CORRECT				200		// Maximum b that does not require correction
#define PP_RND_EPS_POINT_IN_POLYTOPE	1E-5	// Precision for random inequality in PointInPolytope()
//=============================================================================

/*============================== rnd18-0 LP problem =========================*/
#define PP_PROBLEM_NAME	"rnd18-0"
#define PP_M 19		// Number of equations (number of rows in *.mtx)
#define PP_N 37		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 34100
//-----------------------------------------------------------------------------

/*============================== rnd20-0 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd20-0"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 41900
//-----------------------------------------------------------------------------

/*============================== rnd20-1-1 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd20-1-1"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 29920.01741105688
//-----------------------------------------------------------------------------

/*============================== rnd22-0 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd22-0"
#define PP_M 23		// Number of equations (number of rows in *.mtx)
#define PP_N 45		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 50500
//-----------------------------------------------------------------------------

/*============================== rnd22-1-1 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd22-1-1"
#define PP_M 23		// Number of equations (number of rows in *.mtx)
#define PP_N 45		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		39830.26332973469
//-----------------------------------------------------------------------------

/*============================== rnd24-0 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd24-0"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 59900
//-----------------------------------------------------------------------------

/*============================== rnd24-1-1 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd24-1-1"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		48526.02792754769
//-----------------------------------------------------------------------------

/*============================== rnd24-1-2 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd24-1-2"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		46727.43777427761
//-----------------------------------------------------------------------------

/*============================== rnd24-1-3 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd24-1-3"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		43812.13335080786
//-----------------------------------------------------------------------------

/*============================== rnd24-1-4 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd24-1-4"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		42915.78947349642
//-----------------------------------------------------------------------------

/*============================== rnd24-1-5 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd24-1-5"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
#define PP_MAX_OBJ_VALUE 		49582.56001770565
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------/**/