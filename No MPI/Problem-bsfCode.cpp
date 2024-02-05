/*==============================================================================
Project: LiFe
Theme: Surface movement method (No MPI)
Module: Problem-bsfCode.cpp (Implementation of Problem Code)
Prefix: PC
Author: Leonid B. Sokolinsky
This source code has been produced with using BSF-skeleton
==============================================================================*/
#include "Problem-Data.h"			// Problem Types 
#include "Problem-Forwards.h"		// Problem Function Forwards
#include "Problem-bsfParameters.h"	// BSF-skeleton parameters
#include "BSF-SkeletonVariables.h"	// Skeleton Variables
using namespace std;

void PC_bsf_SetInitParameter(PT_bsf_parameter_T* parameter) {
	for (int j = 0; j < PD_n; j++) // Generating initial approximation
		parameter->x[j] = PD_u[j];
}

void PC_bsf_Init(bool* success) {
	*success = MTX_Load__Problem();
	if (*success == false)
		return;

	if (!PointInPolytope(PD_u)) {
		// No MPI
		cout 
			<< "Starting point does not belong to the feasible polytope with precision PP_EPS_ZERO = " << PP_EPS_ZERO << "!!!\n";
		abort();
	}

	MakeHyperplaneList(&PD_mh);

	if (!MakeHyperplaneSubsetCodeList(PD_mh, &PD_K)) {
		*success = false;
		return;
	}

	PD_objF_u = ObjF(PD_u);
	PD_objF_initialValue = PD_objF_u;
}

void PC_bsf_SetListSize(int* listSize) {
	if (PD_K == 0) {
		// No MPI
		cout
			<< "Map-list has zero size!!!\n";
		abort();
	}
	*listSize = PD_K;
}

void PC_bsf_SetMapListElem(PT_bsf_mapElem_T* elem, int i) {
	elem->hyperplaneSubsetCode = &(PD_hyperplaneSubsetCodeList[i]);
}

