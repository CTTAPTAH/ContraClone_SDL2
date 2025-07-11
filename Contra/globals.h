#pragma once
#include <SDL.h>
#include "config.h"
#include "texture.h"
#include "font.h"

extern bool keyPress[SDL_NUM_SCANCODES];
extern bool prev_keyPress[SDL_NUM_SCANCODES];
extern SDL_Window* win;
extern SDL_Renderer* ren;
extern int win_width;
extern int win_height;

enum GameState { MAIN_MENU, GAME, EXIT, GAME_OVER, WIN };
extern GameState game_state;

extern Config config;
struct Texture;
extern Texture texture;

struct Font;
extern Font font;
struct Text;
extern Text text;

enum PlayState { PLAY, PLAY_BOSS };
extern PlayState play_state;