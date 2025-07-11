#pragma once
#include <SDL_image.h>
#include "helper.h"

struct Texture
{
	SDL_Texture* background1, * background2, * background3, * background4;
	SDL_Rect background_area;
	SDL_Texture* platforms;

	SDL_Texture* player_anim_run_left, * player_anim_run_right, * player_anim_run_up_right,
		* player_anim_run_up_left, * player_anim_run_down_right, * player_anim_run_down_left,
		* player_anim_shoot_run_left, * player_anim_shoot_run_right, * player_up_right,
		* player_up_left, * player_lie_right, * player_lie_left, * player_stay_right,
		* player_stay_left, * player_anim_jump_right, * player_anim_jump_left,
		* player_falling_left, * player_falling_right;
	SDL_Rect player_area_anim_run_right, player_area_anim_run_left, player_area_anim_run_up_right,
		player_area_anim_run_up_left, player_area_anim_run_down_right,
		player_area_anim_run_down_left, player_area_anim_shoot_run_left, player_area_anim_shoot_run_right,
		player_area_up_right, player_area_up_left, player_area_lie_right, player_area_lie_left,
		player_area_stay_right, player_area_stay_left, player_area_jump_right, player_area_jump_left,
		player_area_falling_left, player_area_falling_right;
	SDL_Texture* medal;
	SDL_Rect medal_area;

	SDL_Texture* player_bullet;
	SDL_Rect player_bullet_area;

	SDL_Texture* enemy_anim_run;
	SDL_Rect enemy_area_anim_run;

	SDL_Texture* menu;
	SDL_Rect menu_area;

	SDL_Texture* boss, * boss_bullet1, * boss_bullet2, * boss_bullet2_180, * boss_bullet3;
	SDL_Rect boss_area, boss_bullet1_area, boss_bullet2_area, boss_bullet3_area;
};

SDL_Texture* LoadTexture(const char* filename, SDL_Rect& rect);
// Загрузка текстур
void InitTexture(Texture& texture);
void DestroyAllTexture(Texture& texture);