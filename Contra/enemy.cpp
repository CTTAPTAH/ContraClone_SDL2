#include "enemy.h"

// Бегующий враг
EnemyRun* EnemyRunCreate(Background background, Texture& texture)
{
	EnemyRun* enemy_run = (EnemyRun*)malloc(sizeof(EnemyRun));
	if (!enemy_run) {
		printf_s("Ошибка: не удалось выделить память для бегующего врага\n");
		return nullptr;
	}
	// Инициализация
	enemy_run->anim = { 0, 8, 1000 / 8, 0 };
	enemy_run->area_anim_run = enemy_run->position = texture.enemy_area_anim_run;
	enemy_run->position.x = Random(win_width, win_width + 150);
	enemy_run->position.y = Random(0, win_height - 128 - enemy_run->position.h);

	enemy_run->boot = { 0, 0, 29, 3 };
	enemy_run->boot.x = enemy_run->position.x + background.camera.x + 26;
	enemy_run->boot.y = enemy_run->position.y + 177;

	enemy_run->hitbox = { 0, 0, 92, 134 };
	enemy_run->hitbox.x = enemy_run->position.x + background.camera.x;
	enemy_run->hitbox.y = enemy_run->position.y + 46;

	return enemy_run;
}
void EnemyRunSpawn(List& list, EnemyRunSpawner& spawner, Background background, Texture& texture)
{
	if (spawner.stopwatch <= SDL_GetTicks()) {
		spawner.stopwatch = SDL_GetTicks() + spawner.timer;
		int rand_amount = Random(0, 4);
		for (int i = 0; i < rand_amount; i++) {
			EnemyRun* enemy_run = EnemyRunCreate(background, texture);
			ListAdd(list, enemy_run);
		}
	}
}
void EnemyRunRender(EnemyRun enemy_run, Texture texture)
{
	SDL_RenderCopy(ren, texture.enemy_anim_run, &enemy_run.area_anim_run, &enemy_run.position);
}
void EnemyRunAllRender(List& list, Texture texture)
{
	for (Elem* cur = list.head; cur != NULL; cur = cur->next) {
		EnemyRun* enemy_run = (EnemyRun*)cur->data;
		EnemyRunRender(*(EnemyRun*)cur->data, texture);
	}
}
void EnemyRunMovePosition(EnemyRun& enemy_run, int x, int y)
{
	enemy_run.position.x += x; enemy_run.position.y += y;
}
void EnemyRunSetPosition(EnemyRun& enemy_run, int x, int y)
{
	enemy_run.position.x = x; enemy_run.position.y = y;
}
void EnemyRunDefHitbox(EnemyRun& enemy_run, Background& background)
{
	int global_x = enemy_run.position.x + background.camera.x;
	enemy_run.boot = { global_x + 26, enemy_run.position.y + 177, 29, 3 };
	enemy_run.hitbox = { global_x, enemy_run.position.y + 46, 92, 134 };
}
void EnemyRunUpdatePositionX(EnemyRun& enemy_run, Background background, Time time, double ds)
{
	double vector_x = -config.enemy_run_speed * time.dt / 1000;
	if (ds > 0) {
		vector_x -= ds;
	}
	EnemyRunMovePosition(enemy_run, vector_x, 0);
	enemy_run.boot.x += ds;
	enemy_run.hitbox.x += ds;
}
void EnemyRunUpdatePositionY(EnemyRun& enemy_run, Border border, Time time)
{
	double vector_y = config.gravity * time.dt / 1000;
	for (int i = 0; i < AMOUNT_PLATFORMS; i++) {
		int coord_platform_y = SearchCoordsEntityOnPlatform(enemy_run.boot, border, vector_y);
		if (coord_platform_y) {
			EnemyRunSetPosition(enemy_run, enemy_run.position.x, coord_platform_y - enemy_run.position.h);
			return;
		}
	}
	EnemyRunMovePosition(enemy_run, 0, vector_y);
}
void EnemyRunAllUpdatePosition(List& list, Background background, Border border, Time time, double ds)
{
	for (Elem* cur = list.head; cur != NULL; cur = cur->next) {
		EnemyRunUpdatePositionX(*(EnemyRun*)cur->data, background, time, ds);
		EnemyRunUpdatePositionY(*(EnemyRun*)cur->data, border, time);
		EnemyRunDefHitbox(*(EnemyRun*)cur->data, background);
	}
}
void EnemyRunAnimation(EnemyRun& enemy_run, int dt)
{
	Animation(enemy_run.area_anim_run, dt, enemy_run.anim);
}
void EnemyRunAllAnimation(List& list, Time time)
{
	for (Elem* cur = list.head; cur != NULL; cur = cur->next) {
		EnemyRunAnimation(*(EnemyRun*)cur->data, time.dt);
	}
}
// Коллизия с бегуюшим врагом
void EnemyRunCheckAllColisionHitbox(Player& player, Background& background, List& list_bullet, List& list_enemy, Border border, Time time)
{
	for (Elem* cur_enemy = list_enemy.head; cur_enemy != NULL;) {
		Elem* next_enemy = cur_enemy->next;
		EnemyRun enemy_run = *(EnemyRun*)cur_enemy->data;

		for (Elem* cur_bullet = list_bullet.head; cur_bullet != NULL;) {
			Elem* next_bullet = cur_bullet->next;
			PlayerBullet player_bullet = *(PlayerBullet*)cur_bullet->data;
			if (CheckCollisionHitbox(player_bullet.global_pos, enemy_run.hitbox)) {
				ListDel(list_enemy, cur_enemy);
				ListDel(list_bullet, cur_bullet);
				break;
			}
			cur_bullet = next_bullet;
		}
		if (CheckCollisionHitbox(player.hitbox, enemy_run.hitbox) and !player.invincibil) {
			PlayerRemovingHealth(player, background);
		}
		else if (enemy_run.position.x + enemy_run.position.w < border.border_left) {
			ListDel(list_enemy, cur_enemy);
		}
		cur_enemy = next_enemy;
	}
	PlayerInvincible(player, time);
}