/*==============================================================================
Project: LiFe
Theme: Surface movement method (No MPI)
Module: Problem-Forwards.h (Problem Function Forwards)
Author: Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
#include "Problem-bsfTypes.h"
#include "Problem-Types.h"
//====================== Problem Functions ===========================
void		AddOppositeInequality(int hyperplaneIndex, int* m);
bool		Conversion();
void		DirVectorCleanup(PT_vector_T x);
PT_float_T	Distance(PT_vector_T x, PT_vector_T y);
void		MakeHyperplaneList(int* mh);
bool		MakeHyperplaneSubsetCodeList(int mh, int* K);
bool		MTX_Load__Problem();
bool		MTX_Load_A(int* nor, int* noc, int* non, int* noe);
bool		MTX_Load_b(int* nor, int* noc, int* noe);
bool		MTX_Load_c(int* nor, int* noc);
bool		MTX_Load_hi(int* nor, int* noc);
bool		MTX_Load_lo(int* nor, int* noc);
bool		MTX_Load_sp(int* nor, int* noc);
bool		MTX_Save_sp(PT_vector_T x, double elapsedTime);
void		MakeObjVector(PT_vector_T c, PT_float_T length, PT_vector_T objVector);
bool		MovingOnSurface(PT_vector_T directionVector, PT_vector_T point);
PT_float_T	ObjF(PT_vector_T x);
bool		PointInHalfspace(PT_vector_T point, PT_vector_T a, PT_float_T b);
bool		PointInPolytope(PT_vector_T x);
PT_float_T	PolytopeResidual(PT_vector_T x);
double		ProblemScale();
void		Pseudoprojection(PT_vector_T v, PT_vector_T w);
PT_float_T	relativeError(PT_float_T trueValue, PT_float_T calcValue);
void		Shift(PT_vector_T basePoint, PT_vector_T direction, PT_float_T shiftRate, PT_vector_T endPoint);
void		SkipComments(FILE* stream);
void		Vector_Addition(PT_vector_T x, PT_vector_T y, PT_vector_T z);
void		Vector_Copy(PT_vector_T fromPoint, PT_vector_T toPoint);
PT_float_T	Vector_DistanceToHalfspace(PT_vector_T z, PT_vector_T a, PT_float_T b);
void		Vector_DivideByNumber(PT_vector_T x, double r, PT_vector_T y);
void		Vector_DivideEquals(PT_vector_T x, double r);
PT_float_T	Vector_DotProduct(PT_vector_T x, PT_vector_T y);
PT_float_T	Vector_Norm(PT_vector_T x);
PT_float_T	Vector_NormSquare(PT_vector_T x);
void		Vector_MinusEquals(PT_vector_T equalPoint, PT_vector_T minusVector);
void		Vector_MultiplyByNumber(PT_vector_T x, double r, PT_vector_T y);
void		Vector_MultiplyEquals(PT_vector_T x, double r);
void		Vector_PlusEquals(PT_vector_T equalVector, PT_vector_T plusVector);
void		Vector_ObliqueProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, PT_float_T b, PT_vector_T g, PT_vector_T o, int* exitCode);
bool		Vector_OnHyperplane(PT_vector_T point, PT_vector_T a, PT_float_T b);
PT_float_T	Vector_OrthogonalProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, PT_float_T b, PT_vector_T r, int* exitCode);
void		Vector_ResetToZero(PT_vector_T x);
void		Vector_Round(PT_vector_T x);
void		Vector_Subtraction(PT_vector_T x, PT_vector_T y, PT_vector_T z);
void		Vector_Unit(PT_vector_T vector);
//====================== Macros ================================
#define PF_MIN(x,y) (x<y?x:y)
#define PF_MAX(x,y) (x>y?x:y)