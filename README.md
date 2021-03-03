# cxmatrix
cxmatrix library is row major,
has automatic dynamic memory allocation or matrix dimension determination,
and contains a list of linear algebra functions to solve matrix equations.

(in main.c) is a program to project vertices of a 3d cube onto the screen, rotated on the X and Y axis. A line is drawn between corresponding vertices using an adjacecy list (xadj.h). It uses (xdraw.h) functions to draw to screen: works on windows console, there maybe printing problems on linux terminals, due to screen sizes, try to increase the size of your terminal if it doesn't print correctly.

(3d cube on x and y axis, (z orthongonal to x and y))


                                                            .
                                                            ·
                                                            .
                                                            ·
                                                            .
                                                            ·
                                                            .
                                                            ·
                                                  O≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡O
                                                  ≡≡        ·        ≡≡
                                                  ≡ ≡       .       ≡ ≡
                                                  ≡  ≡      ·      ≡  ≡
                                                  ≡   ≡     .     ≡   ≡
                                                  ≡    ≡    ·    ≡    ≡
                                                  ≡     O≡≡≡≡≡≡≡O     ≡
                                                  ≡     ≡   .   ≡     ≡
                                                  ≡     ≡   .   ≡     ≡
                                                  ≡     ≡   ·   ≡     ≡
					 ......·.·.·.·≡·.·.·≡·.·.·.·≡·.·.·≡·.·.·.·......
                                                  ≡     ≡   .   ≡     ≡
                                                  ≡     ≡   ·   ≡     ≡
                                                  ≡     O≡≡≡≡≡≡≡O     ≡
                                                  ≡    ≡    ·    ≡    ≡
                                                  ≡   ≡     .     ≡   ≡
                                                  ≡  ≡      ·      ≡  ≡
                                                  ≡ ≡       .       ≡ ≡
                                                  ≡≡        ·        ≡≡
                                                  O≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡O
                                                            ·
                                                            .
                                                            ·
                                                            .
                                                            ·
                                                            .
                                                            ·
                                                            .
