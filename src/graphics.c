#include "graphics.h"
#include "util.h"

void set_bounds(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if(x1 < 0) x1 = 0;
	if(y1 < 0) y1 = 0;
	if(x2 > WIDTH) x2 = WIDTH;
	if(y2 > HEIGHT) y2 = HEIGHT;
	bounds_top_x = x1;
	bounds_top_y = y1;
	bounds_bottom_x = x2;
	bounds_bottom_y = y2;
}

void reset_bounds()
{
	bounds_top_x = 0;
	bounds_top_y = 0;
	bounds_bottom_x = WIDTH;
	bounds_bottom_y = HEIGHT;
}

void draw_gradient(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t colour_top,
		uint32_t colour_bottom)
{
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(x < bounds_top_x) {
		width -= bounds_top_x - x;
		x = bounds_top_x;
	}
	if(x + width > bounds_bottom_x) width = bounds_bottom_x - x;
	int btm_red = colour_bottom >> 16 & 0xff;
	int btm_green = colour_bottom >> 8 & 0xff;
	int btm_blue = colour_bottom & 0xff;
	int top_red = colour_top >> 16 & 0xff;
	int top_green = colour_top >> 8 & 0xff;
	int top_blue = colour_top & 0xff;
	int i3 = WIDTH - width;
	uint8_t vert_inc = 1;
	int pixel_idx = x + y * WIDTH;
	for(int k3 = 0; k3 < height; k3 += vert_inc)
		if(k3 + y >= bounds_top_y && k3 + y < bounds_bottom_y) {
			int new_colour = ((btm_red * k3 + top_red * (height - k3)) / height << 16)
					+ ((btm_green * k3 + top_green * (height - k3)) / height << 8)
					+ (btm_blue * k3 + top_blue * (height - k3)) / height;
			for(int i4 = -width; i4 < 0; i4++) {
				uint32_t *pixels = surface->pixels;
				pixels[pixel_idx++] = new_colour;
			}

			pixel_idx += i3;
		} else {
			pixel_idx += WIDTH;
		}

	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void draw_line_horiz(uint16_t x, uint16_t y, uint16_t width, uint32_t colour)
{
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(y < bounds_top_y || y >= bounds_bottom_y) return;
	if(x < bounds_top_x) {
		width -= bounds_top_x - x;
		x = bounds_top_x;
	}
	if(x + width > bounds_bottom_x) width = bounds_bottom_x - x;
	int i1 = x + y * WIDTH;
	for(int j1 = 0; j1 < width; j1++) {
		uint32_t *pixels = surface->pixels;
		pixels[i1 + j1] = colour;
	}
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void draw_line_vert(uint16_t x, uint16_t y, uint16_t height, uint32_t colour)
{
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(x < bounds_top_x || x >= bounds_bottom_x) return;
	if(y < bounds_top_y) {
		height -= bounds_top_y - y;
		y = bounds_top_y;
	}
	if(y + height > bounds_bottom_x) height = bounds_bottom_y - y;
	int i1 = x + y * WIDTH;
	for(int j1 = 0; j1 < height; j1++) {
		uint32_t *pixels = surface->pixels;
		pixels[i1 + j1 * WIDTH] = colour;
	}
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void draw_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t colour)
{
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(x < bounds_top_x) {
		w -= bounds_top_x - x;
		x = bounds_top_x;
	}
	if(y < bounds_top_y) {
		h -= bounds_top_y - y;
		y = bounds_top_y;
	}
	if(x + w > bounds_bottom_x) w = bounds_bottom_x - x;
	if(y + h > bounds_bottom_y) h = bounds_bottom_y - y;
	int j1 = WIDTH - w;
	uint8_t vert_inc = 1;
	int pixel_idx = x + y * WIDTH;
	for(int l1 = -h; l1 < 0; l1 += vert_inc) {
		for(int i2 = -w; i2 < 0; i2++) {
			uint32_t *pixels = surface->pixels;
			pixels[pixel_idx++] = colour;
		}

		pixel_idx += j1;
	}
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void draw_button(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	set_bounds(x, y, x + width, y + height);
	draw_gradient(x, y, width, height, SDL_MapRGB(surface->format, 84, 93, 120),
			SDL_MapRGB(surface->format, 135, 146, 179));
	draw_line_horiz(x, y, width, SDL_MapRGB(surface->format, 135, 146, 179));
	draw_line_horiz(x + 1, y + 1, width - 2, SDL_MapRGB(surface->format, 135, 146, 179));
	draw_line_horiz(x + 2, y + 2, width - 4, SDL_MapRGB(surface->format, 97, 112, 151));
	draw_line_vert(x, y, height, SDL_MapRGB(surface->format, 135, 146, 179));
	draw_line_vert(x + 1, y + 1, height - 2, SDL_MapRGB(surface->format, 135, 146, 179));
	draw_line_vert(x + 2, y + 2, height - 4, SDL_MapRGB(surface->format, 97, 112, 151));
	draw_line_horiz(x, (y + height) - 1, width, SDL_MapRGB(surface->format, 84, 93, 120));
	draw_line_horiz(x + 1, (y + height) - 2, width - 2, SDL_MapRGB(surface->format, 84, 93, 120));
	draw_line_horiz(x + 2, (y + height) - 3, width - 4, SDL_MapRGB(surface->format, 88, 102, 136));
	draw_line_vert((x + width) - 1, y, height, SDL_MapRGB(surface->format, 84, 93, 120));
	draw_line_vert((x + width) - 2, y + 1, height - 2, SDL_MapRGB(surface->format, 84, 93, 120));
	draw_line_vert((x + width) - 3, y + 2, height - 4, SDL_MapRGB(surface->format, 88, 102, 136));
	reset_bounds();
	SDL_FreeSurface(surface);
}

void draw_text(uint16_t x, uint16_t y, char *text, uint16_t size) {

	TTF_Font *arial = TTF_OpenFont("res/arialbd.ttf", size);
	SDL_Color white = { 0x00, 0x00, 0x00 };
	SDL_Surface *surface = TTF_RenderText_Solid(arial, text, white);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	if(x < bounds_top_x) {
		w -= bounds_top_x - x;
		x = bounds_top_x;
	}

	if(y < bounds_top_y) {
		h -= bounds_top_y - y;
		y = bounds_top_y;
	}

	if(x + w > bounds_bottom_x) w = bounds_bottom_x - x;
	if(y + h > bounds_bottom_y) h = bounds_bottom_y - y;

	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(arial);
}
