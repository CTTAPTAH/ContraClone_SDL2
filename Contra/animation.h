#pragma once
#include <SDL.h>

struct InfoAnimation
{
	int frame, count_frame;
	double max_frametime, cur_frametime;
};

void Animation(SDL_Rect& rect_animation, int dt, InfoAnimation& anim);