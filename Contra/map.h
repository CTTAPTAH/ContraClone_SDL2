#pragma once
#include <SDL.h>
#include "config.h"
#include "globals.h"

struct Background
{
	SDL_Rect area_background;
	SDL_Rect camera;
};
struct Border
{
	SDL_Rect platforms[AMOUNT_PLATFORMS] = { { 0, 768, 10240, 128 }, {512, 512, 256, 128}, {896, 384, 640, 128},
		{896, 640, 128, 128}, {1664, 256, 384, 128}, {1664, 640, 256, 128}, {2048, 512, 1152, 128}, {3328, 384, 512, 128},
		{3328, 640, 128, 128}, {3968, 256, 768, 128}, {4224, 640, 256, 128}, {4608, 512, 2048, 128}, {4864, 256, 640, 128},
		{5632, 256, 256, 128}, {6016, 256, 256, 128}, {6400, 256, 640, 128}, {6784, 640, 256, 128}, {7168, 512, 768, 128},
		{8064, 384, 512, 128}, {8704, 512, 256, 128} };
	int border_left = 50, border_right = win_width - 100;
};

int SearchCoordsEntityOnPlatform(SDL_Rect boot, Border border, double vector_y);
// Задний фон
void BackgroundRender(Background background, Texture texture);
void BackgroundUpdatePositionX(Background& background, double ds);