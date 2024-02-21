/*==============================================================================
Project: LiFe
Theme: Surface movement method (No MPI)
Module: Problem-Parameters.h (Problem Parameters)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
//-------------------------- Compilation Modes -----------------------
#define PP_DEBUG
#define OUTPUT
// No MPI
#define PP_PATH "D:/YandexDisk/_private/Programming/BSF/BSF SMM/Problems/"

//=========================== Problem Parameters =========================
// The following LP problems were obtained using BSF-LPP-Generator.
// The initial surface points for these problems were calculated using BSF-Apex-Quest.

/*============================== rnd3-0 LP problem ==============================*
// Start point: 200 0 0		
// Solution:   100   200   200
// Face dimension: 2.      Generating hyperplanes : {0}.    Shift length : 216.33308       F(x) = 980
// Face dimension: 2.      Generating hyperplanes: {3}.     Shift length: 28.284271        F(x) = 1020
// Face dimension: 1.      Generating hyperplanes: {2, 3}.  Shift length: 113.13709        F(x) = 1100
#define PP_PROBLEM_NAME	"rnd3-0"
#define PP_M 4		// Number of equations (number of rows in *.mtx)
#define PP_N 7		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		1100			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-0 LP problem ==============================*
// Start point:	200	0...0
// Exact solution:   100   200   200   200   200
// Face dimension: 4.      Generating hyperplanes: {0}.				Shift length: 293.93877        F(x) = 2360
// Face dimension: 3.      Generating hyperplanes: {0, 4}.			Shift length: 53.851648        F(x) = 2650
// Face dimension: 2.      Generating hyperplanes: {0, 3, 4}.       Shift length: 36.055513        F(x) = 2780
// Face dimension: 2.      Generating hyperplanes: {3, 4, 5}.       Shift length: 28.284271        F(x) = 2820
// Face dimension: 1.      Generating hyperplanes: {2, 3, 4, 5}.    Shift length: 113.13709        F(x) = 2900
#define PP_PROBLEM_NAME	"rnd5-0"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2900			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-1 LP problem ==============================*/
// Start point:	200	0...0
// Face dimension: 4.      Generating hyperplanes: {0}.     Shift length: 266.00701        F(x) = 2460.4815
#define PP_PROBLEM_NAME	"rnd5-1-1"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2941.82823		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-2 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 4.      Generating hyperplanes: {0}.				Shift length: 271.2932		F(x) = 2040
// Face dimension: 3.      Generating hyperplanes: {0, 4}.			Shift length: 45.825757     F(x) = 2250
// Face dimension: 2.      Generating hyperplanes: {0, 2, 4}.       Shift length: 39.330441     F(x) = 2337.9455
#define PP_PROBLEM_NAME	"rnd5-1-2"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2405.546		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-3 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 4.      Generating hyperplanes: {0}.     Shift length: 221.45619        F(x) = 2147.0654
#define PP_PROBLEM_NAME	"rnd5-1-3"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2486.6468		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-4 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 4.      Generating hyperplanes: {0}.     Shift length: 222.71057        F(x) = 1640
// Face dimension: 3.      Generating hyperplanes: {0, 2}.  Shift length: 75.021938        F(x) = 1823.7655
#define PP_PROBLEM_NAME	"rnd5-1-4"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		1884.49723		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-5 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 4.      Generating hyperplanes: {0}.     Shift length: 248.8514 F(x) = 2631.8278
#define PP_PROBLEM_NAME	"rnd5-1-5"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2726.8539		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-6 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 4.      Generating hyperplanes: {0}.     Shift length: 271.2932 F(x) = 2640
// Face dimension: 3.      Generating hyperplanes: {0, 2}.  Shift length: 12.375833        F(x) = 2696.7132
#define PP_PROBLEM_NAME	"rnd5-1-6"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2803.0833		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-0 LP problem ==============================*
// Start point:	200	0...0
// Exact solution:	100  200  200  200  200  200  200  200  200  200
// Face dimension: 5.      Generating hyperplanes: {5, 6, 7, 8, 9}.         Shift length: 296.64794        F(x) = 10200
// Face dimension: 4.      Generating hyperplanes: {4, 5, 6, 7, 8, 9}.      Shift length: 54.772256        F(x) = 10500
// Face dimension: 3.      Generating hyperplanes: {3, 4, 5, 6, 7, 8, 9}.   Shift length: 62.360956        F(x) = 10733.333
// Face dimension: 2.      Generating hyperplanes: {2, 3, 4, 5, 6, 7, 8, 9}.Shift length: 74.535599        F(x) = 10900
#define PP_PROBLEM_NAME	"rnd10-0"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		10900			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-1 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 9.      Generating hyperplanes: {0}.     Shift length: 360.39428        F(x) = 7706.3218
#define PP_PROBLEM_NAME	"rnd10-1-1"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		10146.995		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-2 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 9.      Generating hyperplanes: {0}.     Shift length: 373.17457        F(x) = 7466.6667
// Face dimension: 8.      Generating hyperplanes: {0, 2}.  Shift length: 16.714156        F(x) = 7703.6307
#define PP_PROBLEM_NAME	"rnd10-1-2"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		8842.5318		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-3 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 9.      Generating hyperplanes: {0}.     Shift length: 385.40974        F(x) = 8651.1933
#define PP_PROBLEM_NAME	"rnd10-1-3"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		9323			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-4 LP problem ==============================*
// Start point:	200	0...0
// Face dimension: 9.      Generating hyperplanes: {0}.     Shift length: 364.96575        F(x) = 7060
// Face dimension: 8.      Generating hyperplanes: {0, 2}.  Shift length: 20.800175        F(x) = 7377.5009
#define PP_PROBLEM_NAME	"rnd10-1-4"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		9408.9108		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-5 LP problem ==============================*
// u0 = 200 0 ... 0
// Face dimension: 9.      Generating hyperplanes: {0}.     Shift length: 362.21541        F(x) = 7560
// Face dimension: 7.      Generating hyperplanes: {0, 3, 7}.       Shift length: 56.568543        F(x) = 8200
// Face dimension: 6.      Generating hyperplanes: {0, 3, 6, 7}.    Shift length: 29.844884        F(x) = 8438.7591
#define PP_PROBLEM_NAME	"rnd10-1-5"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		8913.1381		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

