#pragma once
#include "gameover.h"

void WinRender(SDL_Rect& cursor);
void Win(Player& player, Background& background, List& player_bullet_list, List& enemy_run_list, Border& border,
	List& boss_bullet_list, Boss& boss);