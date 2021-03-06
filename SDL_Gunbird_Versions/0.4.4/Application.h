#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 16

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleBackgroundCastle;
class ModuleBackgroundSea;
class ModuleBackgroundMine;
class ModuleTitleScreen;
class ModuleScoreScreen;
class ModuleParticles;
class ModulePlayer;
class ModulePlayer2;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleUI;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleTitleScreen* titlescreen;
	ModuleBackgroundCastle* background3;
	ModuleBackgroundMine* background2;
	ModuleBackgroundSea* background;
	ModuleScoreScreen* scorescreen;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleFadeToBlack* fade;
	ModuleUI* ui;
	ModuleEnemies* enemies;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__