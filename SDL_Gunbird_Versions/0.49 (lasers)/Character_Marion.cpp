#include "Application.h"
#include "Character_Marion.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

Character_Marion::Character_Marion(int x, int y) : Character(x, y)
{
	position.x = x;
	position.y = y;

	// idle animation
	blit_idle.PushBack({ 216, 71, 20, 32 }); //1
	blit_idle.PushBack({ 0, 0, 0, 0 }); //2
	blit_idle.PushBack({ 279, 71, 20, 32 }); //3
	blit_idle.PushBack({ 0, 0, 0, 0 }); //4

	blit_idle.speed = 0.25f;

	// left animation
	blit_left.PushBack({ 214, 39, 21, 32 });
	blit_left.PushBack({ 0, 0,0,0 });
	blit_left.PushBack({ 277, 39, 21, 32 });
	blit_left.PushBack({ 0, 0,0,0 });
	blit_left.speed = 0.25f;

	// more left animation
	blit_mleft.PushBack({ 212, 7, 23, 32 });
	blit_mleft.PushBack({ 0, 0,0,0 });
	blit_mleft.PushBack({ 276, 7, 23, 32 });
	blit_mleft.PushBack({ 0, 0,0,0 });
	blit_mleft.speed = 0.25f;

	//right animation
	blit_right.PushBack({ 217, 135, 21, 32 });
	blit_right.PushBack({ 0, 0,0,0 });
	blit_right.PushBack({ 280, 135, 21, 32 });
	blit_right.PushBack({ 0, 0,0,0 });
	blit_right.speed = 0.25f;

	//more right animation
	blit_mright.PushBack({ 217, 103, 23, 32 });
	blit_mright.PushBack({ 0, 0,0,0 });
	blit_mright.PushBack({ 280, 103, 23, 32 });
	blit_mright.PushBack({ 0, 0,0,0 });
	blit_mright.speed = 0.25f;

	//death sprite
	blit_death.PushBack({ 215, 180, 32, 28 });

	collider = App->collision->AddCollider({ position.x, position.y, 20, 32 }, COLLIDER_PLAYER, MARION, (Module*)App->player);

	animation = &blit_idle;

}

void Character_Marion::Move()
{
	animation = &blit_idle;

	int speed = SPEED_CHARACTER;

	if ((position.y < (abs(App->render->camera.y) / SCREEN_SIZE)))
		position.y = (abs(App->render->camera.y) / SCREEN_SIZE);

	else {
		if (movement == false) {
			scroll += 0.5;
			if (scroll == 1.5) {
				position.y -= 1;
				scroll = 0;
			}
		}
	}

	if (this->desactivateInput == false) {

		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT))
		{
			animation = &blit_right;
			position.x += speed;
			if (position.x > (SCREEN_WIDTH - 20)) {
				position.x = (SCREEN_WIDTH - 20);
			}
		}
		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT))
		{
			animation = &blit_left;
			position.x -= speed;
			if (position.x < 0) {
				position.x = 0;
			}
		}
		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT))
		{
			animation = &blit_idle;
			position.y -= speed;
			if (position.y < (abs(App->render->camera.y) / SCREEN_SIZE)) {
				position.y = (abs(App->render->camera.y) / SCREEN_SIZE);
			}
		}
		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT))
		{
			animation = &blit_idle;
			position.y += speed;
			if (position.y > ((abs(App->render->camera.y) + (SCREEN_HEIGHT*SCREEN_SIZE))) / SCREEN_SIZE - 32) {
				position.y = (abs(App->render->camera.y) + (SCREEN_HEIGHT*SCREEN_SIZE)) / SCREEN_SIZE - 32;
			}
		}

		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT))
			animation = &blit_right;

		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT))
			animation = &blit_left;

		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT))
			animation = &blit_right;

		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT))
			animation = &blit_left;

		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT))
			animation = &blit_idle;
	}
}

