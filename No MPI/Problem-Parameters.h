/*==============================================================================
Project: LiFe
Theme: Surface movement method (No MPI)
Module: Problem-Parameters.h (Problem Parameters)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/

#include "../_Problems05-1.h"

//-------------------------- Compilation Modes -----------------------
//#define PP_DEBUG
#define PP_MATRIX_OUTPUT	// To output Matrix
//#define PP_SAVE_RESULT
// No MPI
#define PP_PATH "D:/YandexDisk/_private/Programming/LP-Rnd-Problems/"

//=========================== Problem Parameters =========================
#define PP_MM (2*(PP_M+PP_N))	// Maximal number of inequalities
#define PP_KK 31				// Maximal number of faces that include surface point: 2^17 = 131072
//#define PP_KK 131072				// Maximal number of faces that include surface point: 2^17 = 131072
//#define PP_KK 524288				// Maximal number of faces that include surface point: 2^19 = 524288
//#define PP_KK 1048575				// Maximal number of faces that include surface point: 2^20 = 1 048 576
//#define PP_KK 16777215				// Maximal number of faces that include surface point: 2^25 = 16 777 216
#define PP_MAX_ITER_COUNT	10000000000 // Maximal count of iterations
#define PP_DBL_MAX			1E+308		// Highest value
//-------------------------- Input/Outpoot Parameters ---------------------------
#define PP_OUTPUT_LIMIT	30	// Number of Elements to output
#define PP_SETW 16
//------------------------- Matrix format ----------------
#define PP_INFINITY				1E+308		// Highest bound in *_hi.mtx
#define PP_MTX_PREFIX			"lp_"
#define PP_MTX_POSTFIX_A		".mtx"
#define PP_MTX_POSTFIX_B		"_b.mtx"
#define PP_MTX_POSTFIX_C		"_c.mtx"
#define PP_MTX_POSTFIX_HI		"_hi.mtx"
#define PP_MTX_POSTFIX_LO		"_lo.mtx"
#define PP_MTX_POSTFIX_SO		"_so.mtx"	// Solution point
#define PP_MTX_POSTFIX_U0		"_u0.mtx"	// Start point
//-------------------------- Jobs  -----------------------
#define PP_JOB_GET_BEST_DIRECTION	0 
//------------- Vector Projection Onto Halfspace exit codes -------------
#define PP_EXITCODE_DEGENERATE_INEQUALITY	0
#define PP_EXITCODE_INSIDE_HALFSPACE		1
#define PP_EXITCODE_NATURAL_PROJECTING		2
#define PP_EXITCODE_PARALLEL				3
#define PP_EXITCODE_RECESSIVE				4
#define PP_EXITCODE_ON_HYPERPLANE			5