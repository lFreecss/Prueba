#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	//Shot Enemy
	shot_enemy.anim.PushBack({ 692, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 708, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 724, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 740, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 756, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 772, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 788, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 804, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 820, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 836, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 852, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 868, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 884, 230, 6, 6 });
	shot_enemy.anim.PushBack({ 692, 246, 6, 6 });
	shot_enemy.anim.PushBack({ 708, 246, 6, 6 });
	shot_enemy.anim.PushBack({ 724, 246, 6, 6 });
	shot_enemy.anim.PushBack({ 740, 246, 6, 6 });
	shot_enemy.anim.PushBack({ 756, 246, 6, 6 });
	shot_enemy.anim.speed = 0.5f;
	shot_enemy.life = 10000;
	

	//Explosion
	explosion_balloon.anim.PushBack({ 23,37,92,85 });
	explosion_balloon.anim.PushBack({ 122,33,101,93 });
	explosion_balloon.anim.PushBack({ 230,28,105,102 });
	explosion_balloon.anim.PushBack({ 336,116,99,101 });
	explosion_balloon.anim.PushBack({ 18,141,111,131 });
	explosion_balloon.anim.PushBack({ 127,140,99,104 });
	explosion_balloon.anim.PushBack({ 234,138,100,106 });
	explosion_balloon.anim.PushBack({ 349,145,98,105 });
	explosion_balloon.anim.PushBack({ 29,282,82,82 });
	explosion_balloon.anim.PushBack({ 129,264,83,107 });
	explosion_balloon.anim.PushBack({ 245,281,65,81 });
	explosion_balloon.anim.PushBack({ 357,301,71,51 });
	explosion_balloon.anim.loop = false;
	explosion_balloon.anim.speed = 0.5f;

	// Yuan Nang laser
	laser_nang_v0_0.anim.PushBack({ 511, 40, 17, 30 });
	laser_nang_v0_0.life = 1500;
	laser_nang_v0_1.anim.PushBack({ 560, 39, 17, 30 });
	laser_nang_v0_1.life = 1500;
	laser_nang_v0_2.anim.PushBack({ 604, 39, 17, 30 });
	laser_nang_v0_2.life = 1500;

	laser_nang_v1_0.anim.PushBack({ 512, 83, 17, 42 });
	laser_nang_v1_0.life = 1500;
	laser_nang_v1_1.anim.PushBack({ 561, 81, 17, 42 });
	laser_nang_v1_1.life = 1500;
	laser_nang_v1_2.anim.PushBack({ 602, 80, 17, 42 });
	laser_nang_v1_2.life = 1500;

	laser_nang_v2_0.anim.PushBack({ 510, 139, 23, 38 });
	laser_nang_v2_0.life = 1500;
	laser_nang_v2_1.anim.PushBack({ 557, 139, 23, 38 });
	laser_nang_v2_1.life = 1500;
	laser_nang_v2_2.anim.PushBack({ 600, 138, 23, 38 });
	laser_nang_v2_2.life = 1500;

	laser_nang_v3_0.anim.PushBack({ 513, 188, 45, 38 });
	laser_nang_v3_0.life = 1500;
	laser_nang_v3_1.anim.PushBack({ 584, 186, 45, 38 });
	laser_nang_v3_1.life = 1500;

	nang_sword.anim.PushBack({ 513, 233, 13, 32 });
	nang_sword.anim.PushBack({ 537, 233, 13, 32 });
	nang_sword.anim.PushBack({ 565, 233, 13, 32 });
	nang_sword.anim.PushBack({ 592, 233, 13, 32 });
	nang_sword.anim.PushBack({ 618, 233, 13, 32 });
	nang_sword.life = 1500;

	//Marion laser
	laser_marion_0.anim.PushBack({ 684, 74, 7, 29 });
	laser_marion_0.life = 1500;
	laser_marion_1.anim.PushBack({ 684, 104, 7, 29 });
	laser_marion_1.life = 1500;
	laser_marion_2.anim.PushBack({ 684, 44, 7, 29 });
	laser_marion_2.life = 1500;

	laser_marion_left_0.anim.PushBack({ 698, 44, 6, 29 });
	laser_marion_left_0.life = 1500;
	laser_marion_left_1.anim.PushBack({ 699, 75, 6, 29 });
	laser_marion_left_1.life = 1500;
	laser_marion_left_2.anim.PushBack({ 700, 104, 5, 29 });
	laser_marion_left_2.life = 1500;

	laser_marion_right_0.anim.PushBack({ 709, 44, 6, 29 });
	laser_marion_right_0.life = 1500;
	laser_marion_right_1.anim.PushBack({ 709, 75, 6, 29 });
	laser_marion_right_1.life = 1500;
	laser_marion_right_2.anim.PushBack({ 709, 104, 5, 29 });
	laser_marion_right_2.life = 1500;

	//Laser ash
	laser_ash.anim.PushBack({ 646, 39, 3, 29 });
	laser_ash.life = 1500;

	//Power Up SI NO VA PUES SE BORRA
	power_up.anim.PushBack({ 685, 147, 22, 13 });
	power_up.anim.PushBack({ 710, 147, 22, 13 });
	power_up.anim.PushBack({ 735, 147, 22, 13 });
	power_up.anim.PushBack({ 760, 147, 22, 13 });
	power_up.anim.PushBack({ 785, 147, 22, 13 });
	power_up.anim.PushBack({ 685, 163, 22, 13 });
	power_up.anim.PushBack({ 710, 163, 22, 13 });
	power_up.anim.PushBack({ 735, 163, 22, 13 });
	power_up.anim.PushBack({ 760, 163, 22, 13 });
	power_up.anim.PushBack({ 785, 163, 22, 13 });
	power_up.anim.PushBack({ 685, 180, 22, 13 });
	power_up.anim.PushBack({ 710, 180, 22, 13 });
	power_up.anim.PushBack({ 735, 180, 22, 13 });
	power_up.anim.PushBack({ 760, 180, 22, 13 });
	power_up.anim.PushBack({ 785, 180, 22, 13 });
	power_up.anim.PushBack({ 685, 199, 22, 13 });
	power_up.anim.PushBack({ 710, 199, 22, 13 });
	power_up.anim.PushBack({ 735, 199, 22, 13 });
	power_up.anim.PushBack({ 760, 199, 22, 13 });
	power_up.anim.speed = 0.8f;
	power_up.life = 150000;
}

