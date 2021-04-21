# cxmatrix
cxmatrix library is row major,
has automatic dynamic memory allocation/matrix dimension, and contains a list of linear algebra functions to solve matrix equations. If you want a static matrix, make a static array, and set the pointer in the MATRIX struct to your static array.

(in main.c) is a program to project vertices of a 3d cube onto the screen, rotated on the X and Y axis. A line is drawn between corresponding vertices using an adjacecy list (xadj.h). It uses (xdraw.h) functions to draw to screen (no ncurses and no other external lib): works on windows console, there maybe printing problems on linux terminals, try to increase the size of your terminal (before it prints) if it doesn't print correctly.

![cube](https://user-images.githubusercontent.com/73267302/109907072-9486ac00-7c6f-11eb-80f4-80105f3fdb45.gif)

(man, am I glad I stopped maintaining this library. I guess I now know why its better just to use someone else's library, rather than write your own. It would of came out better if I wrote it in C++, probably because I'm trying to simulate OOP using a vector (1D dynamic array) as a base class, and a matrix derived from (a single) vector. BUT who likes using big languages like C++ to take care of everything for you? WELL... I do now.)
