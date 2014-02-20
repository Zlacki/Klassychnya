/**
 *
 * SLACKNET CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2013] SlackNet, LLC
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of SlackNet, LLC and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to SlackNet, LLC
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from SlackNet, LLC.
 */

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL/SDL.h>

void draw_button(uint16_t, uint16_t, uint16_t, uint16_t);
void fill_rect(uint16_t, uint16_t, uint16_t, uint16_t, uint32_t);
void show_loading_progress(uint8_t, char *);

SDL_Surface *surface;
uint16_t bounds_top_x, bounds_bottom_x, bounds_top_y, bounds_bottom_y, bounds_width, bounds_height;
uint8_t loading_percent, old_ticks;
char *loading_text;

#endif