//================================ Common Paramrters ===========================
#define PP_MM (2*(PP_M+PP_N))	// Maximal number of inequalities
#define PP_KK 131072				// Maximal number of hyperedges that include surface point: 2^17 = 131072
//#define PP_KK 524288				// Maximal number of hyperedges that include surface point: 2^19 = 524288
//#define PP_KK 1048575				// Maximal number of hyperedges that include surface point: 2^20 = 1 048 576
//#define PP_KK 16777215				// Maximal number of hyperedges that include surface point: 2^25 = 16 777 216
#define PP_PROBE_LENGTH			1		// length of probe shift
#define PP_MAX_ITER_COUNT	10000000000 // Maximal count of iterations
#define PP_DBL_MAX			1E+308		// Highest value
//-------------------------- Input/Outpoot Parameters ---------------------------
#define PP_OUTPUT_LIMIT	30	// Number of Elements to output
//#define PP_MATRIX_OUTPUT	// To output Matrix
#define PP_SETW 16
//------------------------- Matrix format ----------------
#define PP_MTX_PREFIX			"lp_"
#define PP_MTX_POSTFIX_A		".mtx"
#define PP_MTX_POSTFIX_B		"_b.mtx"
#define PP_MTX_POSTFIX_LO		"_lo.mtx"
#define PP_MTX_POSTFIX_HI		"_hi.mtx"
#define PP_MTX_POSTFIX_C		"_c.mtx"
#define PP_MTX_POSTFIX_SP		"_sp.mtx" // Surface point
//-------------------------- Jobs  -----------------------
#define PP_JOB_GET_BEST_DIRECTION	0 
//------------- Vector Projection Onto Halfspace exit codes -------------
#define PP_EXITCODE_DEGENERATE_INEQUALITY	0
#define PP_EXITCODE_INSIDE_HALFSPACE		1
#define PP_EXITCODE_NATURAL_PROJECTING		2
#define PP_EXITCODE_PARALLEL				3
#define PP_EXITCODE_RECESSIVE				4
#define PP_EXITCODE_ON_HYPERPLANE			5