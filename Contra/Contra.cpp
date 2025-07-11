#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "globals.h"
#include "list.h"
#include "animation.h"
#include "time.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "helper.h"
#include "font.h"
#include "boss.h"
#include "game_mode.h"
#include "save_load.h"
#include "menu.h"
#include "game_logic.h"
#include "gameover.h"
#include "win.h"

bool keyPress[SDL_NUM_SCANCODES] = { false };
bool prev_keyPress[SDL_NUM_SCANCODES] = { false };
SDL_Window* win = nullptr;
SDL_Renderer* ren = nullptr;
int win_width = 1024, win_height = 896;
GameState game_state = MAIN_MENU;
Config config;
Texture texture;
Font font;
Text text;
PlayState play_state = PLAY;

int main(int argc, char* argv[])
{
	system("chcp 1251>nul");
	srand(time(nullptr));
	InitSDL();

	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	InitTexture(texture);
	font = InitAllFont();
	text = InitAllText(font);

	Border border;
	Time time;

	Background background;
	background.area_background = background.camera = texture.background_area;
	Player player;
	PlayerCreate(player, texture);
	Boss boss;
	BossCreate(boss);

	List player_bullet_list;
	List boss_bullet_list;

	EnemyRunSpawner enemy_run_spawner;
	List enemy_run_list;

	bool isRunning = true;  SDL_Event ev;

	while (isRunning)
	{
		UpdatePrevKeyPress();
		// fps
		FPS(time);
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
					win_width = ev.window.data1;
					win_height = ev.window.data2;
					border.border_right = win_width - 100;
				};
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_D: keyPress[SDL_SCANCODE_D] = true; player.stay_right = true; break;
				case SDL_SCANCODE_A: keyPress[SDL_SCANCODE_A] = true; player.stay_right = false; break;
				case SDL_SCANCODE_S: keyPress[SDL_SCANCODE_S] = true; break;
				case SDL_SCANCODE_W: keyPress[SDL_SCANCODE_W] = true; break;
				case SDL_SCANCODE_SPACE: keyPress[SDL_SCANCODE_SPACE] = true; break;
				case SDL_SCANCODE_K: keyPress[SDL_SCANCODE_K] = true; break;
				case SDL_SCANCODE_F3: keyPress[SDL_SCANCODE_F3] = true; break;
				case SDL_SCANCODE_P: keyPress[SDL_SCANCODE_P] = true; break;
				case SDL_SCANCODE_ESCAPE: keyPress[SDL_SCANCODE_ESCAPE] = true; break;
				} break;
			case SDL_KEYUP:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_D: keyPress[SDL_SCANCODE_D] = false; break;
				case SDL_SCANCODE_A: keyPress[SDL_SCANCODE_A] = false; break;
				case SDL_SCANCODE_S: keyPress[SDL_SCANCODE_S] = false; break;
				case SDL_SCANCODE_W: keyPress[SDL_SCANCODE_W] = false; break;
				case SDL_SCANCODE_SPACE: keyPress[SDL_SCANCODE_SPACE] = false; break;
				case SDL_SCANCODE_K: keyPress[SDL_SCANCODE_K] = false; break;
				case SDL_SCANCODE_F3: keyPress[SDL_SCANCODE_F3] = false; break;
				case SDL_SCANCODE_P: keyPress[SDL_SCANCODE_P] = false; break;
				case SDL_SCANCODE_ESCAPE: keyPress[SDL_SCANCODE_ESCAPE] = false; break;
				} break;
			}
		}
		if (game_state == MAIN_MENU) {
			Menu(texture, time, font, text, background, player, player_bullet_list, enemy_run_spawner, enemy_run_list, boss, boss_bullet_list);
		}
		else if (game_state == GAME) {
			Game(player, enemy_run_list, time, background, border, player_bullet_list, enemy_run_spawner, boss, boss_bullet_list);
		}
		else if (game_state == GAME_OVER) {
			GameOver(player, background, player_bullet_list, enemy_run_list, border, boss_bullet_list, boss);
		}
		else if (game_state == WIN) {
			Win(player, background, player_bullet_list, enemy_run_list, border, boss_bullet_list, boss);
		}
		else if (game_state == EXIT) {
			isRunning = false;
		}

		SDL_RenderPresent(ren);
	}
	// Освобождение всего
	ListFree(player_bullet_list);
	ListFree(enemy_run_list);
	ListFree(boss_bullet_list);
	DestroyAllTexture(texture);
	DestroyAllFont(font);
	DestroyAllText(text);
	DeInitSDL(0);
	return 0;
}