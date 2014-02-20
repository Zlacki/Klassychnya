#include "graphics.h"
#include "util.h"

TTF_Font* load_font(char* file, int ptsize)
{
	TTF_Font* font = TTF_OpenFont(file, ptsize);
	if(!font) {
		printf("Unable to load font: %s %s \n", file, TTF_GetError());
		exit(1);
	}

	return font;
}

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
}

void draw_line_horiz(uint16_t x, uint16_t y, uint16_t width, uint32_t colour)
{
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
}

void draw_line_vert(uint16_t x, uint16_t y, uint16_t height, uint32_t colour)
{
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
}
/*
 void draw_string(char *s, int x, int y, int k, int colour) {
 byte abyte0[] = aByteArrayArray336[k];
 for (int i1 = 0; i1 < s.length(); i1++)
 if (s.charAt(i1) == '@' && i1 + 4 < s.length() && s.charAt(i1 + 4) == '@') {
 if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("red"))
 colour = 0xff0000;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("lre"))
 colour = 0xff9040;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("yel"))
 colour = 0xffff00;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("gre"))
 colour = 65280;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("blu"))
 colour = 255;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("cya"))
 colour = 65535;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("mag"))
 colour = 0xff00ff;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("whi"))
 colour = 0xffffff;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("bla"))
 colour = 0;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("dre"))
 colour = 0xc00000;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("ora"))
 colour = 0xff9040;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("ran"))
 colour = (int) (Math.random() * 16777215D);
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("or1"))
 colour = 0xffb000;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("or2"))
 colour = 0xff7000;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("or3"))
 colour = 0xff3000;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("gr1"))
 colour = 0xc0ff00;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("gr2"))
 colour = 0x80ff00;
 else if (s.substring(i1 + 1, i1 + 4).equalsIgnoreCase("gr3"))
 colour = 0x40ff00;
 i1 += 4;
 } else if (s.charAt(i1) == '~' && i1 + 4 < s.length() && s.charAt(i1 + 4) == '~') {
 char c = s.charAt(i1 + 1);
 char c1 = s.charAt(i1 + 2);
 char c2 = s.charAt(i1 + 3);
 if (c >= '0' && c <= '9' && c1 >= '0' && c1 <= '9' && c2 >= '0' && c2 <= '9')
 x = Integer.parseInt(s.substring(i1 + 1, i1 + 4));
 i1 += 4;
 } else {
 int j1 = anIntArray337[s.charAt(i1)];
 if (loggedIn && !aBooleanArray349[k] && colour != 0)
 method257(j1, x + 1, y, 0, abyte0, aBooleanArray349[k]);
 if (loggedIn && !aBooleanArray349[k] && colour != 0)
 method257(j1, x, y + 1, 0, abyte0, aBooleanArray349[k]);
 method257(j1, x, y, colour, abyte0, aBooleanArray349[k]);
 x += abyte0[j1 + 7];
 }

 return;
 }*/

void draw_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t colour)
{
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
}

void fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
	SDL_Rect rect = { x, y, width, height };
	SDL_FillRect(surface, &rect, color);
}

void show_loading_progress(uint8_t i, char *s)
{
	int j = (WIDTH - 281) / 2;
	int k = (HEIGHT - 148) / 2;
	j += 2;
	k += 90;
	loading_percent = i;
	loading_text = s;
	int l = (277 * i) / 100;
	fill_rect(j, k, l, 20, SDL_MapRGB(surface->format, 132, 132, 132));
	fill_rect(j + l, k, 277 - l, 20, SDL_MapRGB(surface->format, 255, 255, 255));
//	graphics.setColor(new Color(198, 198, 198));
//	drawString(graphics, s, font_timesroman_15, j + 138, k + 10);
}

void draw_button(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
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
}
/*
 void load_jagex() {
 draw_box(0, 0, WIDTH, HEIGHT, SDL_MapRGB(surface->format, 255, 255, 255));
 uint8_t *buff = readDataFile("jagex.jag", "Jagex library", 0);
 if (buff != null) {
 byte logo[] = Utility.loadData("logo.tga", 0, buff);
 image_logo = createImage(logo);
 Surface.createFont("h11p", 0, this);
 Surface.createFont("h12b", 1, this);
 Surface.createFont("h12p", 2, this);
 Surface.createFont("h13b", 3, this);
 Surface.createFont("h14b", 4, this);
 Surface.createFont("h16b", 5, this);
 Surface.createFont("h20b", 6, this);
 Surface.createFont("h24b", 7, this);
 }
 }*/