void PC_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem, int* success) {
	// Map-List index = BSF_sv_addressOffset + BSF_sv_numberInSublist
	int mOld; // Saves value of m before adding opposite inequalities
	int subsetCode = *mapElem->hyperplaneSubsetCode;
	PT_vector_T d;		// direction unit vector
	PT_vector_T u;		// current surface point
	PT_vector_T v;		// v = u + PD_objVector (objVector = PP_OBJECTIVE_VECTOR_LENGTH*e_c)
	PT_vector_T w;		// pseudiprojection of v
	PT_float_T objF_w = -DBL_MAX; // F(w)

#ifdef PP_DEBUG
	cout << "------------------------------------ Map(" << BSF_sv_addressOffset + BSF_sv_numberInSublist << ") ------------------------------------" << endl;
#endif // PP_DEBUG

	mOld = PD_m;
	Vector_Copy(BSF_sv_parameter.x, u);
	PT_float_T objF_u1 = ObjF(u);

#ifdef PP_DEBUG
	// No MPI
	cout << "Subset: {";
#endif // PP_DEBUG

#ifdef PP_DEBUG
	int outpoot = 0;
#endif // PP_DEBUG

	for (int i = 0; i < PD_mh; i++) {
		if (subsetCode % 2 == 1) {
			int ih = PD_index_hyperplanesIncludeSP[i];

#ifdef PP_DEBUG
			if (outpoot > 0) 
				// No MPI
				cout << ", ";
			outpoot++;
#endif // PP_DEBUG

			AddOppositeInequality(ih, &PD_m);

#ifdef PP_DEBUG
			cout << ih;
#endif // PP_DEBUG
		}
		subsetCode /= 2;
	}

	MakeObjVector(PD_c, PP_OBJECTIVE_VECTOR_LENGTH, PD_objVector);

#ifdef PP_DEBUG
	// No MPI
	cout << "}\nObjective vector length : " << Vector_Norm(PD_objVector) << Vector_Norm(PD_objVector) << "\nu =\t    ";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
		// No MPI
		cout << setw(PP_SETW) << u[j];
	if (PP_OUTPUT_LIMIT < PD_n) 
		// No MPI
		cout << " ...";
	// No MPI
	cout << "\tF(u) = " << setw(PP_SETW) << objF_u1 << endl;
#endif // PP_DEBUG

	while (objF_w < objF_u1 + PP_EPS_ZERO) {

		Vector_Addition(u, PD_objVector, v);

		/**
#ifdef PP_DEBUG
		// No MPI
		cout << "v =\t    ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			// No MPI
			cout << setw(PP_SETW) << v[j];
		if (PP_OUTPUT_LIMIT < PD_n) 
			// No MPI
			cout << " ...";
		// No MPI
		cout << "\tF(v) = " << setw(PP_SETW) << ObjF(v) << endl;
#endif // PP_DEBUG /**/

		Pseudoprojection(v, w);

		PD_m = mOld;

		objF_w = ObjF(w);

		if (objF_w < objF_u1 + PP_EPS_ZERO) {

			/*
#ifdef PP_DEBUG
			// No MPI
			cout << "w =\t    ";
			for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
				// No MPI
				cout << setw(PP_SETW) << w[j];
			if (PP_OUTPUT_LIMIT < PD_n) 
				// No MPI
				cout << " ...";
			// No MPI
			cout << "\tF(w) = " << setw(PP_SETW) << ObjF(w) << "\nObjF(u) = " << objF_u1 << " >= ObjF(w) = " << objF_w << endl;
#endif // PP_DEBUG /**/

			if (Vector_Norm(PD_objVector) < PP_EPS_ZERO) {

				for (int j = 0; j < PD_n; j++)
					*reduceElem->nextSurfacePoint[j] = BSF_sv_parameter.x[j];
				reduceElem->objF = objF_u1;

#ifdef PP_DEBUG
				// No MPI
				cout << "u =\t    ";
				for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
					// No MPI
					cout << setw(PP_SETW) << u[j];
				if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
				// No MPI
				cout << "\tF(u) = " << setw(PP_SETW) << objF_u1 << "\nLength of objective vector = " << Vector_Norm(PD_objVector) << " < PP_EPS_ZERO  ===>>> return!!!\n";
#endif // PP_DEBUG /**/
				return;
			}
			Vector_DivideEquals(PD_objVector, 2);

			/**
#ifdef PP_DEBUG
			// No MPI
			cout << "Objective vector length : " << Vector_Norm(PD_objVector) << endl;
#endif // PP_DEBUG /**/
		}
	}

	Vector_Subtraction(w, u, d);
	DirVectorCleanup(d);
	PT_float_T norm_d = Vector_Norm(d);

#ifdef PP_DEBUG
	cout << "w =\t    ";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
		cout << setw(PP_SETW) << w[j];
	if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
	cout << "\tF(w) = " << setw(PP_SETW) << ObjF(w) << endl;

	cout << "w on hyperplanes: ";
	for (int i = 0; i < PD_m; i++) {
		if (Vector_OnHyperplane(w, PD_A[i], PD_b[i]))
			cout << i << " ";
	}
	cout << endl;

	cout << "D = ";
	for (int j = 0; j < PD_n; j++)
		cout << setw(PP_SETW) << d[j];
	cout << endl;
	cout << "\t||w-u|| = " << norm_d << endl;
#endif // PP_DEBUG

	if (norm_d < PP_EPS_ZERO) {
		for (int j = 0; j < PD_n; j++)
			*reduceElem->nextSurfacePoint[j] = BSF_sv_parameter.x[j];
		reduceElem->objF = objF_u1;

#ifdef PP_DEBUG
		cout << "u =\t    ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			cout << setw(PP_SETW) << u[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
		cout << "\tF(u) = " << setw(PP_SETW) << objF_u1 << endl;
		cout << "||w-u|| < PP_EPS_ZERO" << objF_u1 << " >= ObjF(w) = " << objF_w << "  ===>>> return!!!\n";
#endif // PP_DEBUG
		return;
	}

	if (!MovingOnSurface(d, u)) {
		for (int j = 0; j < PD_n; j++)
			*reduceElem->nextSurfacePoint[j] = BSF_sv_parameter.x[j];
		reduceElem->objF = objF_u1;

#ifdef PP_DEBUG
		cout << "u =\t    ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			cout << setw(PP_SETW) << u[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
		cout << "\tF(u) = " << setw(PP_SETW) << objF_u1 << endl;
		cout << "Movement does not affect objective value  ===>>> return!!!\n";
#endif // PP_DEBUG
		return;
	}

	PT_float_T objF_u2 = ObjF(u);

	if (relativeError(objF_u1, objF_u2) < PP_EPS_ZERO) {
		for (int j = 0; j < PD_n; j++)
			*reduceElem->nextSurfacePoint[j] = BSF_sv_parameter.x[j];
		reduceElem->objF = objF_u1;

#ifdef PP_DEBUG
		cout << "u =\t    ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			cout << setw(PP_SETW) << u[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
		cout << "\tF(u) = " << setw(PP_SETW) << objF_u1 << endl;
		cout << "|F(u1)-F(u2)|/|F(u1)| = " << relativeError(objF_u1, objF_u2) << " < PP_EPS_ZERO ===>>> return!!!\n";
#endif // PP_DEBUG

		return;
	}

#ifdef PP_DEBUG
	cout << "u =\t    ";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
		cout << setw(PP_SETW) << u[j];
	if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
	cout << "\tF(u) = " << setw(PP_SETW) << objF_u2 << "\t\t<<==== New edge" << endl;

	cout << "u on hyperplanes: ";
	for (int i = 0; i < PD_m; i++) {
		if (Vector_OnHyperplane(PD_u, PD_A[i], PD_b[i]))
			cout << i << " ";
	}
	cout << endl;
#endif // PP_DEBUG /**/

	for (int j = 0; j < PD_n; j++)
		*reduceElem->nextSurfacePoint[j] = u[j];
	reduceElem->objF = objF_u2;
}

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
	if (x->objF > y->objF) {
		z->objF = x->objF;
		for (int j = 0; j < PD_n; j++)
			*z->nextSurfacePoint[j] = *x->nextSurfacePoint[j];
	}
	else {
		z->objF = y->objF;
		for (int j = 0; j < PD_n; j++)
			*z->nextSurfacePoint[j] = *y->nextSurfacePoint[j];
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

	if (PD_objF_u >= reduceResult->objF - PP_EPS_ZERO) {
		*exit = true;
		return;
	}

	PD_objF_u = reduceResult->objF;
	for (int j = 0; j < PD_n; j++)
		PD_u[j] = *reduceResult->nextSurfacePoint[j];

#ifdef PP_DEBUG
	cout << "The best:\nu =\t    ";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
		cout << setw(PP_SETW) << PD_u[j];
	if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
	cout << "\tF(u) = " << setw(PP_SETW) << PD_objF_u << endl;

	cout << "u on hyperplanes: ";
	for (int i = 0; i < PD_m; i++) {
		PT_float_T residual = fabs(Vector_DotProduct(PD_A[i], PD_u) - PD_b[i]);
		if (residual < PP_EPS_ZERO)
			cout << i << " ";
	}
	cout << endl;
#endif // PP_DEBUG

	* exit = true;
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
	cout << "Number of hyperplane subsets = " << PD_K << endl;
}

