#ifndef _XMATH_H
#define _XMATH_H
#define F32SIGFIGS (7)
#define PI (3.14159265358979323846)

//arcsin, arccos
int numOfdecimalsf32(const double x);
short xabsol(const int x);
int xroundf(const double x);
double xabsolf(const double x);
double xfmod(const double value, const int mod);
int xfactorial(int val);
double xtaylorsine(double x);
double xtaylorcos(double x);
double xsine(double degree);
double xcosine(double degree);
double xpow(const double base, const int exp);
double xroot(const double base, const int root);
int isOddi(const int x);
int isNegi(const int x);
int xfloor(const double x);
int xceil(const double x);
int absol(const int x);

#endif