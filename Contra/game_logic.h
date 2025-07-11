#pragma once
#include "time.h"
#include "game_mode.h"

void AnimScrolling(Background& background, Time& time, Player& player, Boss& boss);
void PlayBoss(Boss& boss, Player& player, Background& background, Time& time, Border& border,
	List& player_bullet_list, List& boss_bullet_list);
void Game(Player& player, List& enemy_run_list, Time& time, Background& background, Border& border, List& player_bullet_list,
	EnemyRunSpawner& enemy_run_spawner, Boss& boss, List& boss_bullet_list);