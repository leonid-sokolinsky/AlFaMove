/*==============================================================================
Project: LiFe
Theme: Surface movement method (MPI)
Module: Problem-bsfCode.cpp (Implementation of Problem Code)
Prefix: PC
Authors: Nikolay A. Olkhovsky & Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
#include "Problem-Data.h"			// Problem Types 
#include "Problem-Forwards.h"		// Problem Function Forwards
#include "Problem-bsfParameters.h"	// BSF-skeleton parameters
#include "BSF-SkeletonVariables.h"	// Skeleton Variables

using namespace std;

void PC_bsf_SetInitParameter(PT_bsf_parameter_T* parameter) {
	Vector_Copy(PD_u, parameter->x);
}

void PC_bsf_Init(bool* success) {
	PD_problemName = PP_PROBLEM_NAME;
	*success = MTX_Load__Problem();
	if (*success == false)
		return;

	if (!PointInPolytope(PD_u)) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Starting point does not belong to the feasible polytope with precision PP_RND_EPS_POINT_IN_POLYTOPE = "
			<< PP_RND_EPS_POINT_IN_POLYTOPE << "!!!\n";
		*success = false;
		return;
	}
}

void PC_bsf_SetListSize(int* listSize) {
	*listSize = PP_KK;
}

void PC_bsf_SetMapListElem(PT_bsf_mapElem_T* elem, int i) {
	elem->hyperplaneSubsetCode = &(PD_hyperplaneSubsetCodeList[i]);
}

void PC_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem, int* success) {
	// Map-List index = BSF_sv_addressOffset + BSF_sv_numberInSublist
	int subsetCode = *mapElem->hyperplaneSubsetCode;
	PT_vector_T u;		// current surface point
	PT_vector_T v;		// v = u + PD_objVector (objVector = PP_OBJECTIVE_VECTOR_LENGTH*e_c)
	PT_vector_T w;		// pseudiprojection of v
	double objF_w = -PP_DBL_MAX; // F(w)

	if (subsetCode == 0) {
		Vector_Zero((*reduceElem).d);
		reduceElem->objF_p = -PP_DBL_MAX;
		reduceElem->subsetCode = 0;
		return;
	}

#ifdef PP_DEBUG
	cout << "------------------------------------ Map(" << BSF_sv_addressOffset + BSF_sv_numberInSublist << ") ------------------------------------" << endl;
#endif // PP_DEBUG

	Vector_Copy(BSF_sv_parameter.x, u);
	double objF_u = ObjF(u);
	reduceElem->subsetCode = subsetCode;

	CodeToSubset(subsetCode, PD_index_activeHalfspaces, &PD_ma);

#ifdef PP_DEBUG
	cout << "Code: " << subsetCode << ".\tSubset: {";
	for (int i = 0; i < PD_ma - 1; i++) {
		cout << PD_index_activeHalfspaces[i] << ", ";
	}
	cout << PD_index_activeHalfspaces[PD_ma - 1] << "}.\n";
#endif // PP_DEBUG

	MakeObjVector(PD_c, PP_OBJECTIVE_VECTOR_LENGTH, PD_objVector);

	Vector_Addition(u, PD_objVector, v);

	PseudoprojectionOnFace(v, w, PP_EPS_P_PROJ_ON_FACE);

	objF_w = ObjF(w);

	Vector_Subtraction(w, u, (*reduceElem).d);
	DirVectorCleanup((*reduceElem).d, PP_EPS_ZERO);

	double norm_d = Vector_Norm((*reduceElem).d);
	if (norm_d < PP_EPS_ZERO) {
#ifdef PP_DEBUG
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t||d|| = ||w-u|| < PP_EPS_ZERO ===>>> movement is impossible.\n";
#endif // PP_DEBUG
		Vector_Zero((*reduceElem).d);
		reduceElem->objF_p = objF_u;
		return;
	}

	Vector_MultiplyEquals((*reduceElem).d, PP_PROBE_LENGTH / norm_d);

	PT_vector_T p;
	Vector_Addition(u, (*reduceElem).d, p);
	
	if (!PointInPolytope(p)) {
#ifdef PP_DEBUG
		cout << "Shifted point p = ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			cout << setw(PP_SETW) << p[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
		cout << "\tnot in feasible polytope ===>>> movement is impossible." << endl;
#endif // PP_DEBUG
		Vector_Zero((*reduceElem).d);
		reduceElem->objF_p = objF_u;
		return;
	}

	reduceElem->objF_p = ObjF(p);

	if (relativeError(objF_u, reduceElem->objF_p) < PP_EPS_ZERO) {
#ifdef PP_DEBUG
		cout << "u =\t    ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			cout << setw(PP_SETW) << u[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
		cout << "\tF(u) = " << setw(PP_SETW) << objF_u << endl;
		cout << "|F(u1)-F(u2)|/|F(u1)| = " << relativeError(objF_u, reduceElem->objF_p) << " < PP_EPS_ZERO ===>>> movement is impossible.\n";
#endif // PP_DEBUG

		Vector_Zero((*reduceElem).d);
		reduceElem->objF_p = objF_u;
		return;
	}

	if (reduceElem->objF_p < objF_u) {
#ifdef PP_DEBUG
		cout << "u =\t    ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			cout << setw(PP_SETW) << u[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
		cout << "\tF(w) = " << setw(PP_SETW) << reduceElem->objF_p << " < F(u) = " << objF_u << " ===>>> movement is impossible.\n";
#endif // PP_DEBUG
		Vector_Zero((*reduceElem).d);
		reduceElem->objF_p = objF_u;
		return;
	}

#ifdef PP_DEBUG
	cout << "Shifted point p = ";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
		cout << setw(PP_SETW) << p[j];
	if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
	cout << "\tF(p) ="
		<< setw(PP_SETW) << reduceElem->objF_p << "\t\t---> Movement is possible." << endl;
#endif // PP_DEBUG
	return;
} // end PC_bsf_MapF

void PC_bsf_MapF_1(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_1* reduceElem, int* success) {
	// not used
}

void PC_bsf_MapF_2(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_2* reduceElem, int* success) {
	// not used
}

void PC_bsf_MapF_3(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_3* reduceElem, int* success) {
	// not used
}

void PC_bsf_ReduceF(PT_bsf_reduceElem_T* x, PT_bsf_reduceElem_T* y, PT_bsf_reduceElem_T* z) { // z = x + y
	if (x->objF_p > y->objF_p) {
		z->objF_p = x->objF_p;
		for (int j = 0; j < PD_n; j++)
			(*z).d[j] = (*x).d[j];
		z->subsetCode = x->subsetCode;
	}
	else {
		z->objF_p = y->objF_p;
		for (int j = 0; j < PD_n; j++)
			(*z).d[j] = (*y).d[j];
		z->subsetCode = y->subsetCode;
	}
}

void PC_bsf_ReduceF_1(PT_bsf_reduceElem_T_1* x, PT_bsf_reduceElem_T_1* y, PT_bsf_reduceElem_T_1* z) {
	// not used
}

void PC_bsf_ReduceF_2(PT_bsf_reduceElem_T_2* x, PT_bsf_reduceElem_T_2* y, PT_bsf_reduceElem_T_2* z) {
	// not used
}

void PC_bsf_ReduceF_3(PT_bsf_reduceElem_T_3* x, PT_bsf_reduceElem_T_3* y, PT_bsf_reduceElem_T_3* z) {
	// not used
}

void PC_bsf_ProcessResults(
	PT_bsf_reduceElem_T* reduceResult,
	int reduceCounter, // Number of successfully produced Elements of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* nextJob,
	bool* exit // "true" if Stopping Criterion is satisfied, and "false" otherwise
) {
	bool success;
	success = MovingOnSurface(reduceResult->d, PD_u);
	if (success) {
		*exit = false;
		CodeToSubset(reduceResult->subsetCode, PD_index_activeHalfspaces, &PD_ma);
		cout << "________________________________________________________________________________________________________________" << endl;
		PD_objF_u = ObjF(PD_u);
		cout << "Code:" << reduceResult->subsetCode << " Face dimension: " << PD_n - PD_ma << ".\tGenerating hyperplanes: {";
		for (int i = 0; i < PD_ma - 1; i++)
			cout << PD_index_activeHalfspaces[i] << ", ";
		cout << PD_index_activeHalfspaces[PD_ma - 1]
			<< "}.\tShift = " << PD_shiftLength << "\tF(x) = " << PD_objF_u << endl;

		cout << "Surface point:\t";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++) cout << setw(PP_SETW) << PD_u[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << "	...";
		cout << endl;

		Vector_Copy(PD_u, parameter->x);
	}
	else {
		*exit = true;
	}
}

void PC_bsf_ProcessResults_1(
	PT_bsf_reduceElem_T_1* reduceResult,
	int reduceCounter, // Number of successfully produced Elements of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* nextJob,
	bool* exit // "true" if Stopping Criterion is satisfied, and "false" otherwise
) {
	// not used
}

void PC_bsf_ProcessResults_2(
	PT_bsf_reduceElem_T_2* reduceResult,
	int reduceCounter, // Number of successfully produced Elements of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* nextJob,
	bool* exit // "true" if Stopping Criterion is satisfied, and "false" otherwise
) {
	// not used
}

void PC_bsf_ProcessResults_3(
	PT_bsf_reduceElem_T_3* reduceResult,
	int reduceCounter, // Number of successfully produced Elements of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* nextJob,
	bool* exit // "true" if Stopping Criterion is satisfied, and "false" otherwise
) {
	// not used
}

void PC_bsf_JobDispatcher(
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* job,
	bool* exit,
	double t
) {
	// Not used
}

void PC_bsf_ParametersOutput(PT_bsf_parameter_T parameter) {
	cout << "=================================================== BSF-SMM ====================================================" << endl;
	cout << "Problem name: " << PD_problemName << endl;
	cout << "Number of Workers: " << BSF_sv_numOfWorkers << endl;
#ifdef PP_BSF_OMP
#ifdef PP_BSF_NUM_THREADS
	cout << "Number of Threads: " << PP_BSF_NUM_THREADS << endl;
#else
	cout << "Number of Threads: " << omp_get_num_procs() << endl;
#endif // PP_BSF_NUM_THREADS
#else
	cout << "OpenMP is turned off!" << endl;
#endif // PP_BSF_OMP

#ifdef PP_BSF_FRAGMENTED_MAP_LIST
	cout << "Map List is Fragmented." << endl;
#else
	cout << "Map List is not Fragmented." << endl;
#endif
	cout << "Before conversion: m =\t" << PP_M << "\tn = " << PP_N << endl;
	cout << "After conversion:  m =\t" << PD_m << "\tn = " << PD_n << endl;
	cout << "Eps Zero:\t\t" << PP_EPS_ZERO << endl;
	cout << "Obj Vector Length:\t" << PP_OBJECTIVE_VECTOR_LENGTH << endl;
	cout << "--------------- Data ---------------\n";
#ifdef PP_MATRIX_OUTPUT
	cout << "------- Matrix PD_A & Column PD_b -------" << endl;
	for (int i = 0; i < PD_m; i++) {
		cout << i << ")";
		for (int j = 0; j < PD_n; j++)
			cout << setw(PP_SETW) << PD_A[i][j];
		cout << "\t<=" << setw(PP_SETW) << PD_b[i] << endl;
	}
#endif // PP_MATRIX_OUTPUT
	cout << "Obj Function:\t";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
		cout << setw(PP_SETW) << PD_c[j];
	if (PP_OUTPUT_LIMIT < PD_n)
		cout << " ...";
	cout << endl;
	cout << "u0 =\t\t";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++) cout << setw(PP_SETW) << PD_u[j];
	if (PP_OUTPUT_LIMIT < PD_n)
		cout << " ...";
	cout << "\tF(x) = " << setw(PP_SETW) << ObjF(PD_u);
	cout << endl;
#ifdef PP_DEBUG
	cout << "u0 on hyperplanes: "; Print_VectorOnHyperplanes(PD_u);
#endif // PP_DEBUG
	if (!PointInPolytope(PD_u))
		cout << "u0 is outside feasible polytope!!!\n";
	else
		cout << "u0 is inside feasible polytope.\n";
	cout << "-------------------------------------------" << endl;
	cout << "Number of hyperplane subsets = "; Print_Number_of_subsets(PD_u);
}

void PC_bsf_CopyParameter(PT_bsf_parameter_T parameterIn, PT_bsf_parameter_T* parameterOutP) {
	for (int j = 0; j < PD_n; j++)
		parameterOutP->x[j] = parameterIn.x[j];
	Preparation_for_Movement(parameterOutP->x);
}

void PC_bsf_IterOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int nextJob) {

	cout << "# " << BSF_sv_iterCounter << "\tTime " << round(elapsedTime);
	cout << "\tx =";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++) cout << setw(PP_SETW) << parameter.x[j];
	if (PP_OUTPUT_LIMIT < PD_n) cout << "	...";
	cout << "\tF(x) = " << setw(PP_SETW) << ObjF(parameter.x);

}

void PC_bsf_IterOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int nextJob)
{
	// not used
};

void PC_bsf_IterOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int nextJob)
{
	// not used
}

void PC_bsf_IterOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int nextJob)
{
	// not used
}

void PC_bsf_ProblemOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter, double t) {
	cout << setprecision(PP_SETW / 2);

	PT_vector_T refined_u;
	PseudoprojectionOnPolytope(PD_u, refined_u);
	Vector_Round(refined_u, PP_EPS_ZERO);
	Vector_Copy(refined_u, PD_u);

	PD_objF_u = ObjF(PD_u);

	cout << "=============================================" << endl;
	cout << "Elapsed time: " << t << endl;
	cout << "Current objective value: " << setprecision(16) << PD_objF_u << endl;
	cout << "Optimal objective value: " << PP_OPTIMAL_OBJ_VALUE << endl;
	cout << "Relative error = " << setprecision(PP_SETW / 2) << relativeError(PP_OPTIMAL_OBJ_VALUE, PD_objF_u) << endl;
	cout << "=============================================" << endl;

	cout << "Solution point:\t";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++) cout << setw(PP_SETW) << PD_u[j];
	if (PP_OUTPUT_LIMIT < PD_n) cout << "	...";
	cout << endl;
#ifdef PP_DEBUG
	cout << "Polytope residual: " << PolytopeResidual(PD_u) << endl;
#endif // PP_DEBUG

#ifdef PP_SAVE_RESULT
	if (MTX_Save_so(PD_u, t))
		cout << "Calculated solution point is saved into file *.so" << endl;
#endif // PP_SAVE_RESULT
} // end PC_bsf_ProblemOutput

void PC_bsf_ProblemOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter, double t) {
	// not used
}

void PC_bsf_ProblemOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter, double t) {
	// not used
}

void PC_bsf_ProblemOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter, double t) {
	// not used
}

// MPI
// MPI
// MPI

//----------------------- Assigning Values to BSF-skeleton Variables (Do not modify!) -----------------------
void PC_bsfAssignAddressOffset(int value) { BSF_sv_addressOffset = value; };
void PC_bsfAssignIterCounter(int value) { BSF_sv_iterCounter = value; };
void PC_bsfAssignJobCase(int value) { BSF_sv_jobCase = value; };
void PC_bsfAssignMpiMaster(int value) { BSF_sv_mpiMaster = value; };
void PC_bsfAssignMpiRank(int value) { BSF_sv_mpiRank = value; };
void PC_bsfAssignNumberInSublist(int value) { BSF_sv_numberInSublist = value; };
void PC_bsfAssignNumOfWorkers(int value) { BSF_sv_numOfWorkers = value; };
void PC_bsfAssignParameter(PT_bsf_parameter_T parameter) { PC_bsf_CopyParameter(parameter, &BSF_sv_parameter); }
void PC_bsfAssignSublistLength(int value) { BSF_sv_sublistLength = value; };

//---------------------------------- Problem functions -------------------------
inline void MakeHyperplaneList(PT_vector_T u, int* mh) {
	double residual;
	*mh = 0;
	for (int i = 0; i < PD_m; i++) {
		if (Vector_OnHyperplane(u, PD_A[i], PD_b[i], PP_EPS_MAKE_H_PLANE_LIST, &residual)) {
			PD_index_includingHyperplanes[*mh] = i;
			(*mh)++; assert((*mh) <= PP_MM);
		}
	}
}

inline void MakeHyperplaneSubsetCodeList(int mh, int* K) {
	int index;

	for (int k = 0; k < PP_KK; k++) {
		PD_hyperplaneSubsetCodeList[k] = 0;
	}

	for (int k = 1; k <= *K; k++) {
		index = rand() % *K;
		if (PD_hyperplaneSubsetCodeList[index] == 0)
			PD_hyperplaneSubsetCodeList[index] = k;
		else {
			for (int ki = 1; ki < *K; ki++) {
				if (PD_hyperplaneSubsetCodeList[(index + ki) % *K] == 0) {
					PD_hyperplaneSubsetCodeList[(index + ki) % *K] = k;
					break;
				}
			}
		}
	}
}

inline void PseudoprojectionOnPolytope(PT_vector_T v, PT_vector_T w) {
	double maxResidual;
	int nonZeroCounter;
	PT_vector_T sum_r;

	for (int j = 0; j < PD_n; j++) {
		w[j] = v[j];
	}

	do {
		maxResidual = 0;
		nonZeroCounter = 0;
		Vector_Zero(sum_r);

		for (int i = 0; i < PD_m; i++) {
			int exitcode;
			PT_vector_T r;
			double halfspaceResidual =
				Vector_OrthogonalProjectionOntoHalfspace(w, PD_A[i], PD_b[i], r, PP_EPS_P_PROJ_ON_POLYTOPE, &exitcode);
			assert(exitcode != PP_EXITCODE_DEGENERATE_INEQUALITY);
			if (exitcode == PP_EXITCODE_NATURAL_PROJECTING) {
				for (int j = 0; j < PD_n; j++) {
					sum_r[j] += r[j];
				}
				nonZeroCounter++;
				maxResidual = PF_MAX(maxResidual, halfspaceResidual);
			}
		}

		if (nonZeroCounter > 0)
			Vector_DivideEquals(sum_r, nonZeroCounter);
		Vector_PlusEquals(w, sum_r);
	} while (maxResidual >= PP_EPS_P_PROJ_ON_POLYTOPE);
}

inline void PseudoprojectionOnFace(PT_vector_T v, PT_vector_T w, double eps) {
	double maxResidual;
	PT_vector_T sum_r;

	Vector_Copy(v, w);

	do {
		maxResidual = 0;
		Vector_Zero(sum_r);

		for (int i = 0; i < PD_ma; i++) {
			int ia = PD_index_activeHalfspaces[i];
			PT_vector_T r;
			double hyperplaneResidual =
				Vector_OrthogonalProjectionOntoHyperplane(w, PD_A[ia], PD_b[ia], r, eps);
			Vector_PlusEquals(sum_r, r);
			maxResidual = PF_MAX(maxResidual, hyperplaneResidual);
		}

		Vector_Round(sum_r, eps * 10);
		if (Vector_NormSquare(sum_r) == 0)
			break;

		Vector_DivideEquals(sum_r, PD_ma);
		Vector_PlusEquals(w, sum_r);
	} while (maxResidual >= eps);
}

inline void AddOppositeInequality(int hyperplaneIndex, int m) {
	for (int j = 0; j < PD_n; j++) {
		PD_A[m][j] = -PD_A[hyperplaneIndex][j];
	}
	PD_b[m] = -PD_b[hyperplaneIndex];
}

inline double Vector_DotProduct(PT_vector_T x, PT_vector_T y) {
	double sum = 0;
	for (int j = 0; j < PD_n; j++)
		sum += x[j] * y[j];
	return sum;
}

inline double Vector_Norm(PT_vector_T x) {
	return sqrt(Vector_NormSquare(x));
}

inline double Vector_NormSquare(PT_vector_T x) {
	double sum = 0;

	for (int j = 0; j < PD_n; j++) {
		sum += x[j] * x[j];
	}
	return sum;
}

inline void Vector_Zero(PT_vector_T x) {
	for (int j = 0; j < PD_n; j++)
		x[j] = 0;
}

inline bool PointInPolytope(PT_vector_T x) { // If the point belongs to the polytope with prescigion of eps
	double eps;
	for (int i = 0; i < PD_m; i++) {
		if (PD_b[i] > PP_MAX_B_NO_CORRECT)
			eps = PP_RND_EPS_POINT_IN_POLYTOPE;
		else
			eps = PP_EPS_ZERO;

		if (!PointInHalfspace(x, PD_A[i], PD_b[i], eps))
			return false;
	}
	return true;
}

inline bool PointInHalfspace // If the point belongs to the Halfspace with prescigion of eps
(PT_vector_T x, PT_vector_T a, double b, double eps) {
	double res = Vector_DotProduct(a, x) - b;
	return res <= eps;
}

inline void Shift(PT_vector_T point, PT_vector_T directionVector, double PD_shiftLength, PT_vector_T shiftedPoint) {
	for (int j = 0; j < PD_n; j++)
		shiftedPoint[j] = point[j] + directionVector[j] * PD_shiftLength;
}

inline void Vector_Copy(PT_vector_T fromPoint, PT_vector_T toPoint) { // toPoint = fromPoint
	for (int j = 0; j < PD_n; j++)
		toPoint[j] = fromPoint[j];
}

inline bool Vector_Equal(PT_vector_T x, PT_vector_T y, double eps) { // x = y
	for (int j = 0; j < PD_n; j++)
		if (fabs(x[j] - y[j]) >= eps)
			return false;
	return true;
}

inline void Vector_PlusEquals(PT_vector_T equalVector, PT_vector_T plusVector) { // equalVector += plusVector
	for (int j = 0; j < PD_n; j++)
		equalVector[j] += plusVector[j];
}

inline void Vector_MinusEquals(PT_vector_T equalPoint, PT_vector_T minusVector) { // equalPoint += minusVector
	for (int j = 0; j < PD_n; j++)
		equalPoint[j] -= minusVector[j];
}

inline void Vector_Addition(PT_vector_T x, PT_vector_T y, PT_vector_T z) {  // z = x + y
	for (int j = 0; j < PD_n; j++)
		z[j] = x[j] + y[j];
}

inline void Vector_Subtraction(PT_vector_T x, PT_vector_T y, PT_vector_T z) {  // z = x - y
	for (int j = 0; j < PD_n; j++)
		z[j] = x[j] - y[j];
}

inline void Vector_MultiplyByNumber(PT_vector_T x, double r, PT_vector_T y) {  // y = r*x
	for (int j = 0; j < PD_n; j++)
		y[j] = x[j] * r;
}

inline void Vector_MultiplyEquals(PT_vector_T x, double r) {  // x = r*x
	for (int j = 0; j < PD_n; j++)
		x[j] *= r;
}

inline void Vector_DivideEquals(PT_vector_T x, double r) {  // x = x/r
	for (int j = 0; j < PD_n; j++)
		x[j] /= r;
}

inline void Vector_DivideByNumber(PT_vector_T x, double r, PT_vector_T y) {  // y = x/r
	for (int j = 0; j < PD_n; j++)
		y[j] = x[j] / r;
}

inline void Vector_Round(PT_vector_T x, double eps) {
	double floorValue;
	double fractionalPart;
	double sign;
	double absValue;

	for (int j = 0; j < PD_n; j++) {
		if (fabs(x[j]) < eps) {
			x[j] = 0;
			continue;
		}
		absValue = fabs(x[j]);
		sign = x[j] > 0 ? 1 : -1;
		floorValue = floor(absValue);
		fractionalPart = absValue - floorValue;
		if (1 - fractionalPart < eps) {
			x[j] = sign * (floorValue + 1);
			continue;
		}
		if (fractionalPart < eps)
			x[j] = sign * floorValue;
	}
}

inline void DirVectorCleanup(PT_vector_T x, double eps) { // Zeroing coordinates less than eps
	for (int j = 0; j < PD_n; j++)
		if (fabs(x[j]) < eps)
			x[j] = 0;
}

inline void Vector_Unit(PT_vector_T vector) { // Calculating unit vector
	double normOfVector = Vector_Norm(vector);
	for (int j = 0; j < PD_n; j++) {
		vector[j] /= normOfVector;
	}
};

inline double ObjF(PT_vector_T x) {
	double s = 0;
	for (int j = 0; j < PD_n; j++)
		s += PD_c[j] * x[j];
	return s;
}

static bool MTX_Load__Problem() {
	int nor,	// Number of matrix rows
		noc,	// Number of matrix columns
		non,	// Number of non-zero elements
		noe;	// Number of equations

	//--------------- Reading A ------------------
	if (!MTX_Load_A(&nor, &noc, &non, &noe))
		return false;

	//--------------- Reading b ------------------
	if (!MTX_Load_b(&nor, &noc, &noe))
		return false;

	//--------------- Reading lo ------------------
	if (!MTX_Load_lo(&nor, &noc))
		return false;

	//--------------- Reading c ------------------
	if (!MTX_Load_c(&nor, &noc))
		return false;

	//--------------- Reading hi ------------------
	if (!MTX_Load_hi(&nor, &noc))
		return false;

	//---------- Conversion to inequalities -----------
	if (!Conversion())
		return false;

	//--------------- Reading surfase point ------------------
	if (!MTX_Load_u0(&nor, &noc))
		return false;

	return true;
}

inline bool MTX_Load_A( // Reading A
	int* nor,	// Number of matrix rows
	int* noc,	// Number of matrix columns
	int* non,	// Number of non-zero elements
	int* noe	// Number of equations
) {
	const char* mtxFile;
	FILE* stream;// Input stream
	char str[80] = { '\0' };
	char* chr = str;

	PD_MTX_File_A = PP_PATH;
	PD_MTX_File_A += PP_MTX_PREFIX;
	PD_MTX_File_A += PD_problemName;
	PD_MTX_File_A += PP_MTX_POSTFIX_A;
	mtxFile = PD_MTX_File_A.c_str();
	stream = fopen(mtxFile, "r+b");

	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d%d", nor, noc, non) < 3) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Unexpected end of file " << mtxFile << endl;
		return false;
	}

	if (*nor >= *noc) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Number of rows m = " << *nor << " must be < " << "Number of columns n = " << *noc << "\n";
		return false;
	}

	if (*noc != PP_N) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Invalid input data: PP_N must be = " << *noc << "\n";
		return false;
	}

	if (*nor != PP_M) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Invalid input data: PP_M must be = " << *nor << "\n";
		return false;
	}

	PD_m = *noe = *nor;
	PD_n = *noc;

	if (2 * *nor + *noc > PP_MM) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Invalid input data: number of inequalities m = " << 2 * *nor + *noc
			<< " must be < PP_MM + 1 =" << PP_MM + 1 << "\n";
		return false;
	}

	for (int k = 0; k < *non; k++) {
		int i, j;

		if (fscanf(stream, "%d%d%s", &i, &j, str) < 3) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout
				<< "Unexpected end of file'" << mtxFile << "'." << endl;
			return false;
		}

		i -= 1;
		j -= 1;
		if (i < 0) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout
				<< "Negative row index in'" << mtxFile << "'.\n" << endl;
			return false;
		}
		if (j < 0) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout
				<< "Negative column index in'" << mtxFile << "'.\n" << endl;
			return false;
		}
		PD_A[i][j] = strtod(str, &chr);
	}

	fclose(stream);

	return true;
}

inline bool MTX_Load_b(
	int* nor,	// Number of matrix rows
	int* noc,	// Number of matrix columns
	int* noe	// Number of equations
) {
	const char* mtxFile;
	FILE* stream;// Input stream
	char str[80] = { '\0' };
	char* chr = str;

	PD_MTX_File_b = PP_PATH;
	PD_MTX_File_b += PP_MTX_PREFIX;
	PD_MTX_File_b += PD_problemName;
	PD_MTX_File_b += PP_MTX_POSTFIX_B;
	mtxFile = PD_MTX_File_b.c_str();
	stream = fopen(mtxFile, "r+b");

	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*noe != *nor) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int i = 0; i < *noe; i++) {
		if (fscanf(stream, "%s", str) < 1) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout
				<< "Unexpected end of file '" << mtxFile << "'." << endl;
			return false;
		}
		PD_b[i] = strtod(str, &chr);
	}
	fclose(stream);

	return true;
}

inline bool MTX_Load_lo(
	int* nor,	// Number of matrix rows
	int* noc	// Number of matrix columns
) {
	const char* mtxFile;
	FILE* stream;// Input stream
	char str[80] = { '\0' };
	char* chr = str;

	PD_MTX_File_lo = PP_PATH;
	PD_MTX_File_lo += PP_MTX_PREFIX;
	PD_MTX_File_lo += PD_problemName;
	PD_MTX_File_lo += PP_MTX_POSTFIX_LO;
	mtxFile = PD_MTX_File_lo.c_str();
	stream = fopen(mtxFile, "r+b");

	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 1) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout
				<< "Unexpected end of file '" << mtxFile << "'." << endl;
			return false;
		}
		PD_lo[j] = strtod(str, &chr);
	}

	fclose(stream);

	return true;
}

inline bool MTX_Load_hi(
	int* nor,	// Number of matrix rows
	int* noc	// Number of matrix columns
) {
	const char* mtxFile;
	FILE* stream;// Input stream
	char str[80] = { '\0' };
	char* chr = str;
	PD_MTX_File_hi = PP_PATH;
	PD_MTX_File_hi += PP_MTX_PREFIX;
	PD_MTX_File_hi += PD_problemName;
	PD_MTX_File_hi += PP_MTX_POSTFIX_HI;
	mtxFile = PD_MTX_File_hi.c_str();
	stream = fopen(mtxFile, "r+b");

	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 1) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout << "Unexpected end of file '" << mtxFile << "'." << endl;
			return false;
		}
		PD_hi[j] = strtod(str, &chr);
	}
	fclose(stream);
	return true;
}

inline bool MTX_Load_c(
	int* nor,	// Number of matrix rows
	int* noc	// Number of matrix columns
) {
	const char* mtxFile;
	FILE* stream;// Input stream
	char str[80] = { '\0' };
	char* chr = str;

	PD_MTX_File_c = PP_PATH;
	PD_MTX_File_c += PP_MTX_PREFIX;
	PD_MTX_File_c += PD_problemName;
	PD_MTX_File_c += PP_MTX_POSTFIX_C;
	mtxFile = PD_MTX_File_c.c_str();
	stream = fopen(mtxFile, "r+b");

	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 0) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout
				<< "Unexpected end of file" << endl;
			return false;
		}
		PD_c[j] = -strtod(str, &chr);
	}
	fclose(stream);

	return true;
}

inline bool MTX_Load_u0(
	int* nor,	// Number of matrix rows
	int* noc	// Number of matrix columns
) {
	const char* mtxFile;
	FILE* stream;// Input stream
	char str[80] = { '\0' };
	char* chr = str;

	PD_MTX_File_u0 = PP_PATH;
	PD_MTX_File_u0 += PP_MTX_PREFIX;
	PD_MTX_File_u0 += PD_problemName;
	PD_MTX_File_u0 += PP_MTX_POSTFIX_U0;
	mtxFile = PD_MTX_File_u0.c_str();
	stream = fopen(mtxFile, "r+b");

	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 0) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout
				<< "Unexpected end of file" << endl;
			return false;
		}
		PD_u[j] = strtod(str, &chr);
	}
	fclose(stream);

	return true;
}

static bool Conversion() { // Transformation to inequalities & dimensionality reduction
	static double fvA[PP_MM]; // Free variable coefficients
	static bool Flag[PP_N];		// Flags of free variables to delete
	static int fvEqI;	// Inequality index of free variable
	static bool single;

	for (int jc = 0; jc < PD_n; jc++)
		if (PD_c[jc] == 0 && PD_hi[jc] == PP_INFINITY && PD_lo[jc] == 0)
			Flag[jc] = true;

	for (int jc = 0; jc < PD_n; jc++) {
		if (!Flag[jc])
			continue;
		for (int i = 0; i < PD_m; i++) { // Find corresponding equation
			if (PD_A[i][jc] == 0)
				continue;
			single = true;
			for (int ii = i + 1; ii < PD_m; ii++) // Vertical uniqueness
				if (PD_A[ii][jc] != 0) {
					single = false;
					break;
				}
			if (single)
				fvEqI = i;
			break;
		}

		if (!single) {
			Flag[jc] = false;
		}
		else
			fvA[fvEqI] = PD_A[fvEqI][jc];
	}

	static bool PD_delete[PP_MM]; // Rows to delete
	double s;

	for (int i = 0; i < PD_m; i++) { // Check inconsistent end degenerate equation
		s = 0;
		for (int j = 0; j < PD_n; j++)
			s += fabs(PD_A[i][j]);
		if (s == 0) {
			if (PD_b[i] != 0) {
				if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
					cout
					<< "Inconsistent equation " << i << ": " << s << " = " << PD_b[i] << endl;
				return false;
				PD_delete[i] = true;
			}
		}
	}

	for (int i = 0; i < PD_m; i++) { // Removing degenerate equations
		if (!PD_delete[i]) continue;
		for (int ii = i; ii < PD_m - 1; ii++) {  // Remove null equation
			for (int j = 0; j < PD_n; j++)
				PD_A[ii][j] = PD_A[ii + 1][j];
			fvA[ii] = fvA[ii + 1];
			PD_b[ii] = PD_b[ii + 1];
		}
		PD_m--;
	}

	for (int jc = 0; jc < PD_n; jc++) { // Delete free variables
		if (!Flag[jc])
			continue;
		for (int j = jc; j < PD_n - 1; j++) { // Delete column
			PD_c[j] = PD_c[j + 1];
			PD_lo[j] = PD_lo[j + 1];
			PD_hi[j] = PD_hi[j + 1];
			Flag[j] = Flag[j + 1];
			for (int i = 0; i < PD_m; i++)
				PD_A[i][j] = PD_A[i][j + 1];
		}

		PD_n--;
		jc--;
		for (int i = 0; i < PD_m; i++)
			PD_A[i][PD_n] = 0;
		PD_c[PD_n] = 0;
		PD_lo[PD_n] = 0;
		PD_hi[PD_n] = 0;
	}

	int m = PD_m;
	for (int i = 0; i < m; i++) { // Conversion to inequalities

		if (fvA[i] == 0) { // Equation without free variable => adding inequality.
			for (int j = 0; j < PD_n; j++)
				PD_A[PD_m][j] = -PD_A[i][j];
			PD_b[PD_m] = -PD_b[i];
			PD_m++; assert(PD_m <= PP_MM);
		}
		else {
			if (fvA[i] < 0) { // Free variable is negative => change sign to opposite.
				for (int j = 0; j < PD_n; j++)
					PD_A[i][j] = -PD_A[i][j];
				PD_b[i] = -PD_b[i];
			}
		}
	}

	for (int i = 0; i < PD_m; i++) // Remove negative sign for zero value
		for (int j = 0; j < PD_n; j++)
			if (PD_A[i][j] == 0)
				PD_A[i][j] = 0;

	for (int i = 0; i < PD_n; i++) { // Adding lower bound conditions
		for (int j = 0; j < PD_n; j++)
			PD_A[i + PD_m][j] = 0;
		PD_A[i + PD_m][i] = -1;
		if (PD_lo[i] == 0)
			PD_b[i + PD_m] = 0;
		else
			PD_b[i + PD_m] = -PD_lo[i];
	}
	PD_m += PD_n; assert(PD_m <= PP_MM);

	for (int i = 0; i < PD_n; i++) { // Adding higher bound conditions
		if (PD_hi[i] != PP_INFINITY) {
			for (int j = 0; j < PD_n; j++)
				PD_A[PD_m][j] = 0;
			PD_A[PD_m][i] = 1;
			PD_b[PD_m] = PD_hi[i];
			PD_m++; assert(PD_m <= PP_MM);
		}
	}
	return true;
}

static bool MTX_Save_so(PT_vector_T x, double elapsedTime) {
	const char* mtxFile;
	FILE* stream;// Input stream

	PD_MTX_File_so = PP_PATH;
	PD_MTX_File_so += PP_MTX_PREFIX;
	PD_MTX_File_so += PD_problemName;
	PD_MTX_File_so += PP_MTX_POSTFIX_SO;
	mtxFile = PD_MTX_File_so.c_str();
	stream = fopen(mtxFile, "w");
	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	fprintf(stream, "%c Elapsed time: %.0f\n%d %d\n", '%', elapsedTime, PD_n, 1);

	for (int j = 0; j < PD_n; j++)
		fprintf(stream, "%.16f\n", x[j]);

	fclose(stream);
	return true;
}

inline bool Vector_OnHyperplane // If the point belongs to the Hyperplane with prescigion of PP_EPS_ZERO
(PT_vector_T point, PT_vector_T a, double b, double eps, double* residual) {
	*residual = fabs(Vector_DotProduct(a, point) - b);
	return *residual < eps;
}

// Vector r of orthogonal projection of point z onto Half-space <a,x> <= b
inline double // maxResidual
Vector_OrthogonalProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, double b, PT_vector_T r, double eps, int* exitCode) {
	double factor;
	double aNormSquare = Vector_NormSquare(a); // ||a||^2
	double a_dot_z_minus_b = Vector_DotProduct(a, z) - b; // <a,z> - b

	if (sqrt(aNormSquare) < eps) {
		*exitCode = PP_EXITCODE_DEGENERATE_INEQUALITY;
		Vector_Zero(r);
		return -1;
	}

	if (a_dot_z_minus_b <= -eps * 10) {
		*exitCode = PP_EXITCODE_INSIDE_HALFSPACE;
		Vector_Zero(r);
		return 0;
	};

	if (fabs(a_dot_z_minus_b) < eps) { // <a,z> - b < 0
		*exitCode = PP_EXITCODE_ON_HYPERPLANE;
		Vector_Zero(r);
		return 0;
	}

	factor = -a_dot_z_minus_b / aNormSquare; // (b - <z,a>) / ||a||^2
	Vector_MultiplyByNumber(a, factor, r);
	*exitCode = PP_EXITCODE_NATURAL_PROJECTING;
	return a_dot_z_minus_b;
}

// Vector r of orthogonal projection of point z onto hyperplane <a,x> = b
inline double // maxResidual
Vector_OrthogonalProjectionOntoHyperplane(PT_vector_T z, PT_vector_T a, double b, PT_vector_T r, double eps) {
	double factor;
	double aNormSquare = Vector_NormSquare(a); // ||a||^2
	double a_dot_z_minus_b = Vector_DotProduct(a, z) - b; // <a,z> - b

	assert(sqrt(aNormSquare) >= eps);

	factor = -a_dot_z_minus_b / aNormSquare; // (b - <z,a>) / ||a||^2
	Vector_MultiplyByNumber(a, factor, r);
	return fabs(a_dot_z_minus_b);
}

// Distance from point z to halfspace <a,x> <= b: |<a,z> - b|/||a||
inline double Vector_DistanceToHalfspace(PT_vector_T z, PT_vector_T a, double b) {
	double aNorm = sqrt(Vector_NormSquare(a)); // ||a||
	double a_dot_z_minus_b; // <a,z> - b

	if (aNorm < PP_EPS_ZERO) //Degenerate equation
		return 0;

	a_dot_z_minus_b = Vector_DotProduct(a, z) - b; // <a,z> - b
	if (a_dot_z_minus_b <= PP_EPS_ZERO) // Point belongs to halfspace
		return 0;

	return a_dot_z_minus_b / aNorm;
}

// Vector o of oblique projection of point z onto Half-space <a,x> <= b with respect to vector g
inline void Vector_ObliqueProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, double b, PT_vector_T g, PT_vector_T o, int* exitCode) {
	double a_dot_g;	// <a,g>
	double a_dot_z_minus_b;	// <a,z> - b
	double factor;	// (b - <a,z>) / <a,g>

	a_dot_z_minus_b = Vector_DotProduct(a, z) - b; // <a,z> - b
	if (a_dot_z_minus_b <= -PP_EPS_ZERO) { // <a,z> - b < 0
		*exitCode = PP_EXITCODE_INSIDE_HALFSPACE;
		for (int j = 0; j < PD_n; j++)
			o[j] = 0;
		return;
	}

	if (fabs(a_dot_z_minus_b) < PP_EPS_ZERO) { // <a,z> - b < 0
		*exitCode = PP_EXITCODE_ON_HYPERPLANE;
		for (int j = 0; j < PD_n; j++)
			o[j] = 0;
		return;
	}

	a_dot_g = Vector_DotProduct(a, g); // <a,g>
	if (fabs(a_dot_g) < PP_EPS_ZERO) {
		*exitCode = PP_EXITCODE_PARALLEL;
		for (int j = 0; j < PD_n; j++)
			o[j] = PP_INFINITY;
		return;
	}

	if (a_dot_g >= PP_EPS_ZERO) {
		*exitCode = PP_EXITCODE_RECESSIVE;
		for (int j = 0; j < PD_n; j++)
			o[j] = PP_INFINITY;
		return;
	}

	factor = a_dot_z_minus_b / a_dot_g; // (<a,z> - b) / <a,g>

	// Oblique projection vector: o = -(<a,z> - b)g/<a, g> = -factor * r
	for (int j = 0; j < PD_n; j++)
		o[j] = -factor * g[j];

	*exitCode = PP_EXITCODE_NATURAL_PROJECTING;
	return;
};

inline double Distance(PT_vector_T x, PT_vector_T y) {
	PT_vector_T z;
	Vector_Subtraction(x, y, z);
	return Vector_Norm(z);
}

inline void MakeObjVector(PT_vector_T c, double length, PT_vector_T objVector) { // Calculating Objective Vector with given length
	double c_norm = Vector_Norm(c);
	Vector_MultiplyByNumber(c, length / c_norm, objVector);
}

inline void SkipComments(FILE* stream) {
	fpos_t pos;	// Position in the input stream
	fscanf(stream, "\n");
	fgetpos(stream, &pos);
	while (getc(stream) == '%') {
		while (getc(stream) != 10);
		fscanf(stream, "\n");
		fgetpos(stream, &pos);
	};
	fsetpos(stream, &pos);
}

inline bool MovingOnSurface(PT_vector_T directionVector, PT_vector_T point) {
	double leftBound = 0;
	double rightBound = PP_DBL_MAX;
	double factor;
	PT_vector_T shiftedPoint;

	if (Vector_Norm(directionVector) < PP_EPS_ZERO)
		return false;

	PD_shiftLength = 100;
	factor = PD_shiftLength;

	while (rightBound - leftBound >= PP_EPS_ZERO) {
		Shift(point, directionVector, PD_shiftLength, shiftedPoint);
		if (PointInPolytope(shiftedPoint)) {
			leftBound = PD_shiftLength;
			PD_shiftLength += factor;
		}
		else {
			rightBound = PD_shiftLength;
			factor /= 2;
			PD_shiftLength -= factor;
		}
	}

	Shift(point, directionVector, PD_shiftLength - factor, shiftedPoint);

	if (Vector_Equal(point, shiftedPoint, PP_EPS_ZERO))
		return false;

	assert(PointInPolytope(shiftedPoint));
	Vector_Copy(shiftedPoint, point);
	return true;
}

inline double PolytopeResidual(PT_vector_T x) { // Measure of distance from point to polytope
	double sum = 0;
	int nonzero = 0;
	double distance;

	for (int i = 0; i < PD_m; i++) {
		distance = Vector_DistanceToHalfspace(x, PD_A[i], PD_b[i]);
		if (distance > 0) {
			sum += distance;
			nonzero++;
		}
	}
	if (nonzero != 0)
		sum /= nonzero;
	return sum;
}

inline double relativeError(double trueValue, double calcValue) {
	if (fabs(trueValue) >= PP_EPS_ZERO)
		return fabs(calcValue - trueValue) / fabs(trueValue);
	else
		return fabs(calcValue - trueValue);
}

inline void CodeToSubset(int code, int subset[PP_MM], int* ma) {
	*ma = 0;
	for (int i = 0; i < PD_mh; i++) {
		if (code % 2 == 1) {
			subset[*ma] = PD_index_includingHyperplanes[i];
			(*ma)++; assert(*ma <= PP_MM);
		}
		code /= 2;
		if (code == 0)
			break;
	}
};

inline void Print_VectorOnHyperplanes(PT_vector_T x) {
	for (int i = 0; i < PD_m; i++) {
			double residual;
		if (Vector_OnHyperplane(x, PD_A[i], PD_b[i], PP_EPS_MAKE_H_PLANE_LIST, &residual))
			cout << i << " ";
	}
	cout << endl;
}

inline void Print_VectorOnActiveHyperplanes(PT_vector_T x) {
	double residual;
	for (int i = 0; i < PD_ma; i++) {
		int ia = PD_index_activeHalfspaces[i];
		if (Vector_OnHyperplane(x, PD_A[ia], PD_b[ia], PP_EPS_ZERO, &residual))
			cout << ia << " ";
	}
	cout << endl;
}

inline void Print_Number_of_subsets(PT_vector_T x) {
	int mh = 0;
	int K;
	for (int i = 0; i < PD_m; i++) {
		double residual;
		if (Vector_OnHyperplane(x, PD_A[i], PD_b[i], PP_EPS_MAKE_H_PLANE_LIST, &residual))
			mh++;
	}
	K = (int)pow(2, (double)mh) - 1;
	cout << K << endl;
}

inline void Preparation_for_Movement(PT_vector_T u) {
	MakeHyperplaneList(u, &PD_mh);
	PD_K = (int)pow(2, (double)PD_mh) - 1;
	if (PD_K > PP_KK) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Parameter PP_KK = " << PP_KK << " must be greater than or equal to " << PD_K << "\n";
		abort();
	}
	MakeHyperplaneSubsetCodeList(PD_mh, &PD_K);
	PD_objF_u = ObjF(PD_u);
	PD_objF_initialValue = PD_objF_u;
}