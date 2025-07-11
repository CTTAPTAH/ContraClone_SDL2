#pragma once
#include "save_load.h"
#include "font.h"

void RenderMenu(Font& font, Text& text, SDL_Rect& cursor);
void RenderNotification(Font& font, Text& text, int stopwatch, char notification[]);
void Menu(Texture& texture, Time& time, Font& font, Text& text, Background& background, Player& player,
	List& player_bullet_list, EnemyRunSpawner& enemy_run_spawner, List& enemy_run_list, Boss& boss, List& boss_bullet_list);
