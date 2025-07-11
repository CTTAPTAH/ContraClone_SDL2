#include "win.h"

// Win
void WinRender(SDL_Rect& cursor)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
	SDL_RenderFillRect(ren, NULL);

	SDL_Color color_white = { 255, 255, 255, 255 }, color_blue = { 59, 131, 189, 255 };
	TextRender(font.despair, text.victory, text.rect_victory, "VICTORY", text.large_size, color_white);

	if (CheckCollisionHitbox(text.rect_restart, cursor)) {
		TextRender(font.despair, text.restart, text.rect_restart, "click to restart", text.medium_size, color_blue);
	}
	else {
		TextRender(font.despair, text.restart, text.rect_restart, "click to restart", text.medium_size, color_white);
	}
}
void Win(Player& player, Background& background, List& player_bullet_list, List& enemy_run_list, Border& border,
	List& boss_bullet_list, Boss& boss)
{
	static SDL_Rect cursor = { 0, 0, 1, 1 };
	static bool mousePressed = false;
	Uint32 buttons = SDL_GetMouseState(&cursor.x, &cursor.y);

	if (keyPress[SDL_SCANCODE_ESCAPE] and !prev_keyPress[SDL_SCANCODE_ESCAPE]) {
		CleanGame(player, background, player_bullet_list, enemy_run_list, boss_bullet_list, boss);
		game_state = MAIN_MENU;
	}
	if (buttons and SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if (!mousePressed) {
			mousePressed = true;

			if (CheckCollisionHitbox(text.rect_restart, cursor)) {
				game_state = MAIN_MENU;
				CleanGame(player, background, player_bullet_list, enemy_run_list, boss_bullet_list, boss);
				return;
			}
		}
	}
	else {
		mousePressed = false;
	}

	// Отрисовка
	BackgroundRender(background, texture);
	PlayerBulletAllRender(player_bullet_list, texture);
	//BossBulletAllRender(boss_bullet_list);
	//EnemyRunAllRender(enemy_run_list, texture);
	BossRender(boss);
	PlayerRender(player, texture);
	PlayerRenderMedal(player);
	F3Mod(player, background, border, player_bullet_list, enemy_run_list);
	F3ModBoss(player, background, border, player_bullet_list, boss, boss_bullet_list);
	WinRender(cursor);
}