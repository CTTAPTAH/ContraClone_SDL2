#include "font.h"

TTF_Font* LoadFont(const char* filename)
{
	TTF_Font* font = TTF_OpenFont(filename, 100);
	if (!font) {
		printf_s("Ошибка загрузки шрифта: %s\n", SDL_GetError());
		DeInitSDL(1);
	}
	return font;
}
Font InitAllFont()
{
	Font font;

	font.despair = LoadFont("font\\despire.otf");
	font.sonic = LoadFont("font\\sonic.ttf");

	return font;
}
void DestroyAllFont(Font& font)
{
	TTF_CloseFont(font.despair);
	TTF_CloseFont(font.sonic);
}
SDL_Texture* TextCreate(TTF_Font* font, const char* text, int size, SDL_Color color, SDL_Rect& rect)
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
	if (!surface) {
		printf_s("Ошибка создания поверхности: %s\n", SDL_GetError());
		TTF_CloseFont(font);
		DeInitSDL(1);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	double coeff;
	if (surface) coeff = double(size) / double(surface->h);
	if (surface) rect = { rect.x, rect.y, int(double(surface->w) * coeff), int(double(surface->h) * coeff) };

	SDL_FreeSurface(surface);
	return texture;
}
void TextRender(TTF_Font* font, SDL_Texture* txt, SDL_Rect& rect_txt, const char* text, int text_size, SDL_Color color_text)
{
	if (color_text.r == 255 and color_text.g == 255 and color_text.b == 255 and text_size == 50) {
		SDL_RenderCopy(ren, txt, NULL, &rect_txt);
		return;
	}

	SDL_Rect rect_new_text = rect_txt;
	SDL_Texture* new_text = TextCreate(font, text, text_size, color_text, rect_new_text);
	SDL_RenderCopy(ren, new_text, NULL, &rect_new_text);
	SDL_DestroyTexture(new_text);
}
void TextRenderCont(TTF_Font* font, SDL_Texture* txt, SDL_Rect rect_txt, const char* text, int text_size, int cont_size, SDL_Color color_cont, SDL_Color color_text)
{
	SDL_Rect rect_cont = rect_txt;
	SDL_Texture* text_cont = TextCreate(font, text, text_size, color_cont, rect_cont);

	rect_cont.x += cont_size;
	SDL_RenderCopy(ren, text_cont, NULL, &rect_cont);
	rect_cont.x -= cont_size + cont_size;
	SDL_RenderCopy(ren, text_cont, NULL, &rect_cont);
	rect_cont.x += cont_size;
	rect_cont.y += cont_size;
	SDL_RenderCopy(ren, text_cont, NULL, &rect_cont);
	rect_cont.y -= cont_size + cont_size;
	SDL_RenderCopy(ren, text_cont, NULL, &rect_cont);
	rect_cont.y += cont_size;
	TextRender(font, txt, rect_txt, text, text_size, color_text);
	SDL_DestroyTexture(text_cont);
}
Text InitAllText(Font& font)
{
	Text text;
	char txt[100];
	SDL_Color color = { 255, 255, 255, 255 };
	text.large_size = 100; text.medium_size = 50; text.small_size = 25;

	strcpy_s(txt, "Contra");
	text.contra = TextCreate(font.sonic, txt, text.large_size, color, text.rect_contra);
	text.rect_contra.x = 25; text.rect_contra.y = 25;

	strcpy_s(txt, "Play");
	text.new_game = TextCreate(font.despair, txt, text.medium_size, color, text.rect_new_game);
	text.rect_new_game.x = win_width / 8; text.rect_new_game.y = win_height / 3 + 10;
	strcpy_s(txt, "Load game");
	text.load = TextCreate(font.despair, txt, text.medium_size, color, text.rect_load);
	text.rect_load.x = win_width / 8; text.rect_load.y = text.rect_new_game.y + text.medium_size + 25;
	strcpy_s(txt, "Save game");
	text.save = TextCreate(font.despair, txt, text.medium_size, color, text.rect_save);
	text.rect_save.x = win_width / 8; text.rect_save.y = text.rect_load.y + text.medium_size + 25;
	strcpy_s(txt, "Exit");
	text.exit = TextCreate(font.despair, txt, text.medium_size, color, text.rect_exit);
	text.rect_exit.x = win_width / 8; text.rect_exit.y = text.rect_save.y + text.medium_size + 25;

	strcpy_s(txt, "The game is saved");
	text.notif_save = TextCreate(font.despair, txt, text.small_size, color, text.rect_notif_save);
	text.rect_notif_save.x = win_width - text.rect_notif_save.w - 18; text.rect_notif_save.y = 0 + text.rect_notif_save.h - 12;
	//text.rect_notif_save.y = win_height - text.rect_notif_save.h - 10;
	strcpy_s(txt, "The game is loaded");
	text.notif_load = TextCreate(font.despair, txt, text.small_size, color, text.rect_notif_load);
	text.rect_notif_load.x = win_width - text.rect_notif_load.w - 10; text.rect_notif_load.y = 0 + text.rect_notif_load.h - 12;

	strcpy_s(txt, "Game Over");
	text.game_over = TextCreate(font.despair, txt, text.large_size, color, text.rect_game_over);
	text.rect_game_over.x = win_width / 6; text.rect_game_over.y = win_height / 3;
	strcpy_s(txt, "Victory");
	text.victory = TextCreate(font.despair, txt, text.large_size, color, text.rect_victory);
	text.rect_victory.x = win_width / 4 + 20; text.rect_victory.y = win_height / 3;
	strcpy_s(txt, "click to restart");
	text.restart = TextCreate(font.despair, txt, text.medium_size, color, text.rect_restart);
	text.rect_restart.x = win_width / 3; text.rect_restart.y = 3 * win_height / 4;

	return text;
}
void DestroyAllText(Text& text)
{
	SDL_DestroyTexture(text.new_game);
	SDL_DestroyTexture(text.load);
	SDL_DestroyTexture(text.save);
	SDL_DestroyTexture(text.exit);
	SDL_DestroyTexture(text.notif_load);
	SDL_DestroyTexture(text.notif_save);
	SDL_DestroyTexture(text.game_over);
	SDL_DestroyTexture(text.victory);
	SDL_DestroyTexture(text.restart);
}