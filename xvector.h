#ifndef _XVECTOR_H
#define _XVECTOR_H

#include <stdlib.h>
#include <math.h>
#include "xerror.h"

typedef int bool;
enum { false = 0, true = 1 };

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#undef size_t
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#define X_MEMORY_RANGE    (4)		/* upper limit for malloc. this shouldn't be negative. instead of reallocing if the lengths aren't equal, */
					/* reallocate if the length of A is less than B (required), or A has X more than B cells allocated. */

#define REALLOCATE(R, Rlength, length) \
    do{\
        if ((Rlength) < (length) || (Rlength) > (length) + X_MEMORY_RANGE) { \
            if ((R) != NULL) free((R)); \
            if (((R) = (double*)malloc(sizeof(double)*(length))) == NULL) return ERR_INIT; \
            (Rlength) = (length); \
        }\
    }while(0)

typedef bool (*compare_func)(const void* const left, const void* const right);
bool compare_double(const void* const left, const void* const right);
bool compare_size_t(const void* const left, const void* const right);

// vector_sort
// vector_reverse
int vector_abs(double* const A, const size_t length);
int vector_negate(double* const A, const size_t length);
int vector_add(const double* const A, const size_t Alength, const double* const B, const size_t Blength, double** const R, size_t* Rsize);
int vector_subtract(const double* const A, const size_t Alength, const double* const B, const size_t Blength, double** R, size_t* Rsize);
int vector_multiply_s(double* const A, const size_t length, const double scalar, const size_t incr);
int vector3_cross(const double* const A, const double* const B, double** const R, size_t* const length);
double vector_angle(const double* const A, const double* const B, const size_t length, ERR* const err);
int vector_normalize(double* const A, const size_t length);
double vector_dotProduct(const double* const A, const double* const B, const size_t length, ERR* const err);
static inline double vector_length(const double* const A, const size_t length) {
	ERR err = 0;
	if (A == NULL) {
		err = ERR_NUL;
        return 0;
	}
	return sqrtf(vector_dotProduct(A,A,length,err));
}
int vector_swapEntrys(double* const A, const size_t Alength, const size_t x, const size_t y, const size_t length, const size_t incr);
int vector_setList(double* const A, const size_t Alength, const char* const list);
int vector_setAll(double* const A, const size_t length, const double val, const size_t incr);
int vector_setEqualArray(double** const A, size_t* const Alength, const double* const B, const size_t Blength, const size_t length, const size_t incr);
int vector_setEntrysEqual(const double* const A, const size_t Alength, double* const R, const size_t Rlength, const size_t length, const size_t incr);
int vector_getEntrys(const double* const A, const size_t Alength, double** R, size_t* const Rsize, const size_t length, const size_t incr);
double vector_retMin(const double* const A, const size_t length, const size_t incr, ERR* const err);
double vector_retMax(const double* const A, const size_t length, const size_t incr, ERR* const err);

bool vector_isEqual(const double* const A, const size_t Alength, const double* const B, const size_t Blength);
bool vector_isZero(const double* const A, const size_t length);

#endif
