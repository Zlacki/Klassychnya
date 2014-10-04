#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

void draw_button(uint16_t, uint16_t, uint16_t, uint16_t);
void draw_text(uint16_t, uint16_t, char *, uint16_t);

SDL_Window *window;
SDL_Renderer *renderer;
uint16_t bounds_top_x, bounds_bottom_x, bounds_top_y, bounds_bottom_y, bounds_width, bounds_height;

#endif
