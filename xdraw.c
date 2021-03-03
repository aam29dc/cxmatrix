#include "xdraw.h"

int drawAxis(const short div) {
	#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #else
        printf("\e[8;%d;%dt",HEIGHT,WIDTH);     // attempt to resize the window
	#endif
	COORD coord = { 0 };
	coord.Y = SHIFT;
	coord.X = (WIDTH / 2) + SHIFT;

	for (; coord.Y < HEIGHT + SHIFT; coord.Y++) {
		#ifdef _WIN32
			SetConsoleCursorPosition(hConsole, coord);
        #else
            printf("\033[%d;%dH",coord.Y,coord.X);
		#endif
		if (((HEIGHT / 2) - (coord.Y - SHIFT)) % div == 0) {
			printf("%c", 176);
		}
		else printf("%c", 250);
	}

	coord.X = SHIFT;
	coord.Y = (HEIGHT / 2) + SHIFT;

	for (; coord.X < WIDTH + SHIFT; coord.X++) {
		#ifdef _WIN32
			SetConsoleCursorPosition(hConsole, coord);
		#else
			printf("\033[%d;%dH",coord.Y,coord.X);
		#endif
		if ((-(WIDTH / 2) + (coord.X - SHIFT)) % div == 0) {
			printf("%c", 176);
		}
		else printf("%c", 250);
	}

	//drawBounds

	return 0;
}

void clearScreen(void) {
	#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif
	COORD coord = { 0 };		// 2d coordinates matrix

	//#123:               ____
	for (; coord.Y < HEIGHT * 5; coord.Y++) {
		for (; coord.X < WIDTH * 5; coord.X++) {
			#ifdef _WIN32
				SetConsoleCursorPosition(hConsole, coord);
			#else
				printf("\033[%d;%dH",coord.Y,coord.X);
			#endif
			printf(" ");
		}
	}
	coord.X = 0;
	coord.Y = 0;
	#ifdef _WIN32
		SetConsoleCursorPosition(hConsole, coord);
	#else
		printf("\033[%d;%dH",coord.Y,coord.X);
	#endif
}

int printPixel(COORD coords, const int c) {
	#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif

	coords.Y = -coords.Y + (HEIGHT / 2);
	coords.X += WIDTH / 2;

	if (coords.X < 0 || coords.Y < 0) return ERR_PARA;
	#ifdef _WIN32
		SetConsoleCursorPosition(hConsole, coords);
	#else
		printf("\033[%d;%dH",coords.Y,coords.X);
	#endif
	printf("%c", c);
	return 0;
}

int drawLine(const int x1, const int y1, const int x2, const int y2) {
	COORD coord = { 0 };
	double m = 0;			//slope
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;

	//dont divide by zero, same x's and different y's
	//here a vertical line will be drawn
	if (x1 == x2) {
		y = xabsol(y1 - y2) + 1;	//delta y
		coord.X = (short)x1;
		coord.Y = (y1 < y2) ? (short)y1 : (short)y2;
		for (i = 0; i < y; i++) {
			printPixel(coord, PIXEL);
			coord.Y++;
		}
		return 0;
	}

	//now division by zero cant happen here
	m = (double)(y1 - y2) / (x1 - x2);

	// i starts the left of x, and increments towards x in loop below
	i = x1 < x2 ? x1 : x2;
	x = x1 < x2 ? x2 : x1;

	// absol(slope) is =< 1, a continuous line will be drawn, 1 iteration of j, for m > 1 atleast 2 iterations, etc
	for (; i < x; i++) {
		// for each x print the vertical y line, of height determined by abs of slope
		if (m == 0) { y = 1; }
		else if (m == (int)m) { y = (int)xabsolf(m); }
		else { y = (int)xabsolf(m) + 1; }

		coord.X = (short)i;
		for (j = 0; j < y; j++) {
			// equation : y - y1 = m(x - x1)
			if (m >= 0) coord.Y = (short)(xroundf(m * (i - x1) + y1) + j);
			else coord.Y = (short)(xroundf(m * (i - x1) + y1) - j);
			printPixel(coord, PIXEL);
		}
	}

	return 0;
}

