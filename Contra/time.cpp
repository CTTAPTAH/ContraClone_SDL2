#include "time.h"

void FPS(Time& time)
{
	time.newtime = SDL_GetTicks();
	time.dt = time.newtime - time.lasttime; // ����� ���� �������� ����� �������
	if (time.dt < 1000 / time.fps) {
		SDL_Delay(1000 / time.fps - time.dt); // ��������, ����� fps ��� ����� ��������� �
		time.newtime = SDL_GetTicks();
		time.dt = time.newtime - time.lasttime; // ����� ���� �������� ����� ������� + ��������
	}
	time.lasttime = time.newtime;
}