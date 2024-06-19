/*==============================================================================
Project: LiFe - New Linear Programming Solvers
Theme: Surface movement method (No MPI)
Module: Problem-Forwards.h (Problem Function Forwards)
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
#include "Problem-bsfTypes.h"
#include "Problem-Types.h"
//====================== Private Functions ===========================
void	PF_CodeToSubset(int code, int subset[PP_MM], int* ma);
void	PF_MakeFaceList(int K);
void	PF_MakeHyperplaneList(PT_vector_T u, int* index_includingHyperplanes, int* mh, double eps);
void	PF_PreparationForIteration(PT_vector_T u);
void	PF_Print_Number_of_faces(PT_vector_T x);
void	PF_PseudoprojectionOnFace(PT_vector_T v, PT_vector_T w, double eps, int* success);
//====================== Shared Functions ===========================
double	SF_Distance_PointToHalfspace_i(PT_vector_T x, int i);
double	SF_Distance_PointToHyperplane_i(PT_vector_T x, int i);
double	SF_Distance_PointToPoint(PT_vector_T x, PT_vector_T y);
double	SF_Distance_PointToPolytope(PT_vector_T x);
void	SF_MakeColumnOfNorms(PT_matrix_T A, PT_column_T norm_a);
void	SF_MovingOnPolytope(PT_vector_T startPoint, PT_vector_T directionVector, PT_vector_T finishPoint, double epsMoving);
void	SF_MovingToPolytope(PT_vector_T point, PT_vector_T directionVector, double eps);
void	SF_MTX_Conversion();
void	SF_MTX_ConversionSimple();
bool	SF_MTX_Load__Problem();
bool	SF_MTX_Load_A();
bool	SF_MTX_Load_b();
bool	SF_MTX_Load_c();
bool	SF_MTX_Load_hi();
bool	SF_MTX_Load_lo();
bool	SF_MTX_LoadPoint(PT_vector_T x, string postfix);
void	SF_MTX_RemoveFreeVariables(int m_equation, int m_inequality, int m_lowerBound, int m_higherBound);
bool	SF_MTX_SavePoint(PT_vector_T x, string postfix);
void	SF_MTX_SkipComments(FILE* stream);
double	SF_ObjF(PT_vector_T x);
void	SF_ObliqueProjectingVectorOntoHalfspace_i(PT_vector_T z, int i, PT_vector_T g, PT_vector_T o, double eps, int* exitCode);
void	SF_OrthogonalProjectingVectorOntoHalfspace_i(PT_vector_T z, int i, PT_vector_T r, double eps, int* exitcode);
void	SF_OrthogonalProjectingVectorOntoHyperplane_i(PT_vector_T x, int i, PT_vector_T p);
bool	SF_PointBelongsHalfspace_i(PT_vector_T point, int i, double eps);
bool	SF_PointBelongsHyperplane_i(PT_vector_T z, int i, double eps);
bool	SF_PointBelongsPolytope(PT_vector_T x, double eps);
void	SF_PointHomothety(PT_vector_T x, PT_vector_T center, double ratio);
bool	SF_PointInsideHalfspace_i(PT_vector_T x, int i, double eps);
void	SF_PolytopeHomothety(PT_vector_T center, double ratio);
void	SF_Print_Inequalities();
void	SF_Print_HyperplanesIncludingPoint(PT_vector_T x, double eps);
void	SF_Print_Vector(PT_vector_T x);
double	SF_RelativeError(double trueValue, double calculatedValue);
void	SF_Shift(PT_vector_T point, PT_vector_T shiftVector, double factor, PT_vector_T shiftedPoint);
void	SF_Vector_Addition(PT_vector_T x, PT_vector_T y, PT_vector_T z);
void	SF_Vector_Copy(PT_vector_T x, PT_vector_T y);
void	SF_Vector_DivideByNumber(PT_vector_T x, double r, PT_vector_T y);
void	SF_Vector_DivideEquals(PT_vector_T x, double r);
double	SF_Vector_DotProduct(PT_vector_T x, PT_vector_T y);
bool	SF_Vector_Is_Tiny(PT_vector_T x, double eps);
void	SF_Vector_MakeLike(PT_vector_T x, double lengthOfLikeVector, PT_vector_T likeVector);
void	SF_Vector_MakeMinus_e(PT_vector_T minus_e);
void	SF_Vector_MinusEquals(PT_vector_T equalPoint, PT_vector_T minusVector);
void	SF_Vector_MultiplyByNumber(PT_vector_T x, double r, PT_vector_T y);
void	SF_Vector_MultiplyEquals(PT_vector_T x, double r);
double	SF_Vector_Norm(PT_vector_T x);
double	SF_Vector_NormSquare(PT_vector_T x);
void	SF_Vector_PlusEquals(PT_vector_T equalVector, PT_vector_T plusVector);
void	SF_Vector_Round(PT_vector_T x, double eps);
void	SF_Vector_Subtraction(PT_vector_T x, PT_vector_T y, PT_vector_T z);
void	SF_Vector_Zeroing(PT_vector_T x);
//====================== Macros ================================
#define PF_MIN(x,y) (x<y?x:y)
#define PF_MAX(x,y) (x>y?x:y)
#define PF_MAP_LIST_INDEX (BSF_sv_addressOffset + BSF_sv_numberInSublist)