void PC_bsf_ParametersOutput(PT_bsf_parameter_T parameter) {
	cout << "\n\n=================================================== SMM ====================================================" << endl;
	cout << "Problem name: " << PD_problemName << endl;
#ifdef PP_USE_LEASTPROJECTION
	cout << "Mode: Least projections " << endl;
#else
	cout << "Mode: Pseudoprojections " << endl;
#endif // PP_USE_LEASTPROJECTION
	cout << "No MPI" << endl;
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
	cout << "Maximum of objF:\t" << PP_OPTIMAL_OBJ_VALUE << endl;
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
	cout << "x0 =\t\t";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++) cout << setw(PP_SETW) << PD_u[j];
	if (PP_OUTPUT_LIMIT < PD_n)
		cout << " ...";
	cout << "\tF(x) = " << setw(PP_SETW) << ObjF(PD_u);
	cout << endl;
	cout << "x0 on hyperplanes: ";
	for (int i = 0; i < PD_m; i++) {
		if (Vector_OnHyperplane(PD_u, PD_A[i], PD_b[i]))
			cout << i << " ";
	}
	cout << endl;
	if (!PointInPolytope(PD_u)) 
		cout << "x0 is outside feasible polytope!!!\n";
	else
		cout << "x0 is inside feasible polytope.\n";
	cout << "-------------------------------------------" << endl;
}

