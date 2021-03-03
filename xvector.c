#include "xvector.h"

bool compare_greaterthan_double(const void* const left, const void* const right) {
    return *(double*)left > *(double*)right;
}

bool compare_greaterthan_size_t(const void* const left, const void* const right) {
    return *(size_t*)left > *(size_t*)right;
}

double vector_angle(const double* const A, const double* const B, const size_t length, ERR* const err) {
	if (A == NULL || B == NULL || err == NULL) {
		*err = ERR_NUL;
		return 0;
	}
	if (length == 0) {
		*err = ERR_ZERO;
		return 0;
	}

	return acos(vector_dotProduct(A,B,length,err) / (vector_length(A,length)*vector_length(B,length)));
}

int vector_abs(double* const A, const size_t length) {
	size_t i = 0;
	if (A == NULL) return ERR_NUL;

	for (; i < length; i++){
        if(A[i] < 0) A[i] = -A[i];
	}
	return 0;
}

int vector_negate(double* const A, const size_t length) {
	size_t i = 0;
	if (A == NULL) return ERR_NUL;

	for (; i < length; i++) {
		A[i] = -A[i];
	}
	return 0;
}

int vector_add_m_array(const double** const A, const size_t* const Alengths, const size_t length, double** R, size_t* const Rsize) {
	size_t i = 0;
	size_t j = 0;
	size_t max_length = 0;
    ERR err = 0;

	if (A == NULL || Alengths == NULL || R == NULL || Rsize == NULL) return ERR_NUL;

	max_length = *(double*)g_vector_retMax(&Alengths, length, sizeof(double), compare_greaterthan_double, 1, &err); /* rewrite vector_retMax as generic */

    if (*Rsize != max_length) {
        if ((*R = (double*)malloc(sizeof(double)*max_length)) == NULL) return ERR_INIT;
    }

    for (i=0; i < length; i++) {
        for (j=0;j < Alengths[i]; j++){
            *R[j] += *A[j];
        }
	}

	return 0;
}

