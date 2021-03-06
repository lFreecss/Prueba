#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 200
#define SPEED_LASER_PLAYER -10
#define SPEED_SWORD_YUAN_NANG -5

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, int speed_x, int speed_y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	//uint last_particle = 0;

	bool up;
	bool left;

public:
	Particle laser_nang_v0_0;
	Particle laser_nang_v0_1;
	Particle laser_nang_v0_2;

	Particle laser_nang_v1_0;
	Particle laser_nang_v1_1;
	Particle laser_nang_v1_2;

	Particle laser_nang_v2_0;
	Particle laser_nang_v2_1;
	Particle laser_nang_v2_2;

	Particle laser_nang_v3_0;
	Particle laser_nang_v3_1;

	Particle nang_sword;	

	Particle laser_marion_0;
	Particle laser_marion_1;
	Particle laser_marion_2;

	Particle laser_marion_left_0;
	Particle laser_marion_left_1;
	Particle laser_marion_left_2;

	Particle laser_marion_right_0;
	Particle laser_marion_right_1;
	Particle laser_marion_right_2;

	Particle laser_ash;

	Particle shot_enemy;

	Particle explosion_balloon;
	Particle power_up;

};

#endif // __MODULEPARTICLES_H__