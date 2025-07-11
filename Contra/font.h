#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "helper.h"

struct Text
{
	SDL_Texture* contra, * new_game, * load, * save, * exit;
	SDL_Rect rect_contra, rect_new_game, rect_load, rect_save, rect_exit;
	int large_size = 100, medium_size = 50, small_size = 25;

	SDL_Texture* notif_load, * notif_save;
	SDL_Rect rect_notif_load, rect_notif_save;

	SDL_Texture* game_over, * victory, * restart;
	SDL_Rect rect_game_over, rect_victory, rect_restart;
};
struct Font
{
	TTF_Font* despair, * sonic;
};

TTF_Font* LoadFont(const char* filename);
Font InitAllFont();
void DestroyAllFont(Font& font);
SDL_Texture* TextCreate(TTF_Font* font, const char* text, int size, SDL_Color color, SDL_Rect& rect);
void TextRender(TTF_Font* font, SDL_Texture* txt, SDL_Rect& rect_txt, const char* text, int text_size, SDL_Color color_text);
void TextRenderCont(TTF_Font* font, SDL_Texture* txt, SDL_Rect rect_txt, const char* text, int text_size, int cont_size, SDL_Color color_cont, SDL_Color color_text);
Text InitAllText(Font& font);
void DestroyAllText(Text& text);