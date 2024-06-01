/*==============================================================================
Project: LiFe - New Linear Programming Solvers
Theme: Surface movement method (MPI)
Module: Problem-Parameters.h (Problem Parameters)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/

/*----------------------------- Problems -------------------------------*/
/**
#include "_Problems05-1.h"
#define PP_PATH "D:/YandexDisk/_private/Programming/LP-Rnd-Problems/"

/**/
#include "_Problems20-1.h"
//#define PP_PATH "D:/YandexDisk/_private/Programming/LP-Rnd-Problems/"
#define PP_PATH "Problems/"

/**
#include "_Problems-Cone-LP.h"
#define PP_PATH "D:/YandexDisk/_private/Programming/LP-Cone-Problems/"

/**
#include "_Problems-Klee-Minty-Cube.h"
#define PP_PATH "D:/YandexDisk/_private/Programming/LP-Klee-Minty-Cube/"
/*---------------------------------------------------------------------*/

//-------------------------- Compilation Modes -----------------------
//#define PP_DEBUG
//#define PP_MATRIX_OUTPUT
//#define PP_SAVE_RESULT
//#define PP_COS_MODE

//=========================== Problem Parameters =========================
#define PP_MM					(2*PP_M+2*PP_N)	// Maximal number of inequalities
#define PP_MAX_ITER_COUNT		10000000000		// Maximal count of iterations
#define PP_DBL_MAX				1E+308			// Highest value
#define PP_START_SHIFT_LENGTH	100
//-------------------------- Input/Outpoot Parameters ---------------------------
#define PP_OUTPUT_LIMIT	30	// Number of Elements to output
#define PP_SETW 16
//------------------------- Matrix format ----------------
#define PP_INFINITY			1E+308		// Highest bound in *_hi.mtx
#define PP_MTX_PREFIX		"lp_"
#define PP_MTX_POSTFIX_A	".mtx"
#define PP_MTX_POSTFIX_B	"_b.mtx"
#define PP_MTX_POSTFIX_C	"_c.mtx"
#define PP_MTX_POSTFIX_HI	"_hi.mtx"
#define PP_MTX_POSTFIX_LO	"_lo.mtx"
#define PP_MTX_POSTFIX_SO	"_so.mtx"	// Solution point
#define PP_MTX_POSTFIX_U0	"_u0.mtx"	// Starting point
//-------------------------- Jobs  -----------------------
#define PP_JOB_GET_BEST_DIRECTION	0 
//------------- Vector Projection Onto Halfspace exit codes -------------
#define PP_EXITCODE_DEGENERATE_INEQUALITY	0
#define PP_EXITCODE_INSIDE_HALFSPACE		1
#define PP_EXITCODE_NATURAL_PROJECTING		2
#define PP_EXITCODE_PARALLEL				3
#define PP_EXITCODE_RECESSIVE				4
#define PP_EXITCODE_ON_HYPERPLANE			5