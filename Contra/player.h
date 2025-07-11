#pragma once
#include <SDL.h>
#include "animation.h"
#include "map.h"
#include "time.h"
#include "list.h"

struct Player
{
	SDL_Rect area_anim_run_right, area_anim_run_left, area_anim_run_up_right,
		area_anim_run_up_left, area_anim_run_down_right,
		area_anim_run_down_left, area_anim_shoot_run_left, area_anim_shoot_run_right,
		area_up_right, area_up_left, area_lie_right,
		area_lie_left, area_stay_right, area_stay_left, area_jump_right, area_jump_left,
		area_falling_left, area_falling_right;
	InfoAnimation anim_run_right, anim_run_left, anim_run_up_right, anim_run_up_left,
		anim_run_down_right, anim_run_down_left, anim_shoot_run_left, anim_shoot_run_right,
		anim_jump_right, anim_jump_left, anim_stay_right, anim_stay_left;

	SDL_Rect position;
	//SDL_Rect boot_left = { 48, 176, 32, 4 }, boot_right = { 16, 176, 32, 4 };
	SDL_Rect hitbox_boot;
	//SDL_Rect hitbox_jump = { 0, 116, 80, 64}, hitbox_left = { 44, 48, 52, 136}, hitbox_right = { 0, 48, 52, 136};
	SDL_Rect hitbox;
	//SDL_Rect prev_hitbox;
	// Состояния
	bool stay_right = true, stay_up_right = false, stay_up_left = false,
		lie_right = false, lie_left = false, jump = false, jump_right = false,
		jump_left = false, run_right = false, run_left = false, run_up_right = false,
		run_up_left = false, run_down_right = false, run_down_left = false,
		shoot_run_left = false, shoot_run_right = false, run_left_right = false,
		get_off = false;

	bool is_jumping = false, is_falling = false, shoot = false;
	bool invincibil = false;
	int jump_finish_y = 0, shoot_time_start = 0, timer_invincibil = 0;
	int hp = 2;
};
struct PlayerBullet
{
	SDL_Rect area;
	SDL_Rect position;
	SDL_Rect global_pos;

	int dir_x;
	int dir_y;
};

// Игровой персонаж
void PlayerCreate(Player& player, Texture& texture);
void PlayerMovePosition(Player& player, int x, int y);
void PlayerSetPosition(Player& player, int x, int y);
void PlayerDefHitbox(Player& player, Background& background);
void PlayerUpdateState(Player& player);
void PlayerAnimation(Player& player, Time time);
void PlayerRender(Player player, Texture texture);
void PlayerUpdatePositionX(Player& player, Background background, Border border, Time time);
double PlayerCalculateDS(Player player, Background background);
void PlayerAdjustPosition(Player& player, Border border, double ds);
void PlayerUpdatePositionY(Player& player, Border border, Time time);
void PlayerUpdatePosition(Player& player, Background background, Border border, Time time, double& ds);
void PlayerRenderMedal(Player& player);
void PlayerRemovingHealth(Player& player, Background& background);
void PlayerInvincible(Player& player, Time& time);
// Пули игрового персонажа
PlayerBullet* PlayerBulletCreate(Player player, Texture& texture, Background background);
void PlayerBulletRender(PlayerBullet& player_bullet, Texture& texture);
void PlayerBulletHandleShooting(List& player_bullet_list, Player player, Texture texture, Background background);
void PlayerBulletAllRender(List& player_bullet_list, Texture texture);
void PlayerBulletDefHitbox(PlayerBullet& player_bullet, Background background);
void PlayerBulletUpdatePosition(PlayerBullet& player_bullet, Time time, Background background, double ds);
void PlayerBulletAllUpdatePosition(List& player_bullet_list, Time time, Background background, double ds);