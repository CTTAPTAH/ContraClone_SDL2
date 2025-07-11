#include "animation.h"

void Animation(SDL_Rect& rect_animation, int dt, InfoAnimation& anim)
{
	anim.cur_frametime += dt;
	if (anim.cur_frametime >= anim.max_frametime) {
		anim.cur_frametime -= anim.max_frametime;
		anim.frame = (anim.frame + 1) % anim.count_frame;
		rect_animation.x = rect_animation.w * anim.frame;
	}
}