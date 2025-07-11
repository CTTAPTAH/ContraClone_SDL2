#include "boss.h"

// Босс
void BossCreate(Boss& boss)
{
	boss.area_anim = texture.boss_area;
	boss.area_anim.w = boss.area_anim.h;
	boss.anim = { 1, 2, 1000 / 2, 0 };

	boss.position = boss.hitbox = boss.area_anim;
	boss.position.x = 1024 - boss.position.w + 50; boss.position.y = 768 - boss.position.h;

	boss.hitbox.w = 236; boss.hitbox.h = 314;
	boss.hitbox.x = (10240 - boss.position.w + 55) + 44; boss.hitbox.y = boss.position.y + 46;

	boss.reload = 1 * 1000;
	boss.hp = config.boss_hp1;
	boss.phase = 1;
}
void BossDefHitbox(Boss& boss, Background& background)
{
	boss.position.x = boss.hitbox.x - background.camera.x - 44; boss.position.y = boss.hitbox.y - 46;
}
void BossAnimation(Boss& boss, Time& time)
{
	Animation(boss.area_anim, time.dt, boss.anim);
}
void BossRender(Boss& boss)
{
	SDL_RenderCopy(ren, texture.boss, &boss.area_anim, &boss.position);
}
void BossRemovingHealth(Boss& boss, Background& background)
{
	boss.hp--;
	if (boss.hp < 0) {
		if (boss.phase < 3) {
			boss.phase++;
			if (boss.phase == 2) {
				boss.hp = config.boss_hp2;
				boss.reload = config.boss_reload2 * 1000;
			}
			else if (boss.phase == 3) {
				boss.hp = config.boss_hp3;
				boss.reload = config.boss_reload3 * 1000;
			}
		}
		else {
			game_state = WIN;
		}
	}
}
//Пули босса
void BossBulletDefHitbox(BossBullet& boss_bullet)
{
	boss_bullet.position.x = boss_bullet.glob_pos.x - 9216; boss_bullet.position.y = boss_bullet.glob_pos.y;
}
BossBullet* BossBulletCreate(Boss& boss)
{
	BossBullet* boss_bullet = (BossBullet*)malloc(sizeof(BossBullet));
	if (!boss_bullet) {
		printf_s("Ошибка создания пули босса на первой фазе: не удалось выделить память для пули\n");
		return NULL;
	}

	if (boss.phase == 1) {
		boss_bullet->area = boss_bullet->position = boss_bullet->glob_pos = texture.boss_bullet1_area;

		boss_bullet->glob_pos.x = boss.hitbox.x - 47; boss_bullet->glob_pos.y = boss.hitbox.y + 131;
		BossBulletDefHitbox(*boss_bullet);

		boss_bullet->jump_finish_y = boss_bullet->glob_pos.y - 40;
		boss_bullet->dir_x = -1; boss_bullet->dir_y = -1;
		boss_bullet->phase = 1;
	}
	else if (boss.phase == 2) {
		boss_bullet->area = boss_bullet->position = boss_bullet->glob_pos = texture.boss_bullet2_area;

		boss_bullet->glob_pos.x = boss.hitbox.x + 180; boss_bullet->glob_pos.y = boss.hitbox.y - 73;
		BossBulletDefHitbox(*boss_bullet);

		boss_bullet->dir_x = 0; boss_bullet->dir_y = -1;
		boss_bullet->phase = 2;
	}
	else if (boss.phase == 3) {
		boss_bullet->area = boss_bullet->position = boss_bullet->glob_pos = texture.boss_bullet3_area;

		boss_bullet->glob_pos.x = boss.hitbox.x + 240 - boss_bullet->area.w;
		boss_bullet->glob_pos.y = boss.hitbox.y - 20 - boss_bullet->area.h;
		BossBulletDefHitbox(*boss_bullet);

		boss_bullet->dir_x = 0; boss_bullet->dir_y = -1;
		boss_bullet->phase = 3;
	}

	return boss_bullet;
}
void BossBulletShoot(List& boss_bullet_list, Boss& boss, Time& time)
{
	if (boss.reload <= 0) {
		ListAdd(boss_bullet_list, BossBulletCreate(boss));
		if (boss.phase == 1) boss.reload = config.boss_reload1 * 1000;
		else if (boss.phase == 2) boss.reload = config.boss_reload2 * 1000;
		else if (boss.phase == 3) boss.reload = config.boss_reload3 * 1000;
	}
	else {
		boss.reload -= time.dt;
	}
}
void BossBulletUpdatePosition(BossBullet& boss_bullet, Player& player, Time& time, Border& border)
{
	if (boss_bullet.phase == 1) {
		boss_bullet.glob_pos.x += boss_bullet.dir_x * config.boss_bullet1_speed * time.dt / 1000;

		if (boss_bullet.glob_pos.y <= boss_bullet.jump_finish_y) boss_bullet.dir_y = 1;

		double vector_y = boss_bullet.dir_y * (config.gravity - 100) * time.dt / 1000;
		int platform_y = SearchCoordsEntityOnPlatform(boss_bullet.position, border, vector_y);
		if (platform_y) boss_bullet.area.y = platform_y + boss_bullet.area.h;
		else boss_bullet.glob_pos.y += vector_y;
	}
	else if (boss_bullet.phase == 2) {
		double vector_y = boss_bullet.dir_y * config.boss_bullet2_speed * time.dt / 1000;
		boss_bullet.glob_pos.y += vector_y;
	}
	else if (boss_bullet.phase == 3) {
		if (boss_bullet.dir_y == -1) {
			double vector_y = boss_bullet.dir_y * config.boss_bullet3_speed * time.dt / 1000;
			boss_bullet.glob_pos.y += vector_y;
		}
		else {
			double vector_x, vector_y;
			double a = player.hitbox.x - boss_bullet.glob_pos.x;
			double b = player.hitbox.y - boss_bullet.glob_pos.y;
			double c = sqrt(a * a + b * b);
			double k = c / (config.boss_bullet3_speed * time.dt / 1000);
			vector_x = a / k;
			vector_y = b / k;
			boss_bullet.glob_pos.x += vector_x;
			boss_bullet.glob_pos.y += vector_y;
		}
	}

	BossBulletDefHitbox(boss_bullet);
}
void BossBulletAllUpdatePosition(List& boss_bullet_list, Player& player, Time& time, Border& border)
{
	for (Elem* cur = boss_bullet_list.head; cur != NULL; cur = cur->next) {
		BossBulletUpdatePosition(*(BossBullet*)cur->data, player, time, border);
	}
}
void BossBulletAllRender(List& boss_bullet_list)
{
	for (Elem* cur = boss_bullet_list.head; cur != NULL; cur = cur->next) {
		BossBullet boss_bullet = *(BossBullet*)cur->data;
		if (boss_bullet.phase == 1) SDL_RenderCopy(ren, texture.boss_bullet1, NULL, &boss_bullet.position);
		else if (boss_bullet.phase == 2) {
			if (boss_bullet.dir_y == 1) SDL_RenderCopy(ren, texture.boss_bullet2_180, NULL, &boss_bullet.position);
			else SDL_RenderCopy(ren, texture.boss_bullet2, NULL, &boss_bullet.position);
		}
		else if (boss_bullet.phase == 3) SDL_RenderCopy(ren, texture.boss_bullet3, NULL, &boss_bullet.position);
	}
}
// Коллизии босса
void BossBulletCheckAllColisionHitbox(Player& player, List& boss_bullet_list, Background& background, Border& border,
	Time& time, List& player_bullet_list)
{
	for (Elem* cur = boss_bullet_list.head; cur != NULL;) {
		Elem* next = cur->next;

		BossBullet* boss_bullet = (BossBullet*)cur->data;
		if (boss_bullet->phase == 1) {
			if (CheckCollisionHitbox(player.hitbox, boss_bullet->glob_pos)) {
				if (!player.invincibil) PlayerRemovingHealth(player, background);
				if (player.hp >= 0) ListDel(boss_bullet_list, cur);
				break;
			}
			else if (boss_bullet->position.x + boss_bullet->position.w < border.border_left or boss_bullet->position.x > border.border_right) {
				ListDel(boss_bullet_list, cur);
			}
		}
		else if (boss_bullet->phase == 2) {
			if (boss_bullet->dir_y == -1 and boss_bullet->position.y + boss_bullet->position.h < 0) {
				boss_bullet->dir_y = 1;

				boss_bullet->area = boss_bullet->position = boss_bullet->glob_pos = texture.boss_bullet2_area;
				boss_bullet->glob_pos.x = Random(9216, 9216 + win_width - 360 - boss_bullet->area.w); boss_bullet->glob_pos.y = -boss_bullet->area.h;
				BossBulletDefHitbox(*boss_bullet);
			}
			else if (CheckCollisionHitbox(boss_bullet->glob_pos, player.hitbox)) {
				if (!player.invincibil) PlayerRemovingHealth(player, background);
				if (player.hp >= 0) ListDel(boss_bullet_list, cur);
				break;
			}
			else if (CheckCollisionHitbox(boss_bullet->glob_pos, border.platforms[0])) {
				ListDel(boss_bullet_list, cur);
			}
		}
		else if (boss_bullet->phase == 3) {
			if (boss_bullet->dir_y == -1 and boss_bullet->position.y + boss_bullet->position.h < 0) {
				boss_bullet->dir_y = 0;

				boss_bullet->area = boss_bullet->position = boss_bullet->glob_pos = texture.boss_bullet3_area;
				boss_bullet->glob_pos.x = Random(9216, 9216 + win_width - 360 - boss_bullet->area.w); boss_bullet->glob_pos.y = -boss_bullet->area.h;
				BossBulletDefHitbox(*boss_bullet);
			}
			else if (CheckCollisionHitbox(boss_bullet->glob_pos, player.hitbox)) {
				if (!player.invincibil) PlayerRemovingHealth(player, background);
				if (player.hp >= 0) ListDel(boss_bullet_list, cur);
				break;
			}
			else if (CheckCollisionHitbox(boss_bullet->glob_pos, border.platforms[0])) {
				ListDel(boss_bullet_list, cur);
			}
			else {
				for (Elem* cur_player_bullet = player_bullet_list.head; cur_player_bullet != NULL;) {
					Elem* next = cur_player_bullet->next;
					PlayerBullet player_bullet = *(PlayerBullet*)cur_player_bullet->data;

					if (CheckCollisionHitbox(player_bullet.global_pos, boss_bullet->glob_pos)) {
						ListDel(player_bullet_list, cur_player_bullet);
						ListDel(boss_bullet_list, cur);
					}

					cur_player_bullet = next;
				}
			}
		}
		cur = next;
	}

	PlayerInvincible(player, time);
}
void BossCheckAllColisionHitbox(Player& player, Background& background, List& player_bullet_list, Boss& boss, Time& time)
{
	for (Elem* cur = player_bullet_list.head; cur != NULL;) {
		Elem* next = cur->next;

		PlayerBullet player_bullet = *(PlayerBullet*)cur->data;
		if (CheckCollisionHitbox(boss.hitbox, player_bullet.global_pos)) {
			BossRemovingHealth(boss, background);
			ListDel(player_bullet_list, cur);
		}

		cur = next;
	}
	if (CheckCollisionHitbox(boss.hitbox, player.hitbox)) PlayerRemovingHealth(player, background);

	PlayerInvincible(player, time);
}