void PC_bsf_CopyParameter(PT_bsf_parameter_T parameterIn, PT_bsf_parameter_T* parameterOutP) {
	for (int j = 0; j < PD_n; j++)
		parameterOutP->x[j] = parameterIn.x[j];
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

	cout << "=============================================" << endl;
	cout << "Elapsed time: " << t << endl;
	cout << "Current objective value: " << PD_objF_u << endl;
	cout << "Optimal objective value: " << PP_OPTIMAL_OBJ_VALUE << endl;
	cout << "Relative error = " << relativeError(PP_OPTIMAL_OBJ_VALUE, PD_objF_u) << endl;
	cout << "=============================================" << endl;

	if (fabs(PD_objF_u - PD_objF_initialValue) < PP_EPS_ZERO) {
		cout << "The initial value of the objective function was not refined!\n";
		return;
	}

		cout << "Surface point:\t";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++) cout << setw(PP_SETW) << PD_u[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << "	...";
		cout << endl;
		cout << "Polytope residual: " << PolytopeResidual(PD_u) << endl;
		cout << "Surface point is on hyperplanes: ";
		for (int i = 0; i < PD_m; i++) {
			if (Vector_OnHyperplane(PD_u, PD_A[i], PD_b[i]))
				cout << i << " ";
		}
		cout << endl;

#ifdef OUTPUT
		if (MTX_Save_sp(PD_u, t))
			cout << "Calculated surface point is saved into file *.sp" << endl;
#endif // OUTPUT
}

void PC_bsf_ProblemOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter, double t) {
	// not used
}

void PC_bsf_ProblemOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter, double t) {
	// not used
}

void PC_bsf_ProblemOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter, double t) {
	// not used
}

void PC_bsf_MainArguments(int argc, char* argv[]) {
// not used
}

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
inline void MakeHyperplaneList(int* mh) {
	*mh = 0;
	for (int i = 0; i < PD_m; i++)
		if (Vector_OnHyperplane(PD_u, PD_A[i], PD_b[i])) {
			PD_index_hyperplanesIncludeSP[*mh] = i;
			(*mh)++;
		}
}

