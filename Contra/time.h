#pragma once
#include <SDL_image.h>

struct Time
{
	const int fps = 60;
	int newtime, lasttime = SDL_GetTicks(), dt;
};

void FPS(Time& time);