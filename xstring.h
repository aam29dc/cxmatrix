#ifndef _XSTRING_H
#define _XSTRING_H
#define F32SIGFIGS (7)

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#undef size_t
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif
#endif

void xswap(void* a, void* b, const size_t size);
int numOfdigits(int x);
int firstdigit(int x);
int deciAtPos(float num, int pos);
int xstrlen(const char* s);
char* xstrcpy(char* d, const char* s);

#endif
