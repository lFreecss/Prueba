#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBackgroundMine.h"
#include "ModuleScoreScreen.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"


ModuleBackgroundMine::ModuleBackgroundMine()
{
	background2.x = 0;
	background2.y = 0;
	background2.w = 224;
	background2.h = 2036;
}

ModuleBackgroundMine::~ModuleBackgroundMine()
{}

// Load assets
bool ModuleBackgroundMine::Start()
{
	App->render->camera.y = -6985;
	LOG("Loading background mine assets");
	bool ret = true;
	graphics = App->textures->Load("assets/Background Mine.png");

	App->player->Enable();
	App->player2->Enable();

	LOG("Init SDL audio");
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_AUDIO could not initialize! SDL_Error:\n");
		LOG(SDL_GetError());
		ret = false;
	}
	else
	{
		Mix_Init(MIX_INIT_OGG);
		Mix_OpenAudio(24000, MIX_DEFAULT_FORMAT, 2, 2048);
		music = Mix_LoadMUS("assets/gunbird-005_Mine.ogg");
		Mix_PlayMusic(music, -1);
	}

	return ret;
}

bool ModuleBackgroundMine::CleanUp()
{
	App->player->Disable();
	App->player2->Disable();

	LOG("Unloading mine stage");
	App->textures->Unload(graphics);

	LOG("Destroying SDL audio");
	Mix_FreeMusic(music);

	return true;
}

// Update: draw background
update_status ModuleBackgroundMine::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, backscroll, &background2, 0.75f);
	backscroll += 2;
	if (backscroll == 1750) {
		backscroll = 250;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(this, App->scorescreen, 1);
	}


	return UPDATE_CONTINUE;
}