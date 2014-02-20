#include "graphics.h"
#include "util.h"

static void process_game(void)
{
	int current_ticks, wait_ticks;
	current_ticks = SDL_GetTicks();
	wait_ticks = (old_ticks + 14 - current_ticks);
	old_ticks = current_ticks;

	if(wait_ticks > 0) SDL_Delay(wait_ticks);

	SDL_LockSurface(surface);
	fill_rect(0, 0, WIDTH, HEIGHT, 0x0);
	draw_button(WIDTH / 2 - 100, 290, 200, 35);
	SDL_UnlockSurface(surface);

	SDL_Flip(surface);
}

static void cleanup(void)
{
	SDL_Quit();
}

static void init_frame(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SEVERE: Could not initialize the SDL.\n");
		exit(1);
	}
	atexit(cleanup);

	SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_HWPALETTE);
	if(screen == NULL ) {
		printf("SEVERE: Could not create window.\n");
		exit(1);
	}

	SDL_WM_SetCaption("Untitled Game by Aleksandr Volkov - PRE-ALPHA UNVERSIONED", NULL );

	surface = screen;
}

#if defined (DARWIN) || defined (WIN32)
int SDL_main(int argc, char *argv[])
{
#else
int main(int argc, char *argv[])
{
#endif
	printf("THIS IS ONLY A PROTOTYPE FOR MY GAME CLIENT!\nIT IS PROBABLY FAR FROM FINISHED.\n\n");
	puts("Loading game...");
	init_frame();
	fill_rect(0, 0, WIDTH, HEIGHT, 0x0);
	//read_data_file("./cache/jagex.jag", "JaGEx library", 15);
	for(;;) {
		process_game();

		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					SDL_Quit();
					exit(0);
					break;
				default:
					printf("Unhandled event.\n");
			}
		}

		SDL_Delay(60);
	}

	return 0;
}
