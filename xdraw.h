#ifndef _XDRAW_H
#define _XDRAW_H

#include <stdio.h>
#include "xerror.h"
#include "xmath.h"
#include "xstring.h"

#ifdef _WIN32
	#include <Windows.h>
#else
	typedef short int SHORT;

	typedef struct _COORD {
	SHORT X;
	SHORT Y;
	} COORD, *PCOORD;
#endif

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#undef size_t
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#ifndef _XMATRIX_STRUCT
#define _XMATRIX_STRUCT
typedef struct {
	size_t rows;
	size_t cols;
	double* m;
}MATRIX;
#endif

#define PIXEL   (240)
#define SCALE	(10)
#define WIDTH	(40)
#define HEIGHT	(40)
#define SHIFT	(0)

// draw functions that print to screen
int drawAxis(const short div);
void clearScreen(void);
int printPixel(COORD coords, const int c);
int drawLine(const int x1, const int y1, const int x2, const int y2);
int matrix_drawEdges(const MATRIX* const A, const size_t* const adj);
int fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
int matrix_screen2dCords(const MATRIX* const A);
int matrix_print(const MATRIX* const A, const short v_offset);

#endif
