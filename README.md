# cxmatrix
cxmatrix library is ROW MAJOR,
has automatic dynamic memory allocation,
contains a list of linear algebra functions to solve matrix equations,
also contains xmath, xstring header files I've created to learn. x prefix.

in _oldmain.c (NOTE: shouldn't compile since im lazy, but same flow. I'll come back and fix it later.) I've written a program to project vertices of a 3d cube onto the screen, and rotated its X and Y axis, using the cxmatrix lib and printf. It uses xdraw.h functions to draw to screen. Works on windows console, there maybe printing problems on linux terminals, due to screen sizes, try to increase the size of your terminal if it doesn't print correctly.

functions like matrix_inverse are slow solutions for large matrices, but I've kept them anyway, incase anyone wants to look at them.

WIP

_saved_deprecated.c is a bunch of deleted/rewritten functions saved