int vector_add_m(const double* const A, const size_t Alength, const double* const B, const size_t Blength, double** R, size_t* Rsize) {
	size_t i = 0;

	if (A == NULL || B == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (Alength != Blength) return ERR_DIM;

	REALLOCATE(*R, *Rsize, Alength);

	for (; i < Alength; i++) {
		*R[i] = A[i] + B[i];
	}

	return 0;
}

int vector_subtract_m(const double* const A, const size_t Alength, const double* const B, const size_t Blength, double** R, size_t* Rsize) {
	size_t i = 0;

	if (A == NULL || B == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (Alength != Blength) return ERR_DIM;

    REALLOCATE(*R, *Rsize, Alength);

	for (; i < Alength; i++) {
		*R[i] = A[i] - B[i];
	}

	return 0;
}

int vector_multiply_s(double* const A, const size_t length, const double scalar, const size_t incr) {
	size_t i = 0;
	if (A == NULL) return ERR_NUL;
	if (incr == 0) return ERR_ZERO;

	for(;i < length;i+=incr){
		A[i] *= scalar;
	}

	return 0;
}

int vector3_cross(const double* const A, const double* const B, double** const R, size_t* const length) {
	if (A == NULL || B == NULL || R == NULL || length == NULL) return ERR_NUL;

	REALLOCATE(*R, *length, 3);

	*R[0] = A[1] * B[2] - A[2] * B[1];
	*R[1] = -(A[0] * B[2] - A[2] * B[0]);
	*R[2] = A[0] * B[1] - A[1] * B[0];

	return 0;
}

int vector_normalize(double* const A, const size_t length){
	size_t i = 0;
	double magnitude = 0;
	ERR err = 0;

	if (A == NULL) return ERR_NUL;

	magnitude = vector_length(A,length);

	for (;i<length;i++){
		A[i] /= magnitude;
	}

	return 0;
}

double vector_projection(const double* const A, const double* const B, double** const R, size_t* const length){
	if (A == NULL || B == NULL || R == NULL || length == NULL) return ERR_NUL;

	//if(*length !=
    return 0;
}

double vector_dotProduct(const double* const A, const double* const B, const size_t length, ERR* const err) {
	size_t i = 0;
	double result = 0;

	if (A == NULL || B == NULL || err == NULL) {
		*err = ERR_NUL;
		return 0;
	}

	for (; i < length; i++) {
		result += A[i] * B[i];
	}

	return result;
}

double vector_distance(const double* const A, const double* const B, const size_t length, ERR* const err) {
	size_t i = 0;
	double result = 0;

	if (A == NULL || B == NULL || err == NULL) {
		*err = ERR_NUL;
		return 0;
	}

	for (; i < length; i++) {
		result += (A[i] - B[i]) * (A[i] - B[i]);
	}

	return sqrtf(result);
}

int g_vector_swapEntrys(void* const arr, const size_t arr_length, const size_t type_size, const size_t x, const size_t y, const size_t length, const size_t incr){
	
}

int vector_swapEntrys(double* const A, const size_t Alength, const size_t x, const size_t y, const size_t length, const size_t incr) {
	size_t i = 0;
	double temp = 0;

	if (A == NULL) return ERR_NUL;
	if (incr == 0) return ERR_ZERO;
	if (x == y || x + length > Alength || y + length > Alength) return ERR_PARA;

	for (; i < length; i+=incr) {
		temp = A[i+x];
		A[i+x] = A[i+y];
		A[i+x] = temp;
	}
	return 0;
}

int vector_setList(double* const A, const size_t Alength, const char* const list) {
	size_t i = 0;
	size_t j = 0;
	double num = 0;
	bool neg = 0;

	if (A == NULL || list == NULL) return ERR_NUL;

	while (list[i] != '\0') {

		if (!((list[i] >= '0' && list[i] <= '9') || list[i] == ',' || list[i] == '-')) return ERR_COMP;

		if (list[i] == '-') {
			neg = true;
			i++;
		}

		if (list[i] == ',') {
			if (j > Alength) return ERR_COMP;

			if (neg == true) A[j] = -num;
			else A[j] = num;

			num = 0;
			neg = false;
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

int vector_setEqualArray(double** const A, size_t* const Alength, const double* const B, const size_t Blength, const size_t length, const size_t incr) {
	size_t i = 0;

	if (A == NULL || B == NULL) return ERR_NUL;
	if (incr == 0) return ERR_ZERO;

	REALLOCATE(*A, *Alength, Blength);

	for (; i < length; i+=incr) {
		*A[i] = B[i];
	}

	return 0;
}

int vector_setEntrysEqual(const double* const A, const size_t Alength, double* const R, const size_t Rlength, const size_t length, const size_t incr) {
	size_t i = 0;

	if (A == NULL || R == NULL) return ERR_NUL;
	if (length > Alength || length > Rlength) return ERR_PARA;
    if (incr == 0) return ERR_ZERO;

	for (; i < length; i+=incr) {
		R[i] = A[i];
	}

	return 0;
}

int vector_setAll(double* const A, const size_t length, const double val, const size_t incr) {
	size_t i = 0;

	if (A == NULL) return ERR_NUL;
	if (incr == 0) return ERR_ZERO;

	for (; i < length; i+=incr) {
		A[i] = val;
	}
	return 0;
}

int vector_getEntrys(const double* const A, const size_t Alength, double** R, size_t* const Rsize, const size_t length, const size_t incr) {
	size_t i = 0;

	if (A == NULL || R == NULL || Rsize == NULL) return ERR_NUL;
	if (length > Alength) return ERR_PARA;
	if (incr == 0) return ERR_ZERO;

	REALLOCATE(*R, *Rsize, length);

	for (; i < length; i+=incr) {
		*R[i] = A[i];
	}

	return 0;
}

double vector_retMax(const double* const A, const size_t length, const size_t incr, ERR* const err) {
	size_t i = 0;
	double max = 0;

	if (A == NULL || err == NULL) {
		*err = ERR_NUL;
		return 0;
	}
	if (incr == 0) {
		*err = ERR_ZERO;
		return 0;
	}

	max = A[0];

	for (; i < length; i+=incr) {
		if (max < A[i]) max = A[i];
	}

	return max;
}

double vector_retMin(const double* const A, const size_t length, const size_t incr, ERR* const err) {
	size_t i = 0;
	double min = 0;

	if (A == NULL || err == NULL) {
		*err = ERR_NUL;
		return 0;
	}
	if (incr == 0) {
		*err = ERR_ZERO;
		return 0;
	}

	min = A[0];

	for (; i < length; i+=incr) {
		if (min > A[i]) min = A[i];
	}

	return min;
}

bool vector_isEqual(const double* const A, const size_t Alength, const double* const B, const size_t Blength) {
	size_t i = 0;

	if (A == NULL || B == NULL) return -ERR_NUL;
	if (Alength != Blength) return false;

	for (; i < Alength; i++) {
		if (A[i] != B[i]) return false;
	}
	return true;
}

bool vector_isZero(const double* const A, const size_t length) {
	size_t i = 0;

	if (A == NULL) return -ERR_NUL;
	if (length == 0) return -ERR_ZERO;

	for (; i < length; i++) {
		if (A[i] != 0) return false;
	}
	return true;
}