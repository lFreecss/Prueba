#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"

ModulePlayer2::ModulePlayer2()
{
	position.x = 150;
	position.y = 2610;

	// idle animation
	idle.PushBack({ 5, 64, 21, 32 }); //1
	idle.PushBack({ 34, 64, 20, 32 }); //2
	idle.PushBack({ 68, 64, 18, 32 }); //3
	idle.PushBack({ 100, 64, 20, 32 }); //4
	
	idle.speed = 0.08f;

	// left animation
	left.PushBack({ 5, 96, 23, 32 });
	left.PushBack({ 37, 96, 23, 32 });
	left.PushBack({ 68, 96, 23, 32 });
	left.PushBack({ 101, 96, 23, 32 });
	left.speed = 0.08f;

	// right animation
	right.PushBack({ 0, 0, 23, 32 });
	right.PushBack({ 31, 0, 23, 32 });
	right.PushBack({ 64, 0, 23, 32 });
	right.PushBack({ 96, 0, 23, 32 });
	right.speed = 0.08f;

	shoot.PushBack({ 34,1516,80,130 });
	shoot.PushBack({ 129,1516,90,130 });
	shoot.PushBack({ 245,1531,90,130 });
	shoot.PushBack({ 351,1531,400,130 });
	shoot.speed = 0.005f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/Marion.png");
	return ret;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player 2");
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	Animation* current_animation = &idle;

	int speed = 3;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &left;
		position.x += speed;
		if (position.x > (SCREEN_WIDTH - 32)) {
			position.x = (SCREEN_WIDTH - 32);
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &right;
		position.x -= speed;
		if (position.x < 0) {
			position.x = 0;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		position.y -= speed;
		if (position.y < 2370) {
			position.y = 2370;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		position.y += speed;
		if (position.y >(SCREEN_HEIGHT + 2335)) {
			position.y = (SCREEN_HEIGHT + 2335);
		}
	}


	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		current_animation = &idle;
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}