/*==============================================================================
Project: LiFe
Theme: Surface movement method
Module: Problem-Parameters.h (Problem Parameters)
Prefix: PP
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
//-------------------------- Compilation Modes -----------------------
//#define PP_DEBUG
//#define OUTPUT
//#define PP_PATH "D:/YandexDisk/_private/Programming/BSF/BSF SMM/Problems/"
#define PP_PATH "Problems/"

//=========================== Problem Parameters =========================
// The following LP problems were obtained using BSF-LPP-Generator.
// The initial surface points for these problems were calculated using BSF-Apex-Quest.

/*============================== rnd5-0 LP problem ==============================*
// Solution:   100   200   200   200   200
// Face dimension : 2.      Generating hyperplanes : {2, 3, 4}.      Path length : 223.6068.
#define PP_PROBLEM_NAME	"rnd5-0"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO	// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2900			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	50				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-1 LP problem ==============================*
// Solution: 194.8143       199.33979       195.52149               0       191.16655
// Relative error = 0.007
// Value of the objective function cannot be refined!
#define PP_PROBLEM_NAME	"rnd5-1-1"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2941.82823		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-2 LP problem ==============================*
// Solution:		200             200             200       5.546             200
// Face dimension : 1.      Generating hyperplanes : {0, 2, 4, 9}.   Path length : 200.
// Face dimension : 1.      Generating hyperplanes : {0, 1, 2, 4}.   Path length : 5.5460114.
#define PP_PROBLEM_NAME	"rnd5-1-2"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2405.546		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-3 LP problem ==============================*
// Solution:	200               0             200        143.3234             200
// Face dimension : 1.      Generating hyperplanes : {0, 2, 4, 7}.   Path length : 143.3234.
#define PP_PROBLEM_NAME	"rnd5-1-3"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2486.6468		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-4 LP problem ==============================*
// Exact solution:		200				200             200			42.2486126				  200
// Computed solution:   200       70.627578             200			 141.25516			70.627578
// Relative error = 0.03
// Face dimension: 3.      Generating hyperplanes: {0, 2}. Path length: 173.00153.
#define PP_PROBLEM_NAME	"rnd5-1-4"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		1884.49723		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd5-1-5 LP problem ==============================*
// Solution:	200       181.71348               0             200               0
// Face dimension: 1.      Generating hyperplanes: {0, 3, 8, 10}.  Path length: 181.71348.
#define PP_PROBLEM_NAME	"rnd5-1-5"
#define PP_M 6		// Number of equations (number of rows in *.mtx)
#define PP_N 11		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		2726.8539		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-0 LP problem ==============================*
// Solution:	100  200  200  200  200  200  200  200  200  200
#define PP_PROBLEM_NAME	"rnd10-0"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		10900			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-1 LP problem ==============================*
// Solution:	0  200  200  0  200  189.3989  200  200  0  200
#define PP_PROBLEM_NAME	"rnd10-1-1"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		10146.995		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-2 LP problem ==============================*
// Relative error = 0.005
// Path length: 0.001
#define PP_PROBLEM_NAME	"rnd10-1-2"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		8842.5318		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-3 LP problem ==============================*
// Relative error = 0.004
// Path length: 0.001
#define PP_PROBLEM_NAME	"rnd10-1-3"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		9323			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-4 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd10-1-4"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		9408.9108		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd10-1-5 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd10-1-5"
#define PP_M 11		// Number of equations (number of rows in *.mtx)
#define PP_N 21		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		8913.1381		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd20-0 LP problem ==============================*
// Solution:	100  200  ...  200
#define PP_PROBLEM_NAME	"rnd20-0"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		41900			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd20-1-1 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd20-1-1"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		29804.7			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd20-1-2 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd20-1-2"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		37823.888				// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd20-1-3 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd20-1-3"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		40049.978				// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd20-1-4 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd20-1-4"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		35207.921				// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd20-1-5 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd20-1-5"
#define PP_M 21		// Number of equations (number of rows in *.mtx)
#define PP_N 41		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		33262.391				// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd24-0 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd24-0"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		59900			// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd24-1-1 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd24-1-1"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		48526.028		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd24-1-2 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd24-1-2"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		49853.284		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd24-1-3 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd24-1-3"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		48648.629		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd24-1-4 LP problem ==============================*
#define PP_PROBLEM_NAME	"rnd24-1-4"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		48879.373		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

/*============================== rnd24-1-5 LP problem ==============================*/
#define PP_PROBLEM_NAME	"rnd24-1-5"
#define PP_M 25		// Number of equations (number of rows in *.mtx)
#define PP_N 49		// Number of variables (number of cols in *.mtx)
//------------------------------------------------------------------
#define PP_EPS_ZERO					1E-8			// Accuracy for comparison with zero
#define PP_EPS_ZERO_DIR				PP_EPS_ZERO		// Accuracy for comparison with zero
#define PP_OPTIMAL_OBJ_VALUE		49582.56		// Exact maximum value of objective function
#define PP_INFINITY					1E+308			// Highest bound in *_hi.mtx
#define PP_OBJECTIVE_VECTOR_LENGTH	1				// Starting length of Objective Vector
//------------------------------------------------------------------/**/

//================================ Common Paramrters ===========================
#define PP_MM (2*(PP_M+PP_N))	// Maximal number of inequalities
//#define PP_KK 131072				// Maximal number of hyperedges that include surface point: 2^17 = 131072
//#define PP_KK 524288				// Maximal number of hyperedges that include surface point: 2^19 = 524288
//#define PP_KK 1048575				// Maximal number of hyperedges that include surface point: 2^20 = 1 048 576
#define PP_KK 16777215				// Maximal number of hyperedges that include surface point: 2^25 = 16 777 216
#define PP_MAX_NUM_SHIFTS_SAME_LENGTH	5			// Maximal number of shifts with the same length
#define PP_MAX_SHIFTS_NUMBER			1000		// Maximum number of shifts
#define PP_MAX_ITER_COUNT				10000000000 // Maximal count of iterations
#define PP_DBL_MAX						1E+308		// Highest value
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