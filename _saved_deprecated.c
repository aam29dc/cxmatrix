


//
/* 1231284y59834ht934ghuiren394ntg938467j8934hgo3eriny3409yh9-34ng93-4gn934-y7h90345*/
//

const void* g_vector_retMin(const void* const arr, const size_t arr_length, const size_t type_size, compare_func const comp, const size_t incr, ERR* const err);
const void* g_vector_retMax(const void* const arr, const size_t arr_length, const size_t type_size, compare_func comp, const size_t incr, ERR* const err);

const void* g_vector_retMin(const void* const arr, const size_t arr_length, const size_t type_size, compare_func const comp_func, const size_t incr, ERR* const err) {
	size_t i = 0;
	const unsigned char* byte = 0;
	const void* min = 0;

    if (arr == NULL || comp_func == NULL) {
		*err = ERR_NUL;
		return 0;
	}
	if (incr == 0 || type_size == 0) {
		*err = ERR_ZERO;
		return 0;
	}

	byte = arr;
	min = &byte[0];

	for (i = 0; i < arr_length; i += incr){
		if (comp_func(min, &byte[i*type_size]) == true)	min = &byte[i*type_size];
	}
	return min;
}

const void* g_vector_retMax(const void* const arr, const size_t arr_length, const size_t type_size, compare_func const comp_func, const size_t incr, ERR* const err){
    size_t i = 0;
    const unsigned char* byte = 0;
    const void* max = 0;

    if (arr == NULL || comp_func == NULL) {
		*err = ERR_NUL;
		return 0;
	}
	if (incr == 0 || type_size == 0) {
		*err = ERR_ZERO;
		return 0;
	}

    byte = arr;
    max = &byte[0];

    for (i = 0; i < arr_length; i += incr){
        if (comp_func(max,&byte[i*type_size]) == false) max = &byte[i*type_size];
    }
    return max;
}

//
/* 1231284y59834ht934ghuiren394ntg938467j8934hgo3eriny3409yh9-34ng93-4gn934-y7h90345*/
//

int g_vector_negate(void* const arr, const size_t length, const size_t type_size);
int g_vector_abs(void* const arr, const size_t length, const size_t type_size);

int g_vector_negate(void* const arr, const size_t length, const size_t type_size) {
	size_t i = 0;
	unsigned char* byte = 0;

	if (arr == NULL) return ERR_NUL;
	if (type_size == 0) return ERR_ZERO;

	byte = arr;

	for (i = 0;i < length; i++){
        byte[i*type_size] = -byte[i*type_size];
	}

	return 0;
}

int g_vector_abs(void* const arr, const size_t length, const size_t type_size) {
	size_t i = 0;
	unsigned char* byte = 0;

	if (arr == NULL) return ERR_NUL;
	if (type_size == 0) return ERR_ZERO;

	byte = arr;

	for (i = 0;i < length; i++){
		if (byte[i*type_size] < 0){
            byte[i*type_size] = -byte[i*type_size];
		}
	}

	return 0;
}

//
/* 1231284y59834ht934ghuiren394ntg938467j8934hgo3eriny3409yh9-34ng93-4gn934-y7h90345*/
//

int matrix_setEqualCol(const MATRIX* const A, MATRIX* const R, const size_t col) {
	size_t i = 0;

	if (A == NULL || R == NULL) return ERR_NUL;
	if (A->rows != R->rows || A->cols != R->cols) return ERR_DIM;
	if (col > A->cols) return ERR_PARA;


	for (; i < A->rows; i++) {
		R->m[(i * A->cols) + col] = A->m[(i * A->cols) + col];
	}

	return 0;
}

int vector_setEntrysEqual(const double* const A, const size_t Alength, double* const R, const size_t Rlength, const size_t length) {
	size_t i = 0;

	if (A == NULL || R == NULL) return ERR_NUL;
	if (length > Alength || length > Rlength) return ERR_PARA;

	for (; i < length; i++) {
		R[i] = A[i];
	}

	return 0;
}

int vector_multiply_s(double* const A, const size_t length, const double scalar){
	size_t i = 0;
	if (A == NULL) return ERR_NUL;

	for(;i < length;i++){
		A[i] *= scalar;
	}

	return 0;
}