inline bool MakeHyperplaneSubsetCodeList(int mh, int* K) {
	int index;

	*K = (int)pow(2, (double)mh) - 1;
	if (*K > PP_KK) {
		//
		cout << "MakeHyperplaneSubsetCodeList: too much subsets!\n";
		return false;
	}

	for (int k = 0; k < *K; k++) {
		PD_hyperplaneSubsetCodeList[k] = 0;
	}

	for (int k = 1; k <= *K; k++) {
		index = rand() % *K;
		assert(index < *K);
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

	return true;
}

inline void Pseudoprojection(PT_vector_T v, PT_vector_T w) {
	PT_float_T maxResidual;
	int nonZeroCounter;
	PT_vector_T sum_r;

	for (int j = 0; j < PD_n; j++) {
		w[j] = v[j];
	}

	do {
		maxResidual = 0;
		nonZeroCounter = 0;
		for (int j = 0; j < PD_n; j++) sum_r[j] = 0;
			
		for (int i = 0; i < PD_m; i++) {
			int exitcode;
			PT_vector_T r;
			PT_float_T halfspaceResidual =
				Vector_OrthogonalProjectionOntoHalfspace(w, PD_A[i], PD_b[i], r, &exitcode);
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
/**
#ifdef PP_DEBUG
		cout << "w =\t    ";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
			cout << setw(PP_SETW) << w[j];
		if (PP_OUTPUT_LIMIT < PD_n) cout << " ...";
		cout << "\tF(w) = " << setw(PP_SETW) << ObjF(w) << "\tmaxResidual = " << maxResidual << endl;
#endif // PP_DEBUG
/**/
	} while (maxResidual >= PP_EPS_ZERO);
}

inline void AddOppositeInequality(int hyperplaneIndex, int* m) {
	for (int j = 0; j < PD_n; j++) {
		PD_A[*m][j] = -PD_A[hyperplaneIndex][j];
	}
	PD_b[*m] = -PD_b[hyperplaneIndex];
	(*m)++; assert(*m <= PP_MM);
}

inline PT_float_T Vector_DotProduct(PT_vector_T x, PT_vector_T y) {
	PT_float_T sum = 0;
	for (int j = 0; j < PD_n; j++)
		sum += x[j] * y[j];
	return sum;
}

inline PT_float_T Vector_Norm(PT_vector_T x) {
	return sqrt(Vector_NormSquare(x));
}

inline PT_float_T Vector_NormSquare(PT_vector_T x) {
	PT_float_T sum = 0;

	for (int j = 0; j < PD_n; j++) {
		sum += x[j] * x[j];
	}
	return sum;
}

inline bool PointInHalfspace // If the point belongs to the Halfspace with prescigion of PP_EPS_ZERO
(PT_vector_T x, PT_vector_T a, PT_float_T b) {
	return (Vector_DotProduct(a, x) - b <= PP_EPS_ZERO);
}

inline bool PointInPolytope(PT_vector_T x) { // If the point belongs to the polytope with prescigion of PP_EPS_ZERO
	for (int i = 0; i < PD_m; i++) {
		if (!PointInHalfspace(x, PD_A[i], PD_b[i]))
			return false;
	}
	return true;
}

inline void Shift(PT_vector_T point, PT_vector_T directionVector, PT_float_T shiftRate, PT_vector_T shiftedPoint) {
	for (int j = 0; j < PD_n; j++)
		shiftedPoint[j] = point[j] + directionVector[j] * shiftRate;
}

inline void Vector_Copy(PT_vector_T fromPoint, PT_vector_T toPoint) { // toPoint = fromPoint
	for (int j = 0; j < PD_n; j++)
		toPoint[j] = fromPoint[j];
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

inline void Vector_ResetToZero(PT_vector_T x) {  // x = 0
	for (int j = 0; j < PD_n; j++) x[j] = 0;
}

inline void Vector_DivideByNumber(PT_vector_T x, double r, PT_vector_T y) {  // y = x/r
	for (int j = 0; j < PD_n; j++)
		y[j] = x[j] / r;
}

inline void Vector_Round(PT_vector_T x) {
	double floorValue;
	double fractionalPart;
	double sign;
	double absValue;

	for (int j = 0; j < PD_n; j++) {
		if (fabs(x[j]) < PP_EPS_ZERO) {
			x[j] = 0;
			continue;
		}
		absValue = fabs(x[j]);
		sign = x[j] > 0 ? 1 : -1;
		floorValue = floor(absValue);
		fractionalPart = absValue - floorValue;
		if (1 - fractionalPart < PP_EPS_ZERO) {
			x[j] = sign * (floorValue + 1);
			continue;
		}
		if (fractionalPart < PP_EPS_ZERO)
			x[j] = sign * floorValue;
	}
}

inline void DirVectorCleanup(PT_vector_T x) { // Zeroing coordinates less than PP_EPS_ZERO_DIR
	for (int j = 0; j < PD_n; j++)
		if (fabs(x[j]) < PP_EPS_ZERO_DIR)
			x[j] = 0;
}

inline void Vector_Unit(PT_vector_T vector) { // Calculating unit vector
	double normOfVector = Vector_Norm(vector);
	for (int j = 0; j < PD_n; j++) {
		vector[j] /= normOfVector;
	}
};

inline PT_float_T ObjF(PT_vector_T x) {
	PT_float_T s = 0;
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
	if (!MTX_Load_sp(&nor, &noc))
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
		// No MPI
		cout
			<< "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d%d", nor, noc, non) < 3) {
		// No MPI
		cout
			<< "Unexpected end of file " << mtxFile << endl;
		return false;
	}

	if (*nor >= *noc) {
		// No MPI
		cout
			<< "Number of rows m = " << *nor << " must be < " << "Number of columns n = " << *noc << "\n";
		return false;
	}

	if (*noc != PP_N) {
		// No MPI
		cout
			<< "Invalid input data: PP_N must be = " << *noc << "\n";
		return false;
	}

	if (*nor != PP_M) {
		// No MPI
		cout
			<< "Invalid input data: PP_M must be = " << *nor << "\n";
		return false;
	}

	PD_m = *noe = *nor;
	PD_n = *noc;

	if (2 * *nor + *noc > PP_MM) {
		// No MPI
		cout
			<< "Invalid input data: number of inequalities m = " << 2 * *nor + *noc
			<< " must be < PP_MM + 1 =" << PP_MM + 1 << "\n";
		return false;
	}

	for (int k = 0; k < *non; k++) {
		int i, j;

		if (fscanf(stream, "%d%d%s", &i, &j, str) < 3) {
			// No MPI	
			cout
				<< "Unexpected end of file'" << mtxFile << "'." << endl;
			return false;
		}

		i -= 1;
		j -= 1;
		if (i < 0) {
			// No MPI
			cout
				<< "Negative row index in'" << mtxFile << "'.\n" << endl;
			return false;
		}
		if (j < 0) {
			// No MPI
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
		// No MPI
		cout
			<< "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		// No MPI
		cout
			<< "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*noe != *nor) {
		// No MPI
		cout
			<< "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		// No MPI
		cout
			<< "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int i = 0; i < *noe; i++) {
		if (fscanf(stream, "%s", str) < 1) {
			// No MPI
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
		// No MPI
		cout
			<< "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		// No MPI
		cout
			<< "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		// No MPI
		cout
			<< "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		// No MPI
		cout
			<< "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 1) {
			// No MPI
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
		// No MPI
		cout
			<< "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		// No MPI
		cout
			<< "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		// No MPI
		cout
			<< "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		// No MPI
		cout
			<< "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 1) {
			// No MPI
			cout
				<< "Unexpected end of file '" << mtxFile << "'." << endl;
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
		// No MPI
		cout
			<< "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		// No MPI
		cout
			<< "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		// No MPI
		cout
			<< "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		// No MPI
		cout
			<< "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 0) {
			// No MPI
			cout
				<< "Unexpected end of file" << endl;
			return false;
		}
		PD_c[j] = -strtod(str, &chr);
	}
	fclose(stream);

	return true;
}

inline bool MTX_Load_sp(
	int* nor,	// Number of matrix rows
	int* noc	// Number of matrix columns
) {
	const char* mtxFile;
	FILE* stream;// Input stream
	char str[80] = { '\0' };
	char* chr = str;

	PD_MTX_File_sp = PP_PATH;
	PD_MTX_File_sp += PP_MTX_PREFIX;
	PD_MTX_File_sp += PD_problemName;
	PD_MTX_File_sp += PP_MTX_POSTFIX_SP;
	mtxFile = PD_MTX_File_sp.c_str();
	stream = fopen(mtxFile, "r+b");

	if (stream == NULL) {
		// No MPI
		cout
			<< "Failure of opening file '" << mtxFile << "'.\n";
		return false;
	}

	SkipComments(stream);
	if (fscanf(stream, "%d%d", nor, noc) < 2) {
		// No MPI
		cout
			<< "Unexpected end of file'" << mtxFile << "'." << endl;
		return false;
	}
	if (*nor != PD_n) {
		// No MPI
		cout
			<< "Incorrect number of rows in'" << mtxFile << "'.\n";
		return false;
	}
	if (*noc != 1) {
		// No MPI
		cout
			<< "Incorrect number of columnws in'" << mtxFile << "'.\n";
		return false;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%s", str) < 0) {
			// No MPI
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
	static PT_float_T fvA[PP_MM]; // Free variable coefficients
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
	PT_float_T s;

	for (int i = 0; i < PD_m; i++) { // Check inconsistent end degenerate equation
		s = 0;
		for (int j = 0; j < PD_n; j++)
			s += fabs(PD_A[i][j]);
		if (s == 0) {
			if (PD_b[i] != 0) {
				// No MPI
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

static bool MTX_Save_sp(PT_vector_T x, double elapsedTime) {
	const char* mtxFile;
	FILE* stream;// Input stream

	PD_MTX_File_sp = PP_PATH;
	PD_MTX_File_sp += PP_MTX_PREFIX;
	PD_MTX_File_sp += PD_problemName;
	PD_MTX_File_sp += PP_MTX_POSTFIX_SP;
	mtxFile = PD_MTX_File_sp.c_str();
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
(PT_vector_T point, PT_vector_T a, PT_float_T b) {
	return (fabs(Vector_DotProduct(a, point) - b) < PP_EPS_ZERO);
}

// Vector r of orthogonal projection of point z onto Half-space <a,x> <= b
inline PT_float_T // maxResidual
Vector_OrthogonalProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, PT_float_T b, PT_vector_T r, int* exitCode) {
	PT_float_T factor;
	PT_float_T aNormSquare = Vector_NormSquare(a); // ||a||^2
	PT_float_T a_dot_z_minus_b = Vector_DotProduct(a, z) - b; // <a,z> - b

	if (sqrt(aNormSquare) < PP_EPS_ZERO) {
		*exitCode = PP_EXITCODE_DEGENERATE_INEQUALITY;
		for (int j = 0; j < PD_n; j++)
			r[j] = 0;
		return -1;
	}

	if (a_dot_z_minus_b < PP_EPS_ZERO) { // <a,z> - b < 0
		if (a_dot_z_minus_b <= -PP_EPS_ZERO)
			*exitCode = PP_EXITCODE_INSIDE_HALFSPACE;
		else
			*exitCode = PP_EXITCODE_ON_HYPERPLANE;
		for (int j = 0; j < PD_n; j++)
			r[j] = 0;
		return 0;
	}

	factor = -a_dot_z_minus_b / aNormSquare; // (b - <z,a>) / ||a||^2
	for (int j = 0; j < PD_n; j++) // a(b - <z,a>) / ||a||^2
		r[j] = factor * a[j];
	*exitCode = PP_EXITCODE_NATURAL_PROJECTING;
	return a_dot_z_minus_b;
}

// Distance from point z to halfspace <a,x> <= b: |<a,z> - b|/||a||
inline PT_float_T Vector_DistanceToHalfspace(PT_vector_T z, PT_vector_T a, PT_float_T b) {
	PT_float_T aNorm = sqrt(Vector_NormSquare(a)); // ||a||
	PT_float_T a_dot_z_minus_b; // <a,z> - b

	if (aNorm < PP_EPS_ZERO) //Degenerate equation
		return 0;

	a_dot_z_minus_b = Vector_DotProduct(a, z) - b; // <a,z> - b
	if (a_dot_z_minus_b <= PP_EPS_ZERO) // Point belongs to halfspace
		return 0;

	return a_dot_z_minus_b / aNorm;
}

// Vector o of oblique projection of point z onto Half-space <a,x> <= b with respect to vector g
inline void Vector_ObliqueProjectionOntoHalfspace(PT_vector_T z, PT_vector_T a, PT_float_T b, PT_vector_T g, PT_vector_T o, int* exitCode) {
	PT_float_T a_dot_g;	// <a,g>
	PT_float_T a_dot_z_minus_b;	// <a,z> - b
	PT_float_T factor;	// (b - <a,z>) / <a,g>

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

inline PT_float_T Distance(PT_vector_T x, PT_vector_T y) {
	PT_vector_T z;
	Vector_Subtraction(x, y, z);
	return Vector_Norm(z);
}

inline void MakeObjVector(PT_vector_T c, PT_float_T length, PT_vector_T objVector) { // Calculating Objective Vector with given length
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
	int numShiftsSameRate = 0; // Number of shifts with the same length
	double	shiftRate = 1; // Start shift rate
	PT_vector_T shiftedPoint;

#ifdef PP_DEBUG
	cout << "\n------------------------------------ Moving on surface ------------------------------------" << endl;
#endif // PP_DEBUG

	Shift(point, directionVector, shiftRate, shiftedPoint);

	if (relativeError(ObjF(point), ObjF(shiftedPoint)) < PP_EPS_ZERO)
		return false;

	int shiftsNumber = 0;
	while (true) {

		if (shiftsNumber > PP_MAX_SHIFTS_NUMBER) {
#ifdef PP_DEBUG
			cout << "Number of shifts exceeded allowed limit PP_MAX_SHIFTS_NUMBER = " << PP_MAX_SHIFTS_NUMBER << "  ===>>> return!!!\n";
#endif // PP_DEBUG
			return false;
		}
		shiftsNumber++;
/**/
#ifdef PP_DEBUG
			cout << "Shift = " << setw(PP_SETW) << shiftRate << "\tt = ";
			for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PD_n); j++)
				cout << setw(PP_SETW) << shiftedPoint[j];
			if (PP_OUTPUT_LIMIT < PD_n) cout << "	...";
			cout << "\tF = " << setw(PP_SETW) << ObjF(shiftedPoint);
			cout << endl;
#endif // PP_DEBUG
/**/
		if (PointInPolytope(shiftedPoint)) {
			numShiftsSameRate++;
			if (numShiftsSameRate > PP_MAX_NUM_SHIFTS_SAME_LENGTH) {
				shiftRate *= 2;
				numShiftsSameRate = 0;
			}
			Vector_Copy(shiftedPoint, point);
			Shift(point, directionVector, shiftRate, shiftedPoint);
			continue;
		}

		if (shiftRate < PP_EPS_ZERO) {
			return true;
		}

		shiftRate /= 2;
		numShiftsSameRate = 0;
		Shift(point, directionVector, shiftRate, shiftedPoint);
	}
}

inline PT_float_T PolytopeResidual(PT_vector_T x) { // Measure of distance from point to polytope
	PT_float_T sum = 0;
	int nonzero = 0;
	PT_float_T distance;

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

inline double ProblemScale() {
	double problemScale = 0;
	for (int i = 0; i < PD_m; i++) {
		for (int j = 0; j < PD_n; j++) {
			if (fabs(PD_A[i][j]) < PP_EPS_ZERO)
				continue;
			problemScale = PF_MAX(problemScale, fabs(PD_b[i] / PD_A[i][j]));
		}
	}
	return problemScale;
}

inline PT_float_T relativeError(PT_float_T trueValue, PT_float_T calcValue) {
	if (fabs(trueValue) >= PP_EPS_ZERO)
		return fabs(calcValue - trueValue) / fabs(trueValue);
	else
		return fabs(calcValue - trueValue);
}