/*==============================================================================
Project: LiFe
Theme: Surface movement method (MPI)
Module: Problem-Forwards.h (Problem Function Forwards)
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
#include "Problem-bsfTypes.h"
#include "Problem-Types.h"
//====================== Problem Functions ===========================
void	AddOppositeInequality(int hyperplaneIndex, int m);
void	CodeToSubset(int code, int subset[PP_MM], int* ma);
bool	Conversion();
void	DirVectorCleanup(PT_vector_T x, double eps);
double	Distance(PT_vector_T x, PT_vector_T y);
void	MakeHyperplaneList(PT_vector_T u, int* mh);
void	MakeHyperplaneSubsetCodeList(int* K);
void	MakeObjVector(PT_vector_T c, double length, PT_vector_T objVector);
bool	MovingOnSurface(PT_vector_T directionVector, PT_vector_T point);
bool	MTX_Load__Problem();
bool	MTX_Load_A(int* nor, int* noc, int* non, int* noe);
bool	MTX_Load_b(int* nor, int* noc, int* noe);
bool	MTX_Load_c(int* nor, int* noc);
bool	MTX_Load_hi(int* nor, int* noc);
bool	MTX_Load_lo(int* nor, int* noc);
bool	MTX_Load_u0(int* nor, int* noc);
bool	MTX_Save_so(PT_vector_T x, double elapsedTime);
double	ObjF(PT_vector_T x);
bool	PointInHalfspace(PT_vector_T point, PT_vector_T a, double b, double eps);
bool	PointInPolytope(PT_vector_T x);
double	PolytopeResidual(PT_vector_T x);
void	Print_Number_of_subsets(PT_vector_T x);
void	Print_VectorOnActiveHyperplanes(PT_vector_T x);
void	Print_VectorOnHyperplanes(PT_vector_T x);
void	Preparation_for_Movement(PT_vector_T u);
void	PseudoprojectionOnFace(PT_vector_T v, PT_vector_T w);
void	PseudoprojectionOnPolytope(PT_vector_T v, PT_vector_T w);
double	relativeError(double trueValue, double calcValue);
void	Shift(PT_vector_T basePoint, PT_vector_T direction, double PD_shiftLength, PT_vector_T endPoint);
void	SkipComments(FILE* stream);
void	Vector_Addition(PT_vector_T x, PT_vector_T y, PT_vector_T z);
void	Vector_Copy(PT_vector_T fromPoint, PT_vector_T toPoint);
double	Vector_DistanceToHalfspace(PT_vector_T z, PT_vector_T a, double b);
void	Vector_DivideByNumber(PT_vector_T x, double r, PT_vector_T y);
void	Vector_DivideEquals(PT_vector_T x, double r);
double	Vector_DotProduct(PT_vector_T x, PT_vector_T y);
bool	Vector_Equal(PT_vector_T x, PT_vector_T y, double eps);
bool	Vector_Is_Tiny(PT_vector_T x, double eps);
double	Vector_Norm(PT_vector_T x);
double	Vector_NormSquare(PT_vector_T x);
void	Vector_MinusEquals(PT_vector_T equalPoint, PT_vector_T minusVector);
void	Vector_MultiplyByNumber(PT_vector_T x, double r, PT_vector_T y);
void	Vector_MultiplyEquals(PT_vector_T x, double r);
void	Vector_PlusEquals(PT_vector_T equalVector, PT_vector_T plusVector);
void	Vector_ObliqueProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, double b, PT_vector_T g, PT_vector_T o, int* exitCode);
bool	Vector_OnHyperplane(PT_vector_T point, PT_vector_T a, double b, double eps, double* residual);
double	Vector_OrthogonalProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, double b, PT_vector_T r, double eps, int* exitCode);
double	Vector_OrthogonalProjectionOntoHyperplane(PT_vector_T z, PT_vector_T a, double b, PT_vector_T r);
void	Vector_Round(PT_vector_T x, double eps);
void	Vector_Subtraction(PT_vector_T x, PT_vector_T y, PT_vector_T z);
void	Vector_Unit(PT_vector_T vector);
void	Vector_Zero(PT_vector_T x);
//====================== Macros ================================
#define PF_MIN(x,y) (x<y?x:y)
#define PF_MAX(x,y) (x>y?x:y)