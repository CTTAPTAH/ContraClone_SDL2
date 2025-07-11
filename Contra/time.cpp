#include "time.h"

void FPS(Time& time)
{
	time.newtime = SDL_GetTicks();
	time.dt = time.newtime - time.lasttime; // Время всех операций между кадрами
	if (time.dt < 1000 / time.fps) {
		SDL_Delay(1000 / time.fps - time.dt); // Задержка, чтобы fps был равен указанном у
		time.newtime = SDL_GetTicks();
		time.dt = time.newtime - time.lasttime; // Время всех операций между кадрами + задержка
	}
	time.lasttime = time.newtime;
}