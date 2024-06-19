/*==============================================================================
Project: LiFe - New Linear Programming Solvers
Theme: Surface movement method (No MPI)
Module: Problem-Data.h (Problem Data)
Prefix: PD
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
#include "Problem-Types.h"		// Problem Parameters 
using namespace std;
//========================== Problem variables ====================================
static int PD_m;					// Current number of inequalities
static int PD_n;					// Space dimension
static int PD_mh;					// Number of hyperplanes that include surface point
static int PD_ma;					// Number of hyperplanes used for pseudoprojection
static int PD_K;					// Number of faces of all possible dimensions
static int PD_iterNo;				// Number of iterations
static double PD_objF_initialValue; // Initial value of objective function
static double PD_objF_u;			// Current value of objective function
//========================== Problem structures ====================================
static PT_matrix_T PD_A;	// Matrix of coefficients of inequalities
static PT_column_T PD_b;	// Column of the constant terms of the system Ax <= PD_b
static PT_vector_T PD_c;	// Gradient of Objective Function
static PT_vector_T PD_e_c;	// PD_e_c = PD_c / ||PD_c||
static PT_vector_T PD_u;	// Current surface point
static PT_vector_T PD_hi;	// Higher bound
static PT_vector_T PD_lo;	// Lower bound
static PT_column_T PD_norm_a;		// Column of norms of matrix rows
static PT_vector_T PD_objVector;	// Used for pseudoprojecting
static int PD_index_includingHyperplanes[PP_MM];	// Index of hyperplanes that include surface point u
static int PD_faceCodeList[PP_KK];					// Face codes
static int PD_index_activeHyperplanes[PP_MM];		// Index of hyperplanes used for pseudoprojection

//========================== Input/Output ====================================
static string PD_problemName;