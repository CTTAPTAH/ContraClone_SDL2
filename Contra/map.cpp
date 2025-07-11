#include "map.h"

int SearchCoordsEntityOnPlatform(SDL_Rect boot, Border border, double vector_y)
{
	for (int platfrom = 0; platfrom < AMOUNT_PLATFORMS; platfrom++) {
		if (CheckCollision(boot, border.platforms[platfrom], vector_y)) {
			return border.platforms[platfrom].y;
		}
	}
	return NULL;
}
// Задний фон
void BackgroundRender(Background background, Texture texture)
{
	static SDL_Rect buffer_background, buffer_camera;
	buffer_camera = background.camera;
	buffer_background = background.area_background;
	SDL_RenderCopy(ren, texture.background4, &texture.background_area, &texture.background_area);

	buffer_camera.x = background.camera.x / 3;
	buffer_background.w = texture.background_area.w - buffer_camera.x;
	SDL_RenderCopy(ren, texture.background3, &buffer_camera, &buffer_background);

	buffer_camera.x = 2 * background.camera.x / 3;
	buffer_background.w = texture.background_area.w - buffer_camera.x;
	SDL_RenderCopy(ren, texture.background2, &buffer_camera, &buffer_background);

	SDL_RenderCopy(ren, texture.background1, &background.camera, &background.area_background);

	SDL_RenderCopy(ren, texture.platforms, &background.camera, &background.area_background);

}
void BackgroundUpdatePositionX(Background& background, double ds)
{
	if (ds > 0) {
		background.camera.x += ds;
		background.area_background.w -= ds;
		if (background.area_background.w < win_width) {
			background.camera.x = background.camera.w - win_width;
			background.area_background.w = win_width;
		}
	}
}