static inline int matrix_multiply_s(const MATRIX* const A, const float scalar){
	return vector_multiply_s(A->m,A->rows*A->cols,scalar);
}
static inline int matrix_multiplyRow(const MATRIX* const A, const size_t row, const float factor){
	return vector_multiply_s((A->m)+(A->cols*row), A->cols, factor);
}

int matrix_swapRow(MATRIX* const A, const size_t x, const size_t y) {
	size_t i = 0;
	double temp = 0;

	if (A == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (x == y) return ERR_PARA;

	for (; i < A->cols; i++) {
		temp = A->m[i + (x * A->cols)];
		A->m[i + (x * A->cols)] = A->m[i + (y * A->cols)];
		A->m[i + (y * A->cols)] = temp;
	}
	return 0;
}

int matrix_swapCol(MATRIX* const A, const size_t x, const size_t y) {
	size_t i = 0;
	double temp = 0;

	if (A == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (x == y) return ERR_PARA;

	for (; i < A->rows; i++) {
		temp = A->m[x + (i * A->cols)];
		A->m[x + (i * A->cols)] = A->m[y + (i * A->cols)];
		A->m[y + (i * A->cols)] = temp;
	}
	return 0;
}

int matrix_setAllCol(MATRIX* const A, const size_t col, const double val) {
	size_t i = 0;

	if (A == NULL) return ERR_NUL;
	if (A->cols < col) return ERR_PARA;

	for (; i < A->rows; i++) {
		A->m[(i * A->cols) + col] = val;
	}
	return 0;
}

#define vector_lengthx(A,length,err)	vector_dotProduct((A).m, (B).m, length, err)

int matrix_getRow(const MATRIX* const A, const size_t row, double** R, size_t* const Rsize) {
	size_t i = 0;

	if (A == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (row > A->rows) return ERR_PARA;

	if (*Rsize != A->cols){
		if (*R != NULL) free(*R);
		if ((*R = (double*)malloc(sizeof(double)*A->cols)) == NULL) return ERR_INIT;
		*Rsize = A->cols;
	}

	for (; i < A->cols; i++) {
		*R[i] = A->m[(A->cols*row)+i];
	}

	return 0;
}

int matrix_getCol(const MATRIX* const A, const size_t col, double** R, size_t* const Rsize) {
	size_t i = 0;

	if (A == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (col > A->cols) return ERR_PARA;

	if (*Rsize != A->rows){
		if (*R != NULL) free(*R);
		if ((*R = (double*)malloc(sizeof(double)*A->rows)) == NULL) return ERR_INIT;
		*Rsize = A->rows;
	}

	for (; i < A->rows; i++) {
		*R[i] = A->m[(A->cols*i)+col];
	}

	return 0;
}

double vector_retMin(const double* const A, const size_t length, ERR* const err) {
	size_t i = 0;
	double min = 0;

	if (A == NULL) {
		*err = ERR_NUL;
		return 0;
	}

	min = A[0];

	for (; i < length; i++) {
		if (min > A[i]) min = A[i];
	}

	return min;
}

double matrix_retColMin(const MATRIX* const A, const size_t col, ERR* const err) {
	size_t i = 0;
	double min = 0;

	if (A == NULL) { 
		*err = ERR_NUL;
		return 0;
	}
	if (A->rows == 0 || A->cols == 0) {
		*err = ERR_ZERO;
		return 0;
	}
	if (col > A->cols) {
		*err = ERR_PARA;
		return 0;
	}

	min = A->m[col];

	for (; i < A->rows; i++) {
		if (min < A->m[col + A->cols * i]) min = A->m[col + A->cols * i];
	}

	return min;
}

double vector_retMax(const double* const A, const size_t length, ERR* const err) {
	size_t i = 0;
	double max = 0;

	if (A == NULL) { 
		*err = ERR_NUL;
		return 0;
	}

	max = A[0];

	for (; i < length; i++) {
		if (max < A[i]) max = A[i];
	}

	return max;
}

double matrix_retColMax(const MATRIX* const A, const size_t col, ERR* const err) {
	size_t i = 0;
	double max = 0;

	if (A == NULL) { 
		*err = ERR_NUL;
		return 0;
	}
	if (A->rows == 0 || A->cols == 0) { 
		*err = ERR_ZERO;
		return 0;
	}
	if (col > A->cols) {
		*err = ERR_PARA;
		return 0;
	}

	max = A->m[col];

	for (; i < A->rows; i++) {
		if (max < A->m[col + A->cols*i]) max = A->m[col + A->cols * i];
	}

	return max;
}

int matrix_setEqualValues(MATRIX* const A, const MATRIX* const B) {
	size_t i = 0;
	//matrices assumed to be equal sizes
	if (A == NULL || B == NULL) return ERR_NUL;
	if (A->rows != B->rows || A->cols != B->cols) return ERR_DIM;

	for (; i < A->rows * A->cols; i++) {
		A->m[i] = B->m[i];
	}
	return 0;
}

int matrix_setEqualMatrix(MATRIX* const A, const MATRIX* const B) {
	//	MATRIX A = B
	size_t i = 0;

	if (A == NULL || B == NULL) return ERR_NUL;
	if (B->rows == 0 || B->cols == 0) return ERR_ZERO;

	if (A->m != NULL) free(A->m);
	A->rows = B->rows;
	A->cols = B->cols;

	if ((A->m = (double*)malloc(sizeof(double) * (B->rows * B->cols))) == NULL) return ERR_MEM;

	for (; i < B->rows * B->cols; i++) {
		A->m[i] = B->m[i];
	}

	return 0;
}

BOOL matrix_isEqual(const MATRIX* const A, const MATRIX* const B) {
	size_t i = 0;

	if (A == NULL || B == NULL) return -ERR_NUL;

	if ((A->rows != B->rows) || (A->cols != B->cols)) return FALSE;
	for (; i < A->rows * A->cols; i++) {
		if (A->m[i] != B->m[i]) return FALSE;
	}
	return TRUE;
}

//
/* 1231284y59834ht934ghuiren394ntg938467j8934hgo3eriny3409yh9-34ng93-4gn934-y7h90345*/
//

#define vector_magnitude(A, length, err)  vector_length(A, length, err)
#define matrix_abs(A)   vector_abs(A, (A).rows * (A).cols
#define matrix_negate(A)    vector_negate((A).m, (A).cols * (A).rows)
#define matrix_add_m(A, B, R, X)    vector_add_m((A).m, (A).rows*(A).cols,(B).m, (B).rows*(B).cols, (R).m, (R).rows*(R).cols, X)
#define matrix_add(A, B, R)         matrix_add_m(A, B, R, 0)
#define matrix_subract(A, B, R)     matrix_add_m(A, B, R, 1)
#define matrix_multiply_s(A, s)  vector_multiply_s((A).m,(A).rows*(A).cols,s)
#define matrix_multiplyRow(A, row, factor)    vector_multiply_s(((A).m)+((A).cols*row), (A).cols, factor)
#define matrix_setList(A,list)  vector_setList((A).m,(A).rows*(A).cols,list)
#define matrix_setAllRow(A, row, val) vector_setAll(((A).m)+((A).cols*row), (A).cols, val)
#define matrix_setEqualRow(A,R,row)    vector_setEntrysEqual((A).m+((A).cols*row),(A).cols,(R).m,(R).cols,(R).cols)     // reversed order
#define matrix_retRowMin(A, row, err)   vector_retMin(((A).m)+((A).cols*row),(A).cols,err)
#define matrix_retRowMax(A, row, err)   vector_retMax(((A).m)+((A).cols*row),(A).cols,err)
#define matrix_isZero(A)    vector_isZero((A).m, (A).rows*(A).cols)

//
/* 1231284y59834ht934ghuiren394ntg938467j8934hgo3eriny3409yh9-34ng93-4gn934-y7h90345*/
//

int matrix_getRow(const MATRIX* const A, const size_t row, double** R, size_t* const Rsize) {
	size_t i = 0;

	if (A == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (row > A->rows) return ERR_PARA;

	if (*Rsize != A->cols){
		if (*R != NULL) free(*R);
		if ((*R = (double*)malloc(sizeof(double)*A->cols)) == NULL) return ERR_INIT;
		*Rsize = A->cols;
	}

	for (; i < A->cols; i++) {
		*R[i] = A->m[(A->cols*row)+i];
	}

	return 0;
}

int matrix_setEqualRow(const MATRIX* const A, MATRIX* const R, const size_t row) {
	size_t i = 0;

	if (A == NULL || R == NULL) return ERR_NUL;
	if (A->rows != R->rows || A->cols != R->cols) return ERR_DIM;
	if (row > A->rows) return ERR_PARA;


	for (; i < A->cols; i++) {
		R->m[i + (row * A->cols)] = A->m[i + (row * A->cols)];
	}

	return 0;
}

double matrix_retRowMax(const MATRIX* const A, const size_t row, ERR* const err) {
	size_t i = 0;
	double max = 0;

	if (A == NULL) *err = ERR_NUL;
	if (A->rows == 0 || A->cols == 0) *err = ERR_ZERO;
	if (row > A->rows) *err = ERR_PARA;

	max = A->m[A->cols * row];

	for (; i < A->cols; i++) {
		if (max < A->m[(A->cols * row) + i]) max = A->m[(A->cols * row) + i];
	}

	return max;
}

int matrix_multiplyRow(MATRIX* const A, const size_t row, double const factor) {
	size_t i = 0;

	if (A == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (row > A->rows) return ERR_PARA;

	for (; i < A->cols; i++) {
		A->m[(row * A->cols) + i] = factor * A->m[(row * A->cols) + i];
	}
	return 0;
}

BOOL matrix_isZero(const MATRIX* const A) {
	size_t i = 0;

	if (A == NULL) return -ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return -ERR_ZERO;

	for (; i < A->rows * A->cols; i++) {
		if (A->m[i] != 0) return FALSE;
	}
	return TRUE;
}

int matrix_setAllRow(MATRIX* const A, const size_t row, const double val) {
	size_t i = 0;

	if (A == NULL) return ERR_NUL;
	if (A->rows < row) return ERR_PARA;

	for (; i < A->cols; i++) {
		A->m[(row * A->cols) + i] = val;
	}
	return 0;
}

int matrix_setList(MATRIX* const A, const char* const list) {
	size_t i = 0;
	size_t j = 0;
	double num = 0;
	BOOL neg = 0;

	if (A == NULL || list == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;

	while (list[i] != '\0') {

		if (!((list[i] >= '0' && list[i] <= '9') || list[i] == ',' || list[i] == '-')) return ERR_COMP;

		if (list[i] == '-') {
			neg = TRUE;
			i++;
		}

		if (list[i] == ',') {
			if (j > A->rows * A->cols) return ERR_COMP;

			if (neg == TRUE) A->m[j] = -num;
			else A->m[j] = num;

			num = 0;
			neg = FALSE;
			j++;
			i++;
			continue;
		}

		num = num * 10;
		num = num + (list[i] - '0');

		i++;
	}

	return 0;
}

int matrix_add_m(const MATRIX* const A, const MATRIX* const B, MATRIX* const R, const BOOL neg_b) {
	size_t i = 0;

	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return ERR_ZERO;
	if (A->rows != B->rows || A->cols != B->cols) return ERR_DIM;

    // check if already allocated
    if (R->cols*R->rows != A->rows*A->cols) {
        if (matrix_init(R,A->rows,A->cols,0)) return ERR_INIT;
    }

	if (neg_b == FALSE){
		for (; i < R->cols * R->rows; i++) {
				R->m[i] = A->m[i] + B->m[i];
		}
	}
	else{
		for (; i < R->cols * R->rows; i++) {
				R->m[i] = A->m[i] - B->m[i];
		}
	}

	return 0;
}

int matrix_setEqualMatrix(MATRIX* const A, const MATRIX* const B) {
	//	MATRIX A = B
	size_t i = 0;

	if (A == NULL || B == NULL) return ERR_NUL;
	if (B->rows == 0 || B->cols == 0) return ERR_ZERO;

	if (A->m != NULL) free(A->m);
	A->rows = B->rows;
	A->cols = B->cols;

	if ((A->m = (double*)malloc(sizeof(double) * (B->rows * B->cols))) == NULL) return ERR_MEM;

	for (; i < B->rows * B->cols; i++) {
		A->m[i] = B->m[i];
	}

	return 0;
}

int matrix_setEqualValues(MATRIX* const A, const MATRIX* const B) {
	size_t i = 0;
	//matrices assumed to be equal sizes
	if (A == NULL || B == NULL) return ERR_NUL;
	if (A->rows != B->rows || A->cols != B->cols) return ERR_DIM;

	for (; i < A->rows * A->cols; i++) {
		A->m[i] = B->m[i];
	}
	return 0;
}

int matrix_setAll(MATRIX* const A, const double val) {
	size_t i = 0;

	if (A == NULL) return ERR_NUL;

	for (; i < A->cols * A->rows; i++) {
		A->m[i] = val;
	}
	return 0;
}


BOOL matrix_isOrthonormal(const MATRIX* const A) {
	size_t i = 0;
	size_t j = 0;
	double magnitude = 0;

	if (A == NULL) return -ERR_NUL;

	if (matrix_isOrthogonal(A) == FALSE) return FALSE;

	for (;j<A->rows;j++){
		magnitude = 0;
		for (;i<A->cols;i++){
			magnitude += A->m[(A->cols*j)+i]*A->m[(A->cols*j)+i];
		}
		if(magnitude != 1) return FALSE;
	}

	return TRUE;
}

BOOL matrix_isSymmetric(const MATRIX* const A) {
	// A^T =? A
	size_t i = 1;
	size_t j = 0;

	if (A == NULL) return -ERR_NUL;
	//if (A->rows != A->cols) -ERR_DIM;
	if (A->rows == 0 || A->cols == 0) return -ERR_ZERO;

	//check the diagonal
	for (; j < A->rows - 1; j++) {
		for (i = 0; i < A->cols; i++) {
			if (A->m[i + (j * A->cols)] != A->m[(i - 1) + ((j + 1) * A->cols)]) return FALSE;
		}
	}

	//check other corresponding entries
	for (j = 0; j < A->rows - 1; j++) {
		for (i = j + 2; i < A->cols; i++) {
			if (A->m[i + (j * A->cols)] != A->m[j + (i * A->cols)]) return FALSE;
		}
	}

	return TRUE;
}

BOOL matrix_isOrthogonal(const MATRIX* const A) {
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	double sum = 0;

	if(A == NULL) return -ERR_NUL;

	for (;i<A->cols-1;i++){
		for (j=i+1;j<A->cols;i++){
			sum = 0;
			for(k=0;k<A->rows;k++){
				sum += A->m[(A->cols*k)+i] * A->m[(A->cols*k)+j];
			}
			if(sum != 0) return FALSE;
		}
	}

	return TRUE;
}

BOOL matrix_isIdentity(const MATRIX* const A) {		// slow
	size_t i = 0;
	size_t j = 0;

	if (A == NULL) return -ERR_NUL;
	if (A->rows == 0 || A->cols == 0) return -ERR_ZERO;

	if (A->rows != A->cols) return FALSE;

	for (; i < A->rows * A->cols; i++) {
		//diagonals
		if (i % A->cols == j) {				//
			if (A->m[i] != 1) return FALSE;
			j++;
		}
		//non-diagonals
		else {
			if (A->m[i] != 0) return FALSE;
		}
	}
	
	return TRUE;
}

int matrix_getDiagonal(const MATRIX* const A, VECTOR* const R) {
	size_t i = 0;

	if (A == NULL || R == NULL) return ERR_NUL;
	if (matrix_init(R,1,A->cols,0)) return ERR_INIT;

	for(;i<A->cols;i++){
		R->m[i] = A->m[(A->cols*i)+i];
	}

	return 0;
}

int matrix_getRow(const MATRIX* const A, VECTOR* const R, const size_t row) {
	size_t i = 0;

	if (A == NULL || R == NULL) return ERR_NUL;
	if (row > A->rows) return ERR_PARA;
	if (matrix_init(R,A->rows,1,0)) return ERR_INIT;

	for (; i < A->cols; i++) {
		R->m[i] = A->m[i + (row * A->cols)];
	}

	return 0;
}

int matrix_getCol(const MATRIX* const A, VECTOR* const R, const size_t col) {
	size_t i = 0;

	if (A == NULL || R == NULL) return ERR_NUL;
	if (col > A->cols) return ERR_PARA;
	if (matrix_init(R,1,A->cols,0)) return ERR_INIT;

	for (; i < A->rows; i++) {
		R->m[i] = A->m[(i * A->cols) + col];
	}

	return 0;
}

int matrix_solveOrthogonal(const MATRIX* const A, const VECTOR* const B, VECTOR* const R){
	size_t i = 0;
	ERR err = 0;
	VECTOR col = { 0 };
	double denominator = 0;

	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	if (A->rows != B->rows) return ERR_DIM;
	if (matrix_isOrthogonal(A) == FALSE) return ERR_PARA;

	if (matrix_init(R,A->rows,1,0)) return ERR_INIT;

	for(;i<A->rows;i++){
		matrix_getCol(A,&col,i);
		R->m[i] = vector_dotProduct(B,&col,&err);
		if ((denominator = vector_dotProduct(&col,&col,&err)) == 0){ return ERR_DIVZ;}		// if matrix is orthonormal, then denom = 1 for all, and this step can be skipped
		else { R->m[i] /= denominator; }
	}

	matrix_free_data(&col);

	return 0;
}

int matrix_solvebackSub(const MATRIX* const A, const VECTOR* const B, VECTOR* const R) {
	//Ar=b
	size_t i = 0;
	size_t j = 0;

	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	if (B->cols != 1 || A->rows != B->rows) return ERR_DIM;

	if (matrix_isUpper(A) == FALSE) return ERR_PARA;

	if (matrix_init(R,A->rows,1,0)) return ERR_INIT;		//#123:	return row or col ?

	for(i = A->rows-1; i >= 0; i--){
		if (A->m[(A->cols*i)+i]!=0){	//if coef in A is zero then skip, r value will stay zero
			R->m[i] = B->m[i];
			// negative increment sum S: from:(j=2) down to:( i+1): S(x_j)*(a_ij)
			for(j=A->rows-1;j>i;j--){
				R->m[i] += R->m[j] * (A->m[(A->cols*i)+j]);
			}
			R->m[i] /= A->m[(A->cols*i)+i];
		}
	}

	return 0;
}

int matrix_solveforwardSub(const MATRIX* const A, const VECTOR* const B, VECTOR* const R) {
	//Ar=b
	size_t i = 0;
	size_t j = 0;

	if (A == NULL || B == NULL) return ERR_NUL;
	if (B->cols != 1 || A->rows != B->rows) return ERR_DIM;

	if (matrix_isLower(A) == FALSE) return ERR_PARA;

	if (matrix_init(R,A->rows,1,0)) return ERR_INIT;

	for(;i<A->rows-1;i++){
		if (A->m[(A->cols*i)+i]!=0){	//if coef in A is zero then skip, r value will stay zero
			R->m[i] = B->m[i];
			for (j=0;j<i-1;j++){
				R->m[i] += R->m[j] * (A->m[(A->cols*i)+j]);
			}
			R->m[i] /= A->m[(A->cols*i)+i];
		}
	}

	return 0;
}

int matrix_solveSeidel(MATRIX* const A, VECTOR* const B, VECTOR* const R, const size_t iter) {
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	VECTOR prev_iter = { 0 };

	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	if (A->rows != A->cols || A->rows != B->rows || B->cols != 1) return ERR_DIM;
	if (iter <= 0) return ERR_PARA;
	if (matrix_isStrictDiagDom(A)==FALSE) return ERR_PARA;		// otherwise check if diagonal entries are non-zero

	if (matrix_init(R,A->rows,1,0)) return ERR_INIT;

	if (matrix_init(&prev_iter,A->rows,1,0)) return ERR_INIT;

	for (;k<iter;k++){

		if (k!=0 && matrix_setEqualValues(&prev_iter, R)) return ERR_FUNC;

		for (i=0;i < A->rows;i++){
			if (A->m[(A->cols*i)+i]!=0){
				R->m[i] = B->m[i];
				for (j=0;j < A->rows;j++){
					if(j==i) continue;
					R->m[i] -= A->m[(A->cols*i)+j] * R->m[j];
				}
				R->m[i] /= A->m[(A->cols*i)+i];
			}
			else return ERR_PARA;
		}

		if (matrix_isEqual(R,&prev_iter) == TRUE) goto converged;		// converged

	}

	converged:
	matrix_free_data(&prev_iter);

	return 0;
}


double vector_angle(const VECTOR* const A, const VECTOR* const B, ERR* const err) {
	if (A == NULL || B == NULL) *err = ERR_NUL;
	if (A->cols < 2 || B->cols < 2) *err = ERR_DIM;

	return acos(vector_dotProduct(A,B,err)/(vector_length(A,err)*vector_length(B,err)));
}

int vector3_cross(const VECTOR* const A, const VECTOR* const B, VECTOR* const R) {
	if (A == NULL || B == NULL || R == NULL) return ERR_NUL;
	if ((A->rows != 1 || A->cols != 1) && (B->rows != 1 || B->cols != 1)
		&& (A->rows != B->rows || A->cols != B->cols)) return ERR_DIM;

	if (matrix_init(R,1,3,0)) return ERR_INIT;

	R->m[0] = A->m[1] * B->m[2] - A->m[2] * B->m[1];
	R->m[1] = -(A->m[0] * B->m[2] - A->m[2] * B->m[0]);
	R->m[2] = A->m[0] * B->m[1] - A->m[1] * B->m[0];

	return 0;
}

int vector_normalize(VECTOR* const A){
	size_t i = 0;
	size_t n = 0;
	double magnitude = 0;
	ERR err = 0;

	if (A == NULL) return ERR_NUL;
	if (A->rows != 1 || A->cols != 1) return ERR_DIM;

	magnitude = vector_length(A,&err);

	n = A->cols >= A->rows ? A->cols : A->rows;		// row or col vector

	for (;i<n;i++){
		A->m[i] /= magnitude;
	}

	return 0;
}

int vector_transpose(VECTOR* const A){
	size_t temp = 0;
	if (A == NULL) return ERR_NUL;
	if (A->rows != 1 || A->cols != 1) return ERR_DIM;

	temp = A->rows;
	A->rows = A->cols;
	A->cols = temp;

	return 0;
}

double vector_dotProduct(const VECTOR* const A, const VECTOR* const B, ERR* const err) {
	size_t i = 0;
	size_t n = 0;
	double result = 0;

	if (A == NULL || B == NULL) *err = ERR_NUL;
	if ((A->rows != 1 || A->cols != 1) && (B->rows != 1 || B->cols != 1)
		&& (A->rows != B->rows || A->cols != B->cols)) *err = ERR_DIM;

	n = A->cols >= A->rows ? A->cols : A->rows;		// row or col vector

	for (; i < n; i++) {
		result += A->m[i] * B->m[i];
	}

	return result;
}

double vector_length(const VECTOR* const A, ERR* const err) {
	if (A == NULL) *err = ERR_NUL;
	return sqrtf(vector_dotProduct(A,A,err));
}

double vector_distance(const VECTOR* const A, const VECTOR* const B, ERR* const err) {
	size_t i = 0;
	size_t n = 0;
	double result = 0;

	if (A == NULL || B == NULL) *err = ERR_NUL;
	if ((A->rows != 1 || A->cols != 1) && (B->rows != 1 || B->cols != 1)
		&& (A->rows != B->rows || A->cols != B->cols)) *err = ERR_DIM;

	n = A->cols >= A->rows ? A->cols : A->rows;		// row or col vector

	for (; i < n; i++) {
		result += (A->m[i] - B->m[i]) * (A->m[i] - B->m[i]);
	}

	return sqrtf(result);
}
