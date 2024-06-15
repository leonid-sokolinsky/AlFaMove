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

//============================== Problem Parameters =============================
// PP_OBJECTIVE_VECTOR_LENGTH - direct dependence on dimension PD_n.
// P_EPS_ZERO - inverse dependence on PP_OBJECTIVE_VECTOR_LENGTH.
// PP_EPS_VECTOR_ROUND - inverse dependence on PP_OBJECTIVE_VECTOR_LENGTH. 
//						This parameter affects terminate condition when 
//						calculating pseudoprojection.
//-------------------------------------------------------------------------------
#define PP_EPS_ZERO					1E-9				// Accuracy for comparison with zero
#define PP_EPS_POINT_IN_HALFSPACE	1E-5				// Precision for point to be in halfspace
#define 		(PP_EPS_ZERO/10)	// Precision for moving bounds
#define PP_EPS_MOVING_ON_POLYTOPE	(PP_EPS_ZERO/100)	// Precision for moving on polytope (affects Shift = 0)
#define PP_EPS_VECTOR_ROUND			PP_EPS_ZERO			// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+9				// Length of Objective Vector
//-------------------------------------------------------------------------------
#define PP_KK	1081311	// Maximal number of faces that include surface point ((2^20/32767)+1)*32767 (compilator limit: 2 147 483 647) 
#define PP_M	21		// Number of equations (number of rows in *.mtx)
#define PP_N	41		// Number of variables (number of cols in *.mtx)
#define PP_PROBE_LENGTH			1					// Length of probe shift
#define PP_START_SHIFT_LENGTH	100
//-------------------------------------------------------------------------------

/*============================== rnd15-0 LP problem =========================*
// Solution:	100  200  ...  200
#define PP_PROBLEM_NAME	"rnd15-0"
#define PP_MAX_OBJ_VALUE 41900
//-----------------------------------------------------------------------------

/*============================== rnd15-1-1 LP problem =========================*/
#define PP_PROBLEM_NAME	"rnd15-1-1"
#define PP_MAX_OBJ_VALUE 29920.01741109104
//-----------------------------------------------------------------------------

/*============================== rnd15-1-2 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd15-1-2"
#define PP_MAX_OBJ_VALUE 37836.93296985723
//-----------------------------------------------------------------------------

/*============================== rnd15-1-3 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd15-1-3"
#define PP_MAX_OBJ_VALUE 40150.02344129269
//-----------------------------------------------------------------------------

/*============================== rnd15-1-4 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd15-1-4"
#define PP_MAX_OBJ_VALUE 35207.92054548806
//-----------------------------------------------------------------------------

/*============================== rnd15-1-5 LP problem =========================*
#define PP_PROBLEM_NAME	"rnd15-1-5"
#define PP_MAX_OBJ_VALUE 33275.8272893071		
//-----------------------------------------------------------------------------

/*=============================================================================*/