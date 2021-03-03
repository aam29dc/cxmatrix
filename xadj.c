#include "xadj.h"

int adj_init(size_t** adj, const size_t size) {
	size_t i = 0;

	if (size <= 1) return ERR_PARA;

	if (*adj != NULL) free(*adj);

	if ((*adj = malloc(sizeof(size_t) * size)) == NULL) return ERR_MEM;	// dont need cast

	for (; i < size; i++) {
		(*adj)[i] = i + 1;
	}

	return 0;
}

int adj_set(size_t** const adj, const size_t size, const char* const list) {
	size_t i = 0;
	size_t j = 0;
	if (*adj == NULL) return 1;
	if (size <= 1) return ERR_PARA;

	for (j = 0; j < size; j++) {
		if (!(list[i] == '0' || list[i] == '1' || list[i] == ',')) return ERR_COMP;
		if (list[i] == ',') { i++; }
		(*adj)[j] = list[i] - '0';
		i++;
	}

	return 0;
}

int adj_print(const size_t* const adj, const size_t rows, const size_t cols) {
	size_t i = 0;
	size_t j = 0;

	if (adj == NULL) return 1;
	if (rows * cols <= 1) return ERR_PARA;

	for (; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			printf("%lu ", (unsigned long)adj[i + (j * cols)]);
		}
	}

	return 0;
}
