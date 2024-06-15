/*==============================================================================
Project: LiFe - New Linear Programming Solvers
Theme: Surface movement method (MPI)
Module: Problems10-1.h (LP problems of dimension 10 with 1 randome inequality)
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
#define PP_EPS_VECTOR_ROUND			1E-8				// Precision of rounding vector r
#define PP_OBJECTIVE_VECTOR_LENGTH	1E+9				// Length of Objective Vector
//-------------------------------------------------------------------------------
#define PP_KK	1023	// Maximal number of faces that include surface point (compilator limit: 2 147 483 647)
#define PP_M	11		// Number of equations (number of rows in *.mtx)
#define PP_N	21		// Number of variables (number of cols in *.mtx)
#define PP_PROBE_LENGTH			1					// Length of probe shift
#define PP_START_SHIFT_LENGTH	100
//-------------------------------------------------------------------------------

/*============================== rnd10-0 LP problem ==============================*
// Start point:	200	0...0
// Exact solution:	100  200  200  200  200  200  200  200  200  200
// _________________________________________________ 1 _____________________________________________________
//Face code:31.   Dimension: 5    Hyperplanes: {5, 6, 7, 8, 9}.   Shift = 296.64794       F(x) = 10200
//New surface point:                    40              80             120             160             200             200             200             200             200             200
//Including hyperplanes:  {4, 5, 6, 7, 8, 9}
//_________________________________________________ 2 _____________________________________________________
//Face code:63.   Dimension: 4    Hyperplanes: {5, 6, 7, 8, 9, 16}.       Shift = 54.772256       F(x) = 10500
//New surface point:                    50             100             150             200             200             200             200             200             200             200
//Including hyperplanes:  {3, 4, 5, 6, 7, 8, 9}
//_________________________________________________ 3 _____________________________________________________
//Face code:127.  Dimension: 3    Hyperplanes: {5, 6, 7, 8, 9, 16, 17}.   Shift = 62.360956       F(x) = 10733.333
//New surface point:             66.666667       133.33333             200             200             200             200             200             200             200             200
//Including hyperplanes:  {2, 3, 4, 5, 6, 7, 8, 9}
//_________________________________________________ 4 _____________________________________________________
//Face code:255.  Dimension: 2    Hyperplanes: {5, 6, 7, 8, 9, 16, 17, 18}.       Shift = 74.535599       F(x) = 10900
//New surface point:                   100             200             200             200             200             200             200             200             200             200
//Including hyperplanes:  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
#define PP_PROBLEM_NAME	"rnd10-0"
#define PP_MAX_OBJ_VALUE		10900			
//-------------------------------------------------------------------------------

/*============================== rnd10-1-1 LP problem ==============================*
// Start point:	200	0	200	200	0	200	200	0	0	200
// _________________________________________________ 1 _____________________________________________________
// Face code:63.   Dimension: 4    Hyperplanes: {0, 2, 3, 5, 6, 9}.        Shift = 104.13206       F(x) = 9336.3249
// New surface point:                   200       14.726497             200             200       44.179492             200             200       29.452994       88.358983             200
// Including hyperplanes:  {0, 2, 3, 5, 6, 9, 10}
// _________________________________________________ 2 _____________________________________________________
// Face code:127.  Dimension: 3    Hyperplanes: {0, 2, 3, 5, 6, 9, 12}.    Shift = 22.125406       F(x) = 9411.2938
// New surface point:                   200               0             200             200        45.47622             200             200        24.89867       104.17797             200
// Including hyperplanes:  {0, 2, 3, 5, 6, 9, 10, 19}
// _________________________________________________ 3 _____________________________________________________
// Face code:255.  Dimension: 2    Hyperplanes: {0, 2, 3, 5, 6, 9, 12, 13}.        Shift = 37.39896        F(x) = 9490.3154
// New surface point:                   200               0             200             200       35.953912             200             200               0       130.40895             200
// Including hyperplanes:  {0, 2, 3, 5, 6, 9, 10, 13, 19}
// _________________________________________________ 4 _____________________________________________________
// Face code:511.  Dimension: 1    Hyperplanes: {0, 2, 3, 5, 6, 9, 12, 13, 16}.    Shift = 45.665963       F(x) = 9551.3829
// New surface point:                   200               0             200             200               0             200             200               0       158.56381             200
// Including hyperplanes:  {0, 2, 3, 5, 6, 9, 10, 13, 16, 19}
#define PP_PROBLEM_NAME	"rnd10-1-1"
#define PP_MAX_OBJ_VALUE 9551.382889057459 
//-------------------------------------------------------------------------------

/*============================== rnd10-1-2 LP problem ==============================*
// Start point:	0	200	200	200	0	0	200	200	0	200
// _________________________________________________ 1 _____________________________________________________
// Face code:63.   Dimension: 4    Hyperplanes: {1, 2, 3, 6, 7, 9}.        Shift = 86.170754       F(x) = 9015.3823
// New surface point:             60.331595             200             200             200       48.265276       12.066319             200             200       36.198957             200
// Including hyperplanes:  {1, 2, 3, 6, 7, 9, 10}
// _________________________________________________ 2 _____________________________________________________
// Face code:127.  Dimension: 3    Hyperplanes: {1, 2, 3, 6, 7, 9, 12}.    Shift = 27.156722       F(x) = 9063.8588
// New surface point:             72.711398             200             200             200       60.613355               0             200             200       19.282783             200
// Including hyperplanes:  {1, 2, 3, 6, 7, 9, 10, 15}
// _________________________________________________ 3 _____________________________________________________
// Face code:255.  Dimension: 2    Hyperplanes: {1, 2, 3, 6, 7, 9, 12, 15}.        Shift = 24.586081       F(x) = 9102.8261
// New surface point:             83.263679             200             200             200       71.626938               0             200             200               0             200
// Including hyperplanes:  {1, 2, 3, 6, 7, 9, 10, 12, 15}
// _________________________________________________ 4 _____________________________________________________
// Face code:511.  Dimension: 1    Hyperplanes: {1, 2, 3, 6, 7, 9, 12, 15, 16}.    Shift = 137.42141       F(x) = 9123.805
// New surface point:                     0             200             200             200       180.95124               0             200             200               0             200
// Including hyperplanes:  {1, 2, 3, 6, 7, 9, 10, 12, 15, 20}
#define PP_PROBLEM_NAME	"rnd10-1-2"
#define PP_MAX_OBJ_VALUE 9123.804967374708 
//-------------------------------------------------------------------------------

/*============================== rnd10-1-3 LP problem ==============================*
// Start point:	200	200	200	200	0	200	0	200	0	200
// _________________________________________________ 1 _____________________________________________________
// Face code:127.  Dimension: 3    Hyperplanes: {0, 1, 2, 3, 5, 7, 9}.     Shift = 24.979362       F(x) = 9893.4642
// New surface point:                   200             200             200             200       20.028046             200        13.35203             200       6.6760152             200
// Including hyperplanes:  {0, 1, 2, 3, 5, 7, 9, 10}
// _________________________________________________ 2 _____________________________________________________
// Face code:255.  Dimension: 2    Hyperplanes: {0, 1, 2, 3, 5, 7, 9, 12}. Shift = 13.607489       F(x) = 9921.184
// New surface point:                   200             200             200             200       31.871711             200       12.784451             200               0             200
// Including hyperplanes:  {0, 1, 2, 3, 5, 7, 9, 10, 12}
// _________________________________________________ 3 _____________________________________________________
// Face code:511.  Dimension: 1    Hyperplanes: {0, 1, 2, 3, 5, 7, 9, 12, 14}.     Shift = 25.20726        F(x) = 9960.7893
// New surface point:                   200             200             200             200       53.596439             200               0             200               0             200
// Including hyperplanes:  {0, 1, 2, 3, 5, 7, 9, 10, 12, 14}
#define PP_PROBLEM_NAME	"rnd10-1-3"
#define PP_MAX_OBJ_VALUE 9960.789316531009 
//-------------------------------------------------------------------------------

/*============================== rnd10-1-4 LP problem ==============================*
// Start point:	200	0	200	200	200	0	0	0	200	0
// _________________________________________________ 1 _____________________________________________________
// Face code:31.   Dimension: 5    Hyperplanes: {0, 2, 3, 4, 8}.   Shift = 167.88899       F(x) = 9092.23
// New surface point:                   200       18.888987             200             200             200       37.777974       75.555949       132.22291             200       56.666962
// Including hyperplanes:  {0, 2, 3, 4, 8, 10}
// _________________________________________________ 2 _____________________________________________________
// Face code:63.   Dimension: 4    Hyperplanes: {0, 2, 3, 4, 8, 11}.       Shift = 32.059448       F(x) = 9203.3258
// New surface point:                   200               0             200             200             200       40.867731       65.025925       155.68046             200       57.241145
// Including hyperplanes:  {0, 2, 3, 4, 8, 10, 19}
// _________________________________________________ 3 _____________________________________________________
// Face code:127.  Dimension: 3    Hyperplanes: {0, 2, 3, 4, 8, 11, 13}.   Shift = 57.746447       F(x) = 9357.9721
// New surface point:                   200               0             200             200             200       44.205245       28.566222             200             200       51.765588
// Including hyperplanes:  {0, 2, 3, 4, 7, 8, 10, 19}
// _________________________________________________ 4 _____________________________________________________
// Face code:255.  Dimension: 2    Hyperplanes: {0, 2, 3, 4, 8, 11, 13, 14}.       Shift = 54.630828       F(x) = 9404.3394
// New surface point:                   200               0             200             200             200        80.19444               0             200             200       81.316835
// Including hyperplanes:  {0, 2, 3, 4, 7, 8, 10, 14, 19}
// _________________________________________________ 5 _____________________________________________________
// Face code:511.  Dimension: 1    Hyperplanes: {0, 2, 3, 4, 8, 11, 13, 14, 15}.   Shift = 137.72811       F(x) = 9440.1346
// New surface point:                   200               0             200             200             200             200               0             200             200       13.378189
// Including hyperplanes:  {0, 2, 3, 4, 5, 7, 8, 10, 14, 19}
#define PP_PROBLEM_NAME	"rnd10-1-4"
#define PP_MAX_OBJ_VALUE 9440.134567875188		
//-------------------------------------------------------------------------------

/*============================== rnd10-1-5 LP problem ==============================*
// u0 = 200	200	200	0	0	0	200	200	200	200
// _________________________________________________ 1 _____________________________________________________
// Face code:127.  Dimension: 3    Hyperplanes: {0, 1, 2, 6, 7, 8, 9}.     Shift = 78.509654       F(x) = 10093.756
// New surface point:                   200             200             200       41.965175       20.982588       62.947763             200             200             200             200
// Including hyperplanes:  {0, 1, 2, 6, 7, 8, 9, 10}
// _________________________________________________ 2 _____________________________________________________
// Face code:255.  Dimension: 2    Hyperplanes: {0, 1, 2, 6, 7, 8, 9, 15}. Shift = 30.037233       F(x) = 10138.241
// New surface point:                   200             200             200       61.606595               0       71.675938             200             200             200             200
// Including hyperplanes:  {0, 1, 2, 6, 7, 8, 9, 10, 16}
// _________________________________________________ 3 _____________________________________________________
// Face code:511.  Dimension: 1    Hyperplanes: {0, 1, 2, 6, 7, 8, 9, 15, 16}.     Shift = 149.1287        F(x) = 10248.355
// New surface point:                   200             200             200             200               0       16.118454             200             200             200             200
// Including hyperplanes:  {0, 1, 2, 3, 6, 7, 8, 9, 10, 16}
#define PP_PROBLEM_NAME	"rnd10-1-5"
#define PP_MAX_OBJ_VALUE 10248.35536348363		
//-------------------------------------------------------------------------------

/*============================== rnd10-1-6 LP problem ==============================*/
// Start point:	200	200	200	0	200	0	200	200	0	0
// _________________________________________________ 1 _____________________________________________________
// Face code:63.   Dimension: 4    Hyperplanes: {0, 1, 2, 4, 6, 7}.        Shift = 154.54518       F(x) = 9846.4788
// New surface point:                   200             200             200       56.431922             200       112.86384             200             200       28.215961       84.647883
// Including hyperplanes:  {0, 1, 2, 4, 6, 7, 10}
// _________________________________________________ 2 _____________________________________________________
// Face code:127.  Dimension: 3    Hyperplanes: {0, 1, 2, 4, 6, 7, 11}.    Shift = 38.177298       F(x) = 9953.4845
// New surface point:                   200             200             200       63.884418             200       129.00942             200             200               0         103.226
// Including hyperplanes:  {0, 1, 2, 4, 6, 7, 10, 12}
// _________________________________________________ 3 _____________________________________________________
// Face code:255.  Dimension: 2    Hyperplanes: {0, 1, 2, 4, 6, 7, 11, 12}.        Shift = 109.39849       F(x) = 10020.872
// New surface point:                   200             200             200       31.881547             200       89.277338             200             200               0             200
// Including hyperplanes:  {0, 1, 2, 4, 6, 7, 9, 10, 12}
// _________________________________________________ 4 _____________________________________________________
// Face code:511.  Dimension: 1    Hyperplanes: {0, 1, 2, 4, 6, 7, 11, 12, 15}.    Shift = 35.878308       F(x) = 10022.936
// New surface point:                   200             200             200               0             200       105.73395             200             200               0             200
// Including hyperplanes:  {0, 1, 2, 4, 6, 7, 9, 10, 12, 17}
#define PP_PROBLEM_NAME	"rnd10-1-6"
#define PP_MAX_OBJ_VALUE 10022.93578020059
//-------------------------------------------------------------------------------

/*===============================================================================*/