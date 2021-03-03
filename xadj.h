#ifndef _XADJ_H
#define _XADJ_H

#include <stdio.h>
#include <stdlib.h>
#include "xerror.h"

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#undef size_t
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif
#endif

// adjacency list
int adj_init(size_t** adj, const size_t size);
int adj_setList(size_t** const adj, const size_t size, const char* const list);
int adj_print(const size_t* const adj, const size_t rows, const size_t cols);

#endif
