#pragma once

struct Config
{
	const int boss_hp1 = 25, boss_hp2 = 25, boss_hp3 = 25;
	const double boss_reload1 = 2, boss_reload2 = 0.5, boss_reload3 = 1,
		boss_bullet1_speed = 400, boss_bullet2_speed = 800, boss_bullet3_speed = 400;

	const int player_hp = 2, player_time_invincibil = 2;
	const double player_speed = 400, enemy_run_speed = 400, player_bullet_speed = 1000;
	const int height_jump = 300; const double shoot_timer = 0.4;

	const double gravity = 400;
	const double scrolling_speed = 800;
};
#define AMOUNT_PLATFORMS 20