ModuleParticles::~ModuleParticles()
{
}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/particles/particles.png");

	//Laser Yuan Nang audio
	laser_nang_v0_0.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");
	laser_nang_v0_1.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");
	laser_nang_v0_2.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");

	laser_nang_v1_0.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");
	laser_nang_v1_1.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");
	laser_nang_v1_2.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");

	laser_nang_v2_0.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");
	laser_nang_v2_1.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");

	laser_nang_v3_0.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");
	laser_nang_v3_1.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-056_Shoot_YungNang.wav");
	
	//Laser Marion audio
	laser_marion_0.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");
	laser_marion_1.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");
	laser_marion_2.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");

	laser_marion_left_0.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");
	laser_marion_left_1.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");
	laser_marion_left_2.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");

	laser_marion_right_0.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");
	laser_marion_right_1.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");
	laser_marion_right_2.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-055_Shoot_Marion.wav");

	//Laser Ash audio
		laser_ash.fx = App->audio->LoadWAV("assets/audio/sound/gunbird-059_Shoot_Ash.wav");
	
	up = true;
	left = true;
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	App->audio->UnloadWAV(laser_nang_v0_0.fx);
	App->audio->UnloadWAV(laser_nang_v0_1.fx);
	App->audio->UnloadWAV(laser_nang_v0_2.fx);
	App->audio->UnloadWAV(laser_nang_v1_0.fx);
	App->audio->UnloadWAV(laser_nang_v1_1.fx);
	App->audio->UnloadWAV(laser_nang_v1_2.fx);
	App->audio->UnloadWAV(laser_nang_v2_0.fx);
	App->audio->UnloadWAV(laser_nang_v2_1.fx);
	App->audio->UnloadWAV(laser_nang_v3_0.fx);
	App->audio->UnloadWAV(laser_nang_v3_1.fx);
	App->audio->UnloadWAV(laser_marion_0.fx);
	App->audio->UnloadWAV(laser_marion_1.fx);
	App->audio->UnloadWAV(laser_marion_2.fx);
	App->audio->UnloadWAV(laser_marion_left_0.fx);
	App->audio->UnloadWAV(laser_marion_left_1.fx);
	App->audio->UnloadWAV(laser_marion_left_2.fx);
	App->audio->UnloadWAV(laser_marion_right_0.fx);
	App->audio->UnloadWAV(laser_marion_right_1.fx);
	App->audio->UnloadWAV(laser_marion_right_2.fx);
	App->audio->UnloadWAV(laser_ash.fx);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayWAV(p->fx);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, int speed_x, int speed_y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->speed.x = speed_x;
			p->speed.y = speed_y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}