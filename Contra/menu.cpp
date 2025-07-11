#include "menu.h"

// Μενώ
void RenderMenu(Font& font, Text& text, SDL_Rect& cursor)
{
	SDL_RenderCopy(ren, texture.menu, &texture.menu_area, &texture.menu_area);

	SDL_Color color_cont = { 0, 0, 0, 255 }, color_text_white = { 255, 255, 255, 255 }, color_text_blue = { 59, 131, 189, 255 };
	TextRenderCont(font.sonic, text.contra, text.rect_contra, "Contra", text.large_size, 5, color_cont, color_text_white);

	if (CheckCollisionHitbox(text.rect_new_game, cursor)) {
		TextRenderCont(font.despair, text.new_game, text.rect_new_game, "Play", text.medium_size, 3, color_cont, color_text_blue);
	}
	else {
		TextRenderCont(font.despair, text.new_game, text.rect_new_game, "Play", text.medium_size, 3, color_cont, color_text_white);
	}

	if (CheckCollisionHitbox(text.rect_load, cursor)) {
		TextRenderCont(font.despair, text.load, text.rect_load, "Load game", text.medium_size, 3, color_cont, color_text_blue);
	}
	else {
		TextRenderCont(font.despair, text.load, text.rect_load, "Load game", text.medium_size, 3, color_cont, color_text_white);
	}

	if (CheckCollisionHitbox(text.rect_save, cursor)) {
		TextRenderCont(font.despair, text.save, text.rect_save, "Save game", text.medium_size, 3, color_cont, color_text_blue);
	}
	else {
		TextRenderCont(font.despair, text.save, text.rect_save, "Save game", text.medium_size, 3, color_cont, color_text_white);
	}

	if (CheckCollisionHitbox(text.rect_exit, cursor)) {
		TextRenderCont(font.despair, text.exit, text.rect_exit, "Exit", text.medium_size, 3, color_cont, color_text_blue);
	}
	else {
		TextRenderCont(font.despair, text.exit, text.rect_exit, "Exit", text.medium_size, 3, color_cont, color_text_white);
	}
}
void RenderNotification(Font& font, Text& text, int stopwatch, char notification[])
{
	SDL_Color color_white = { 255, 255, 255, 255 };
	if (stopwatch > SDL_GetTicks()) {
		SDL_Rect notification_rect = { win_width - text.rect_notif_load.w - 15, 0,
			text.rect_notif_load.w + 20, text.rect_notif_load.h + 20 };
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 150);
		if (!strcmp(notification, "load")) {
			SDL_RenderFillRect(ren, &notification_rect);
			TextRender(font.despair, text.notif_load, text.rect_notif_load, "The game is loaded", text.small_size, color_white);
		}
		else if (!strcmp(notification, "save")) {
			SDL_RenderFillRect(ren, &notification_rect);
			TextRender(font.despair, text.notif_save, text.rect_notif_save, "The game is saved", text.small_size, color_white);
		}
	}
}
void Menu(Texture& texture, Time& time, Font& font, Text& text, Background& background, Player& player,
	List& player_bullet_list, EnemyRunSpawner& enemy_run_spawner, List& enemy_run_list, Boss& boss, List& boss_bullet_list)
{
	static char notification[50];
	const int timer = 2 * 1000;
	static int stopwatch = 0;

	static SDL_Rect cursor = { 0, 0, 1, 1 };
	static bool mousePressed = false;
	Uint32 buttons = SDL_GetMouseState(&cursor.x, &cursor.y);

	if (keyPress[SDL_SCANCODE_ESCAPE] and !prev_keyPress[SDL_SCANCODE_ESCAPE]) {
		game_state = GAME;
		return;
	}
	if (buttons and SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if (!mousePressed) {
			mousePressed = true;

			if (CheckCollisionHitbox(text.rect_new_game, cursor)) {
				game_state = GAME;
				return;
			}
			if (CheckCollisionHitbox(text.rect_exit, cursor)) {
				game_state = EXIT;
				return;
			}

			if (CheckCollisionHitbox(text.rect_save, cursor)) {
				SaveGame(background, player, player_bullet_list, enemy_run_spawner, enemy_run_list, boss, boss_bullet_list);
				stopwatch = SDL_GetTicks() + timer;
				strcpy_s(notification, "save");
			}
			if (CheckCollisionHitbox(text.rect_load, cursor)) {
				LoadGame(background, player, player_bullet_list, enemy_run_spawner, enemy_run_list, boss, boss_bullet_list);
				stopwatch = SDL_GetTicks() + timer;
				strcpy_s(notification, "load");
			}
		}
	}
	else {
		mousePressed = false;
	}

	RenderMenu(font, text, cursor);
	RenderNotification(font, text, stopwatch, notification);
}