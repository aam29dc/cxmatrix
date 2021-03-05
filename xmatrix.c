#include "xmatrix.h"

static int matrix_getGAVRow(const MATRIX* const A, const size_t row, const size_t col, size_t* const pos);
static int matrix_zeroBelowPivot(MATRIX* const A, const size_t row, const size_t col);
static int matrix_zeroAbovePivot(MATRIX* const A, const size_t row, const size_t col);

int matrix_appendRHS(MATRIX* const A, const MATRIX* const B) {
	//append on right hand side of matrix A, the matrix B, for [A | B]
	MATRIX temp = { 0 };
	size_t i = 0;
	size_t j = 0;
	if (A == NULL || B == NULL) return ERR_NUL;
	if (A->rows != B->rows) return ERR_DIM;

	if (matrix_init(&temp, A->rows, A->cols + B->cols)) return ERR_INIT;
	CLEAR_MATRIX(&temp, 0);

	//put A on LHS of temp
	for (; i < A->rows * A->cols; i++) {
		if (i != 0 && (i % A->cols == 0)) j += B->cols;		//skip b cols of [A | B]
		temp.m[j] = A->m[i];
		j++;
	}

	j = A->cols;

	//put B on RHS of temp
	for (i = 0; i < B->rows * B->cols; i++) {
		if(i!=0 && (i % B->cols == 0)) j += A->cols;
		temp.m[j] = B->m[i];
		j++;
	}

	if (matrix_setEqualMatrix(A, &temp)) return ERR_INIT;
	matrix_free_data(&temp);

	return 0;
}

