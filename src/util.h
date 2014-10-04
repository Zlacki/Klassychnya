#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include <stdio.h>

#define WIDTH 512
#define HEIGHT 384

typedef enum { WAITING, RENDERING } renderloop_t;

typedef struct {
	void *TODO;
} npc_t;

renderloop_t RENDER_LOOP;

void *safe_malloc(size_t);
size_t text_width(char *);
size_t text_pt_height(size_t);

#endif
