# cxmatrix
cxmatrix library is row major, is non-static with automatic dynamic memory allocation, and contains a list of linear algebra functions to solve matrix equations.



(in main.c) is a program using cxmatrix to project vertices of a 3d cube onto the screen, rotated on the X and Y axis. A line is drawn between corresponding vertices using an adjacecy list (xadj.h). It uses (xdraw.h) functions to draw to screen (no ncurses and no other external lib): works on windows console, there maybe printing problems on linux terminals, try to increase the size of your terminal (before it prints) if it doesn't print correctly.

![cube](https://user-images.githubusercontent.com/73267302/109907072-9486ac00-7c6f-11eb-80f4-80105f3fdb45.gif)

(use glm)
