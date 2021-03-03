#include "xdraw.h"
#include "xmatrix.h"
#include "xadj.h"

int main(void){
    MATRIX A = { 0 };

    matrix_init(&A,4,4,0);
    matrix_setList(&A,"1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,");
    matrix_print(&A,0);

    matrix_REF(&A,0);
    matrix_print(&A,5);

    return 0;
}
