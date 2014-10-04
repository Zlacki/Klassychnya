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

size_t text_pt_width(char *text)
{
	return -1;
}

size_t text_pt_height(size_t pt) {
	switch(pt) {
		case 0:
			return 12;
		case 1:
		case 2:
			return 14;
		case 3:
		case 4:
			return 15;
		case 5:
			return 19;
		case 6:
			return 24;
		case 7:
			return 29;
		default:
			return -1;
	}
}
