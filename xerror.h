#ifndef _XERROR_H
#define _XERROR_H

typedef enum ERR {
	ERR_OK = 0,
	ERR_NUL,	    //	null pointers
	ERR_ZERO,		//	zero row/col size
	ERR_DIM,		//	wrong matrix dimension
	ERR_PARA,		//	wrong func parameter
	ERR_FUNC,		//	a function called returnd an error before it could finish
	ERR_INIT,		//	error init matrix
	ERR_MEM,		// 	out of memory
	ERR_DIVZ,       //  division by zero
	ERR_COMP,		//	bad comparison
	ERR_COUNT,
} ERR;

extern const char* const ERR_MSG[];

const char* print_err(const ERR err);

#endif
