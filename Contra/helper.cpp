#include "helper.h"

// Инициализаия и деинициализация библиотеки SDL
void DeInitSDL(int error)
{
	if (ren != nullptr) SDL_DestroyRenderer(ren);
	if (win != nullptr) SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error);
}
void InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf_s("Не удалось инциализировать SDL. Ошибка: %s", SDL_GetError());
		DeInitSDL(1);
	}
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
		printf_s("Не удалось инциализировать SDL_Image. Ошибка: %s", SDL_GetError());
		DeInitSDL(1);
	}
	if (TTF_Init()) {
		printf("Ошибка инициализации SDL_ttf: %s\n", SDL_GetError());
		return;
	}
	win = SDL_CreateWindow("Contra", SDL_WINDOWPOS_CENTERED, 25, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_MAXIMIZED*/);
	if (win == 0) {
		printf_s("Не удалось создать окно. Ошибка: %s", SDL_GetError());
		DeInitSDL(1);
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == 0) {
		printf_s("Не удалось создать рисовальщик. Ошибка: %s", SDL_GetError());
		DeInitSDL(1);
	}
}
// Общие функции
int Random(int start, int end)
{
	return rand() % (end - start + 1) + start;
}
void UpdatePrevKeyPress()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		prev_keyPress[i] = keyPress[i];
	}
}
bool CheckCollision(SDL_Rect& rect_player, SDL_Rect rect, double h)
{
	if (rect_player.x + rect_player.w >= rect.x and rect_player.x <= rect.x + rect.w) {
		if (rect_player.y + rect_player.h == rect.y)
			return true;
		double final_y = rect_player.y + h;
		if (rect_player.y + rect_player.h < rect.y and final_y + rect_player.h >= rect.y)
			return true;
	}
	return false;
}
bool CheckCollisionHitbox(SDL_Rect rect_player, SDL_Rect rect_enemy)
{
	if (rect_player.x + rect_player.w >= rect_enemy.x and rect_player.x <= rect_enemy.x + rect_enemy.w) {
		if (rect_player.y + rect_player.h >= rect_enemy.y and rect_player.y <= rect_enemy.y + rect_enemy.h) {
			return true;
		}
	}
	return false;
}
// Информация об игре
//void F3Mod(Player player, Background background, Border border, List player_bullet_list, List enemy_run_list)
//{
//	static bool isModding = false;
//	if (!isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = true;
//	else if (isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = false;
//	if (isModding) {
//		SDL_Rect boot;
//		SDL_Rect hitbox;
//		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
//		// Хитбокс игрока
//		boot = player.hitbox_boot; boot.x -= background.camera.x;
//		hitbox = player.hitbox; hitbox.x -= background.camera.x;
//		SDL_RenderDrawRect(ren, &boot);
//		SDL_RenderDrawRect(ren, &hitbox);
//		// Хитбокс всех платформ
//		SDL_Rect platform;
//		for (int i = 0; i < AMOUNT_PLATFORMS; i++) {
//			platform = border.platforms[i]; platform.x -= background.camera.x;
//			SDL_RenderDrawRect(ren, &platform);
//		}
//		// Хитбокс пульки игрока
//		for (Elem* cur = player_bullet_list.head; cur != nullptr; cur = cur->next) {
//			hitbox = ((PlayerBullet*)cur->data)->global_pos; hitbox.x -= background.camera.x;
//			SDL_RenderDrawRect(ren, &hitbox);
//		}
//		// Хитбокс бегущего врага
//		for (Elem* cur = enemy_run_list.head; cur != nullptr; cur = cur->next) {
//			boot = ((EnemyRun*)cur->data)->boot;
//			hitbox = ((EnemyRun*)cur->data)->hitbox;
//			boot.x -= background.camera.x;
//			hitbox.x -= background.camera.x;
//			SDL_RenderDrawRect(ren, &boot);
//			SDL_RenderDrawRect(ren, &hitbox);
//		}
//	}
//}
//void F3ModBoss(Player player, Background background, Border border, List player_bullet_list, Boss boss, List boss_bullet_list)
//{
//	static bool isModding = false;
//	if (!isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = true;
//	else if (isModding and !prev_keyPress[SDL_SCANCODE_F3] and keyPress[SDL_SCANCODE_F3]) isModding = false;
//	if (isModding) {
//		SDL_Rect boot;
//		SDL_Rect hitbox;
//		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
//		// Хитбокс игрока
//		boot = player.hitbox_boot; boot.x -= background.camera.x;
//		hitbox = player.hitbox; hitbox.x -= background.camera.x;
//		SDL_RenderDrawRect(ren, &boot);
//		SDL_RenderDrawRect(ren, &hitbox);
//		// Хитбокс всех платформ
//		SDL_Rect platform;
//		for (int i = 0; i < AMOUNT_PLATFORMS; i++) {
//			platform = border.platforms[i]; platform.x -= background.camera.x;
//			SDL_RenderDrawRect(ren, &platform);
//		}
//		// Хитбокс пульки игрока
//		for (Elem* cur = player_bullet_list.head; cur != nullptr; cur = cur->next) {
//			hitbox = ((PlayerBullet*)cur->data)->global_pos; hitbox.x -= background.camera.x;
//			SDL_RenderDrawRect(ren, &hitbox);
//		}
//		// Хитбокс босса
//		hitbox = boss.hitbox;
//		hitbox.x -= background.camera.x;
//		SDL_RenderDrawRect(ren, &hitbox);
//		// Хитбокс пуль босса
//		for (Elem* cur = boss_bullet_list.head; cur != nullptr; cur = cur->next) {
//			hitbox = ((BossBullet*)cur->data)->glob_pos; hitbox.x -= background.camera.x;
//			SDL_RenderDrawRect(ren, &hitbox);
//		}
//	}
//}