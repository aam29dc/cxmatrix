# cxmatrix
cxmatrix library is row major, with automatic dynamic memory (non-static) allocation. This libray contains a list of functions to solve matrix equations (see xmatrix.h,.c). This library was built to help me learn numerical linear algebra and computer graphics.

(in main.c) is a program using cxmatrix to project vertices of a 3d cube onto the screen, rotated on two of its axises. A line is drawn between corresponding vertices using an adjacecy list (xadj.h). It uses (xdraw.h) functions to draw to screen (no ncurses and no other external lib): works on windows console, there maybe printing problems on linux terminals, try to increase the size of your terminal (before it prints) if it doesn't print correctly.

![cube](https://user-images.githubusercontent.com/73267302/109907072-9486ac00-7c6f-11eb-80f4-80105f3fdb45.gif)

(use glm)
