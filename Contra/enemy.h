#pragma once
#include <SDL.h>
#include "animation.h"
#include "map.h"
#include "list.h"
#include "time.h"
#include "player.h"

struct EnemyRunSpawner
{
	int timer = 1 * 1000;
	int stopwatch = SDL_GetTicks() + timer;
};
struct EnemyRun
{
	InfoAnimation anim = { 0, 8, 1000 / 8, 0 };
	SDL_Rect area_anim_run;
	SDL_Rect position;
	SDL_Rect boot = { 26, 177, 29, 3 };
	SDL_Rect hitbox = { 0, 46, 92, 134 }; // y = pos + 46, h = 180 + 46
	//bool is_jumping = false;
	bool is_falling = false;
	int jump_finish_y = 0;
};

// Бегующий враг
EnemyRun* EnemyRunCreate(Background background, Texture& texture);
void EnemyRunSpawn(List& list, EnemyRunSpawner& spawner, Background background, Texture& texture);
void EnemyRunRender(EnemyRun enemy_run, Texture texture);
void EnemyRunAllRender(List& list, Texture texture);
void EnemyRunMovePosition(EnemyRun& enemy_run, int x, int y);
void EnemyRunSetPosition(EnemyRun& enemy_run, int x, int y);
void EnemyRunDefHitbox(EnemyRun& enemy_run, Background& background);
void EnemyRunUpdatePositionX(EnemyRun& enemy_run, Background background, Time time, double ds);
void EnemyRunUpdatePositionY(EnemyRun& enemy_run, Border border, Time time);
void EnemyRunAllUpdatePosition(List& list, Background background, Border border, Time time, double ds);
void EnemyRunAnimation(EnemyRun& enemy_run, int dt);
void EnemyRunAllAnimation(List& list, Time time);
// Коллизия с бегуюшим врагом
void EnemyRunCheckAllColisionHitbox(Player& player, Background& background, List& list_bullet, List& list_enemy, Border border, Time time);