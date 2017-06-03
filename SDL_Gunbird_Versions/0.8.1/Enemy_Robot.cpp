#include "Application.h"
#include "Enemy_Robot.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleBackgroundCastle.h"

#define PI 3.14159265 
#define REACH_ANGLE 15f
#define CONVERT_ANGLE (180.0 / PI)


Enemy_Robot::Enemy_Robot(int x, int y) : Enemy(x, y)
{
	robot.PushBack({ 685,123,85,74 });
	robot.PushBack({ 583,23,85,74 });
	robot.PushBack({ 689,21,85,74 });
	robot.PushBack({ 794,23,76,74 });
	robot.PushBack({ 895,24,76,74 });
	robot.PushBack({ 795,124,76,74 });

	front.PushBack({ 588,233,16,18 }); //0

	r1.PushBack({ 608,233,18,18 });
	r2.PushBack({ 628,233,18,18 });
	r3.PushBack({ 650,234,18,18 });

	r4.PushBack({ 671,234,18,18 }); //90

	r5.PushBack({ 694,234,18,18 });
	r6.PushBack({ 716,234,18,18 });
	r7.PushBack({ 740,233,18,18 });
	
	back.PushBack({ 588,233,18,18 }); //180

	l1.PushBack({ 784,233,18,18 });
	l2.PushBack({ 806,233,18,18 });
	l3.PushBack({ 827,233,18,18 });

	l4.PushBack({ 851,233,18,18 }); //270

	l5.PushBack({ 875,232,18,18 });
	l6.PushBack({ 898,232,18,18 });
	l7.PushBack({ 923,232,18,18 });

	pos[0].x = 12;
	pos[0].y = 15;
	pos[1].x = 48;
	pos[1].y = 15;

	
	

	robot.speed = 0.25f;

	lastTime = 0;

	hitPoints = 3;

	score = 500;

	animation = &robot;

	collider = App->collision->AddCollider({ 0, 0, 76, 74 }, COLLIDER_TYPE::COLLIDER_ENEMY, NULL, (Module*)App->enemies);

	original_pos.y = y;
	original_pos.x = x;
}

void Enemy_Robot::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Robot::Cannon()
{

}

void Enemy_Robot::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT) {
		hit_animation = true;
		hitPoints -= 1;
	}
}

uint Enemy_Robot::getHitPoints() {
	return hitPoints;
}