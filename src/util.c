#include "util.h"

void *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if(ptr == NULL ) {
		puts("SEVERE: Could not allocate enough memory.");
		exit(1);
	}

	return ptr;
}
