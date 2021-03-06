#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleParticles.h"

ModulePlayer::ModulePlayer()
{
	position.x = 50;
	position.y = 2610;

	// idle animation
	idle.PushBack({ 9, 6, 27, 48 }); //1
	idle.PushBack({ 107, 7, 27, 48 }); //2
	idle.PushBack({ 61, 96, 27, 48 }); //3
	idle.PushBack({ 112, 97, 27, 48 }); //4
	idle.PushBack({ 159, 5, 27, 48 }); //5
	idle.PushBack({ 53, 6, 27, 48 }); //6
	idle.PushBack({ 14, 95, 27, 48 }); //7
	idle.PushBack({ 163, 99, 27, 48 }); //8
	idle.speed = 0.08f;

	// left animation
	left.PushBack({ 18, 417, 24, 47 });
	left.PushBack({ 73, 418, 24, 47 });
	left.PushBack({ 122, 419, 24, 47 });
	left.PushBack({ 170, 420, 24, 46 });

	left.PushBack({ 18, 350, 26, 48 });
	left.PushBack({ 73, 351, 27, 48 });
	left.PushBack({ 120, 351, 27, 48 });
	left.PushBack({ 170, 351, 27, 48 }); 
	left.loop = false;
	left.speed = 0.08f;

	// right animation
	right.PushBack({ 70, 171, 26, 48 });
	right.PushBack({ 119, 171, 27, 48 });
	right.PushBack({ 168, 172, 27, 48 });
	right.PushBack({ 15, 174, 27, 48 });
	right.loop = false;
	right.PushBack({ 20, 246, 27, 47 });
	right.PushBack({ 79, 248, 27, 47 });
	right.PushBack({ 121, 247, 27, 46 });
	right.PushBack({ 171, 248, 27, 46 });
	right.speed = 0.08f;

	shoot.PushBack({ 34,1516,80,130 });
	shoot.PushBack({ 129,1516,90,130 });
	shoot.PushBack({ 245,1531,90,130 });
	shoot.PushBack({ 351,1531,400,130 });
	shoot.speed = 0.005f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/Yuan_Nang.png");
	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player 1");
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 3;

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &right;
		position.x += speed;
		if (position.x > (SCREEN_WIDTH - 32)) {
			position.x = (SCREEN_WIDTH - 32);
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &left;
		position.x -= speed;
		if (position.x < 0) {
			position.x = 0;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		position.y -= speed;
		if (position.y < 2370) {
			position.y = 2370;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		position.y += speed;
		if (position.y >(SCREEN_HEIGHT + 2335)) {
			position.y = (SCREEN_HEIGHT + 2335);
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 9, position.y - 30);

	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		current_animation = &idle;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}