#ifndef _XMATRIX_H
#define _XMATRIX_H

#include "xvector.h"
#include "xstring.h"
#include "xmath.h"

#ifndef _XMATRIX_STRUCT
#define _XMATRIX_STRUCT
typedef struct {
	size_t rows;
	size_t cols;
	double* m;
}MATRIX;
#endif

#define ROW_MAJOR   (1)

// matrix operations
int matrix_LUfactor(const MATRIX* const A, MATRIX* const R);
int matrix_inverse(const MATRIX* const A, MATRIX* const R);
int matrix_appendRHS(MATRIX* const A, const MATRIX* const B);
int matrix_solveOrthogonal(const MATRIX* const Q, const double* const B, double** const R, size_t* const Rsize);
int matrix_solveSeidel(MATRIX* const A, double* const B, double** const R, size_t* const Rsize, const size_t iter);
int matrix_solveBackward(const MATRIX* const U, const double* const B, double** const R, size_t* const Rsize);
int matrix_solveForward(const MATRIX* const L, const double* const B, double** const R, size_t* const Rsize);
int matrix_obtain3dCoords(MATRIX* const A);

static inline int matrix_abs(MATRIX* const A) {
	if (A == NULL) return ERR_NUL;
	return vector_abs(A->m, A->rows*A->cols);
}

int matrix_EF(MATRIX* const A);
int matrix_REF(MATRIX* const A, const bool is_eform);
double matrix_determinate(const MATRIX* const A, ERR* const err);
int matrix_transpose(MATRIX* const A);

static inline int matrix_negate(MATRIX* const A) {
	if (A == NULL) return ERR_NUL;
	return vector_negate(A->m, A->rows*A->cols);
}

static inline int matrix_add(const MATRIX* const A, const MATRIX* const B, MATRIX* R) {
	size_t Rsize = 0;
	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	R->rows = A->rows;
	R->cols = A->cols;
	return vector_add(A->m, A->rows*A->cols, B->m, B->rows*B->cols, &(R->m), &Rsize);
}
static inline int matrix_subtract(const MATRIX* const A, const MATRIX* const B, MATRIX* R) {
	size_t Rsize = 0;
	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	R->rows = A->rows;
	R->cols = A->cols;
	return vector_subtract(A->m, A->rows*A->cols, B->m, B->rows*B->cols, &(R->m), &Rsize);
}

int matrix_multiply(const MATRIX* const A, const MATRIX* const B, MATRIX* const R);

static inline int matrix_multiply_s(const MATRIX* const A, const float scalar) {
	if (A == NULL) return ERR_NUL;
	return vector_multiply_s(A->m, A->rows*A->cols, scalar, ROW_MAJOR);
}
static inline int matrix_multiplyRow(const MATRIX* const A, const size_t row, const double factor) {
	if (A == NULL) return ERR_NUL;
	return vector_multiply_s((A->m)+(A->cols*row), A->cols, factor, ROW_MAJOR);
}
static inline int matrix_multiplyCol(const MATRIX* const A, const size_t col, const double factor) {
	if (A == NULL) return ERR_NUL;
	return vector_multiply_s((A->m)+col, A->rows*A->cols, factor, A->cols);
}

// matrix_addRow
// matrix_addCol
// matrix_deleteRow
// matrix_deleteCol
static inline int matrix_swapRow(MATRIX* const A, const size_t x, const size_t y) {
	if (A == NULL) return ERR_NUL;
	return vector_swapEntrys(A->m, A->rows*A->cols, x*A->cols, y*A->cols, A->cols, ROW_MAJOR);
}
static inline int matrix_swapCol(MATRIX* const A, const size_t x, const size_t y) {
	if (A == NULL) return ERR_NUL;
	return vector_swapEntrys(A->m, A->rows*A->cols, x, y, A->rows, A->cols);
}

int matrix_init(MATRIX* const A, const size_t rows, const size_t cols, const double val);
int matrix_free_data(MATRIX* const A);

static inline int matrix_setList(MATRIX* const A, const char* const list) {
	if (A == NULL || list == NULL) return ERR_NUL;
	return vector_setList(A->m, A->rows*A->cols, list);
}

static inline int matrix_setEntry(MATRIX* const A, const size_t row, const size_t col, const float val) {
    if (A == NULL) return ERR_NUL;
    if (row > A->rows || col > A->cols) return ERR_PARA;
    return vector_setAll((A->m)+(A->cols*row)+col, 1, val, ROW_MAJOR);
}