void Character_Marion::Laser() {
	if (this->desactivateInput == false) {
		if ((App->player->characters[0]->type == MARION && App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN || (0 < time)) ||
			(App->player->characters[1] != nullptr && App->player->characters[1]->type == MARION && App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN || (0 < time))) {

			if (level == 0) {
				if (time == 0)
				{
					App->particles->AddParticle(App->particles->laser_marion_0, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					shot = false;
				}
				if (time == 5)
				{
					App->particles->AddParticle(App->particles->laser_marion_1, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 10)
				{
					App->particles->AddParticle(App->particles->laser_marion_2, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 15)
				{
					App->particles->AddParticle(App->particles->laser_marion_0, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					time = 0;
					shot = true;
				}
				if (shot == false)
					time++;
			}

			if (level == 1) {
				if (time == 0)
				{
					App->particles->AddParticle(App->particles->laser_marion_2, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_2, position.x + 10, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					shot = false;
				}
				if (time == 5)
				{
					App->particles->AddParticle(App->particles->laser_marion_0, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_0, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 10)
				{
					App->particles->AddParticle(App->particles->laser_marion_1, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_1, position.x + 9, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 15)
				{
					App->particles->AddParticle(App->particles->laser_marion_2, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_2, position.x + 10, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					time = 0;
					shot = true;
				}
				if (shot == false)
					time++;
			}

			if (level == 2) {
				if (time == 0)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_0, position.x + 3, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_0, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_0, position.x + 11, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					shot = false;
				}
				if (time == 5)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_1, position.x + 3, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_1, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_1, position.x + 11, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 10)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_2, position.x + 3, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_2, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_2, position.x + 11, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 15)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_0, position.x + 3, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_0, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_0, position.x + 11, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					time = 0;
					shot = true;
				}
				if (shot == false)
					time++;
			}
			//NEXT TO DO
			if (level == 3) {
				if (time == 0)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_0, position.x - 7, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_left_0, position.x - 1, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_0, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_0, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_0, position.x + 8, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_0, position.x + 14, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					shot = false;
				}
				if (time == 5)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_1, position.x - 10, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_left_1, position.x - 1, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_1, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_1, position.x + 9, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_1, position.x + 10, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_1, position.x + 18, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 10)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_2, position.x - 10, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_left_2, position.x - 1, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_2, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_2, position.x + 10, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_1, position.x + 11, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_1, position.x + 19, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
				}
				if (time == 15)
				{
					App->particles->AddParticle(App->particles->laser_marion_left_0, position.x - 7, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_left_0, position.x - 1, position.y, -2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_0, position.x, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_0, position.x + 7, position.y, 0, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_0, position.x + 8, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser_marion_right_0, position.x + 14, position.y, 2, SPEED_LASER_PLAYER, MARION, COLLIDER_PLAYER_SHOT);
					App->audio->PlayWAV(App->particles->laser_marion_fx);
					time = 0;
					shot = true;
				}
				if (shot == false)
					time++;
			}
		}
	}
}

void Character_Marion::Dead() {
	if (this->playerDead == true) {
		animation = &blit_death;
		this->desactivateInput = true;

		if (this->spawnPlayer == false && position.y <= 50 + ((abs(App->render->camera.y) + (SCREEN_HEIGHT*SCREEN_SIZE))) / SCREEN_SIZE)
			position.y += 4;

		else {
			this->spawnPlayer = true;
			if (position.y >= ((abs(App->render->camera.y) + (SCREEN_HEIGHT*SCREEN_SIZE))) / SCREEN_SIZE) {
				if (App->player->characters[0]->type == MARION)
					position.x = App->render->camera.x + 50;
				if (App->player->characters[1] != nullptr) {
					if (App->player->characters[1]->type == MARION)
						position.x = App->render->camera.x + 150;
				}
			}

			animation = &blit_idle;

			if (position.y >= ((abs(App->render->camera.y) + (SCREEN_HEIGHT*SCREEN_SIZE))) / SCREEN_SIZE - 80)
				position.y -= 1;

			else {
				if (this->scroll == 0) {
					position.y = abs(App->render->camera.y / SCREEN_SIZE) + 240;
					this->spawnPlayer = false;
					this->playerDead = false;
					this->desactivateInput = false;
				}
			}
		}
	}
}

void Character_Marion::OnCollision(Collider* collider) {

}
