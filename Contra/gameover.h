#pragma once
#include "game_mode.h"

void CleanGame(Player& player, Background& background, List& player_bullet_list, List& enemy_run_list, List& boss_bullet_list, Boss& boss);
void GameOverRender(SDL_Rect& cursor);
void GameOver(Player& player, Background& background, List& player_bullet_list, List& enemy_run_list, Border& border,
	List& boss_bullet_list, Boss& boss);