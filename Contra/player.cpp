#include "player.h"

// Игровой персонаж
void PlayerCreate(Player& player, Texture& texture)
{
	player.hp = config.player_hp;

	player.area_anim_run_right = texture.player_area_anim_run_right,
		player.area_anim_run_left = texture.player_area_anim_run_left,
		player.area_anim_run_up_right = texture.player_area_anim_run_up_right,
		player.area_anim_run_up_left = texture.player_area_anim_run_up_left,
		player.area_anim_run_down_right = texture.player_area_anim_run_down_right,
		player.area_anim_run_down_left = texture.player_area_anim_run_down_left,
		player.area_anim_shoot_run_left = texture.player_area_anim_shoot_run_left,
		player.area_anim_shoot_run_right = texture.player_area_anim_shoot_run_right,
		player.area_up_right = texture.player_area_up_right,
		player.area_up_left = texture.player_area_up_left,
		player.area_lie_right = texture.player_area_lie_right,
		player.area_lie_left = texture.player_area_lie_left,
		player.area_stay_right = texture.player_area_stay_right,
		player.area_stay_left = texture.player_area_stay_left,
		player.area_jump_right = texture.player_area_jump_right,
		player.area_jump_left = texture.player_area_jump_left,
		player.area_falling_left = texture.player_area_falling_left,
		player.area_falling_right = texture.player_area_falling_right;

	player.anim_run_right = player.anim_run_left = player.anim_shoot_run_right = player.anim_shoot_run_left = { 0, 5, 1000 / 8, 0 };
	player.anim_run_up_right = player.anim_run_up_left = player.anim_run_down_right = player.anim_run_down_left = { 0, 3, 1000 / 8, 0 };
	player.anim_jump_right = player.anim_jump_left = { 0, 4, 1000 / 8, 0 };
	player.anim_stay_right = player.anim_stay_left = { 0, 2, 1000 / 2, 0 };

	player.position = { 100, win_height / 2, player.area_stay_right.w, player.area_stay_right.h };
	player.hitbox = { player.position.x, player.position.y, 52, 136 };

	player.stay_right = true;
	player.invincibil = false; player.timer_invincibil = 0;
}
void PlayerMovePosition(Player& player, int x, int y)
{
	player.position.x += x;
	player.position.y += y;
}
void PlayerSetPosition(Player& player, int x, int y)
{
	player.position.x = x;
	player.position.y = y;
}
void PlayerDefHitbox(Player& player, Background& background)
{
	int global_x = player.position.x + background.camera.x;
	if (player.stay_right) player.hitbox_boot = { global_x + 16, player.position.y + 176, 32, 4 };
	else player.hitbox_boot = { global_x + 48, player.position.y + 176, 32, 4 };

	if (player.is_jumping) player.hitbox = { global_x, player.position.y + 116, 80, 64 };
	else if (player.stay_right) player.hitbox = { global_x, player.position.y + 48, 52, 136 };
	else player.hitbox = { global_x + 44, player.position.y + 48, 52, 136 };
}
void PlayerUpdateState(Player& player)
{
	// Что именно делает персонаж (его состояние)
	player.run_right = keyPress[SDL_SCANCODE_D]; player.run_left = keyPress[SDL_SCANCODE_A];
	player.run_left_right = player.run_right and player.run_left;
	player.lie_right = keyPress[SDL_SCANCODE_S] and player.stay_right and !player.run_left_right;
	player.lie_left = keyPress[SDL_SCANCODE_S] and !player.stay_right and !player.run_left_right;
	player.run_up_right = keyPress[SDL_SCANCODE_D] and keyPress[SDL_SCANCODE_W] and !player.run_left_right;
	player.run_up_left = keyPress[SDL_SCANCODE_A] and keyPress[SDL_SCANCODE_W] and !player.run_left_right;
	player.stay_up_right = keyPress[SDL_SCANCODE_W] and player.stay_right and !player.run_up_right and !player.run_left_right;
	player.stay_up_left = keyPress[SDL_SCANCODE_W] and !player.stay_right and !player.run_up_left and !player.run_left_right;
	player.run_down_right = keyPress[SDL_SCANCODE_D] and keyPress[SDL_SCANCODE_S] and !player.run_left_right;
	player.run_down_left = keyPress[SDL_SCANCODE_A] and keyPress[SDL_SCANCODE_S] and !player.run_left_right;
	player.jump = !prev_keyPress[SDL_SCANCODE_SPACE] and keyPress[SDL_SCANCODE_SPACE];
	player.jump_right = player.is_jumping and player.stay_right; player.jump_left = player.is_jumping and !player.stay_right;
	player.get_off = keyPress[SDL_SCANCODE_S] and keyPress[SDL_SCANCODE_SPACE] and !player.run_down_right and !player.run_down_left;
	// Стрельба
	player.shoot = !prev_keyPress[SDL_SCANCODE_K] and keyPress[SDL_SCANCODE_K];
	if (player.shoot) {
		player.shoot_time_start = SDL_GetTicks();
	}
	double shoot_time_pass = (double)(SDL_GetTicks() - player.shoot_time_start) / 1000;
	player.shoot_run_right = keyPress[SDL_SCANCODE_D] and shoot_time_pass <= config.shoot_timer and player.shoot_time_start;
	player.shoot_run_left = keyPress[SDL_SCANCODE_A] and shoot_time_pass <= config.shoot_timer and player.shoot_time_start;
}
void PlayerAnimation(Player& player, Time time)
{
	if (player.stay_right) Animation(player.area_stay_right, time.dt, player.anim_stay_right);
	if (!player.stay_right) Animation(player.area_stay_left, time.dt, player.anim_stay_left);
	if (player.run_right) Animation(player.area_anim_run_right, time.dt, player.anim_run_right);
	if (player.run_left) Animation(player.area_anim_run_left, time.dt, player.anim_run_left);
	if (player.run_up_right) Animation(player.area_anim_run_up_right, time.dt, player.anim_run_up_right);
	if (player.run_up_left) Animation(player.area_anim_run_up_left, time.dt, player.anim_run_up_left);
	if (player.run_down_right) Animation(player.area_anim_run_down_right, time.dt, player.anim_run_down_right);
	if (player.run_down_left) Animation(player.area_anim_run_down_left, time.dt, player.anim_run_down_left);
	if (player.shoot_run_left) Animation(player.area_anim_shoot_run_left, time.dt, player.anim_shoot_run_left);
	if (player.shoot_run_right) Animation(player.area_anim_shoot_run_right, time.dt, player.anim_shoot_run_right);
	if (player.jump_right) Animation(player.area_jump_right, time.dt, player.anim_jump_right);
	if (player.jump_left) Animation(player.area_jump_left, time.dt, player.anim_jump_left);
}
void PlayerRender(Player player, Texture texture)
{
	if (0 * 1000 * config.player_time_invincibil / 6 < player.timer_invincibil and
		player.timer_invincibil < 1 * 1000 * config.player_time_invincibil / 6 or
		2 * 1000 * config.player_time_invincibil / 6 < player.timer_invincibil and
		player.timer_invincibil < 3 * 1000 * config.player_time_invincibil / 6 or
		4 * 1000 * config.player_time_invincibil / 6 < player.timer_invincibil and
		player.timer_invincibil < 5 * 1000 * config.player_time_invincibil / 6)
		return;

	if (player.jump_right) { // Прыжок вправо
		SDL_RenderCopy(ren, texture.player_anim_jump_right, &player.area_jump_right, &player.position);
	}
	else if (player.jump_left) { // Прыжок влево
		SDL_RenderCopy(ren, texture.player_anim_jump_left, &player.area_jump_left, &player.position);
	}
	else if (player.is_falling and player.stay_right) { // Если падает без прыжка
		SDL_RenderCopy(ren, texture.player_falling_right, &player.area_falling_right, &player.position);
	}
	else if (player.is_falling and !player.stay_right) { // Если падает без прыжка
		SDL_RenderCopy(ren, texture.player_falling_left, &player.area_falling_left, &player.position);
	}
	else if (player.run_right and player.run_left) { // Если нажали влево и вправо вместе
		if (player.stay_right) {
			SDL_RenderCopy(ren, texture.player_stay_right, &player.area_stay_right, &player.position);
		}
		else {
			SDL_RenderCopy(ren, texture.player_stay_left, &player.area_stay_right, &player.position);
		}
	}
	else if (player.run_up_right) { // вверх вправо
		SDL_RenderCopy(ren, texture.player_anim_run_up_right, &player.area_anim_run_up_right, &player.position);
	}
	else if (player.run_up_left) { // вверх влево
		SDL_RenderCopy(ren, texture.player_anim_run_up_left, &player.area_anim_run_up_left, &player.position);
	}
	else if (player.run_down_right) { // вниз вправо
		SDL_RenderCopy(ren, texture.player_anim_run_down_right, &player.area_anim_run_down_right, &player.position);
	}
	else if (player.run_down_left) { // вниз влево
		SDL_RenderCopy(ren, texture.player_anim_run_down_left, &player.area_anim_run_down_left, &player.position);
	}
	else if (player.shoot_run_left) { // Стреляет и бежит влево
		SDL_RenderCopy(ren, texture.player_anim_shoot_run_left, &player.area_anim_shoot_run_left, &player.position);
	}
	else if (player.shoot_run_right) { // Стреляет и бежит вправо
		SDL_RenderCopy(ren, texture.player_anim_shoot_run_right, &player.area_anim_shoot_run_right, &player.position);
	}
	else if (player.lie_right) { // лежит вправо
		SDL_RenderCopy(ren, texture.player_lie_right, &player.area_lie_right, &player.position);
	}
	else if (player.lie_left) { // лежит влево
		SDL_RenderCopy(ren, texture.player_lie_left, &player.area_lie_left, &player.position);
	}
	else if (player.stay_up_right) { // смотрит вверх справа
		SDL_RenderCopy(ren, texture.player_up_right, &player.area_up_right, &player.position);
	}
	else if (player.stay_up_left) { // смотрит вверх слева
		SDL_RenderCopy(ren, texture.player_up_left, &player.area_up_left, &player.position);
	}
	else if (player.run_right) { // вправо
		SDL_RenderCopy(ren, texture.player_anim_run_right, &player.area_anim_run_right, &player.position);
	}
	else if (player.run_left) { // влево
		SDL_RenderCopy(ren, texture.player_anim_run_left, &player.area_anim_run_left, &player.position);
	}
	else if (player.stay_right) { // стоит и смотри вправо
		SDL_RenderCopy(ren, texture.player_stay_right, &player.area_stay_right, &player.position);
	}
	else { // стоит и смотрит влево
		SDL_RenderCopy(ren, texture.player_stay_left, &player.area_stay_left, &player.position);
	}
}
void PlayerUpdatePositionX(Player& player, Background background, Border border, Time time)
{
	double vector_x = 0;
	if (player.run_right and player.run_left) return;
	else if (player.run_right or player.run_up_right or player.run_down_right) {
		vector_x = config.player_speed * time.dt / 1000;
	}
	else if (player.run_left or player.run_up_left or player.run_down_left) {
		vector_x = -config.player_speed * time.dt / 1000;
	}
	PlayerMovePosition(player, vector_x, 0);
}
double PlayerCalculateDS(Player player, Background background)
{
	if (player.position.x > win_width / 2 and background.area_background.w > win_width) {
		return player.position.x - win_width / 2;
	}
	return 0;
}
void PlayerAdjustPosition(Player& player, Border border, double ds)
{
	if (ds > 0) {
		PlayerSetPosition(player, win_width / 2, player.position.y);
	}
	if (player.position.x < border.border_left) {
		int way_beyond_borders = border.border_left - player.position.x;
		PlayerMovePosition(player, way_beyond_borders, 0);
	}
	else if (player.position.x > border.border_right) {
		int way_beyond_borders = player.position.x - border.border_right;
		PlayerMovePosition(player, -way_beyond_borders, 0);
	}
}
void PlayerUpdatePositionY(Player& player, Border border, Time time)
{
	double vector_y = 0;
	if (player.is_jumping and !player.is_falling) { // Если прыгает
		vector_y = -config.gravity * time.dt / 1000;
		PlayerMovePosition(player, 0, vector_y);
		if (player.position.y <= player.jump_finish_y) {
			player.is_falling = true;
		}
	}
	else { // Если падает
		player.is_falling = true;
		vector_y = config.gravity * time.dt / 1000;
		int coord_platform_y = SearchCoordsEntityOnPlatform(player.hitbox_boot, border, vector_y);
		if (coord_platform_y) {
			player.is_falling = player.is_jumping = false;
			if (coord_platform_y == player.position.y + player.position.h) {
				if (player.get_off and player.position.y + player.position.h < border.platforms[0].y) {
					player.is_falling = true;
					PlayerMovePosition(player, 0, vector_y);
				}
				else if (player.jump) {
					player.is_jumping = true; player.jump_finish_y = player.position.y - config.height_jump;
				}
			}
			else { // Если персонаж упал на платформу
				PlayerSetPosition(player, player.position.x, coord_platform_y - player.position.h);
			}
		}
		else {
			PlayerMovePosition(player, 0, vector_y);
		}
	}
}
void PlayerUpdatePosition(Player& player, Background background, Border border, Time time, double& ds)
{
	PlayerUpdatePositionX(player, background, border, time);
	ds = PlayerCalculateDS(player, background);
	PlayerAdjustPosition(player, border, ds);
	PlayerUpdatePositionY(player, border, time);
	PlayerDefHitbox(player, background);
}
void PlayerRenderMedal(Player& player)
{
	SDL_Rect buffer_medal_area = texture.medal_area;
	for (int i = 0; i < player.hp; i++) {
		buffer_medal_area.x += texture.medal_area.w + 20; buffer_medal_area.y = 20;
		SDL_RenderCopy(ren, texture.medal, NULL, &buffer_medal_area);
	}
}
void PlayerRemovingHealth(Player& player, Background& background)
{
	player.hp--;
	if (player.hp < 0) {
		game_state = GAME_OVER;
		return;
	}
	player.invincibil = true;
	player.timer_invincibil = config.player_time_invincibil * 1000;
	PlayerSetPosition(player, 0, 0);
	PlayerDefHitbox(player, background);
}
void PlayerInvincible(Player& player, Time& time)
{
	if (player.invincibil) {
		if (player.timer_invincibil <= 0) {
			player.invincibil = false;
		}
		else {
			player.timer_invincibil -= time.dt;
		}
	}
}
// Пули игрового персонажа
PlayerBullet* PlayerBulletCreate(Player player, Texture& texture, Background background)
{
	PlayerBullet* player_bullet = (PlayerBullet*)malloc(sizeof(PlayerBullet));
	if (!player_bullet) {
		printf_s("Ошибка: не удалось выделить память под пульку\n");
		return nullptr;
	}

	player_bullet->area = player_bullet->position = texture.player_bullet_area;
	if (player.jump_right) {
		player_bullet->position.x = player.position.x + 79;
		player_bullet->position.y = player.position.y + 148;
	}
	else if (player.jump_left) {
		player_bullet->position.x = player.position.x - texture.player_bullet_area.w;
		player_bullet->position.y = player.position.y + 148;
	}
	else if (player.run_up_left) {
		player_bullet->position.x = player.position.x - texture.player_bullet_area.w;
		player_bullet->position.y = player.position.y + 47;
	}
	else if (player.run_up_right) {
		player_bullet->position.x = player.position.x + 72;
		player_bullet->position.y = player.position.y + 39;
	}
	else if (player.run_down_left) {
		player_bullet->position.x = player.position.x - texture.player_bullet_area.w;
		player_bullet->position.y = player.position.y + 123;
	}
	else if (player.run_down_right) {
		player_bullet->position.x = player.position.x + 84;
		player_bullet->position.y = player.position.y + 115;
	}
	else if (player.stay_up_left) {
		player_bullet->position.x = player.position.x + 9;
		player_bullet->position.y = player.position.y - texture.player_bullet_area.h;
	}
	else if (player.stay_up_right) {
		player_bullet->position.x = player.position.x + 41;
		player_bullet->position.y = player.position.y - texture.player_bullet_area.h;
	}
	else if (player.lie_left) {
		player_bullet->position.x = player.position.x - texture.player_bullet_area.w;
		player_bullet->position.y = player.position.y + 139;
	}
	else if (player.lie_right) {
		player_bullet->position.x = player.position.x + 136;
		player_bullet->position.y = player.position.y + 139;
	}
	else if (player.stay_right) {
		player_bullet->position.x = player.position.x + 96;
		player_bullet->position.y = player.position.y + 85;
	}
	else {
		player_bullet->position.x = player.position.x - texture.player_bullet_area.w;
		player_bullet->position.y = player.position.y + 89;
	}
	player_bullet->global_pos = player_bullet->position;
	player_bullet->global_pos.x += background.camera.x;

	player_bullet->dir_x = player_bullet->dir_y = 0;
	if (player.stay_right and !player.stay_up_right) player_bullet->dir_x = 1;
	else if (!player.stay_right and !player.stay_up_left) player_bullet->dir_x = -1;
	if (player.stay_up_right or player.stay_up_left or player.run_up_left or player.run_up_right) player_bullet->dir_y = -1;
	else if (player.run_down_left or player.run_down_right) player_bullet->dir_y = 1;

	return player_bullet;
}
void PlayerBulletRender(PlayerBullet& player_bullet, Texture& texture)
{
	SDL_RenderCopy(ren, texture.player_bullet, &player_bullet.area, &player_bullet.position);
}
void PlayerBulletHandleShooting(List& player_bullet_list, Player player, Texture texture, Background background)
{
	if (player.shoot) {
		PlayerBullet* bullet = PlayerBulletCreate(player, texture, background);
		if (bullet) {
			ListAdd(player_bullet_list, bullet);
		}
	}
}
void PlayerBulletAllRender(List& player_bullet_list, Texture texture)
{
	for (Elem* cur = player_bullet_list.head; cur != nullptr; cur = cur->next) {
		PlayerBullet* bullet = (PlayerBullet*)cur->data;
		PlayerBulletRender(*bullet, texture);
	}
}
void PlayerBulletDefHitbox(PlayerBullet& player_bullet, Background background)
{
	player_bullet.global_pos = player_bullet.position;
	player_bullet.global_pos.x += background.camera.x;
}
void PlayerBulletUpdatePosition(PlayerBullet& player_bullet, Time time, Background background, double ds)
{
	double vector_x, vector_y;
	if (player_bullet.dir_x) vector_x = player_bullet.dir_x * config.player_bullet_speed * time.dt / 1000;
	else vector_x = 0;
	if (player_bullet.dir_y) vector_y = player_bullet.dir_y * config.player_bullet_speed * time.dt / 1000;
	else vector_y = 0;

	if (ds and player_bullet.dir_x > 0) vector_x -= ds;
	else if (ds and player_bullet.dir_x < 0) vector_x -= ds;

	player_bullet.position.x += vector_x;
	player_bullet.position.y += vector_y;
	PlayerBulletDefHitbox(player_bullet, background);
}
void PlayerBulletAllUpdatePosition(List& player_bullet_list, Time time, Background background, double ds)
{
	for (Elem* cur = player_bullet_list.head; cur != nullptr;) {
		PlayerBullet* bullet = (PlayerBullet*)cur->data;
		PlayerBulletUpdatePosition(*bullet, time, background, ds);
		if (bullet->position.x > win_width or bullet->position.x < 0 or
			bullet->position.y > win_height or bullet->position.y < 0) {
			Elem* next = cur->next;
			ListDel(player_bullet_list, cur);
			cur = next;
		}
		else {
			cur = cur->next;
		}
	}
}