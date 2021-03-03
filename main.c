#include "xdraw.h"
#include "xmatrix.h"
#include "xadj.h"

int main(void) {
	COORD coord = { 0 };
	MATRIX V = { 0 };			// vertices matrix
	MATRIX P = { 0 };			// projection matrix
	MATRIX Rotatex = { 0 };			// rotation matrix
	MATRIX Rotatey = { 0 };			// rotation matrix
	MATRIX coords = { 0 };			// 2d coordinates matrix for vertices matrix
	size_t* adj = 0;

	//vertices matrix setup
	matrix_init(&V, 4, 8, 0);
	matrix_setList(&V, "5,-5,-5,5,5,-5,-5,5,5,5,-5,-5,5,5,-5,-5,5,5,5,5,-4,-4,-4,-4,1,1,1,1,1,1,1,1,");

	//adjacent matrix setup (what vertices are connected)
	adj_init(&adj, 8 * 8);
	adj_setList(&adj, 8 * 8, "0,1,0,1,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,");

	//projection matrix setup
	matrix_init(&P, 4, 4, 0);
	matrix_setList(&P, "1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,");
	matrix_setEntry(&P, 3, 2, (float)(-1 / 10.0));			// set distance from yx plane

	//coords matrix is form P*V
	matrix_init(&coords, P.rows, V.cols, 0);

	//rotation matrix setup, rotate clockwise y axis
	matrix_init(&Rotatey, 4, 4, 0);
	matrix_setAllDiagonals(&Rotatey, 1);
	matrix_setEntry(&Rotatey, 0, 0, (sqrtf(6) + sqrtf(2)) / 4);	// cos(15 deg)
	matrix_setEntry(&Rotatey, 2, 0, (sqrtf(6) - sqrtf(2)) / 4);	// sin(15 deg)
	matrix_setEntry(&Rotatey, 0, 2, -(sqrtf(6) - sqrtf(2)) / 4);	// -sin(15 deg)
	matrix_setEntry(&Rotatey, 2, 2, (sqrtf(6) + sqrtf(2)) / 4);	// cos(15 deg)

	//rotation matrix setup, rotate clockwise x axis
	matrix_init(&Rotatex, 4, 4, 0);
	matrix_setAllDiagonals(&Rotatex, 1);
	matrix_setEntry(&Rotatex, 1, 1, (sqrtf(6) + sqrtf(2)) / 4);	// cos(15 deg)
	matrix_setEntry(&Rotatex, 2, 1, (sqrtf(6) - sqrtf(2)) / 4);	// sin(15 deg)
	matrix_setEntry(&Rotatex, 1, 2, -(sqrtf(6) - sqrtf(2)) / 4);	// -sin(15 deg)
	matrix_setEntry(&Rotatex, 2, 2, (sqrtf(6) + sqrtf(2)) / 4);	// cos(15 deg)

	while (1) {
		//	multiply vertices by projection matrix
		matrix_multiply(&P, &V, &coords);
		//	divide every col by its 4th entry
		matrix_obtain3dCoords(&coords);
		drawAxis(2);
		matrix_drawEdges(&coords, adj);
		matrix_screen2dCords(&coords);
		//	rotate vertices around x axis
		matrix_multiply(&Rotatex, &V, &V);

		//	rotate vertices around y axis
		matrix_multiply(&Rotatey, &V, &V);

		#ifdef _WIN32
            		system("cls");
        	#else
            		clearScreen();
        	#endif

	}

	return 0;
}
