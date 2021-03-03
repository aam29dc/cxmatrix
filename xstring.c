#include "xstring.h"

void xswap(void* a, void* b, const size_t size) {
	unsigned char* x = (unsigned char*)a;
	unsigned char* y = (unsigned char*)b;
	unsigned char temp = 0;
	size_t i = 0;

	for (; i < size; i++) {
		temp = x[i];
		x[i] = y[i];
		y[i] = temp;
	}
}

int numOfdigits(int x) {
	int i = 0;

	if (x < 0) x = -x;

	while (x > 0) {
		i++;
		x /= 10;
	}
	return i;
}

int firstdigit(int x) {
	while (numOfdigits(x) > 1) {
		x /= 10;
	}
	return x;
}

int deciAtPos(float num, int pos) {
	while (pos > 0) {
		num = num - (int)num;
		num *= 10;
		pos--;
	}
	return (int)num;
}

int xstrlen(const char* s) {
	const char* front = s;
	while (*s != '\0') {
		s++;
	}
	return s - front;
}

char* xstrcpy(char* d, const char* s)
{
	char* saved = d;
	while (*s)
	{
		*d++ = *s++;
	}
	*d = 0;
	return saved;
}
