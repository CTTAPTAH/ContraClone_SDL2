#pragma once
#include "player.h"
#include "boss.h"
#include "enemy.h"
#include "map.h"
#include "list.h"

// Информация об игре
void F3Mod(Player player, Background background, Border border, List player_bullet_list, List enemy_run_list);
void F3ModBoss(Player player, Background background, Border border, List player_bullet_list, Boss boss, List boss_bullet_list);