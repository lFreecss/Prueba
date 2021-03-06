#include "Application.h"
#include "Enemy_Building.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_timer.h"

Enemy_Building::Enemy_Building(int x, int y) : Enemy(x, y)
{
	building.PushBack({ 732,444,64,86 });

	
	lastTime = 0;

	hitPoints = 25;

	score = 3000;

	animation = &building;

	collider = App->collision->AddCollider({ 0, 0, 64, 86 }, COLLIDER_TYPE::COLLIDER_ENEMY, NULL, (Module*)App->enemies);

	original_pos.y = y;
	original_pos.x = x;
}

void Enemy_Building::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT)
	hitPoints -= 1;
}

uint Enemy_Building::getHitPoints() {
	return hitPoints;
}