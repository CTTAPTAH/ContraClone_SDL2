#pragma once
#include "animation.h"
#include "map.h"
#include "time.h"
#include "player.h"

struct Boss
{
	SDL_Rect area_anim;
	InfoAnimation anim;

	SDL_Rect position;
	SDL_Rect hitbox;
	int reload;
	int hp = 25;
	int phase = 1;
};
struct BossBullet
{
	int phase;
	SDL_Rect area;
	SDL_Rect position, glob_pos;

	int jump_finish_y;

	int dir_x, dir_y;
};

// Босс
void BossCreate(Boss& boss);
void BossDefHitbox(Boss& boss, Background& background);
void BossAnimation(Boss& boss, Time& time);
void BossRender(Boss& boss);
void BossRemovingHealth(Boss& boss, Background& background);
// Пули босса
void BossBulletDefHitbox(BossBullet& boss_bullet);
BossBullet* BossBulletCreate(Boss& boss);
void BossBulletShoot(List& boss_bullet_list, Boss& boss, Time& time);
void BossBulletUpdatePosition(BossBullet& boss_bullet, Player& player, Time& time, Border& border);
void BossBulletAllUpdatePosition(List& boss_bullet_list, Player& player, Time& time, Border& border);
void BossBulletAllRender(List& boss_bullet_list);
// Коллизии босса
void BossBulletCheckAllColisionHitbox(Player& player, List& boss_bullet_list, Background& background, Border& border,
	Time& time, List& player_bullet_list);
void BossCheckAllColisionHitbox(Player& player, Background& background, List& player_bullet_list, Boss& boss, Time& time);