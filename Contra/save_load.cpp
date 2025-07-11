#include "save_load.h"

// Сохранение/загрузка
void SaveGame(Background background, Player player, List player_bullet_list, EnemyRunSpawner enemy_run_spawner,
	List enemy_run_list, Boss boss, List boss_bullet_list)
{
	FILE* file;
	if (fopen_s(&file, "save\\save.txt", "w")) {
		printf_s("Ошибка сохранения игры: не удалось открыть файл\n");
		return;
	}

	fprintf_s(file, "Background %d %d %d %d %d %d %d %d\n", background.area_background.x, background.area_background.y,
		background.area_background.w, background.area_background.h, background.camera.x, background.camera.y,
		background.camera.w, background.camera.h);

	fprintf_s(file, "Player %d %d %d %d %d %d %d %d %d %d %d %d\n", player.hp, player.position.x, player.position.y,
		player.position.w, player.position.h, player.stay_right, player.is_jumping, player.is_falling,
		player.jump_finish_y, player.shoot_time_start, player.timer_invincibil, player.invincibil);

	for (Elem* cur = player_bullet_list.head; cur != NULL; cur = cur->next) {
		PlayerBullet player_bullet = *(PlayerBullet*)cur->data;
		fprintf_s(file, "PlayerBullet %d %d %d %d %d %d\n", player_bullet.position.x, player_bullet.position.y,
			player_bullet.position.w, player_bullet.position.h, player_bullet.dir_x, player_bullet.dir_y);
	}

	for (Elem* cur = enemy_run_list.head; cur != NULL; cur = cur->next) {
		EnemyRun enemy_run = *(EnemyRun*)cur->data;
		fprintf_s(file, "EnemyRun %d %d %d %d %d\n", enemy_run.position.x, enemy_run.position.y,
			enemy_run.position.w, enemy_run.position.h, enemy_run.is_falling);
	}

	fprintf_s(file, "Boss %d %d %d %d %d %d %d\n", boss.hp, boss.hitbox.x, boss.hitbox.y, boss.hitbox.w, boss.hitbox.h,
		boss.phase, boss.reload);

	for (Elem* cur = boss_bullet_list.head; cur != NULL; cur = cur->next) {
		BossBullet boss_bullet = *(BossBullet*)cur->data;
		fprintf_s(file, "BossBullet %d %d %d %d %d %d %d %d\n", boss_bullet.glob_pos.x, boss_bullet.glob_pos.y,
			boss_bullet.glob_pos.w, boss_bullet.glob_pos.h, boss_bullet.phase, boss_bullet.jump_finish_y,
			boss_bullet.dir_x, boss_bullet.dir_y);
	}

	fclose(file);
}
void LoadGame(Background& background, Player& player, List& player_bullet_list, EnemyRunSpawner& enemy_run_spawner,
	List& enemy_run_list, Boss& boss, List& boss_bullet_list)
{
	ListFree(player_bullet_list);
	ListFree(enemy_run_list);
	ListFree(boss_bullet_list);

	FILE* file;
	if (fopen_s(&file, "save\\save.txt", "r")) {
		printf_s("Ошибка сохранения игры: не удалось открыть файл\n");
		return;
	}

	char key[100];
	while (fscanf_s(file, "%s", key, (unsigned)_countof(key)) != EOF) {
		if (!strcmp(key, "Background")) {
			fscanf_s(file, "%d %d %d %d %d %d %d %d", &background.area_background.x, &background.area_background.y,
				&background.area_background.w, &background.area_background.h, &background.camera.x, &background.camera.y,
				&background.camera.w, &background.camera.h);
		}
		else if (!strcmp(key, "Player")) {
			fscanf_s(file, "%d %d %d %d %d %d %d %d %d %d %d %d", &player.hp, &player.position.x, &player.position.y,
				&player.position.w, &player.position.h, &player.stay_right, &player.is_jumping, &player.is_falling,
				&player.jump_finish_y, &player.shoot_time_start, &player.timer_invincibil, &player.invincibil);
			PlayerDefHitbox(player, background);
		}
		else if (!strcmp(key, "PlayerBullet")) {
			PlayerBullet* player_bullet = PlayerBulletCreate(player, texture, background);
			fscanf_s(file, "%d %d %d %d %d %d", &player_bullet->position.x, &player_bullet->position.y,
				&player_bullet->position.w, &player_bullet->position.h, &player_bullet->dir_x, &player_bullet->dir_y);

			PlayerBulletDefHitbox(*player_bullet, background);
			ListAdd(player_bullet_list, player_bullet);
		}
		else if (!strcmp(key, "EnemyRun")) {
			EnemyRun* enemy_run = EnemyRunCreate(background, texture);
			fscanf_s(file, "%d %d %d %d %d", &enemy_run->position.x, &enemy_run->position.y,
				&enemy_run->position.w, &enemy_run->position.h, &enemy_run->is_falling);

			EnemyRunDefHitbox(*enemy_run, background);
			ListAdd(enemy_run_list, enemy_run);
		}
		else if (!strcmp(key, "Boss")) {
			fscanf_s(file, "%d %d %d %d %d %d %d", &boss.hp, &boss.hitbox.x, &boss.hitbox.y, &boss.hitbox.w, &boss.hitbox.h,
				&boss.phase, &boss.reload);
		}
		else if (!strcmp(key, "BossBullet")) {
			BossBullet* boss_bullet = BossBulletCreate(boss);
			fscanf_s(file, "%d %d %d %d %d %d %d %d", &boss_bullet->glob_pos.x, &boss_bullet->glob_pos.y,
				&boss_bullet->glob_pos.w, &boss_bullet->glob_pos.h, &boss_bullet->phase, &boss_bullet->jump_finish_y,
				&boss_bullet->dir_x, &boss_bullet->dir_y);

			BossBulletDefHitbox(*boss_bullet);
			boss_bullet->area = boss_bullet->glob_pos;
			boss_bullet->area.x = boss_bullet->area.y = 0;
			ListAdd(boss_bullet_list, boss_bullet);
		}
	}

	fclose(file);
}