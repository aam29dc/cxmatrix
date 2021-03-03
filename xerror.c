#include "xerror.h"

const char* const ERR_MSG[] = {
	"ERROR_OK",
	"ERROR_NULL",
	"ERROR_ZERO",
	"ERROR_DIMENSION",
	"ERROR_BAD_PARAMETER",
	"ERROR_FUNCTION",
	"ERROR_INIT",
	"ERROR_MEMORY",
	"ERROR_DIVIDE_BY_ZERO",
	"ERROR_BAD_COMPARISON"
};

const char* print_err(const ERR err){
	if(err >= ERR_COUNT) return 0;
	return ERR_MSG[err];
}
