#pragma once
#include "map.h"
#include "player.h"
#include "list.h"
#include "boss.h"
#include "enemy.h"

void SaveGame(Background background, Player player, List player_bullet_list, EnemyRunSpawner enemy_run_spawner,
	List enemy_run_list, Boss boss, List boss_bullet_list);
void LoadGame(Background& background, Player& player, List& player_bullet_list, EnemyRunSpawner& enemy_run_spawner,
	List& enemy_run_list, Boss& boss, List& boss_bullet_list);