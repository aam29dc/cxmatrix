#include "xmath.h"

int numOfdecimalsf32(const double x) {
	int i = 0;
	int num = 0;

	while (i < F32SIGFIGS) {
		if ((int)(((double)x - (int)x) * 10) != 0)
			num++;
		else num++;

		i++;
	}
	return i;
}

short xabsol(const int x) {
	if (x < 0) return (short)(-x);
	else return (short)x;
}

int xroundf(const double x) {
	if (x < 0.0)
		return (int)(x - 0.5);
	else
		return (int)(x + 0.5);
}

double xabsolf(const double x) {
	if (x < 0) return -x;
	else return x;
}

double xfmod(const double value, const int mod) {
	return ((int)value % mod) + (value - (int)value);
}

int xfactorial(int val) {
	int i = val - 1;
	for (; i > 1; i--) {
		val *= i;
	}
	return val;
}

double xtaylorsine(double x) {
	//by now x has been reduced modulus 360
	x *= (double)PI / 180;

	//y = -(x * x) / xfactorial(7);y += (double)1. / xfactorial(5);y *= -(x * x);y += (double)1. / xfactorial(3);y *= -(x * x);y += 1;y *= x;
	return (((-(x * x) / xfactorial(7) + (double)1. / xfactorial(5)) * -(x * x) + (double)1. / xfactorial(3)) * -(x * x) + 1) * x;
}

double xtaylorcos(double x) {
	//by now x has been reduced modulus 360
	x *= (double)PI / 180;

	//y = -(x * x) / xfactorial(6);y += (double)1. / xfactorial(4);y *= -(x * x);y += (double)1. / xfactorial(2);y *= -(x * x);y += 1;
	return 1 + ((-(x * x) / xfactorial(6) + (double)1. / xfactorial(4)) * -(x * x) + (double)1. / xfactorial(2)) * -(x * x);
}

double xsine(double degree) {
	double value = 0;
	int isNeg = 0;
	if (degree < 0) {
		isNeg = 1;
	}
	degree = xabsolf(degree);

	//if degree is mult of 90/180/270 degrees return 1,0,-1
	if (degree == 0) return 0;
	else if ((degree == (int)degree) && ((int)degree % 270 == 0)) return -1;
	else if ((degree == (int)degree) && ((int)degree % 180 == 0)) return 0;
	else if ((degree == (int)degree) && ((int)degree % 90 == 0)) return 1;

	//reduce degree till under 360
	if (degree > 360) {
		degree = xfmod(degree, 360);
	}

	if (degree < 90) {
		value = xtaylorsine(degree);
	}
	else if (degree > 90 && degree < 180) {
		value = xtaylorcos(xfmod(degree, 90));
	}
	else if (degree > 180 && degree < 270) {
		value = -xtaylorsine(xfmod(degree, 90));
	}
	else value = -xtaylorcos(xfmod(degree, 90));

	return isNeg == 0 ? value : -value;
}

double xcosine(double degree) {
	degree = xabsolf(degree);

	//if degree is mult of 90/180/370 degrees return 0,-1,1
	if (degree == 0) return 1;
	else if ((degree == (int)degree) && ((int)degree % 360 == 0)) return 1;
	else if ((degree == (int)degree) && ((int)degree % 270 == 0)) return 0;
	else if ((degree == (int)degree) && ((int)degree % 180 == 0)) return -1;
	else if (degree == 90) return 0;

	//reduce number till under 360
	if (degree > 360) {
		degree = xfmod(degree, 360);
	}

	if (degree < 90) {
		return xtaylorcos(degree);
	}
	else if (degree > 90 && degree < 180) {
		return -xtaylorsine(xfmod(degree, 90));
	}
	else if (degree > 180 && degree < 270) {
		return -xtaylorcos(xfmod(degree, 90));
	}
	else return xtaylorsine(xfmod(degree, 90));
}

double xpow(const double base, const int exp) {
	int i = 0;
	double equ = base;
	while (i < exp) {
		equ *= base;
		i++;
	}
	return equ;
}

double xroot(const double base, const int root) {
	double i = 1;
	double inc = 1;
	double x = 0;

	//if (base == 0) return 0.0;
	//else if (base == 1) return 1.0;
	//else if (root == 1) return base;

	while (x != base || numOfdecimalsf32(i) < F32SIGFIGS) {
		x = xpow(i, root);


		while (x < base) {

			i += inc;
			x = xpow(i, root);
		}

		i -= inc;
		inc /= 10.0;
	}
	return x;
}

int isOddi(const int x) {
	return (x & 1) == 1 ? 1 : 0;
}

int isNegi(const int x) {
	return x < 0 ? 1 : 0;
}

int xfloor(const double x) {
	if (!isNegi((int)x)) return (int)x;
	else return (int)x - 1;
}

int xceil(const double x) {
	if (isNegi((int)x)) return (int)x;
	else return (int)x + 1;
}

int absol(const int x) {
	if (x < 0) return -x;
	else return x;
}
