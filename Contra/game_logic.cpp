#include "game_logic.h"

void AnimScrolling(Background& background, Time& time, Player& player, Boss& boss)
{
	if (background.camera.x != background.camera.w - 1024 or background.area_background.w != 1024) {
		background.camera.x += config.scrolling_speed * time.dt / 1000;
		background.area_background.w -= config.scrolling_speed * time.dt / 1000;
		if (background.camera.x >= background.camera.w - 1024) {
			background.camera.x = background.camera.w - 1024;
			background.area_background.w = 1024;
		}
		player.position.x -= config.scrolling_speed * time.dt / 1000;
		PlayerDefHitbox(player, background);
		BossDefHitbox(boss, background);
	}
}
void PlayBoss(Boss& boss, Player& player, Background& background, Time& time, Border& border,
	List& player_bullet_list, List& boss_bullet_list)
{
	AnimScrolling(background, time, player, boss);
	// Состояния
	PlayerUpdateState(player);
	// Анимация sprite sheet
	PlayerAnimation(player, time);
	BossAnimation(boss, time);
	// Перемещения сущностей
	double ds = 0;
	PlayerUpdatePosition(player, background, border, time, ds);
	PlayerBulletAllUpdatePosition(player_bullet_list, time, background, ds);
	BossBulletAllUpdatePosition(boss_bullet_list, player, time, border);
	// Создание сущностей
	PlayerBulletHandleShooting(player_bullet_list, player, texture, background);
	BossBulletShoot(boss_bullet_list, boss, time);
	// Проверка на коллизии хитбоксов
	BossBulletCheckAllColisionHitbox(player, boss_bullet_list, background, border, time, player_bullet_list);
	BossCheckAllColisionHitbox(player, background, player_bullet_list, boss, time);
	// Отрисовка
	BackgroundRender(background, texture);
	PlayerBulletAllRender(player_bullet_list, texture);
	BossRender(boss);
	BossBulletAllRender(boss_bullet_list);
	PlayerRender(player, texture);
	PlayerRenderMedal(player);
	F3ModBoss(player, background, border, player_bullet_list, boss, boss_bullet_list);
}
void Game(Player& player, List& enemy_run_list, Time& time, Background& background, Border& border, List& player_bullet_list,
	EnemyRunSpawner& enemy_run_spawner, Boss& boss, List& boss_bullet_list)
{
	if (keyPress[SDL_SCANCODE_ESCAPE] and !prev_keyPress[SDL_SCANCODE_ESCAPE]) {
		game_state = MAIN_MENU;
		play_state = PLAY;
		return;
	}

	if (play_state == PLAY and player.hitbox.x >= background.camera.w - 1024) play_state = PLAY_BOSS;
	if (play_state == PLAY_BOSS) {
		ListFree(enemy_run_list);
		PlayBoss(boss, player, background, time, border, player_bullet_list, boss_bullet_list);
		return;
	}

	// Состояния
	PlayerUpdateState(player);
	// Анимация sprite sheet
	PlayerAnimation(player, time);
	EnemyRunAllAnimation(enemy_run_list, time);
	// Перемещения сущностей
	double ds;
	PlayerUpdatePosition(player, background, border, time, ds);
	BackgroundUpdatePositionX(background, ds);
	PlayerBulletAllUpdatePosition(player_bullet_list, time, background, ds);
	EnemyRunAllUpdatePosition(enemy_run_list, background, border, time, ds);
	// Создание сущностей
	EnemyRunSpawn(enemy_run_list, enemy_run_spawner, background, texture);
	PlayerBulletHandleShooting(player_bullet_list, player, texture, background);
	// Проверка на коллизии хитбоксов
	EnemyRunCheckAllColisionHitbox(player, background, player_bullet_list, enemy_run_list, border, time);
	// Отрисовка
	BackgroundRender(background, texture);
	PlayerBulletAllRender(player_bullet_list, texture);
	EnemyRunAllRender(enemy_run_list, texture);
	PlayerRender(player, texture);
	PlayerRenderMedal(player);
	F3Mod(player, background, border, player_bullet_list, enemy_run_list);
}