int matrix_solveOrthogonal(const MATRIX* const Q, const double* const B, double** const R, size_t* const Rsize) {
	size_t i = 0;
	double denominator = 0;
	double* col = 0;
	size_t colsize = 0;

	if (Q == NULL || B == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (matrix_isOrthogonal(Q) == false) return ERR_PARA;

    	REALLOCATE(*R, *Rsize, Q->rows);

	for (;i<Q->rows;i++){
		matrix_getCol(Q,i,&col,&colsize);
		(*R)[i] = vector_dotProduct(B,col,colsize);
		/* if matrix is orthonormal, then denom = 1 for all, and this step can be skipped */
		if ((denominator = vector_dotProduct(col,col,colsize)) == 0) { return ERR_DIVZ;}
		else { (*R)[i] /= denominator; }
	}

	free(col);

	return 0;
}

int matrix_solveBackward(const MATRIX* const U, const double* const B, double** const R, size_t* const Rsize) {
	//Ar=b
	int i = 0;
	size_t j = 0;

	if (U == NULL || B == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (matrix_isUpper(U) == false) return ERR_PARA;

    	REALLOCATE(*R, *Rsize, U->rows);

	for (i = U->rows-1; i >= 0; i--) {
		if (U->m[(U->cols*i)+i] != 0) {	//if coef in U is zero then skip, r value will stay zero
			(*R)[i] = B[i];
			// negative increment sum S: from:(j=2) down to:( i+1): S(x_j)*(a_ij)
			for(j=U->rows-1;(int)j>i;j--){
				(*R)[i] += (*R)[j] * (U->m[(U->cols*i)+j]);
			}
			(*R)[i] /= U->m[(U->cols*i)+i];
		}
	}

	return 0;
}

int matrix_solveForward(const MATRIX* const L, const double* const B, double** const R, size_t* const Rsize) {
	//Ar=b
	size_t i = 0;
	size_t j = 0;

	if (L == NULL || B == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (matrix_isLower(L) == false) return ERR_PARA;

    	REALLOCATE(*R, *Rsize, L->rows);

	for(;i<L->rows-1;i++){
		if (L->m[(L->cols*i)+i] != 0) {	//if coef in A is zero then skip, r value will stay zero
			(*R)[i] = B[i];
			for (j=0; j < i-1;j++) {
				(*R)[i] += (*R)[j] * (L->m[(L->cols*i)+j]);
			}
			(*R)[i] /= L->m[(L->cols*i)+i];
		}
	}

	return 0;
}

int matrix_solveSeidel(MATRIX* const A, double* const B, double** const R, size_t* const Rsize, const size_t iter) {
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	double* prev_iter = { 0 };

	if (A == NULL || B == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (A->rows != A->cols) return ERR_DIM;
	if (iter <= 0) return ERR_PARA;
	if (matrix_isStrictDiagDom(A) == false) return ERR_PARA;		// otherwise check if diagonal entries are non-zero

    	REALLOCATE(*R, *Rsize, A->rows);

	if ((prev_iter = (double*)malloc(sizeof(double)*(A->rows))) == NULL) return ERR_INIT;

	for (;k<iter;k++){
		if (k != 0 && vector_setEntrysEqual(prev_iter, A->rows, *R, *Rsize, *Rsize, ROW_MAJOR)) return ERR_FUNC;

		for (i = 0;i < A->rows;i++){
			if (A->m[(A->cols*i)+i] != 0){
				(*R)[i] = B[i];
				for (j = 0;j < A->rows;j++){
					if(j == i) continue;
					(*R)[i] -= A->m[(A->cols*i)+j] * ((*R)[j]);
				}
				(*R)[i] /= A->m[(A->cols*i)+i];
			}
			else return ERR_PARA;
		}
		if (vector_isEqual(*R, *Rsize, prev_iter, *Rsize) == true) goto converged;		// prev vector is equal to current
	}

	converged:
	free(prev_iter);

	return 0;
}

int matrix_obtain3dCoords(MATRIX* const A) {
	// divides each column vector by its 4th entry
	size_t i = 0;
	size_t j = 0;
	if (A == NULL) return ERR_NUL;
	if (A->rows != 4 || A->cols == 0) return ERR_DIM;

	for (j = 0; j < A->cols; j++) {
		for (i = 0; i < A->rows - 1; i++) {
			if (((A->cols * 3) + j) == 0) break;			// if 4th entry of col vector is 0, skip
			A->m[(i * A->cols) + j] /= A->m[(A->cols * 3) + j];
		}
		A->m[(A->cols * 3) + j] = 1;
	}

	return 0;
}

static int matrix_getGAVRow(const MATRIX* const A, const size_t row, const size_t col, size_t* const pos) {
	// return the row # of the greatest absolute value using index(row,col) as first entry of [[sub matrix]]
	size_t i = 0;
	double prev = 0;
	double next = 0;

	if (A == NULL || pos == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (row >= A->rows || col >= A->cols) return ERR_PARA;

	prev = xabsolf(A->m[(row * A->cols) + col]);

	for (; i < A->rows - row; i++) {
		next = xabsolf(A->m[((i + row) * A->cols) + col]);
		if (next > prev) {
			prev = next; *pos = i + row;
		}
	}

	return 0;
}

static int matrix_zeroBelowPivot(MATRIX* const A, const size_t row, const size_t col) {
	size_t i = 0;
	size_t j = 0;
	double lcoef = 1;		// leading coef of pivot row
	double factor = 1;		// factor of the row to be reduced

	if (A == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (row >= A->rows || col >= A->cols) return ERR_PARA;

	lcoef = A->m[(row * A->cols) + col];
	if (lcoef != 0) {		//	dont divide by zero
		for (; j < A->rows - row - 1; j++) {
			factor = A->m[((row + 1 + j) * A->cols) + col];
			if (factor != 0) {					// skip row if factor is zero
				for (i = 0; i < A->cols - col; i++) {
					A->m[((row + 1 + j) * A->cols) + col + i] -= factor * (A->m[(row * A->cols) + col + i] / lcoef);
				}
			}
		}
	}
	return 0;
}

static int matrix_zeroAbovePivot(MATRIX* const A, const size_t row, const size_t col) {
	size_t i = 0;
	size_t j = 0;
	// leading coef of pivot row is assumed to be 1
	double factor = 1;			// factor of the row to be reduced

	if (A == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (row == 0) return ERR_PARA;

	for (; j < row; j++) {
		factor = A->m[((row - 1 - j) * A->cols) + col];
		if (factor != 0) {		// skip row if factor is zero
			for (i = 0; i < A->cols - col; i++) {
				//only cols to the right above the pivot are reduced, left cols assumed to be zero
				A->m[((row - 1 - j) * A->cols) + col + i] -= factor * A->m[(row * A->cols) + col + i];
			}
		}
	}

	return 0;
}

int matrix_LUfactor(const MATRIX* const A, MATRIX* const R) {
	//factor only for square matrices although can work for non square matrix...
	size_t i = 0;
	size_t j = 0 ;
	MATRIX T = { 0 };	// dont change A, Temp=A

	if (A == NULL || R == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (A->rows != A->cols) return ERR_DIM;

	if (matrix_setEqualMatrix(&T, A)) return ERR_INIT;
	if (T.m == NULL) return ERR_NUL;

	// R is compact form of LU with L lower form of R and U upper form
	if (matrix_init(R, A->rows, A->cols)) return ERR_INIT;

	//EF(A) without row swaps, from top down, left to right, if 0 is along diagonal LU factor DNE
	while (i < T.cols - 1) {
		if (T.m[(T.cols * i) + i] == 0) return ERR_COMP;			//check if pivot is zero
		if (matrix_setEqualCol(&T, R, i)) return ERR_FUNC;			//copy whole pivot column
		if (matrix_zeroBelowPivot(&T, i, i)) return ERR_FUNC;			//zero entrys under diagonal using pivot
		i++;
	}

	if (matrix_setEqualCol(&T, R, i)) return ERR_FUNC;

	//divide entrys under pivot cols
	i = 0;
	while (i < R->cols) {
		j = i + 1;
		while (j < R->rows) {
			R->m[(R->cols * j) + i] /= R->m[(R->cols * i) + i];
			j++;
		}
		i++;
	}

	matrix_free_data(&T);

	return 0;
}

int matrix_EF(MATRIX* const A) {
	size_t i = 0;
	size_t pos = 0;

	if (A == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;

	while (i < A->cols - 1 && i < A->rows - 1) {
		//find row (j) pivot with greatest absolute value in first col /kth col, ignoring previous row
		if (matrix_getGAVRow(A, i, i, &pos)) return ERR_FUNC;

		//swap pivot row with kth/0th row
		if (matrix_swapRow(A, i, pos)) return ERR_FUNC;

		//negate pivot row _if_ negative
		if (A->m[(i * A->cols) + i] < 0) {
			if (matrix_multiplyRow(A, i, -1)) return ERR_FUNC;
		}

		//zero entrys under the leading entry
		if (matrix_zeroBelowPivot(A, i, i)) return ERR_FUNC;
		i++;
	}
	return 0;
}

int matrix_REF(MATRIX* const A, const bool is_eform) {
	size_t i = 0;

	if (A == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;

	//skip reducing to EF form if already in EF form
	if (is_eform){
		if (matrix_EF(A)) return ERR_FUNC;
	}

	//divide each row by its leading coef to get 1's on the diagonal
	for (; i < A->rows; i++) {
		if (A->m[(i * A->cols) + i] != 0) {			// dont divide by zero
			if (matrix_multiplyRow(A, i, 1 / A->m[(i * A->cols) + i])) return ERR_FUNC;
		}
	}

	//solve for Reduced echelon form by zeroing above each pivot, along diagonal, skip first row
	for (i = 1; i < A->rows; i++) {
		if (matrix_zeroAbovePivot(A, i, i)) return ERR_FUNC;
	}

	return 0;
}

int matrix_inverse(const MATRIX* const A, MATRIX* const R) {
	//AB=C => [c1 ... cn ] = [Ab1 ... Abn], solve Ab1 = c1 instead of using large matrix, [ M ] = [ A | I ] ~ [ I | A_inv ]
	//LU factorization, then forward and back substitution
	//uses a super augmented matrix [A | I]
	size_t i = 0;
	size_t j = 0;
	MATRIX temp = { 0 };

	if (A == NULL || R == NULL) return ERR_NUL;

	//no inverse of non-square matrices
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (A->rows != A->cols) return ERR_DIM;
		//R should be equal to size of A
		//|| A->rows != R->rows || A->cols != R->cols) return ERR_PARA;

	//#123: if A contains a zero col or zero row then A_inv DNE since A doesnt reduce to Identity, return 1;

	if (matrix_init(&temp, A->rows, 2 * A->cols)) return ERR_INIT;
	CLEAR_MATRIX(&temp, 0);
	//copy values of A to temp on LHS for a matrix form [temp] = [A | I]
	for (; j < A->rows; j++) {
		for (i = 0; i < A->cols; i++) {
			temp.m[i + (j * temp.cols)] = A->m[i + (j * A->cols)];
		}
	}

	//put a idenity matrix on the RHS, 1 down the diagonal for [A | I] form
	j = 1;
	for (i = 0; i < A->cols; i++) {
		temp.m[(j * A->cols) + i] = 1;
		j += 2;
	}

	//solve for reduced echelon form, matrix is [ I | A_inv ] form
	if (matrix_REF(&temp,0)) return ERR_FUNC;

	//#123: if LHS != Identity then A_inv DNE, return 1;

	//put RHS of temp into R matrix
	if (matrix_init(R,A->rows,A->cols)) return ERR_INIT;

	j = 1;
	for (i = 0; i < A->rows * A->cols; i++) {
		if (i / 3 == 0) { j += 2; }
		R->m[i] = temp.m[i + (A->cols) * j];
	}

	matrix_free_data(&temp);

	return 0;
}

int matrix_getCofactor(const MATRIX* const A, const size_t row, const size_t col, MATRIX* const R) {
	size_t i = 0;
	size_t j = 0;
	if (A == NULL || R == NULL) return ERR_NUL;

	if (matrix_init(R, A->rows - 1, A->cols - 1)) return ERR_INIT;

	//go through A[i] skipping the corresponding row and cols, put values into R[j]
	while (i < A->rows * A->cols) {
		//skip entire row
		if (i == A->cols * row) {
			i += A->cols;
			continue;
		}

		//skip corresponding cols
		if ((int)(i - col) % (int)(A->cols) == 0) {			//#123: why (int) ?
			i++;
			continue;
		}

		R->m[j] = A->m[i];
		j++;
		i++;
	}

	return 0;
}

double matrix_determinate(const MATRIX* const A, ERR* const err) {
	//doesnt use reduced EF
	//doesnt check for any rows or cols that are all 0, for det(A) = 0, and doesnt check for identical rows or cols, for det(A) = 0
	//formula: det(A) = a11*det(A11)-a12*det(A12)+a13(det(13) - ... + a1n*det(A1n)
	//uses row 0 as coefficients and calls determininate on sub matrix's Amn from row 0
	size_t i = 0;
	MATRIX cof = { 0 };
	double tempf = 0;
	double result = 0;

	//determinate of square matrix of size n>=2 only, since A->rows = A->cols we only check A->rows
	if (A == NULL || err == NULL) {
		return 0;
	}
	if (A->rows == 0 || A->cols == 0) {
		*err = ERR_ZERO;
		return 0;
	}

	//if smallest submatrix size we are finished
	if (A->rows == 2) {
		result = A->m[0] * A->m[3] - A->m[1] * A->m[2];
	}
	else {
		for (; i < A->cols; i++) {
			if (matrix_getCofactor(A, 0, i, &cof)) {
				*err = ERR_FUNC;	//in this case we always go over the first row
				return 0;
			}
			tempf = matrix_determinate(&cof,err);
			if (isOddi(i) == 1) tempf = -tempf;		//checkerboard
			result += (A->m[i]) * tempf;
		}
	}

	matrix_free_data(&cof);

	return result;
}

int matrix_transpose(MATRIX* const A) {
	MATRIX T = { 0 };
	size_t i = 0;
	size_t j = 0;

	if (A == NULL) return ERR_NUL;

	if (A->rows == 1 || A-> cols == 1){         		// if col or row vector, just swap A.cols and A.rows
		xswap(&A->rows,&A->cols,sizeof(size_t));
		return 0;
	}

	if (matrix_init(&T, A->cols, A->rows)) return ERR_INIT;
	CLEAR_MATRIX(&T, 0);

	for (; j < A->cols; j++) {
		for (i = 0; i < A->rows; i++) {
			T.m[i + (j * A->cols)] = A->m[(i * A->cols) + j];
		}
	}

	if (matrix_setEqualMatrix(A, &T)) return ERR_FUNC;

	matrix_free_data(&T);

	return 0;
}
int matrix_multiply(const MATRIX* const A, const MATRIX* const B, MATRIX* const R) {
	// R = A*B, A is left matrix, and B is right matrix
	// A.rows = B.cols , A.cols = B.rows
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	MATRIX temp = { 0 };	// since A or B could = R in parameters

	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (A->cols != B->rows) return ERR_DIM;

	if (matrix_init(&temp, A->rows, B->cols)) return ERR_INIT;
	CLEAR_MATRIX(&temp, 0);

	for (k = 0; k < A->rows; k++) {
		for (j = 0; j < B->cols; j++) {
			for (i = 0; i < A->cols; i++) {
				temp.m[j + (k * B->cols)] += A->m[i + (k * A->cols)] * B->m[(i * B->cols) + j];
			}
		}
	}

	if (matrix_init(R, temp.rows, temp.cols)) return ERR_INIT;
	if (vector_setEntrysEqual(temp.m, temp.rows*temp.cols, R->m, R->rows*R->cols, temp.rows*temp.cols, ROW_MAJOR)) return ERR_FUNC;

	matrix_free_data(&temp);

	return 0;
}

int matrix_init(MATRIX* const A, const size_t rows, const size_t cols) {
	if (A == NULL) return ERR_NUL;
	if (rows == 0 || cols == 0) return ERR_PARA;

	if (A->rows * A->cols < rows*cols || A->rows * A->cols > rows*cols + X_MEMORY_RANGE) {
		if (A->m != NULL) free(A->m);
		if ((A->m = (double*)malloc(sizeof(double)*(rows*cols))) == NULL) return ERR_INIT;
	}

	A->rows = rows;
	A->cols = cols;

	return 0;
}

int matrix_free_data(MATRIX* const A){
	if (A == NULL) return ERR_NUL;
	if (A->m != NULL) free(A->m);
	A->rows = 0;
	A->cols = 0;
	return 0;
}

int matrix_setAllDiagonals(MATRIX* const A, const double val) {
	size_t i = 0;
	size_t n = 0;

	if (A == NULL) return ERR_NUL;

	n = A->cols < A->rows ? A->cols : A->rows;

	for (; i < n; i++) {
		A->m[(A->cols * i) + i] = val;
	}

	return 0;
}

double matrix_retSparsity(const MATRIX* const A) {
	// 1 = zero matrix, 0 = every entry is non zero
	size_t i = 0;
	size_t zeros = 0;

	if (A == NULL) {
		return 0;
	}
	if (A->rows == 0 || A->cols == 0) {
		return 0;
	}

	for (;i<A->cols * A->rows;i++) {
		if( A->m[i] == 0) zeros++;
	}

	return zeros / (A->cols * A->rows);
}

int matrix_getDiagonal(const MATRIX* const A, double** R, size_t* const Rsize) {
	size_t i = 0;
	size_t n = 0;

	if (A == NULL || R == NULL || Rsize == NULL) return ERR_NUL;

	n = A->cols <= A->rows ? A->cols : A->rows;

    	REALLOCATE(*R, *Rsize, n);

	for (;i<n;i++){
		(*R)[i] = A->m[(A->cols*i)+i];
	}

	return 0;
}

bool matrix_isLower(const MATRIX* const A) {
	size_t i = 0;
	size_t j = 0;

	if (A == NULL) return -ERR_NUL;
	if (A->rows != A->cols) return false;

	for (;i<A->rows-1;i++){
		for (j=i+1;j<A->cols;j++){
			if(A->m[(A->cols*i)+j] != 0) return false;
		}
	}

	return true;
}

bool matrix_isUpper(const MATRIX* const A) {
	size_t i = 1;
	size_t j = 0;

	if (A == NULL) return -ERR_NUL;
	if (A->rows != A->cols) return false;

	for (;i<A->rows;i++){
		for (j=0;j<i;j++){
			if (A->m[(A->cols*i)+j] != 0) return false;
		}
	}

	return true;
}

bool matrix_isInvertible(const MATRIX* const A) {
	// not a very fast solution
	MATRIX temp = {0};
	bool result = 0;

	if (A == NULL) return -ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return -ERR_ZERO;
	if (A->rows != A->cols) return false;

	if (matrix_setEqualMatrix(&temp,A)) return -ERR_INIT;
	if (matrix_REF(&temp, 0)) return false; // ERR_FUNC
	result = matrix_isIdentity(&temp);

	matrix_free_data(&temp);

	return result;
}

bool matrix_isOrthonormal(const MATRIX* const A) {
	size_t i = 0;
	size_t j = 0;
	double magnitude = 0;

	if (A == NULL) return -ERR_NUL;

	if (matrix_isOrthogonal(A) == false) return false;

	for(;i<A->rows;i++) {
		magnitude = 0;
		for(j=0;j<A->cols;j++) {
			magnitude += A->m[(A->cols*i)+j] * A->m[(A->cols*i)+j];
		}
		if(magnitude != 1) return false;
	}

	return true;
}

bool matrix_isOrthogonal(const MATRIX* const A) {
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	double sum = 0;

	if(A == NULL) return -ERR_NUL;

	for (;i<A->rows;i++){
		for (j=i+1;j<A->rows;j++){
			sum = 0;
			for (k=0;k<A->cols;k++){
				sum += A->m[(A->cols*i)+k] * A->m[(A->cols*j)+k];
			}
			if (sum != 0) return false;
		}
	}

	return true;
}

bool matrix_isStochastic(const MATRIX* const A) {
	size_t i = 0;
	size_t j = 0;
	double sum = 0;

	if(A == NULL) return -ERR_NUL;
	if(A->rows != A->cols) return -ERR_DIM;

	for(;i<A->cols;i++) {
		sum = 0;
		for(j=0;j<A->rows;j++) {
			sum += A->m[(A->cols*j)+i];
		}
		if(sum!=1) return false;
	}

	return true;
}

bool matrix_isStrictDiagDom(const MATRIX* const A) {
	//checks if the diagonal entrys of a matrix is greater than the absolute value of the entrys of corresponding row
	//non-zero matrix, and diagonal entries are non-zero
	size_t i = 0;
	size_t j = 0;
	double sum = 0;

	if (A == NULL) return -ERR_NUL;

	for (;i<A->rows;i++){
		sum = 0;
		for (j=0;j<A->cols;j++){
			if (i == j) continue;		//skip diagonal from total sum of col
			sum += A->m[(A->cols*i)+j];
		}
		if (A->m[(A->cols*i)+i] <= sum) return false;
	}

	return true;
}

bool matrix_isIdentity(const MATRIX* const A) {
	size_t i = 0;
	size_t j = 0;

	if (A == NULL) return -ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return -ERR_ZERO;

	if (A->rows != A->cols) return false;

	for (; i < A->cols; i++) {		// check diagonal
		if (A->m[(A->cols*i)+i] != 1) return false;
	}

	for (i=0;i<A->rows;i++) {			// check non-diagonals
		for (j=i+1;j<A->cols;j++) {
			if (A->m[(A->cols*i)+j] != 0) return false;
		}
	}

	return true;
}

bool matrix_isSymmetric(const MATRIX* const A) {
	// A^T =? A
	size_t i = 1;
	size_t j = 0;

	if (A == NULL) return -ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return -ERR_ZERO;
	if (A->cols != A->rows) return false;

	for (;i<A->rows-1;i++) {
		for (j=i+1;j<A->cols;j++) {
			if (A->m[(A->cols*i)+j] != A->m[(A->cols*j)+i]) return false;
		}
	}

	return true;
}

double matrix_retTrace(const MATRIX* const A) {
	size_t i = 0;
	double result = 0;

	if (A == NULL) {
		return 0;
	}
	if (A->rows == 0 || A->cols == 0) {
		return 0;
	}

	for (;i < A->cols;i++) {
		result += A->m[(A->cols * i) + i];
	}

	return result;
}
