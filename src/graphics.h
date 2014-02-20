#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

void draw_button(uint16_t, uint16_t, uint16_t, uint16_t);
void fill_rect(uint16_t, uint16_t, uint16_t, uint16_t, uint32_t);
void show_loading_progress(uint8_t, char *);

SDL_Surface *surface;
uint16_t bounds_top_x, bounds_bottom_x, bounds_top_y, bounds_bottom_y, bounds_width, bounds_height;
uint8_t loading_percent, old_ticks;
char *loading_text;

#endif
