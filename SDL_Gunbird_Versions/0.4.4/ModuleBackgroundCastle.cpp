#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBackgroundCastle.h"
#include "ModuleBackgroundMine.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "SDL\include\SDL_timer.h"

ModuleBackgroundCastle::ModuleBackgroundCastle()
{
	background.x = 0;
	background.y = 0;
	background.w = 228;
	background.h = 1685;

	

}

ModuleBackgroundCastle::~ModuleBackgroundCastle()
{}

// Load assets
bool ModuleBackgroundCastle::Start()
{
	App->render->camera.y = (-1685 + SCREEN_HEIGHT) * SCREEN_SIZE;
	App->render->camera.x = 0 * SCREEN_SIZE;

	App->player->position.x = App->render->camera.x + 50;
	App->player->position.y = abs(App->render->camera.y / SCREEN_SIZE) + 270;
	
	if (App->player->activatePlayer2 == true) {
	}
	LOG("Loading background castle assets");
	bool ret = true;
	graphics = App->textures->Load("assets/backgrounds/Background castle.png");

	App->player->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->ui->Enable();

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
		music = Mix_LoadMUS("assets/audio/music/gunbird-002_Title_Castle.ogg");
		Mix_PlayMusic(music, -1);
	}

	return ret;
}

bool ModuleBackgroundCastle::CleanUp()
{
	App->ui->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->player2->Disable();
	App->player->Disable();
	
	LOG("Unloading castle stage");
	App->textures->Unload(graphics);

	LOG("Destroying SDL audio");
	Mix_FreeMusic(music);

	return true;
}

// Update: draw background
update_status ModuleBackgroundCastle::Update()
{
	if (App->player->activatePlayer2 == true) {
		if (gate == true) {
			App->player2->position.x = App->render->camera.x + 150;
			App->player2->position.y = abs(App->render->camera.y / SCREEN_SIZE) + 270;
			gate = false;
		}
		App->player2->Enable();
	}

	//ENEMIES
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::BALLOON, BALLOON_CASTLE, 95, 1255);
	}

	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::TURRET, NO_MOVE, 162, 1241);
	}
	//BUILDING
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::BUILDING, BUILDING_CASTLE, 147, 1059);
	}
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::BUILDING2, BUILDING_CASTLE, 78, 799);
	}
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::FLAG, BUILDING_CASTLE, 177, 1049);
	}
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::FLAG, BUILDING_CASTLE, 110, 785);
	}
	//MISILE
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::MISSILE, BUILDING_CASTLE, -10, 1130);
	}
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::MISSILE, BUILDING_CASTLE, -40, 1100);
	}
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::MISSILE, BUILDING_CASTLE, -70, 1070);
	}
	if (App->render->camera.y == (-1355 * SCREEN_SIZE)) {
		App->enemies->AddEnemy(ENEMY_TYPES::MISSILE, BUILDING_CASTLE, -80, 1040);
	}
	
	//App->enemies->AddEnemy(ENEMY_TYPES::MISSILE, NO_MOVE , 12, 1241);


	// Draw everything --------------------------------------
	if (App->render->camera.y == -20 * SCREEN_SIZE) {
		App->render->camera.y = -20 * SCREEN_SIZE;
		App->player->movement = true;
		App->player2->movement = true;
	}
	else {
		App->render->camera.y += 1 * SCREEN_SIZE;
	}

	App->render->Blit(graphics, 0, 0, NULL);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->fade->IsFading() == false) {
		App->fade->FadeToBlack(this, App->background2, 1);
	}

	SDL_Delay(40);

	return UPDATE_CONTINUE;
}