static inline int matrix_setAllRow(MATRIX* const A, const size_t row, const float val) {
	if (A == NULL) return ERR_NUL;
	if (row > A->rows) return ERR_PARA;
	return vector_setAll((A->m)+(A->cols*row), A->cols, val, ROW_MAJOR);
}
static inline int matrix_setAllCol(MATRIX* const A, const size_t col, const double val) {
	if (A == NULL) return ERR_NUL;
	if (col > A->cols) return ERR_PARA;
	return vector_setAll(A->m+col, A->cols*A->rows, val, A->cols);
}
int matrix_setAllDiagonals(MATRIX* const A, const double val);

static inline int matrix_setEqualMatrix(MATRIX* const A, const MATRIX* const B) {
	size_t Alength = 0;
	if (A == NULL || B == NULL) return ERR_NUL;
	A->rows = B->rows;
	A->cols = B->cols;
	Alength = B->cols * B->rows;
	return vector_setEqualArray(&A->m, &Alength, B->m, B->cols * B->rows, B->cols * B->rows, ROW_MAJOR);
}

static inline int matrix_setEqualValues(MATRIX* const A, const MATRIX* const B) {
	if (A == NULL || B == NULL) return ERR_NUL;
	if (A->rows != B->rows || A->cols != B->cols) return ERR_DIM;
	return vector_setEntrysEqual(A->m, A->cols*A->rows, B->m, B->cols*B->rows, A->cols*A->rows, ROW_MAJOR);
}
static inline int matrix_setEqualCol(const MATRIX* const A, MATRIX* const R, const size_t col) {
	if (A == NULL || R == NULL) return ERR_NUL;
	return vector_setEntrysEqual(A->m+col, A->rows*A->cols, R->m, R->rows*R->cols, A->rows*A->cols, A->cols);
}
static inline int matrix_setEqualRow(const MATRIX* const A, MATRIX* const R, const size_t row) {
	if (A == NULL || R == NULL) return ERR_NUL;
	return vector_setEntrysEqual((A->m)+(A->cols*row), A->cols, R->m, R->cols, R->cols, ROW_MAJOR);
}

static inline int matrix_getRow(const MATRIX* const A, const size_t row, double** R, size_t* const Rsize) {
	if (A == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	return vector_getEntrys(A->m+(A->cols*row), A->rows*A->cols, R, Rsize, A->cols, ROW_MAJOR);
}
static inline int matrix_getCol(const MATRIX* const A, const size_t col, double** R, size_t* const Rsize) {
	if (A == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	return vector_getEntrys(A->m+col, A->rows*A->cols, R, Rsize, A->rows, A->cols);
}

int matrix_getDiagonal(const MATRIX* const A, double** R, size_t* const Rsize);
int matrix_getCofactor(const MATRIX* const A, const size_t row, const size_t col, MATRIX* const R);

static inline double matrix_retRowMin(const MATRIX* const A, const size_t row) {
	if (A == NULL) {	return 0;}
	return vector_retMin((A->m)+(A->cols*row), A->cols, ROW_MAJOR);
}
static inline double matrix_retColMin(const MATRIX* const A, const size_t col) {
	if (A == NULL) {	return 0;}
	return vector_retMin(A->m+col, A->rows*A->cols, A->cols);
}

static inline double matrix_retRowMax(const MATRIX* const A, const size_t row) {
	if (A == NULL) {	return 0;}
	return vector_retMax((A->m)+(A->cols*row), A->cols, ROW_MAJOR);
}
static inline double matrix_retColMax(const MATRIX* const A, const size_t col) {
	if (A == NULL) {	return 0;}
	return vector_retMax(A->m+col, A->rows*A->cols, A->cols);
}

double matrix_retSparsity(const MATRIX* const A);
double matrix_retTrace(const MATRIX* const A);

// matrix_isIndependent
bool matrix_isInvertible(const MATRIX* const A);
bool matrix_isOrthonormal(const MATRIX* const A);
bool matrix_isOrthogonal(const MATRIX* const A);
bool matrix_isStochastic(const MATRIX* const A);
bool matrix_isLower(const MATRIX* const A);
bool matrix_isUpper(const MATRIX* const A);
bool matrix_isStrictDiagDom(const MATRIX* const A);

static inline bool matrix_isEqual(const MATRIX* const A, const MATRIX* const B) {
	if (A == NULL || B == NULL) return ERR_NUL;
	if (A->cols != B->cols || A->rows != B->rows) return false;
	return vector_isEqual(A->m, A->cols*A->rows, B->m, B->cols*B->rows);
}
static inline bool matrix_isZero(const MATRIX* const A) {
	if (A == NULL) return ERR_NUL;
	return vector_isZero(A->m, A->rows*A->cols);
}
bool matrix_isIdentity(const MATRIX* const A);
bool matrix_isSymmetric(const MATRIX* const A);

#endif