int matrix_drawEdges(const MATRIX* const A, const size_t* const adj) {
	size_t i = 0;
	size_t j = 0;

	if (adj == NULL || A == NULL) return ERR_NUL;

	//skip diagonal and everything to the left of diagonal
	//adj is a square matrix and A->cols is the amount of vertices
	for (j = 0; j < A->cols; j++) {
		for (i = j; i < A->cols; i++) {
			if (adj[i + (j * A->cols)] == 1) {
				// v1: i / A->cols == row , v2: i % A->cols == col for [3x3]
				if (drawLine(xroundf(A->m[i]), xroundf(A->m[i + A->cols]), xroundf(A->m[j]), xroundf(A->m[j + A->cols]))) return ERR_FUNC;
				/*
				err = drawLine(a,b,c,d);
				if(err!=0) return err;
				*/
			}
		}
	}
	return 0;
}

int matrix_screen2dCords(const MATRIX* const A) {
	size_t i = 0;
	COORD coord = { 0 };

	if (A == NULL) return ERR_NUL;
	if (A->rows <= 1) return ERR_DIM;

	for (; i < A->cols; i++) {
		coord.X = (short)xroundf(A->m[i]);
		coord.Y = (short)xroundf(A->m[i + A->cols]);
		printPixel(coord, 'O');
	}
	return 0;
}

int fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	int i = 0;
	int j = 0;
	int dy = 0;
	double m = 0;
	// all three different points for a triangle
	if ((x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3))	return ERR_PARA;

	//sort pairs in increasing order on x's, rename min of set of x's to x1, then the line with x2 and x3 is where we draw to
	if (x2 < x1) {
		xswap(&x1, &x2, sizeof(int));
		xswap(&y1, &y2, sizeof(int));
	}
	if (x3 < x1) {
		xswap(&x1, &x3, sizeof(int));
		xswap(&y1, &y3, sizeof(int));
	}
	if (x3 < x2) {
		xswap(&x2, &x3, sizeof(int));
		xswap(&y2, &y3, sizeof(int));
	}

	//vertical line
	if (x2 == x3) {
		//make y2 our min
		if (y3 < y2) { xswap(&y3, &y2, sizeof(int)); }

		for (i = y2; i < (y3 + 1); i++) {
			drawLine(x1, y1, x2, i);
		}

	}
	//non vertical line
	else {
		m = (double)(y2 - y3) / (x2 - x3);

		//dy is the height of a vertical line in each iter of x
		if (m == 0) { dy = 1; }
		else if (m == (int)m) { dy = (int)xabsolf(m); }
		else { dy = (int)xabsolf(m) + 1; }

		printf("%f %d %d", m, (int)m, dy);

		for (i = x2; i <= x3; i++) {
			//getchar();
			//y = y2 + m * (i - x2);
			for (j = 0; j < dy; j++) {

				if (m >= 0) {
					drawLine(x1, y1, i, xroundf(y2 + m * (i - x2)) + j);
				}
				else {
					drawLine(x1, y1, i, xroundf(y2 + m * (i - x2)) - j);
				}
			}
		}
	}
	return 0;
}

int matrix_print(const MATRIX* const A, const short v_offset) {
	#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif
	COORD coord = { 0,v_offset };
	size_t i = 0;

	if (A == NULL) return ERR_NUL;
	#ifdef _WIN32
		SetConsoleCursorPosition(hConsole, coord);
	#else
		printf("\033[%d;%dH",coord.Y,coord.X);
	#endif
	for (; i < A->rows * A->cols; i++) {
		if ((i != 0) && i % A->cols == 0) printf("\n");
		printf(" %.4f ", A->m[i]);
	}
	printf("\n");
	/*coord.X = 0;
	coord.Y = 0;
	#ifdef _WIN32
		SetConsoleCursorPosition(hConsole, coord);
	#else
		printf("\033[%d;%dH",coord.Y,coord.X);
	#endif*/

	return 0;
}
