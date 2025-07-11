#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "globals.h"

void DeInitSDL(int error);
void InitSDL();
int Random(int start, int end);
void UpdatePrevKeyPress();
bool CheckCollision(SDL_Rect& rect_player, SDL_Rect rect, double h);
bool CheckCollisionHitbox(SDL_Rect rect_player, SDL_Rect rect_enemy);
