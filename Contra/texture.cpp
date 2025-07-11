#include "texture.h"

SDL_Texture* LoadTexture(const char* filename, SDL_Rect& rect)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == nullptr) {
		printf_s("Не удалось загрузить картинку %s. Ошибка: %s\n", filename, SDL_GetError());
		DeInitSDL(1);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	rect = { 0, 0, surface->w, surface->h };
	SDL_FreeSurface(surface);
	return texture;
}
// Загрузка текстур
void InitTexture(Texture& texture)
{
	texture.platforms = LoadTexture("texture\\platforms.png", texture.background_area);
	texture.background1 = LoadTexture("texture\\background1.png", texture.background_area);
	texture.background1 = LoadTexture("texture\\background1.png", texture.background_area);
	texture.background2 = LoadTexture("texture\\background2.png", texture.background_area);
	texture.background3 = LoadTexture("texture\\background3.png", texture.background_area);
	texture.background4 = LoadTexture("texture\\background4.png", texture.background_area);

	texture.player_anim_run_right = LoadTexture("texture\\run_right.png", texture.player_area_anim_run_right);
	texture.player_area_anim_run_right.w = texture.player_area_anim_run_right.h;
	texture.player_anim_run_left = LoadTexture("texture\\run_left.png", texture.player_area_anim_run_left);
	texture.player_area_anim_run_left.w = texture.player_area_anim_run_left.h;
	texture.player_anim_run_up_right = LoadTexture("texture\\run_up_right.png", texture.player_area_anim_run_up_right);
	texture.player_area_anim_run_up_right.w = texture.player_area_anim_run_up_right.h;
	texture.player_anim_run_up_left = LoadTexture("texture\\run_up_left.png", texture.player_area_anim_run_up_left);
	texture.player_area_anim_run_up_left.w = texture.player_area_anim_run_up_left.h;
	texture.player_anim_run_down_right = LoadTexture("texture\\run_down_right.png", texture.player_area_anim_run_down_right);
	texture.player_area_anim_run_down_right.w = texture.player_area_anim_run_down_right.h;
	texture.player_anim_run_down_left = LoadTexture("texture\\run_down_left.png", texture.player_area_anim_run_down_left);
	texture.player_area_anim_run_down_left.w = texture.player_area_anim_run_down_left.h;
	texture.player_anim_shoot_run_left = LoadTexture("texture\\shoot_run_left.png", texture.player_area_anim_shoot_run_left);
	texture.player_area_anim_shoot_run_left.w = texture.player_area_anim_shoot_run_left.h;
	texture.player_anim_shoot_run_right = LoadTexture("texture\\shoot_run_right.png", texture.player_area_anim_shoot_run_right);
	texture.player_area_anim_shoot_run_right.w = texture.player_area_anim_shoot_run_right.h;
	texture.player_up_right = LoadTexture("texture\\up_right.png", texture.player_area_up_right);
	texture.player_up_left = LoadTexture("texture\\up_left.png", texture.player_area_up_left);
	texture.player_lie_right = LoadTexture("texture\\lie_right.png", texture.player_area_lie_right);
	texture.player_lie_left = LoadTexture("texture\\lie_left.png", texture.player_area_lie_left);
	texture.player_stay_right = LoadTexture("texture\\stay_right.png", texture.player_area_stay_right);
	texture.player_area_stay_right.w = texture.player_area_stay_right.h;
	texture.player_stay_left = LoadTexture("texture\\stay_left.png", texture.player_area_stay_left);
	texture.player_area_stay_left.w = texture.player_area_stay_left.h;
	texture.player_anim_jump_right = LoadTexture("texture\\jump_right.png", texture.player_area_jump_right);
	texture.player_area_jump_right.w = texture.player_area_jump_right.h;
	texture.player_anim_jump_left = LoadTexture("texture\\jump_left.png", texture.player_area_jump_left);
	texture.player_area_jump_left.w = texture.player_area_jump_left.h;
	texture.player_falling_left = LoadTexture("texture\\falling_left.png", texture.player_area_falling_left);
	texture.player_falling_right = LoadTexture("texture\\falling_right.png", texture.player_area_falling_right);

	texture.player_bullet = LoadTexture("texture\\Player_bullet.png", texture.player_bullet_area);

	texture.enemy_anim_run = LoadTexture("texture\\enemy_run.png", texture.enemy_area_anim_run);
	texture.enemy_area_anim_run.w = texture.enemy_area_anim_run.h;

	texture.menu = LoadTexture("texture\\menu.png", texture.menu_area);

	texture.medal = LoadTexture("texture\\medal.png", texture.medal_area);

	texture.boss = LoadTexture("texture\\boss.png", texture.boss_area);
	texture.boss_bullet1 = LoadTexture("texture\\boss_bullet1.png", texture.boss_bullet1_area);
	texture.boss_bullet2 = LoadTexture("texture\\boss_bullet2.png", texture.boss_bullet2_area);
	texture.boss_bullet2_180 = LoadTexture("texture\\boss_bullet2_180.png", texture.boss_bullet2_area);
	texture.boss_bullet3 = LoadTexture("texture\\boss_bullet3.png", texture.boss_bullet3_area);
}
void DestroyAllTexture(Texture& texture)
{
	SDL_DestroyTexture(texture.background1);
	SDL_DestroyTexture(texture.background2);
	SDL_DestroyTexture(texture.background3);
	SDL_DestroyTexture(texture.background4);
	SDL_DestroyTexture(texture.platforms);

	SDL_DestroyTexture(texture.player_anim_run_right);
	SDL_DestroyTexture(texture.player_anim_run_left);
	SDL_DestroyTexture(texture.player_anim_run_up_right);
	SDL_DestroyTexture(texture.player_anim_run_up_left);
	SDL_DestroyTexture(texture.player_anim_run_down_right);
	SDL_DestroyTexture(texture.player_anim_run_down_left);
	SDL_DestroyTexture(texture.player_anim_shoot_run_left);
	SDL_DestroyTexture(texture.player_anim_shoot_run_right);
	SDL_DestroyTexture(texture.player_up_right);
	SDL_DestroyTexture(texture.player_up_left);
	SDL_DestroyTexture(texture.player_lie_right);
	SDL_DestroyTexture(texture.player_lie_left);
	SDL_DestroyTexture(texture.player_stay_right);
	SDL_DestroyTexture(texture.player_stay_left);
	SDL_DestroyTexture(texture.player_anim_jump_right);
	SDL_DestroyTexture(texture.player_anim_jump_left);
	SDL_DestroyTexture(texture.player_falling_left);
	SDL_DestroyTexture(texture.player_falling_right);

	SDL_DestroyTexture(texture.player_bullet);

	SDL_DestroyTexture(texture.enemy_anim_run);

	SDL_DestroyTexture(texture.menu);

	SDL_DestroyTexture(texture.medal);

	SDL_DestroyTexture(texture.boss);
	SDL_DestroyTexture(texture.boss_bullet1);
	SDL_DestroyTexture(texture.boss_bullet2);
	SDL_DestroyTexture(texture.boss_bullet2_180);
	SDL_DestroyTexture(texture.boss_bullet3);
}