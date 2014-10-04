#include "graphics.h"
#include "util.h"

int render(void *dummy)
{
	RENDER_LOOP = RENDERING;
	for(;;) {
		if(RENDER_LOOP == RENDERING) {
			SDL_RenderClear(renderer);
			draw_button(WIDTH / 2 - 100, 290, 200, 35);
			draw_text(WIDTH / 2 - 75, 295, "Click here to login", 19);
			SDL_RenderPresent(renderer);
			RENDER_LOOP = WAITING;
		} else
			SDL_Delay(50);
	}
}

static void cleanup(void)
{
	SDL_Quit();
}

static void init_frame(void)
{
	atexit(cleanup);
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		puts("SEVERE: Could not initialize the SDL library.");
		printf("Editors note: %s", SDL_GetError());
		exit(1);
	}
	if(TTF_Init() < 0) {
		puts("SEVERE: Could not initialize the TTF library.");
		exit(1);
	}

	window = SDL_CreateWindow("Klassychnya", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if(window == NULL) {
		puts("SEVERE: Could not create window.");
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

#if defined (DARWIN) || defined (WIN32)
int SDL_main(int argc, char *argv[])
{
#else
int main(int argc, char *argv[])
{
#endif
	puts("Loading application...");
	init_frame();
	SDL_CreateThread(render, "Renderer", NULL);
	SDL_Event event;
	for(;;) {
		if(SDL_WaitEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					exit(0);
					break;
				default:
					printf("Unhandled event.\n");
					break;
			}
		}
	}

	return 0;
}
