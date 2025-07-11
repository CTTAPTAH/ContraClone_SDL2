#include "game_mode.h"

// ����������� � ����
void F3Mod(Player player, Background background, Border border, List player_bullet_list, List enemy_run_list)
{
	static bool isModding = false;
	if (!isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = true;
	else if (isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = false;
	if (isModding) {
		SDL_Rect boot;
		SDL_Rect hitbox;
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		// ������� ������
		boot = player.hitbox_boot; boot.x -= background.camera.x;
		hitbox = player.hitbox; hitbox.x -= background.camera.x;
		SDL_RenderDrawRect(ren, &boot);
		SDL_RenderDrawRect(ren, &hitbox);
		// ������� ���� ��������
		SDL_Rect platform;
		for (int i = 0; i < AMOUNT_PLATFORMS; i++) {
			platform = border.platforms[i]; platform.x -= background.camera.x;
			SDL_RenderDrawRect(ren, &platform);
		}
		// ������� ������ ������
		for (Elem* cur = player_bullet_list.head; cur != nullptr; cur = cur->next) {
			hitbox = ((PlayerBullet*)cur->data)->global_pos; hitbox.x -= background.camera.x;
			SDL_RenderDrawRect(ren, &hitbox);
		}
		// ������� �������� �����
		for (Elem* cur = enemy_run_list.head; cur != nullptr; cur = cur->next) {
			boot = ((EnemyRun*)cur->data)->boot;
			hitbox = ((EnemyRun*)cur->data)->hitbox;
			boot.x -= background.camera.x;
			hitbox.x -= background.camera.x;
			SDL_RenderDrawRect(ren, &boot);
			SDL_RenderDrawRect(ren, &hitbox);
		}
	}
}
void F3ModBoss(Player player, Background background, Border border, List player_bullet_list, Boss boss, List boss_bullet_list)
{
	static bool isModding = false;
	if (!isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = true;
	else if (isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = false;
	if (isModding) {
		SDL_Rect boot;
		SDL_Rect hitbox;
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		// ������� ������
		boot = player.hitbox_boot; boot.x -= background.camera.x;
		hitbox = player.hitbox; hitbox.x -= background.camera.x;
		SDL_RenderDrawRect(ren, &boot);
		SDL_RenderDrawRect(ren, &hitbox);
		// ������� ���� ��������
		SDL_Rect platform;
		for (int i = 0; i < AMOUNT_PLATFORMS; i++) {
			platform = border.platforms[i]; platform.x -= background.camera.x;
			SDL_RenderDrawRect(ren, &platform);
		}
		// ������� ������ ������
		for (Elem* cur = player_bullet_list.head; cur != nullptr; cur = cur->next) {
			hitbox = ((PlayerBullet*)cur->data)->global_pos; hitbox.x -= background.camera.x;
			SDL_RenderDrawRect(ren, &hitbox);
		}
		// ������� �����
		hitbox = boss.hitbox;
		hitbox.x -= background.camera.x;
		SDL_RenderDrawRect(ren, &hitbox);
		// ������� ���� �����
		for (Elem* cur = boss_bullet_list.head; cur != nullptr; cur = cur->next) {
			hitbox = ((BossBullet*)cur->data)->glob_pos; hitbox.x -= background.camera.x;
			SDL_RenderDrawRect(ren, &hitbox);
		}
	}
}